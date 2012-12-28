/*
 * double.c - routines for C double support in gawk.
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
#include "math.h"
#include "random.h"
#include "floatmagic.h"	/* definition of isnan */

/* Can declare these, since we always use the random shipped with gawk */
extern char *initstate(unsigned long seed, char *state, long n);
extern char *setstate(char *state);
extern long random(void);
extern void srandom(unsigned long seed);

/*
 * Since we supply the version of random(), we know what
 * value to use here.
 */
#define GAWK_RANDOM_MAX 0x7fffffffL

extern NODE **fmt_list;          /* declared in eval.c */

/* exported routines */

static NODE *make_awknum(AWKNUM);
static int cmp_awknums(const NODE *, const NODE *);
static void negate_awknum(NODE *);
static NODE *str2awknum(char *, char **, int, bool);
static NODE *force_awknum(NODE *);
static NODE *format_awknum_val(const char *, int, NODE *);
static unsigned long awknum_toulong(const NODE *);
static long awknum_tolong(const NODE *);
static AWKNUM awknum_todouble(const NODE *);
static uintmax_t awknum_touintmax_t(const NODE *);
static int awknum_sgn(const NODE *);
static bool awknum_is_integer(const NODE *);
static NODE *awknum_copy(const NODE *);
static NODE *format_nodes_awknum(const char *, size_t, NODE **, long);
static bool awknum_init(bltin_t **);
static NODE *awknum_add(const NODE *, const NODE *);
static NODE *awknum_sub(const NODE *, const NODE *);
static NODE *awknum_mul(const NODE *, const NODE *);
static NODE *awknum_div(const NODE *, const NODE *);
static NODE *awknum_mod(const NODE *, const NODE *);
static NODE *awknum_pow(const NODE *, const NODE *);
static NODE *awknum_add_long(const NODE *, long);
static NODE *awknum_update_var(NODE *);
static void awknum_set_var(const NODE *);
static long awknum_increment_var(const NODE *, long);
static void awknum_init_vars(void);

static NODE *do_and(int);
static NODE *do_atan2(int);
static NODE *do_compl(int);
static NODE *do_cos(int);
static NODE *do_exp(int);
static NODE *do_int(int);
static NODE *do_log(int);
static NODE *do_lshift(int);
static NODE *do_or(int);
static NODE *do_rand(int);
static NODE *do_rshift(int);
static NODE *do_sin(int);
static NODE *do_sqrt(int);
static NODE *do_srand(int);
static NODE *do_strtonum(int);
static NODE *do_xor(int);

/* internal routines */
static double double_to_int(double d);
static int is_ieee_magic_val(const char *val);
static AWKNUM get_ieee_magic_val(const char *val);
static AWKNUM calc_exp(AWKNUM x1, AWKNUM x2);


numbr_handler_t awknum_hndlr = {
	awknum_init,
	NULL,	/* version_str */
	NULL,	/* load_procinfo */
	make_awknum,
	str2awknum,
	awknum_copy,
	NULL,	/* free_awknum --- not needed for AWKNUM */
	force_awknum,
	negate_awknum,
	cmp_awknums,
	awknum_sgn,
	awknum_is_integer,
	format_awknum_val,
	format_nodes_awknum,
	awknum_todouble,
	awknum_tolong,
	awknum_toulong,
	awknum_touintmax_t,
	awknum_add,
	awknum_sub,
	awknum_mul,
	awknum_div,
	awknum_mod,
	awknum_pow,
	awknum_add_long,
	awknum_update_var,
	awknum_set_var,
	awknum_increment_var,
	awknum_init_vars,
};

/* awknum_init --- initialization routine */

static bool
awknum_init(bltin_t **numbr_bltins)
{
	static bltin_t awknum_bltins[] = {
		{ "and",	do_and },
		{ "atan2",	do_atan2 },
		{ "compl",	do_compl },
		{ "cos",	do_cos },
		{ "exp",	do_exp },
		{ "int",	do_int },
		{ "log",	do_log },
		{ "lshift",	do_lshift },
		{ "or",		do_or },
		{ "rand",	do_rand },
		{ "rshift",	do_rshift },
		{ "sin",	do_sin },
		{ "sqrt",	do_sqrt },
		{ "srand",	do_srand },
		{ "strtonum",	do_strtonum },
		{ "xor",	do_xor },
		{ NULL, NULL },
	};

	/* set the numeric value of null string */
	Nnull_string->numbr = 0.0;
	Nnull_string->flags |= (NUMCUR|NUMBER);

	/* initialize TRUE and FALSE nodes */
	false_node = make_awknum(0.0);
	true_node = make_awknum(1.0);
	false_node->flags |= NUMINT;
	true_node->flags |= NUMINT;

	*numbr_bltins = awknum_bltins;
	return true;
}

/* awknum_toulong --- conversion to unsigned long */

static unsigned long
awknum_toulong(const NODE *n)
{
	return n->numbr;
}

/* awknum_tolong --- conversion to long */

static long
awknum_tolong(const NODE *n)
{
	return n->numbr;
}

/* awknum_todouble --- conversion to AWKNUM */

static AWKNUM
awknum_todouble(const NODE *n)
{
	return n->numbr;
}

/* awknum_touintmax_t --- conversion to uintmax_t */

static uintmax_t
awknum_touintmax_t(const NODE *n)
{
	return n->numbr;
}

/* awknum_sgn --- return 1 if number > 0, zero if number == 0, and -1 if number < 0 */

static int
awknum_sgn(const NODE *n)
{
	return (n->numbr < 0.0 ? -1 : n->numbr > 0.0);
}

/* awknum_is_integer --- check if a number is an integer */

static bool
awknum_is_integer(const NODE *n)
{
	if (isnan(n->numbr) || isinf(n->numbr))
		return false;
	return double_to_int(n->numbr) == n->numbr;
}

/* negate_awknum --- negate AWKNUM in NODE */

static void
negate_awknum(NODE *n)
{
	n->numbr = - n->numbr;
}

/* awknum_add --- add two numbers */

static NODE *
awknum_add(const NODE *t1, const NODE *t2)
{
	return make_awknum(t1->numbr + t2->numbr);
}

/* awknum_sub --- subtract two numbers */

static NODE *
awknum_sub(const NODE *t1, const NODE *t2)
{
	return make_awknum(t1->numbr - t2->numbr);
}

/* awknum_mul --- multiply two numbers */

static NODE *
awknum_mul(const NODE *t1, const NODE *t2)
{
	return make_awknum(t1->numbr * t2->numbr);
}

/* awknum_add --- quotient of two numbers */

static NODE *
awknum_div(const NODE *t1, const NODE *t2)
{
	if (t2->numbr == 0)
		fatal(_("division by zero attempted"));
	return make_awknum(t1->numbr / t2->numbr);
}

/* awknum_add_long --- add long value to a number */

static NODE *
awknum_add_long(const NODE *t1, long n)
{
	return make_awknum(t1->numbr + n);
}

/* awknum_copy --- copy a number */

static NODE *
awknum_copy(const NODE *t1)
{
	return make_awknum(t1->numbr);
}

/* awknum_update_var --- update a special variable from internal variables */

static NODE *
awknum_update_var(NODE *var)
{
	NODE *val = var->var_value;

	if (var == NR_node) {
		if (val->numbr != NR) {
			unref(val);
			val = NR_node->var_value = make_awknum(NR);
		}
		return val;
	}

	assert(var == FNR_node);
	if (val->numbr != FNR) {
		unref(val);
		val = FNR_node->var_value = make_awknum(FNR);
	}
	return val;
}

/*
 * awknum_set_vars --- update internal variables for assignment
 *	to a special variable.
 */

static void
awknum_set_var(const NODE *var)
{
	NODE *val = var->var_value;
	if (var == NR_node)
		NR = val->numbr;
	else if (var == FNR_node)
		FNR = val->numbr;

	/* N.B: PREC and ROUNMODE -- not relevant */
}

/* awknum_increment_var --- increment NR or FNR */

static long
awknum_increment_var(const NODE *var ATTRIBUTE_UNUSED, long nr)
{
	/* var == (F)NR_node */
	return ++nr;
}

/* awknum_init_vars --- initialize special variables */

static void
awknum_init_vars()
{
	/* dummy function */
}

/* make_awknum --- allocate a node with defined number */

static NODE *
make_awknum(AWKNUM x)
{
	NODE *r;
	getnode(r);
	r->type = Node_val;
	r->numbr = x;
	r->flags = MALLOC|NUMBER|NUMCUR;
	r->valref = 1;
	r->stptr = NULL;
	r->stlen = 0;
#if MBS_SUPPORT
	r->wstptr = NULL;
	r->wstlen = 0;
#endif /* defined MBS_SUPPORT */
	return r;
}

/* make_integer - Convert an integer to a number node.  */

static inline NODE *
make_integer(uintmax_t n)
{
	n = adjust_uint(n);
	return make_awknum(n);
}

/* do_lshift --- perform a << operation */

static NODE *
do_lshift(int nargs)
{
	NODE *s1, *s2;
	uintmax_t uval, ushift, res;
	AWKNUM val, shift;

	s2 = POP_SCALAR();
	s1 = POP_SCALAR();
	if (do_lint) {
		if ((s1->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("lshift: received non-numeric first argument"));
		if ((s2->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("lshift: received non-numeric second argument"));
	}
	val = force_number(s1)->numbr;
	shift = force_number(s2)->numbr;
	if (do_lint) {
		if (val < 0 || shift < 0)
			lintwarn(_("lshift(%f, %f): negative values will give strange results"),
					(double) val, (double) shift);
		if (double_to_int(val) != val || double_to_int(shift) != shift)
			lintwarn(_("lshift(%f, %f): fractional values will be truncated"),
					(double) val, (double) shift);
		if (shift >= sizeof(uintmax_t) * CHAR_BIT)
			lintwarn(_("lshift(%f, %f): too large shift value will give strange results"),
					(double) val, (double) shift);
	}

	DEREF(s1);
	DEREF(s2);

	uval = (uintmax_t) val;
	ushift = (uintmax_t) shift;

	res = uval << ushift;
	return make_integer(res);
}

/* do_rshift --- perform a >> operation */

static NODE *
do_rshift(int nargs)
{
	NODE *s1, *s2;
	uintmax_t uval, ushift, res;
	AWKNUM val, shift;

	s2 = POP_SCALAR();
	s1 = POP_SCALAR();
	if (do_lint) {
		if ((s1->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("rshift: received non-numeric first argument"));
		if ((s2->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("rshift: received non-numeric second argument"));
	}
	val = force_number(s1)->numbr;
	shift = force_number(s2)->numbr;
	if (do_lint) {
		if (val < 0 || shift < 0)
			lintwarn(_("rshift(%f, %f): negative values will give strange results"),
					(double) val, (double) shift);
		if (double_to_int(val) != val || double_to_int(shift) != shift)
			lintwarn(_("rshift(%f, %f): fractional values will be truncated"),
					(double) val, (double) shift);
		if (shift >= sizeof(uintmax_t) * CHAR_BIT)
			lintwarn(_("rshift(%f, %f): too large shift value will give strange results"),
					(double) val, (double) shift);
	}

	DEREF(s1);
	DEREF(s2);

	uval = (uintmax_t) val;
	ushift = (uintmax_t) shift;

	res = uval >> ushift;
	return make_integer(res);
}

/* do_and --- perform an & operation */

static NODE *
do_and(int nargs)
{
	NODE *s1;
	uintmax_t res, uval;
	AWKNUM val;
	int i;

	res = ~0;	/* start off with all ones */
	if (nargs < 2)
		fatal(_("and: called with less than two arguments"));

	for (i = 1; nargs > 0; nargs--, i++) {
		s1 = POP_SCALAR();
		if (do_lint && (s1->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("and: argument %d is non-numeric"), i);

		val = force_number(s1)->numbr;
		if (do_lint && val < 0)
			lintwarn(_("and: argument %d negative value %g will give strange results"),
					i, (double) val);

		uval = (uintmax_t) val;
		res &= uval;

		DEREF(s1);
	}

	return make_integer(res);
}

/* do_or --- perform an | operation */

static NODE *
do_or(int nargs)
{
	NODE *s1;
	uintmax_t res, uval;
	AWKNUM val;
	int i;

	res = 0;
	if (nargs < 2)
		fatal(_("or: called with less than two arguments"));

	for (i = 1; nargs > 0; nargs--, i++) {
		s1 = POP_SCALAR();
		if (do_lint && (s1->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("or: argument %d is non-numeric"), i);

		val = force_number(s1)->numbr;
		if (do_lint && val < 0)
			lintwarn(_("or: argument %d negative value %g will give strange results"),
					i, (double) val);

		uval = (uintmax_t) val;
		res |= uval;

		DEREF(s1);
	}

	return make_integer(res);
}

/* do_xor --- perform an ^ operation */

static NODE *
do_xor(int nargs)
{
	NODE *s1;
	uintmax_t res, uval;
	AWKNUM val;
	int i;

	if (nargs < 2)
		fatal(_("xor: called with less than two arguments"));

	res = 0;	/* silence compiler warning */
	for (i = 1; nargs > 0; nargs--, i++) {
		s1 = POP_SCALAR();
		if (do_lint && (s1->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("xor: argument %d is non-numeric"), i);

		val = force_number(s1)->numbr;
		if (do_lint && val < 0)
			lintwarn(_("xor: argument %d negative value %g will give strange results"),
					i, (double) val);

		uval = (uintmax_t) val;
		if (i == 1)
			res = uval;
		else
			res ^= uval;

		DEREF(s1);
	}

	return make_integer(res);
}

/* do_compl --- perform a ~ operation */

static NODE *
do_compl(int nargs)
{
	NODE *tmp;
	AWKNUM d;
	uintmax_t uval;

	tmp = POP_SCALAR();
	if (do_lint && (tmp->flags & (NUMCUR|NUMBER)) == 0)
		lintwarn(_("compl: received non-numeric argument"));
	d = force_number(tmp)->numbr;
	DEREF(tmp);

	if (do_lint) {
		if (d < 0)
			lintwarn(_("compl(%f): negative value will give strange results"),
					(double) d);
		if (double_to_int(d) != d)
			lintwarn(_("compl(%f): fractional value will be truncated"),
					(double) d);
	}

	uval = (uintmax_t) d;
	uval = ~ uval;
	return make_integer(uval);
}

/* nondec2awknum --- convert octal or hex value to double */

/*
 * Because of awk's concatenation rules and the way awk.y:yylex()
 * collects a number, this routine has to be willing to stop on the
 * first invalid character.
 */

static AWKNUM
nondec2awknum(char *str, size_t len)
{
	AWKNUM retval = 0.0;
	char save;
	short val;
	char *start = str;

	if (*str == '0' && (str[1] == 'x' || str[1] == 'X')) {
		/*
		 * User called strtonum("0x") or some such,
		 * so just quit early.
		 */
		if (len <= 2)
			return (AWKNUM) 0.0;

		for (str += 2, len -= 2; len > 0; len--, str++) {
			switch (*str) {
			case '0':
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				val = *str - '0';
				break;
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				val = *str - 'a' + 10;
				break;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				val = *str - 'A' + 10;
				break;
			default:
				goto done;
			}
			retval = (retval * 16) + val;
		}
	} else if (*str == '0') {
		for (; len > 0; len--) {
			if (! isdigit((unsigned char) *str))
				goto done;
			else if (*str == '8' || *str == '9') {
				str = start;
				goto decimal;
			}
			retval = (retval * 8) + (*str - '0');
			str++;
		}
	} else {
decimal:
		save = str[len];
		retval = strtod(str, NULL);
		str[len] = save;
	}
done:
	return retval;
}


/* do_rand --- do the rand function */

static bool firstrand = true;
/* Some systems require this array to be integer aligned. Sigh. */
#define SIZEOF_STATE 256
static uint32_t istate[SIZEOF_STATE/sizeof(uint32_t)];
static char *const state = (char *const) istate;

/* ARGSUSED */
static NODE *
do_rand(int nargs ATTRIBUTE_UNUSED)
{
	if (firstrand) {
		(void) initstate((unsigned) 1, state, SIZEOF_STATE);
		/* don't need to srandom(1), initstate() does it for us. */
		firstrand = false;
		setstate(state);
	}
	/*
	 * Per historical practice and POSIX, return value N is
	 *
	 * 	0 <= n < 1
	 */
	return make_awknum((AWKNUM) (random() % GAWK_RANDOM_MAX) / GAWK_RANDOM_MAX);
}

/* do_srand --- seed the random number generator */

static NODE *
do_srand(int nargs)
{
	NODE *tmp;
	static long save_seed = 1;
	long ret = save_seed;	/* SVR4 awk srand returns previous seed */

	if (firstrand) {
		(void) initstate((unsigned) 1, state, SIZEOF_STATE);
		/* don't need to srandom(1), we're changing the seed below */
		firstrand = false;
		(void) setstate(state);
	}

	if (nargs == 0)
		srandom((unsigned int) (save_seed = (long) time((time_t *) 0)));
	else {
		tmp = POP_SCALAR();
		if (do_lint && (tmp->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("srand: received non-numeric argument"));
		srandom((unsigned int) (save_seed = (long) force_number(tmp)->numbr));
		DEREF(tmp);
	}
	return make_awknum((AWKNUM) ret);
}


/* str2awknum --- create a number node from string */

static NODE *
str2awknum(char *str, char **endptr, int base, bool is_integer ATTRIBUTE_UNUSED)
{
	NODE *r;
	AWKNUM d;

	if (base == 0) {
		/*
		 * special case -- only used to parse input in the debugger?
		 * FIXME: reject ieee specials we don't want and/or use the same
		 * rules when reading numbers from a source file and nuke this case.
		 */

		errno = 0;
		d = strtod(str, endptr);
		if (errno != 0)
			d = 0;
	} else {
		if (base == 8 || base == 16)
			d = nondec2awknum(str, strlen(str));
		else
			d = atof(str);
	}
	r = make_awknum(d);
	if (d <= INT32_MAX && d >= INT32_MIN && d == (int32_t) d)
		r->flags |= NUMINT;
	return r;
}

/* awknum_mod --- remainder from division of two numbers */

static NODE *
awknum_mod(const NODE *t1, const NODE *t2)
{
	AWKNUM x;

	if (t2->numbr == 0)
		fatal(_("division by zero attempted in `%%'"));
#ifdef HAVE_FMOD
	x = fmod(t1->numbr, t2->numbr);
#else	/* ! HAVE_FMOD */
	(void) modf(t1->numbr / t2->numbr, & x);
	x = t1->numbr - x * t2->numbr;
#endif	/* ! HAVE_FMOD */
	return make_awknum(x);
}

/* awknum_pow --- power function */

static NODE *
awknum_pow(const NODE *t1, const NODE *t2)
{
	return make_awknum(calc_exp(t1->numbr, t2->numbr));
}


/*
 * calc_exp_posint --- calculate x^n for positive integral n,
 *	using exponentiation by squaring without recursion.
 */

static AWKNUM
calc_exp_posint(AWKNUM x, long n)
{
	AWKNUM mult = 1;

	while (n > 1) {
		if ((n % 2) == 1)
			mult *= x;
		x *= x;
		n /= 2;
	}
	return mult * x;
}

/* calc_exp --- calculate x1^x2 */

static AWKNUM
calc_exp(AWKNUM x1, AWKNUM x2)
{
	long lx;

	if ((lx = x2) == x2) {		/* integer exponent */
		if (lx == 0)
			return 1;
		return (lx > 0) ? calc_exp_posint(x1, lx)
				: 1.0 / calc_exp_posint(x1, -lx);
	}
	return (AWKNUM) pow((double) x1, (double) x2);
}

/* cmp_awknums --- compare two AWKNUMs */

static int
cmp_awknums(const NODE *t1, const NODE *t2)
{
	/*
	 * This routine is also used to sort numeric array indices or values.
	 * For the purposes of sorting, NaN is considered greater than
	 * any other value, and all NaN values are considered equivalent and equal.
	 * This isn't in compliance with IEEE standard, but compliance w.r.t. NaN
	 * comparison at the awk level is a different issue, and needs to be dealt
	 * with in the interpreter for each opcode seperately.
	 */

	if (isnan(t1->numbr))
		return ! isnan(t2->numbr);
	if (isnan(t2->numbr))
		return -1;
	/* don't subtract, in case one or both are infinite */
	if (t1->numbr == t2->numbr)
		return 0;
	if (t1->numbr < t2->numbr)
		return -1;
	return 1;
}

/* force_awknum --- force a value to be numeric */

static NODE *
force_awknum(NODE *n)
{
	char *cp;
	char *cpend;
	char save;
	char *ptr;
	unsigned int newflags;

	if ((n->flags & NUMCUR) != 0)
		return n;

	/* all the conditionals are an attempt to avoid the expensive strtod */

	/* Note: only set NUMCUR if we actually convert some digits */

	n->numbr = 0.0;

	if (n->stlen == 0) {
		return n;
	}

	cp = n->stptr;
	/*
	 * 2/2007:
	 * POSIX, by way of severe language lawyering, seems to
	 * allow things like "inf" and "nan" to mean something.
	 * So if do_posix, the user gets what he deserves.
	 * This also allows hexadecimal floating point. Ugh.
	 */
	if (! do_posix) {
		if (isalpha((unsigned char) *cp)) {
			return n;
		} else if (n->stlen == 4 && is_ieee_magic_val(n->stptr)) {
			if ((n->flags & MAYBE_NUM) != 0)
				n->flags &= ~MAYBE_NUM;
			n->flags |= NUMBER|NUMCUR;
			n->numbr = get_ieee_magic_val(n->stptr);
			return n;
		}
		/* else
			fall through */
	}
	/* else not POSIX, so
		fall through */

	cpend = cp + n->stlen;
	while (cp < cpend && isspace((unsigned char) *cp))
		cp++;

	if (   cp == cpend		/* only spaces, or */
	    || (! do_posix		/* not POSIXLY paranoid and */
	        && (isalpha((unsigned char) *cp)	/* letter, or */
					/* CANNOT do non-decimal and saw 0x */
		    || (! do_non_decimal_data && cp[0] == '0'
		        && (cp[1] == 'x' || cp[1] == 'X'))))) {
		return n;
	}

	if ((n->flags & MAYBE_NUM) != 0) {
		newflags = NUMBER;
		n->flags &= ~MAYBE_NUM;
	} else
		newflags = 0;

	if (cpend - cp == 1) {		/* only one character */
		if (isdigit((unsigned char) *cp)) {	/* it's a digit! */
			n->numbr = (AWKNUM)(*cp - '0');
			n->flags |= newflags;
			n->flags |= NUMCUR;
			if (cp == n->stptr)		/* no leading spaces */
				n->flags |= NUMINT;
		}
		return n;
	}

	if (do_non_decimal_data) {	/* main.c assures false if do_posix */
		errno = 0;
		if (! do_traditional && get_numbase(cp, true) != 10) {
			n->numbr = nondec2awknum(cp, cpend - cp);
			n->flags |= NUMCUR;
			ptr = cpend;
			goto finish;
		}
	}

	errno = 0;
	save = *cpend;
	*cpend = '\0';
	n->numbr = (AWKNUM) strtod((const char *) cp, &ptr);

	/* POSIX says trailing space is OK for NUMBER */
	while (isspace((unsigned char) *ptr))
		ptr++;
	*cpend = save;
finish:
	if (errno == 0 && ptr == cpend) {
		n->flags |= newflags;
		n->flags |= NUMCUR;
	} else {
		errno = 0;
	}

	return n;
}


/*
 * The following lookup table is used as an optimization in force_string;
 * (more complicated) variations on this theme didn't seem to pay off, but 
 * systematic testing might be in order at some point.
 */
static const char *values[] = {
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
};
#define	NVAL	(sizeof(values)/sizeof(values[0]))

/* format_awknum_val --- format a numeric value based on format */

static NODE *
format_awknum_val(const char *format, int index, NODE *s)
{
	char buf[BUFSIZ];
	char *sp = buf;
	double val;

	/*
	 * 2/2007: Simplify our lives here. Instead of worrying about
	 * whether or not the value will fit into a long just so we
	 * can use sprintf("%ld", val) on it, always format it ourselves.
	 * The only thing to worry about is that integral values always
	 * format as integers. %.0f does that very well.
	 *
	 * 6/2008: Would that things were so simple. Always using %.0f
	 * imposes a notable performance penalty for applications that
	 * do a lot of conversion of integers to strings. So, we reinstate
	 * the old code, but use %.0f for integral values that are outside
	 * the range of a long.  This seems a reasonable compromise.
	 *
	 * 12/2009: Use <= and >= in the comparisons with LONG_xxx instead of
	 * < and > so that things work correctly on systems with 64 bit integers.
	 */

	/* not an integral value, or out of range */
	if ((val = double_to_int(s->numbr)) != s->numbr
			|| val <= LONG_MIN || val >= LONG_MAX
	) {
		/*
		 * Once upon a time, we just blindly did this:
		 *	sprintf(sp, format, s->numbr);
		 *	s->stlen = strlen(sp);
		 *	s->stfmt = (char) index;
		 * but that's no good if, e.g., OFMT is %s. So we punt,
		 * and just always format the value ourselves.
		 */

		NODE *dummy[2], *r;
		unsigned int oflags;

		/* create dummy node for a sole use of format_tree */
		dummy[1] = s;
		oflags = s->flags;

		if (val == s->numbr) {
			/* integral value, but outside range of %ld, use %.0f */
			r = format_tree("%.0f", 4, dummy, 2);
			s->stfmt = -1;
		} else {
			r = format_tree(format, fmt_list[index]->stlen, dummy, 2);
			assert(r != NULL);
			s->stfmt = (char) index;
		}
		s->flags = oflags;
		s->stlen = r->stlen;
		if ((s->flags & STRCUR) != 0)
			efree(s->stptr);
		s->stptr = r->stptr;
		freenode(r);	/* Do not unref(r)! We want to keep s->stptr == r->stpr.  */

		goto no_malloc;
	} else {
		/*
		 * integral value; force conversion to long only once.
		 */
		long num = (long) val;

		if (num < NVAL && num >= 0) {
			sp = (char *) values[num];
			s->stlen = 1;
		} else {
			(void) sprintf(sp, "%ld", num);
			s->stlen = strlen(sp);
		}
		s->stfmt = -1;
		if ((s->flags & INTIND) != 0) {
			s->flags &= ~(INTIND|NUMBER);
			s->flags |= STRING;
		}
	}
	if (s->stptr != NULL)
		efree(s->stptr);
	emalloc(s->stptr, char *, s->stlen + 2, "format_awknum_val");
	memcpy(s->stptr, sp, s->stlen + 1);
no_malloc:
	s->flags |= STRCUR;
	free_wstr(s);
	return s;
}

/* is_ieee_magic_val --- return true for +inf, -inf, +nan, -nan */

static int
is_ieee_magic_val(const char *val)
{
	/*
	 * Avoid strncasecmp: it mishandles ASCII bytes in some locales.
	 * Assume the length is 4, as the caller checks this.
	 */
	return (   (val[0] == '+' || val[0] == '-')
		&& (   (   (val[1] == 'i' || val[1] == 'I')
			&& (val[2] == 'n' || val[2] == 'N')
			&& (val[3] == 'f' || val[3] == 'F'))
		    || (   (val[1] == 'n' || val[1] == 'N')
			&& (val[2] == 'a' || val[2] == 'A')
			&& (val[3] == 'n' || val[3] == 'N'))));
}

/* get_ieee_magic_val --- return magic value for string */

static AWKNUM
get_ieee_magic_val(const char *val)
{
	static bool first = true;
	static AWKNUM inf;
	static AWKNUM nan;
	char *ptr;
	AWKNUM v;

	v = strtod(val, & ptr);

	if (val == ptr) { /* Older strtod implementations don't support inf or nan. */
		if (first) {
			first = false;
			nan = sqrt(-1.0);
			inf = -log(0.0);
		}

		v = ((val[1] == 'i' || val[1] == 'I') ? inf : nan);
		if (val[0] == '-')
			v = -v;
	}

	return v;
}

/* double_to_int --- convert double to int, used in several places */

static double
double_to_int(double d)
{
	if (d >= 0)
		d = Floor(d);
	else
		d = Ceil(d);
	return d;
}

/* do_int --- convert double to int for awk */

static NODE *
do_int(int nargs)
{
	NODE *tmp;
	AWKNUM d;

	tmp = POP_SCALAR();
	if (do_lint && (tmp->flags & (NUMCUR|NUMBER)) == 0)
		lintwarn(_("int: received non-numeric argument"));
	(void) force_number(tmp);
	d = tmp->numbr;
	DEREF(tmp);
	return make_awknum(double_to_int(d));
}

/* do_log --- the log function */

static NODE *
do_log(int nargs)
{
	NODE *tmp;
	AWKNUM d, arg;

	tmp = POP_SCALAR();
	if (do_lint && (tmp->flags & (NUMCUR|NUMBER)) == 0)
		lintwarn(_("log: received non-numeric argument"));
	arg = force_number(tmp)->numbr;
	if (arg < 0.0)
		warning(_("log: received negative argument %g"), (double) arg);
	d = log(arg);
	DEREF(tmp);
	return make_awknum(d);
}

/* do_sqrt --- do the sqrt function */

static NODE *
do_sqrt(int nargs)
{
	NODE *tmp;
	AWKNUM arg;

	tmp = POP_SCALAR();
	if (do_lint && (tmp->flags & (NUMCUR|NUMBER)) == 0)
		lintwarn(_("sqrt: received non-numeric argument"));
	arg = force_number(tmp)->numbr;
	DEREF(tmp);
	if (arg < 0.0)
		warning(_("sqrt: called with negative argument %g"), (double) arg);
	return make_awknum(sqrt(arg));
}

/* do_exp --- exponential function */

static NODE *
do_exp(int nargs)
{
	NODE *tmp;
	AWKNUM d, res;

	tmp = POP_SCALAR();
	if (do_lint && (tmp->flags & (NUMCUR|NUMBER)) == 0)
		lintwarn(_("exp: received non-numeric argument"));
	d = force_number(tmp)->numbr;
	DEREF(tmp);
	errno = 0;
	res = exp(d);
	if (errno == ERANGE)
		warning(_("exp: argument %g is out of range"), (double) d);
	return make_awknum(res);
}


/* do_atan2 --- do the atan2 function */

static NODE *
do_atan2(int nargs)
{
	NODE *t1, *t2;
	AWKNUM d1, d2;

	t2 = POP_SCALAR();
	t1 = POP_SCALAR();
	if (do_lint) {
		if ((t1->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("atan2: received non-numeric first argument"));
		if ((t2->flags & (NUMCUR|NUMBER)) == 0)
			lintwarn(_("atan2: received non-numeric second argument"));
	}
	d1 = force_number(t1)->numbr;
	d2 = force_number(t2)->numbr;
	DEREF(t1);
	DEREF(t2);
	return make_awknum(atan2(d1, d2));
}

/* do_sin --- do the sin function */

static NODE *
do_sin(int nargs)
{
	NODE *tmp;
	AWKNUM d;

	tmp = POP_SCALAR();
	if (do_lint && (tmp->flags & (NUMCUR|NUMBER)) == 0)
		lintwarn(_("sin: received non-numeric argument"));
	d = sin(force_number(tmp)->numbr);
	DEREF(tmp);
	return make_awknum(d);
}

/* do_cos --- do the cos function */

static NODE *
do_cos(int nargs)
{
	NODE *tmp;
	AWKNUM d;

	tmp = POP_SCALAR();
	if (do_lint && (tmp->flags & (NUMCUR|NUMBER)) == 0)
		lintwarn(_("cos: received non-numeric argument"));
	d = cos(force_number(tmp)->numbr);
	DEREF(tmp);
	return make_awknum(d);
}

/* do_strtonum --- the strtonum function */

static NODE *
do_strtonum(int nargs)
{
	NODE *tmp;
	AWKNUM d;

	tmp = POP_SCALAR();
	if ((tmp->flags & (NUMBER|NUMCUR)) != 0)
		d = force_number(tmp)->numbr;
	else if (get_numbase(tmp->stptr, use_lc_numeric) != 10)
		d = nondec2awknum(tmp->stptr, tmp->stlen);
	else
		d = force_number(tmp)->numbr;

	DEREF(tmp);
	return make_awknum(d);
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

static NODE *
format_nodes_awknum(
	const char *fmt_string,
	size_t n0,
	NODE **the_args,
	long num_args)
{
/* copy 'l' bytes from 's' to 'obufout' checking for space in the process */
/* difference of pointers should be of ptrdiff_t type, but let us be kind */
#define bchunk(s, l) if (l) { \
	while ((l) > ofre) { \
		size_t olen = obufout - obuf; \
		erealloc(obuf, char *, osiz * 2, "format_tree"); \
		ofre += osiz; \
		osiz *= 2; \
		obufout = obuf + olen; \
	} \
	memcpy(obufout, s, (size_t) (l)); \
	obufout += (l); \
	ofre -= (l); \
}

/* copy one byte from 's' to 'obufout' checking for space in the process */
#define bchunk_one(s) { \
	if (ofre < 1) { \
		size_t olen = obufout - obuf; \
		erealloc(obuf, char *, osiz * 2, "format_tree"); \
		ofre += osiz; \
		osiz *= 2; \
		obufout = obuf + olen; \
	} \
	*obufout++ = *s; \
	--ofre; \
}

/* Is there space for something L big in the buffer? */
#define chksize(l)  if ((l) >= ofre) { \
	size_t olen = obufout - obuf; \
	size_t delta = osiz+l-ofre; \
	erealloc(obuf, char *, osiz + delta, "format_tree"); \
	obufout = obuf + olen; \
	ofre += delta; \
	osiz += delta; \
}

	size_t cur_arg = 0;
	NODE *r = NULL;
	int i, nc;
	bool toofew = false;
	char *obuf, *obufout;
	size_t osiz, ofre;
	const char *chbuf;
	const char *s0, *s1;
	int cs1;
	NODE *arg;
	long fw, prec, argnum;
	bool used_dollar;
	bool lj, alt, big_flag, bigbig_flag, small_flag, have_prec, need_format;
	long *cur = NULL;
	uintmax_t uval;
	bool sgn;
	int base;
	/*
	 * Although this is an array, the elements serve two different
	 * purposes. The first element is the general buffer meant
	 * to hold the entire result string.  The second one is a
	 * temporary buffer for large floating point values. They
	 * could just as easily be separate variables, and the
	 * code might arguably be clearer.
	 */
	struct {
		char *buf;
		size_t bufsize;
		char stackbuf[30];
	} cpbufs[2];
#define cpbuf	cpbufs[0].buf
	char *cend = &cpbufs[0].stackbuf[sizeof(cpbufs[0].stackbuf)];
	char *cp;
	const char *fill;
	AWKNUM tmpval = 0.0;
	char signchar = '\0';
	size_t len;
	bool zero_flag = false;
	bool quote_flag = false;
	int ii, jj;
	char *chp;
	size_t copy_count, char_count;

	static const char sp[] = " ";
	static const char zero_string[] = "0";
	static const char lchbuf[] = "0123456789abcdef";
	static const char Uchbuf[] = "0123456789ABCDEF";

#define INITIAL_OUT_SIZE	512
	emalloc(obuf, char *, INITIAL_OUT_SIZE, "format_tree");
	obufout = obuf;
	osiz = INITIAL_OUT_SIZE;
	ofre = osiz - 2;

	cur_arg = 1;

	{
		size_t k;
		for (k = 0; k < sizeof(cpbufs)/sizeof(cpbufs[0]); k++) {
			cpbufs[k].bufsize = sizeof(cpbufs[k].stackbuf);
			cpbufs[k].buf = cpbufs[k].stackbuf;
		}
	}

	/*
	 * The point of this goop is to grow the buffer
	 * holding the converted number, so that large
	 * values don't overflow a fixed length buffer.
	 */
#define PREPEND(CH) do {	\
	if (cp == cpbufs[0].buf) {	\
		char *prev = cpbufs[0].buf;	\
		emalloc(cpbufs[0].buf, char *, 2*cpbufs[0].bufsize, \
		 	"format_tree");	\
		memcpy((cp = cpbufs[0].buf+cpbufs[0].bufsize), prev,	\
		       cpbufs[0].bufsize);	\
		cpbufs[0].bufsize *= 2;	\
		if (prev != cpbufs[0].stackbuf)	\
			efree(prev);	\
		cend = cpbufs[0].buf+cpbufs[0].bufsize;	\
	}	\
	*--cp = (CH);	\
} while(0)

	/*
	 * Check first for use of `count$'.
	 * If plain argument retrieval was used earlier, choke.
	 *	Otherwise, return the requested argument.
	 * If not `count$' now, but it was used earlier, choke.
	 * If this format is more than total number of args, choke.
	 * Otherwise, return the current argument.
	 */
#define parse_next_arg() { \
	if (argnum > 0) { \
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

	need_format = false;
	used_dollar = false;

	s0 = s1 = fmt_string;
	while (n0-- > 0) {
		if (*s1 != '%') {
			s1++;
			continue;
		}
		need_format = true;
		bchunk(s0, s1 - s0);
		s0 = s1;
		cur = &fw;
		fw = 0;
		prec = 0;
		base = 0;
		argnum = 0;
		base = 0;
		have_prec = false;
		signchar = '\0';
		zero_flag = false;
		quote_flag = false;
		lj = alt = big_flag = bigbig_flag = small_flag = false;
		fill = sp;
		cp = cend;
		chbuf = lchbuf;
		s1++;

retry:
		if (n0-- == 0)	/* ran out early! */
			break;

		switch (cs1 = *s1++) {
		case (-1):	/* dummy case to allow for checking */
check_pos:
			if (cur != &fw)
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

				if (fw && ! have_prec)
					msg = _("field width is ignored for `%%' specifier");
				else if (fw == 0 && have_prec)
					msg = _("precision is ignored for `%%' specifier");
				else if (fw && have_prec)
					msg = _("field width and precision are ignored for `%%' specifier");

				if (msg != NULL)
					lintwarn("%s", msg);
			}
			bchunk_one("%");
			s0 = s1;
			break;

		case '0':
			/*
			 * Only turn on zero_flag if we haven't seen
			 * the field width or precision yet.  Otherwise,
			 * screws up floating point formatting.
			 */
			if (cur == & fw)
				zero_flag = true;
			if (lj)
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
			if (prec >= 0)
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
			if (prec < 0) 	/* negative precision is discarded */
				have_prec = false;
			if (cur == &prec)
				cur = NULL;
			if (n0 == 0)	/* badly formatted control string */
				continue;
			goto retry;
		case '$':
			if (do_traditional) {
				msg(_("fatal: `$' is not permitted in awk formats"));
				goto out;
			}

			if (cur == &fw) {
				argnum = fw;
				fw = 0;
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
			if (*cur < 0 && cur == &fw) {
				*cur = -*cur;
				lj++;
			}
			if (cur == &prec) {
				if (*cur >= 0)
					have_prec = true;
				else
					have_prec = false;
				cur = NULL;
			}
			goto retry;
		case ' ':		/* print ' ' or '-' */
					/* 'space' flag is ignored */
					/* if '+' already present  */
			if (signchar != false) 
				goto check_pos;
			/* FALL THROUGH */
		case '+':		/* print '+' or '-' */
			signchar = cs1;
			goto check_pos;
		case '-':
			if (prec < 0)
				break;
			if (cur == &prec) {
				prec = -1;
				goto retry;
			}
			fill = sp;      /* if left justified then other */
			lj++; 		/* filling is ignored */
			goto check_pos;
		case '.':
			if (cur != &fw)
				break;
			cur = &prec;
			have_prec = true;
			goto retry;
		case '#':
			alt = true;
			goto check_pos;
		case '\'':
#if defined(HAVE_LOCALE_H)       
			/* allow quote_flag if there is a thousands separator. */
			if (loc.thousands_sep[0] != '\0')
				quote_flag = true;
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

					memcpy(cpbuf, buf, count);
					prec = count;
					cp = cpbuf;
					goto pr_tail;
				}
out0:
				;
				/* else,
					fall through */
#endif
				if (do_lint && uval > 255) {
					lintwarn("[s]printf: value %g is too big for %%c format",
							arg->numbr);
				}
				cpbuf[0] = uval;
				prec = 1;
				cp = cpbuf;
				goto pr_tail;
			}
			/*
			 * As per POSIX, only output first character of a
			 * string value.  Thus, we ignore any provided
			 * precision, forcing it to 1.  (Didn't this
			 * used to work? 6/2003.)
			 */
			cp = arg->stptr;
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
				if (count == 0
				    || count == (size_t)-1
				    || count == (size_t)-2)
					goto out2;
				prec = count;
				goto pr_tail;
			}
out2:
			;
#endif
			prec = 1;
			goto pr_tail;
		case 's':
			need_format = false;
			parse_next_arg();
			arg = force_string(arg);
			if (fw == 0 && ! have_prec)
				prec = arg->stlen;
			else {
				char_count = mbc_char_count(arg->stptr, arg->stlen);
				if (! have_prec || prec > char_count)
					prec = char_count;
			}
			cp = arg->stptr;
			goto pr_tail;
		case 'd':
		case 'i':
			need_format = false;
			parse_next_arg();
			(void) force_number(arg);
			tmpval = arg->numbr;

			/*
			 * Check for Nan or Inf.
			 */
			if (isnan(tmpval) || isinf(tmpval))
				goto out_of_range;
			else
				tmpval = double_to_int(tmpval);

			/*
			 * ``The result of converting a zero value with a
			 * precision of zero is no characters.''
			 */
			if (have_prec && prec == 0 && tmpval == 0)
				goto pr_tail;

			if (tmpval < 0) {
				tmpval = -tmpval;
				sgn = true;
			} else {
				if (tmpval == -0.0)
					/* avoid printing -0 */
					tmpval = 0.0;
				sgn = false;
			}
			/*
			 * Use snprintf return value to tell if there
			 * is enough room in the buffer or not.
			 */
			while ((i = snprintf(cpbufs[1].buf,
					     cpbufs[1].bufsize, "%.0f",
					     tmpval)) >=
			       cpbufs[1].bufsize) {
				if (cpbufs[1].buf == cpbufs[1].stackbuf)
					cpbufs[1].buf = NULL;
				if (i > 0) {
					cpbufs[1].bufsize += ((i > cpbufs[1].bufsize) ?
							      i : cpbufs[1].bufsize);
				}
				else
					cpbufs[1].bufsize *= 2;
				assert(cpbufs[1].bufsize > 0);
				erealloc(cpbufs[1].buf, char *,
					 cpbufs[1].bufsize, "format_tree");
			}
			if (i < 1)
				goto out_of_range;
			chp = &cpbufs[1].buf[i-1];
			ii = jj = 0;
			do {
				PREPEND(*chp);
				chp--; i--;
#if defined(HAVE_LOCALE_H)
				if (quote_flag && loc.grouping[ii] && ++jj == loc.grouping[ii]) {
					if (i)	/* only add if more digits coming */
						PREPEND(loc.thousands_sep[0]);	/* XXX - assumption it's one char */
					if (loc.grouping[ii+1] == 0)
						jj = 0;		/* keep using current val in loc.grouping[ii] */
					else if (loc.grouping[ii+1] == CHAR_MAX)
						quote_flag = false;
					else {                 
						ii++;
						jj = 0;
					}
				}
#endif
			} while (i > 0);

			/* add more output digits to match the precision */
			if (have_prec) {
				while (cend - cp < prec)
					PREPEND('0');
			}

			if (sgn)
				PREPEND('-');
			else if (signchar)
				PREPEND(signchar);
			/*
			 * When to fill with zeroes is of course not simple.
			 * First: No zero fill if left-justifying.
			 * Next: There seem to be two cases:
			 * 	A '0' without a precision, e.g. %06d
			 * 	A precision with no field width, e.g. %.10d
			 * Any other case, we don't want to fill with zeroes.
			 */
			if (! lj
			    && ((zero_flag && ! have_prec)
				 || (fw == 0 && have_prec)))
				fill = zero_string;
			if (prec > fw)
				fw = prec;
			prec = cend - cp;
			if (fw > prec && ! lj && fill != sp
			    && (*cp == '-' || signchar)) {
				bchunk_one(cp);
				cp++;
				prec--;
				fw--;
			}
			goto pr_tail;
		case 'X':
			chbuf = Uchbuf;	/* FALL THROUGH */
		case 'x':
			base += 6;	/* FALL THROUGH */
		case 'u':
			base += 2;	/* FALL THROUGH */
		case 'o':
			base += 8;
			need_format = false;
			parse_next_arg();
			(void) force_number(arg);
			tmpval = arg->numbr;

			/*
			 * ``The result of converting a zero value with a
			 * precision of zero is no characters.''
			 *
			 * If I remember the ANSI C standard, though,
			 * it says that for octal conversions
			 * the precision is artificially increased
			 * to add an extra 0 if # is supplied.
			 * Indeed, in C,
			 * 	printf("%#.0o\n", 0);
			 * prints a single 0.
			 */
			if (! alt && have_prec && prec == 0 && tmpval == 0)
				goto pr_tail;

			if (tmpval < 0) {
				uval = (uintmax_t) (intmax_t) tmpval;
				if ((AWKNUM)(intmax_t)uval != double_to_int(tmpval))
					goto out_of_range;
			} else {
				uval = (uintmax_t) tmpval;
				if ((AWKNUM)uval != double_to_int(tmpval))
					goto out_of_range;
			}

			/*
			 * When to fill with zeroes is of course not simple.
			 * First: No zero fill if left-justifying.
			 * Next: There seem to be two cases:
			 * 	A '0' without a precision, e.g. %06d
			 * 	A precision with no field width, e.g. %.10d
			 * Any other case, we don't want to fill with zeroes.
			 */
			if (! lj
			    && ((zero_flag && ! have_prec)
				 || (fw == 0 && have_prec)))
				fill = zero_string;
			ii = jj = 0;
			do {
				PREPEND(chbuf[uval % base]);
				uval /= base;
#if defined(HAVE_LOCALE_H)
				if (base == 10 && quote_flag && loc.grouping[ii] && ++jj == loc.grouping[ii]) {
					if (uval)	/* only add if more digits coming */
						PREPEND(loc.thousands_sep[0]);	/* XXX --- assumption it's one char */
					if (loc.grouping[ii+1] == 0)                                          
						jj = 0;     /* keep using current val in loc.grouping[ii] */
					else if (loc.grouping[ii+1] == CHAR_MAX)                        
						quote_flag = false;
					else {                 
						ii++;
						jj = 0;
					}
				}
#endif
			} while (uval > 0);

			/* add more output digits to match the precision */
			if (have_prec) {
				while (cend - cp < prec)
					PREPEND('0');
			}

			if (alt && tmpval != 0) {
				if (base == 16) {
					PREPEND(cs1);
					PREPEND('0');
					if (fill != sp) {
						bchunk(cp, 2);
						cp += 2;
						fw -= 2;
					}
				} else if (base == 8)
					PREPEND('0');
			}
			base = 0;
			if (prec > fw)
				fw = prec;
			prec = cend - cp;
	pr_tail:
			if (! lj) {
				while (fw > prec) {
			    		bchunk_one(fill);
					fw--;
				}
			}
			copy_count = prec;
			if (fw == 0 && ! have_prec)
				;
			else if (gawk_mb_cur_max > 1 && (cs1 == 's' || cs1 == 'c')) {
				assert(cp == arg->stptr || cp == cpbuf);
				copy_count = mbc_byte_count(arg->stptr, prec);
			}
			bchunk(cp, copy_count);
			while (fw > prec) {
				bchunk_one(fill);
				fw--;
			}
			s0 = s1;
			break;

     out_of_range:
			/* out of range - emergency use of %g format */
			if (do_lint)
				lintwarn(_("[s]printf: value %g is out of range for `%%%c' format"),
							(double) tmpval, cs1);
			cs1 = 'g';
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
			need_format = false;
			parse_next_arg();
			(void) force_number(arg);
			tmpval = arg->numbr;
     fmt1:
			if (! have_prec)
				prec = DEFAULT_G_PRECISION;

			chksize(fw + prec + 11);	/* 11 == slop */
			cp = cpbuf;
			*cp++ = '%';
			if (lj)
				*cp++ = '-';
			if (signchar)
				*cp++ = signchar;
			if (alt)
				*cp++ = '#';
			if (zero_flag)
				*cp++ = '0';
			if (quote_flag)
				*cp++ = '\'';

#if defined(LC_NUMERIC)
			if (quote_flag && ! use_lc_numeric)
				setlocale(LC_NUMERIC, "");
#endif

			sprintf(cp, "*.*%c", cs1);
			while ((nc = snprintf(obufout, ofre, cpbuf,
				     (int) fw, (int) prec,
				     (double) tmpval)) >= ofre)
				chksize(nc)

#if defined(LC_NUMERIC)
			if (quote_flag && ! use_lc_numeric)
				setlocale(LC_NUMERIC, "C");
#endif

			len = strlen(obufout);
			ofre -= len;
			obufout += len;
			s0 = s1;
			break;
		default:
			if (do_lint && isalpha(cs1))
				lintwarn(_("ignoring unknown format specifier character `%c': no argument converted"), cs1);
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
			lintwarn(
			_("[s]printf: format specifier does not have control letter"));
		if (cur_arg < num_args)
			lintwarn(
			_("too many arguments supplied for format string"));
	}
	bchunk(s0, s1 - s0);
	r = make_str_node(obuf, obufout - obuf, ALREADY_MALLOCED);
	obuf = NULL;
out:
	{
		size_t k;
		size_t count = sizeof(cpbufs)/sizeof(cpbufs[0]);
		for (k = 0; k < count; k++) {
			if (cpbufs[k].buf != cpbufs[k].stackbuf)
				efree(cpbufs[k].buf);
		}
		if (obuf != NULL)
			efree(obuf);
	}

	if (r == NULL)
		gawk_exit(EXIT_FATAL);
	return r;
}
