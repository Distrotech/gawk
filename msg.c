/*
 * msg.c - routines for error messages.
 */

/* 
 * Copyright (C) 1986, 1988, 1989, 1991-2001, 2003, 2010
 * the Free Software Foundation, Inc.
 * 
 * This file is part of GAWK, the GNU implementation of the
 * AWK Programming Language.
 * 
 * GAWK is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
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

extern NODE *format_tree(const char *, size_t, NODE **, long);	/* format.c */
extern FILE *output_fp;
int sourceline = 0;
char *source = NULL;
static const char *srcfile = NULL;
static int srcline;

jmp_buf fatal_tag;
bool fatal_tag_valid = false;

/* err --- print an error message with source line and file and record */

/* VARARGS2 */
void
err(bool isfatal, const char *s, const char *emsg, va_list argp)
{
	char *file;
	const char *me;

	(void) fflush(output_fp);
	me = myname;
	(void) fprintf(stderr, "%s: ", me);
#ifdef GAWKDEBUG
	if (srcfile != NULL) {
		fprintf(stderr, "%s:%d:", srcfile, srcline);
		srcfile = NULL;
	}
#endif /* GAWKDEBUG */

	if (sourceline > 0) {
		if (source != NULL)
			(void) fprintf(stderr, "%s:", source);
		else
			(void) fprintf(stderr, _("cmd. line:"));

		(void) fprintf(stderr, "%d: ", sourceline);
	}

	if (FNR_node != NULL && (FNR_node->var_value->flags & (NUMBER|NUMCUR)) != 0) {
		NODE *val;
		val = numbr_hndlr->update_numvar(FNR_node);
		if (sgn_number(val) > 0) {	/* positive nonzero number */ 
			file = FILENAME_node->var_value->stptr;
			(void) putc('(', stderr);
			if (file)
				(void) fprintf(stderr, "FILENAME=%s ", file);
			fprintf(stderr, "FNR=%s) ", fmt_number("%d", val));
		}
	}

	(void) fprintf(stderr, "%s", s);
	vfprintf(stderr, emsg, argp);
	(void) fprintf(stderr, "\n");
	(void) fflush(stderr);

	if (isfatal) {
#ifdef GAWKDEBUG
		abort();
#endif
		gawk_exit(EXIT_FATAL);
	}
}


/*
 * fmt_number --- format a number node for use in error messages.
 *
 * N.B: format is awk printf format. MUST NOT generate warning
 * in format_tree(). "%ld" is BAD, "%d" is OK!
 */

const char *
fmt_number(const char *format, const NODE *n)
{
	NODE *dummy[2], *r, *tmp;
	static char *num_str;
	extern bool fmt_ok(const char *p);

	/* FIXME: %d etc -- assert(fmt_ok(format) == true); */
	assert((n->flags & (NUMBER|NUMCUR)) != 0);

	/* copy number so not to change state of the original including flags */
	tmp = numbr_hndlr->gawk_copy_number(n);
	if (num_str != NULL)
		efree(num_str);

	/* create dummy node for sole use of format_tree */
	dummy[1] = tmp;
	r = format_tree(format, strlen(format), dummy, 2);
	assert(r != NULL);
	num_str = r->stptr;
	num_str[r->stlen] = '\0';
	freenode(r);
	unref(tmp);
	return num_str;
}


/* msg --- take a varargs error message and print it */

void
msg(const char *mesg, ...)
{
	va_list args;
	va_start(args, mesg);
	err(false, "", mesg, args);
	va_end(args);
}

/* warning --- print a warning message */

void
warning(const char *mesg, ...)
{
	va_list args;
	va_start(args, mesg);
	err(false, _("warning: "), mesg, args);
	va_end(args);
}

void
error(const char *mesg, ...)
{
	va_list args;
	va_start(args, mesg);
	err(false, _("error: "), mesg, args);
	va_end(args);
}

/* set_loc --- set location where a fatal error happened */

void
set_loc(const char *file, int line)
{
	srcfile = file;
	srcline = line;

	/* This stupid line keeps some compilers happy: */
	file = srcfile; line = srcline;
}

/* r_fatal --- print a fatal error message */

void
r_fatal(const char *mesg, ...)
{
	va_list args;
	va_start(args, mesg);
	err(true, _("fatal: "), mesg, args);
	va_end(args);
}

/* gawk_exit --- longjmp out if necessary */

void
gawk_exit(int status)
{
	if (fatal_tag_valid) {
		exit_val = status;
		longjmp(fatal_tag, 1);
	}

	final_exit(status);
}

/* final_exit --- run extension exit handlers and exit */

void
final_exit(int status)
{
	/* run any extension exit handlers */
	run_ext_exit_handlers(status);

	/* we could close_io() here */
	close_extensions();

	exit(status);
}
