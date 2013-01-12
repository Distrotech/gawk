/*
 * format.h - (s)printf formatting related definitions.
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

/* format specification */

struct format_spec {
	int base;
	long fw;
	long prec;
	const char *fill;
	const char *chbuf;
	bool lj;
	bool alt;
	bool have_prec;
	bool zero_flag;
	bool quote_flag;
	char signchar;
	char fmtchar;
};

/* indices in `fmt_index' for "%d" and "%.0f" */

enum { INT_d_FMT_INDEX, INT_0f_FMT_INDEX };


/* struct to manage awk (s)printf formatted string */

struct print_fmt_buf {
	char *buf;	/* beginning of buffer */
	char *dataend;	/* end of current data */
	size_t bufsize;
	size_t room_left;
	bool is_malloced;	/* true if this struct is malloc-ed */
	void (*chksize)(struct print_fmt_buf *, size_t);
	void (*cpbuf_chksize)(struct print_fmt_buf *);

	/*
	 * temporary buffer: can be used to prepend one character at a time
	 *	without overflowing the buffer; used primarily to format integers.
	 */
	struct {
		char *buf;	/* beginning of buffer */
		char *bufend;	/* end of buffer */
		size_t bufsize;
		char *databegin;	/* start of current data */
	} cpbuf;
};

extern struct print_fmt_buf *get_fmt_buf(void);
extern void format_nondecimal(uintmax_t, struct format_spec *, struct print_fmt_buf *);
extern NODE *format_tree(const char *, size_t, NODE **, long);

extern char lchbuf[];
extern char Uchbuf[];
extern char space_string[];
extern char zero_string[];

#	define buf_start(ob)	((ob)->buf)
#	define buf_end(ob)	((ob)->dataend)
#	define buf_space(ob)	((ob)->room_left)
#	define cpbuf_start(ob)	((ob)->cpbuf.databegin)
#	define cpbuf_end(ob)	((ob)->cpbuf.bufend)
#	define cpbuf(ob)	((ob)->cpbuf.buf)


/* chksize --- make room for something LEN big in the output buffer */

static inline void
chksize(struct print_fmt_buf *outb, size_t len)
{
	if (len > outb->room_left)
		outb->chksize(outb, len);
}

/* bchunk --- copy LEN bytes from STR checking for space in the process */

static inline void
bchunk(struct print_fmt_buf *outb, const char *str, size_t len)
{
	if (len > 0) {
		if (len > outb->room_left)
			outb->chksize(outb, len);
		outb->dataend = (char *) memcpy(outb->dataend, str, len) + len;
		outb->room_left -= len;
	}
}

/* bchunk_one --- copy one byte from STR checking for space in the process */

static inline void
bchunk_one(struct print_fmt_buf *outb, const char *str)
{
	if (1 > outb->room_left)
		outb->chksize(outb, 1);
	*outb->dataend++ = *str;
	--outb->room_left;
}

/* buf_adjust --- adjust buffer after appending LEN bytes */

static inline void
buf_adjust(struct print_fmt_buf *outb, size_t len)
{
	assert(len <= outb->room_left);
	outb->dataend += len;
	outb->room_left -= len;
}

/* bytes2node --- convert bytes to string NODE */

static inline NODE *
bytes2node(struct print_fmt_buf *outb, NODE *node)
{
	/* FIXME -- realloc buf? AFAIK, never done before or an issue at all -- JH */
	if (node != NULL) {
		node->stptr = outb->buf;
		node->stlen = outb->dataend - outb->buf;
	} else
		node = make_str_node(outb->buf, outb->dataend - outb->buf, ALREADY_MALLOCED);
	outb->buf = NULL;
	return node;
}

/* tmpbuf_prepend --- prepend one byte to temporary buffer */

static inline void
tmpbuf_prepend(struct print_fmt_buf *outb, char ch)
{
	if (outb->cpbuf.databegin == outb->cpbuf.buf)
		outb->cpbuf_chksize(outb);
	*--outb->cpbuf.databegin = ch;
}

/* pr_fill --- fill buffer with current fill character */

static inline void
pr_fill(struct format_spec *spec, struct print_fmt_buf *outb)
{
	while (spec->fw > spec->prec) {
    		bchunk_one(outb, spec->fill);
		spec->fw--;
	}
}

static inline void
pr_num_tail(const char *cp, size_t copy_count, struct format_spec *spec, struct print_fmt_buf *outb)
{
	if (! spec->lj)
		pr_fill(spec, outb);
	bchunk(outb, cp, copy_count);
	pr_fill(spec, outb);
}


/* free_print_fmt_buf --- free buffer */

static inline void
free_fmt_buf(struct print_fmt_buf *outb)
{
	if (outb->buf != NULL) {
		efree(outb->buf);
		outb->buf = NULL;
	}
	efree(outb->cpbuf.buf);
	if (outb->is_malloced)
		efree(outb);
}
