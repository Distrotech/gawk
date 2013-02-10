/*
 * float80.c - 80-bit float without any math routine.
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

#ifdef NUMDEBUG

#include <math.h>
#include "random.h"
#include "floatmagic.h"	/* definition of isnan */

#include "format.h"

#define AWKLDBL	long double
#define LDBL_VAL(n)	(*((AWKLDBL *) (n)->qnumbr))
#define LDC(x)		x##L

#ifndef FLT_RADIX
#define FLT_RADIX 2
#endif

#define GAWK_LDBL_FRAC_BITS	LDBL_MANT_DIG
#define GAWK_LDBL_MAX_EXP	LDBL_MAX_EXP
#define	GAWK_LDBL_INT_BITS	64

#define get_long_double(d)	emalloc(d, void *, sizeof(AWKLDBL), "float80")
#define free_long_double(d)	efree(d)

/* we want to format integers ourself */
#define GAWK_FMT_INT 1

#define gawk_int_t long
#define gawk_uint_t unsigned long
#ifdef SIZEOF_GAWK_INT
#undef SIZEOF_GAWK_INT
#undef GAWK_INT_MAX
#undef GAWK_INT_MIN
#undef GAWK_UINT_MAX
#endif

#define SIZEOF_GAWK_INT	4
#define	GAWK_INT_MAX	LONG_MAX
#define	GAWK_INT_MIN	LONG_MIN
#define	GAWK_UINT_MAX	ULONG_MAX

static int format_uint_finite_p(char *str, size_t size, AWKLDBL x);
static AWKLDBL gawk_floorl_finite_p(AWKLDBL x, gawk_uint_t *chunk);
static int format_float_1(char *str, size_t size, const char *format, int fw, int prec, AWKLDBL x);
static int format_uint_1(char *str, size_t size, AWKLDBL x);
static AWKLDBL double_to_int(AWKLDBL x);

#define gawk_strtold strtold

#define GAWK_INFINITY	HUGE_VALL
#define GAWK_NAN	(LDC(0.0) / LDC(0.0))

/*
 * The relative error need to be less than 5 X 10^-k for rounding to
 * k significant digits.
 */

#define	REL_ERROR	LDC(5.0e-20)

numbr_handler_t float80_hndlr;

#define awkldbl_hndlr float80_hndlr

#ifndef USE_INCLUDED_MATH_FUNCS
#define USE_INCLUDED_MATH_FUNCS
#endif
#ifdef HAVE_FMODL
#undef HAVE_FMODL
static AWKLDBL gawk_fmodl(AWKLDBL x, AWKLDBL y);
#endif

#include "misc/gawk_math.h"
#include "long_double.h"
#include "misc/gawk_math.c"

/*
 * format_float_1 --- format a single AWKLDBL value according to FORMAT.
 *	The value must be finite.	
 */

static int
format_float_1(char *str, size_t size, const char *format, int fw, int prec, AWKLDBL x)
{
	return snprintf(str, size, format, fw, prec, x);
}

/*
 * format_uint_1 --- format a long double as an unsigned integer. The double value
 *	must be finite and >= 0.
 */

static int
format_uint_1(char *str, size_t size, AWKLDBL x)
{
	int ret;
	if ((ret = format_uint_finite_p(str, size, x)) < 0)
		return snprintf(str, size, "%.0Lf", x);
	return ret;
}

/* double_to_int --- convert double to int, used in several places */

static AWKLDBL
double_to_int(AWKLDBL x)
{
	AWKLDBL intval;
	int sign = 1;

	if (isnan(x) || isinf(x) || x == LDC(0.0))
		return x;
	if (x < LDC(0.0)) {
		sign = -1;
		x = -x;
	}
	if ((intval = gawk_floorl_finite_p(x, NULL)) < LDC(0.0)) {
		/* outside range, use floorl() */
		intval = (AWKLDBL) floorl((long double) x);
	}
	return intval * ((AWKLDBL) sign);
}

#endif	/* NUMDEBUG */
