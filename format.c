/*
 * format.c - routines for (s)printf formatting.
 */

/* 
 * Copyright (C) 2012 the Free Software Foundation, Inc.
 * 
 * This file is part of GAWK, the GNU implementation of the
 * AWK Programming Language.
 * 
 * GAWK is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 * 
 * GAWK is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "awk.h"

#include "format.h"

char lchbuf[] = "0123456789abcdef";
char Uchbuf[] = "0123456789ABCDEF";
char space_string[] = " ";
char zero_string[] = "0";

/* mbc_byte_count --- return number of bytes for corresponding numchars multibyte characters */

static size_t
mbc_byte_count(const char *ptr, size_t numchars)
{
#if MBS_SUPPORT
	mbstate_t cur_state;
	size_t sum = 0;
	int mb_len;

	memset(& cur_state, 0, sizeof(cur_state));

	assert(gawk_mb_cur_max > 1);
	mb_len = mbrlen(ptr, numchars * gawk_mb_cur_max, &cur_state);
	if (mb_len <= 0)
		return numchars;	/* no valid m.b. char */

	for (; numchars > 0; numchars--) {
		mb_len = mbrlen(ptr, numchars * gawk_mb_cur_max, &cur_state);
		if (mb_len <= 0)
			break;
		sum += mb_len;
		ptr += mb_len;
	}

	return sum;
#else
	return numchars;
#endif
}

/* mbc_char_count --- return number of m.b. chars in string, up to numbytes bytes */

static size_t
mbc_char_count(const char *ptr, size_t numbytes)
{
#if MBS_SUPPORT
	mbstate_t cur_state;
	size_t sum = 0;
	int mb_len;

	if (gawk_mb_cur_max == 1)
		return numbytes;

	memset(& cur_state, 0, sizeof(cur_state));

	mb_len = mbrlen(ptr, numbytes * gawk_mb_cur_max, &cur_state);
	if (mb_len <= 0)
		return numbytes;	/* no valid m.b. char */

	for (; numbytes > 0; numbytes--) {
		mb_len = mbrlen(ptr, numbytes * gawk_mb_cur_max, &cur_state);
		if (mb_len <= 0)
			break;
		sum++;
		ptr += mb_len;
	}

	return sum;
#else
	return numbytes;
#endif
}


#define OUTBUF_INIT_SIZE	510

/* chksize__internal --- make room for something LEN big in the output buffer */

static void
chksize__internal(struct print_fmt_buf *outb, size_t len)
{
	size_t delta, newsize;

	assert(outb->buf != NULL);
	delta = outb->dataend - outb->buf;
	newsize = delta + len + OUTBUF_INIT_SIZE;
	erealloc(outb->buf, char *, newsize + 2, "chksize__internal");
	outb->dataend = outb->buf + delta;
	outb->bufsize = newsize;
	outb->room_left = len + OUTBUF_INIT_SIZE;
}

/* cpbuf_chksize__internal --- enlarge the temporary buffer */

static void
cpbuf_chksize__internal(struct print_fmt_buf *outb)
{
	char *cp, *prev = outb->cpbuf.buf;
	size_t oldsize = outb->cpbuf.bufsize;
	size_t newsize;

	newsize = outb->cpbuf.bufsize = 2 * oldsize;
	emalloc(outb->cpbuf.buf, char *, newsize + 2, "cpbuf_chksize__internal");
	memcpy((cp = outb->cpbuf.buf + oldsize), prev,  oldsize);
	efree(prev);
	outb->cpbuf.bufend = outb->cpbuf.buf + newsize;
	outb->cpbuf.databegin = cp;
}

static struct print_fmt_buf static_outb;

/* get_fmt_buf --- buffer(s) to manage (s)printf formatting */
 
struct print_fmt_buf *
get_fmt_buf()
{
	struct print_fmt_buf *outb;

	if (static_outb.buf == NULL)
		outb = & static_outb;
	else {
		emalloc(outb, struct print_fmt_buf *, sizeof (struct print_fmt_buf), "get_fmt_buf");
		outb->is_malloced = true;
	}

	emalloc(outb->buf, char *, OUTBUF_INIT_SIZE + 2, "get_fmt_buf");
	outb->bufsize = OUTBUF_INIT_SIZE;
	outb->room_left = outb->bufsize;
	outb->dataend = outb->buf;
	outb->chksize = chksize__internal;

	emalloc(outb->cpbuf.buf, char *, 64, "get_fmt_buf");
	outb->cpbuf.bufsize = 62;
	outb->cpbuf.databegin = outb->cpbuf.bufend = outb->cpbuf.buf + outb->cpbuf.bufsize;
	outb->cpbuf_chksize = cpbuf_chksize__internal;
	return outb;
}

/* fmt_parse --- parse a single format code */  

struct format_spec *
fmt_parse(NODE *n, const char *fmt_string, size_t fmt_len)
{
	struct format_spec *spec = NULL;

	spec = (struct format_spec *) format_tree(fmt_string, fmt_len, NULL, LONG_MIN);
	if (spec != NULL && n == CONVFMT_node
		&& (spec->fmtchar == 's' || spec->fmtchar == 'c')
	) {
		efree(spec);
		spec = NULL;
	}
 	return spec;
}


/* format_nondecimal --- output a nondecimal number according to a format */

void
format_nondecimal(uintmax_t val, struct format_spec *spec, struct print_fmt_buf *outb)
{
	uintmax_t uval = val;
	int ii, jj;
	const char *chbuf = spec->chbuf;

#	define CP		cpbuf_start(outb)
#	define CEND		cpbuf_end(outb)

	/*
	 * When to fill with zeroes is of course not simple.
	 * First: No zero fill if left-justifying.
	 * Next: There seem to be two cases:
	 * 	A '0' without a precision, e.g. %06d
	 * 	A precision with no field width, e.g. %.10d
	 * Any other case, we don't want to fill with zeroes.
	 */
	if (! spec->lj
		    && ((spec->zero_flag && ! spec->have_prec)
			|| (spec->fw == 0 && spec->have_prec))
	)
		spec->fill = zero_string;

	ii = jj = 0;
	do {
		tmpbuf_prepend(outb, chbuf[uval % spec->base]);
		uval /= spec->base;
#if defined(HAVE_LOCALE_H)
		if (spec->base == 10 && spec->quote_flag && loc.grouping[ii] && ++jj == loc.grouping[ii]) {
			if (uval)	/* only add if more digits coming */
				tmpbuf_prepend(outb, loc.thousands_sep[0]);	/* XXX --- assumption it's one char */
			if (loc.grouping[ii+1] == 0)                                          
				jj = 0;     /* keep using current val in loc.grouping[ii] */
			else if (loc.grouping[ii+1] == CHAR_MAX)                        
				spec->quote_flag= false;
			else {                 
				ii++;
				jj = 0;
			}
		}
#endif
	} while (uval > 0);

	/* add more output digits to match the precision */
	if (spec->have_prec) {
		while (CEND - CP < spec->prec)
			tmpbuf_prepend(outb, '0');
	}

	if (spec->alt && val != 0) {
		if (spec->base == 16) {
			tmpbuf_prepend(outb, spec->fmtchar);
			tmpbuf_prepend(outb, '0');
			if (spec->fill != space_string) {
				bchunk(outb, CP, 2);
				CP += 2;
				spec->fw -= 2;
			}
		} else if (spec->base == 8)
			tmpbuf_prepend(outb, '0');
	}

	spec->base = 0;
	if (spec->prec > spec->fw)
		spec->fw = spec->prec;
	spec->prec = CEND - CP;
	pr_num_tail(CP, spec->prec, spec, outb);

#undef CP
#undef CEND
}


/*
 * format_tree() formats arguments of sprintf,
 * and accordingly to a fmt_string providing a format like in
 * printf family from C library.  Returns a string node which value
 * is a formatted string.  Called by  sprintf function.
 *
 * It is one of the uglier parts of gawk.  Thanks to Michal Jaegermann
 * for taming this beast and making it compatible with ANSI C.
 */


NODE *
format_tree(
	const char *fmt_string,
	size_t n0,
	NODE **the_args,
	long num_args)
{
	size_t cur_arg = 0;
	NODE *retval = NULL;
	bool toofew = false;
	const char *s0, *s1;
	int cs1;
	NODE *arg;
	long argnum;

	bool used_dollar;
	bool big_flag, bigbig_flag, small_flag, need_format;
	long *cur = NULL;
	uintmax_t uval;
	char *cp;
	size_t copy_count, char_count;

	struct print_fmt_buf *outb;
	struct format_spec spec;

#	define CP		cpbuf_start(outb)
#	define CEND		cpbuf_end(outb)
#	define CPBUF		cpbuf(outb)

/* parse a single format specifier */
#define do_parse_fmt	(num_args == LONG_MIN)

	/*
	 * Check first for use of `count$'.
	 * If plain argument retrieval was used earlier, choke.
	 *	Otherwise, return the requested argument.
	 * If not `count$' now, but it was used earlier, choke.
	 * If this format is more than total number of args, choke.
	 * Otherwise, return the current argument.
	 */
#define parse_next_arg() { \
	if (do_parse_fmt) \
		goto out; \
	else if (argnum > 0) { \
		if (cur_arg > 1) { \
			msg(_("fatal: must use `count$' on all formats or none")); \
			goto out; \
		} \
		arg = the_args[argnum]; \
	} else if (used_dollar) { \
		msg(_("fatal: must use `count$' on all formats or none")); \
		arg = 0; /* shutup the compiler */ \
		goto out; \
	} else if (cur_arg >= num_args) { \
		arg = 0; /* shutup the compiler */ \
		toofew = true; \
		break; \
	} else { \
		arg = the_args[cur_arg]; \
		cur_arg++; \
	} \
}

	outb = get_fmt_buf();
	cur_arg = 1;

	need_format = false;
	used_dollar = false;

	s0 = s1 = fmt_string;

	while (n0-- > 0) {
		if (*s1 != '%') {
			s1++;
			continue;
		}
		need_format = true;
		bchunk(outb, s0, s1 - s0);
		s0 = s1;
		argnum = 0;

		memset(& spec, '\0', sizeof (spec));
		cur = & spec.fw;
		spec.fill = space_string;	/* always space for string */

		big_flag = bigbig_flag = small_flag = false;
		CP = CEND;
		s1++;

retry:
		if (n0-- == 0)	/* ran out early! */
			break;

		switch (cs1 = *s1++) {
		case (-1):	/* dummy case to allow for checking */
check_pos:
			if (cur != & spec.fw)
				break;		/* reject as a valid format */
			goto retry;
		case '%':
			need_format = false;
			/*
			 * 29 Oct. 2002:
			 * The C99 standard pages 274 and 279 seem to imply that
			 * since there's no arg converted, the field width doesn't
			 * apply.  The code already was that way, but this
			 * comment documents it, at least in the code.
			 */
			if (do_lint) {
				const char *msg = NULL;

				if (spec.fw && ! spec.have_prec)
					msg = _("field width is ignored for `%%' specifier");
				else if (spec.fw == 0 && spec.have_prec)
					msg = _("precision is ignored for `%%' specifier");
				else if (spec.fw && spec.have_prec)
					msg = _("field width and precision are ignored for `%%' specifier");

				if (msg != NULL)
					lintwarn("%s", msg);
			}
			bchunk_one(outb, "%");
			s0 = s1;
			break;

		case '0':
			/*
			 * Only turn on zero_flag if we haven't seen
			 * the field width or precision yet.  Otherwise,
			 * screws up floating point formatting.
			 */
			if (cur == & spec.fw)
				spec.zero_flag = true;
			if (spec.lj)
				goto retry;
			/* FALL through */
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
			if (cur == NULL)
				break;
			if (spec.prec >= 0)
				*cur = cs1 - '0';
			/*
			 * with a negative precision *cur is already set
			 * to -1, so it will remain negative, but we have
			 * to "eat" precision digits in any case
			 */
			while (n0 > 0 && *s1 >= '0' && *s1 <= '9') {
				--n0;
				*cur = *cur * 10 + *s1++ - '0';
			}
			if (spec.prec < 0) 	/* negative precision is discarded */
				spec.have_prec = false;
			if (cur == & spec.prec)
				cur = NULL;
			if (n0 == 0)	/* badly formatted control string */
				continue;
			goto retry;
		case '$':
			if (do_traditional) {
				msg(_("fatal: `$' is not permitted in awk formats"));
				goto out;
			}
			if (do_parse_fmt)
				goto out;

			if (cur == & spec.fw) {
				argnum = spec.fw;
				spec.fw = 0;
				used_dollar = true;
				if (argnum <= 0) {
					msg(_("fatal: arg count with `$' must be > 0"));
					goto out;
				}
				if (argnum >= num_args) {
					msg(_("fatal: arg count %ld greater than total number of supplied arguments"), argnum);
					goto out;
				}
			} else {
				msg(_("fatal: `$' not permitted after period in format"));
				goto out;
			}

			goto retry;
		case '*':
			if (cur == NULL)
				break;
			if (! do_traditional && isdigit((unsigned char) *s1)) {
				int val = 0;

				for (; n0 > 0 && *s1 && isdigit((unsigned char) *s1); s1++, n0--) {
					val *= 10;
					val += *s1 - '0';
				}
				if (*s1 != '$') {
					msg(_("fatal: no `$' supplied for positional field width or precision"));
					goto out;
				} else {
					s1++;
					n0--;
				}
				if (val >= num_args) {
					toofew = true;
					break;
				}
				arg = the_args[val];
			} else {
				parse_next_arg();
			}

			(void) force_number(arg);
			*cur = get_number_si(arg);
			if (*cur < 0 && cur == & spec.fw) {
				*cur = -*cur;
				spec.lj++;
			}
			if (cur == & spec.prec) {
				if (*cur >= 0)
					spec.have_prec = true;
				else
					spec.have_prec = false;
				cur = NULL;
			}
			goto retry;
		case ' ':		/* print ' ' or '-' */
					/* 'space' flag is ignored */
					/* if '+' already present  */
			if (spec.signchar != false) 
				goto check_pos;
			/* FALL THROUGH */
		case '+':		/* print '+' or '-' */
			spec.signchar = cs1;
			goto check_pos;
		case '-':
			if (spec.prec < 0)
				break;
			if (cur == & spec.prec) {
				spec.prec = -1;
				goto retry;
			}
			spec.lj++; 		/* filling is ignored */
			goto check_pos;
		case '.':
			if (cur != & spec.fw)
				break;
			cur = & spec.prec;
			spec.have_prec = true;
			goto retry;
		case '#':
			spec.alt = true;
			goto check_pos;
		case '\'':
#if defined(HAVE_LOCALE_H)       
			/* allow quote_flag if there is a thousands separator. */
			if (loc.thousands_sep[0] != '\0')
				spec.quote_flag= true;
			goto check_pos;
#else
			goto retry;  
#endif
		case 'l':
			if (big_flag)
				break;
			else {
				static bool warned = false;
				
				if (do_lint && ! warned) {
					lintwarn(_("`l' is meaningless in awk formats; ignored"));
					warned = true;
				}
				if (do_posix) {
					msg(_("fatal: `l' is not permitted in POSIX awk formats"));
					goto out;
				}
			}
			big_flag = true;
			goto retry;
		case 'L':
			if (bigbig_flag)
				break;
			else {
				static bool warned = false;
				
				if (do_lint && ! warned) {
					lintwarn(_("`L' is meaningless in awk formats; ignored"));
					warned = true;
				}
				if (do_posix) {
					msg(_("fatal: `L' is not permitted in POSIX awk formats"));
					goto out;
				}
			}
			bigbig_flag = true;
			goto retry;
		case 'h':
			if (small_flag)
				break;
			else {
				static bool warned = false;
				
				if (do_lint && ! warned) {
					lintwarn(_("`h' is meaningless in awk formats; ignored"));
					warned = true;
				}
				if (do_posix) {
					msg(_("fatal: `h' is not permitted in POSIX awk formats"));
					goto out;
				}
			}
			small_flag = true;
			goto retry;
		case 'c':
			need_format = false;
			spec.fmtchar = cs1;
			parse_next_arg();
			/* user input that looks numeric is numeric */
			if ((arg->flags & (MAYBE_NUM|NUMBER)) == MAYBE_NUM)
				(void) force_number(arg);
			if ((arg->flags & NUMBER) != 0) {
				uval = get_number_uj(arg);
#if MBS_SUPPORT
				if (gawk_mb_cur_max > 1) {
					char buf[100];
					wchar_t wc;
					mbstate_t mbs;
					size_t count;

					memset(& mbs, 0, sizeof(mbs));
					wc = uval;

					count = wcrtomb(buf, wc, & mbs);
					if (count == 0
					    || count == (size_t)-1
					    || count == (size_t)-2)
						goto out0;

					memcpy(CPBUF, buf, count);
					spec.prec = count;
					cp = CPBUF;
					goto pr_tail;
				}
out0:
				;
				/* else,
					fall through */
#endif
				if (do_lint && uval > 255) {
					lintwarn("[s]printf: value %g is too big for %%c format",
							get_number_d(arg));
				}
				CPBUF[0] = uval;
				spec.prec = 1;
				cp = CPBUF;
				goto pr_tail;
			}
			/*
			 * As per POSIX, only output first character of a
			 * string value.  Thus, we ignore any provided
			 * precision, forcing it to 1.  (Didn't this
			 * used to work? 6/2003.)
			 */
			cp = arg->stptr;
			spec.prec = 1;
#if MBS_SUPPORT
			/*
			 * First character can be multiple bytes if
			 * it's a multibyte character. Grr.
			 */
			if (gawk_mb_cur_max > 1) {
				mbstate_t state;
				size_t count;

				memset(& state, 0, sizeof(state));
				count = mbrlen(cp, arg->stlen, & state);
				if (count > 0) {
					spec.prec = count;
					/* may need to increase fw so that padding happens, see pr_tail code */
					if (spec.fw > 0)
						spec.fw += count - 1;
				}
			}
#endif
			goto pr_tail;
		case 's':
			need_format = false;
			spec.fmtchar = cs1;
			parse_next_arg();
			arg = force_string(arg);
			if (spec.fw == 0 && ! spec.have_prec)
				spec.prec = arg->stlen;
			else {
				char_count = mbc_char_count(arg->stptr, arg->stlen);
				if (! spec.have_prec || spec.prec > char_count)
					spec.prec = char_count;
			}
			cp = arg->stptr;
	pr_tail:
			if (! spec.lj)
				pr_fill(& spec, outb);

			copy_count = spec.prec;
			if (spec.fw == 0 && ! spec.have_prec)
				;
			else if (gawk_mb_cur_max > 1) {
				if (cs1 == 's') {
					assert(cp == arg->stptr || cp == CPBUF);
					copy_count = mbc_byte_count(arg->stptr, spec.prec);
				}
				/* prec was set by code for %c */
				/* else
					copy_count = prec; */
			}

			bchunk(outb, cp, copy_count);
			pr_fill(& spec, outb);

			s0 = s1;
			break;

		case 'X':
			/* FALL THROUGH */
		case 'x':
			spec.base += 6;
			/* FALL THROUGH */
		case 'u':
			spec.base += 2;
			/* FALL THROUGH */
		case 'o':
			spec.base += 8;
			goto fmt1;
		case 'F':
#if ! defined(PRINTF_HAS_F_FORMAT) || PRINTF_HAS_F_FORMAT != 1
			cs1 = 'f';
			/* FALL THROUGH */
#endif
		case 'g':
		case 'G':
		case 'e':
		case 'f':
		case 'E':
		case 'd':
		case 'i':
	fmt1:
			need_format = false;
			spec.fmtchar = cs1;
			parse_next_arg();
			(void) force_number(arg);
			spec.fmtchar = cs1;
			if (format_number_printf(arg, & spec, outb) < 0)
				goto out;

			s0 = s1;
			break;
#ifdef NUMDEBUG
		case 'a':	/* hexadecimal */
		case 'b':	/* MPFR binary format */
			if (numbr_hndlr ==  & awknum_hndlr || numbr_hndlr == & awkldbl_hndlr)
				;	/* fall through -- make sure the stupid test will pass */
			else
				goto fmt1;
#endif
		default:
			if (isalpha(cs1)) {
				if (do_lint)
	lintwarn(_("ignoring unknown format specifier character `%c': no argument converted"), cs1);
				if (do_parse_fmt)
					goto out;
			}
			break;
		}
		if (toofew) {
			msg("%s\n\t`%s'\n\t%*s%s",
			      _("fatal: not enough arguments to satisfy format string"),
			      fmt_string, (int) (s1 - fmt_string - 1), "",
			      _("^ ran out for this one"));
			goto out;
		}
	}

	if (do_lint) {
		if (need_format)
			lintwarn(_("[s]printf: format specifier does not have control letter"));
		if (cur_arg < num_args)
			lintwarn(_("too many arguments supplied for format string"));
	}

	bchunk(outb, s0, s1 - s0);
	retval = bytes2node(outb, NULL);
out:
	free_fmt_buf(outb);

	if (do_parse_fmt) {
		struct format_spec *cp_spec;

		assert(retval == NULL);
		if (spec.fmtchar == (char) 0)
			return NULL;
		emalloc(cp_spec, struct format_spec *, sizeof (*cp_spec), "format_tree");
		*cp_spec = spec;
		return (NODE *) cp_spec;
	}

	if (retval == NULL)
		gawk_exit(EXIT_FATAL);	/* debugger needs this */

	return retval;

#undef CP
#undef CEND
#undef CPBUF
}
