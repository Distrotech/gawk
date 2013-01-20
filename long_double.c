/*
 * long_double.c - routines for C long double support in gawk.
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

#ifdef USE_LONG_DOUBLE

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

/*
 * XXX: LDBL_MANT_DIG is defined if we are here. Assume FLT_RADIX = 2 or 16.
 */
#if FLT_RADIX == 2
#define LDBL_FRAC_BITS LDBL_MANT_DIG
#else
#define LDBL_FRAC_BITS (4 * LDBL_MANT_DIG)
#endif

/*
 * N.B: If printf does not have "%Lf" format and the long double type is capable of
 * supporting integers wider than 64 bits, must have 64-bit long type.
 *
 * We actually use a maximum of 113 bits when LDBL_INT_BITS is 128.
 */

#if SIZEOF_GAWK_INT == 8 && LDBL_FRAC_BITS > 64
#define	LDBL_INT_BITS	128
#else
#define	LDBL_INT_BITS	64
#endif

#define get_long_double(d) 	getblock(d, BLOCK_LDBL, AWKLDBL *)
#define free_long_double(d)	freeblock(d, BLOCK_LDBL)

#ifdef HAVE_SINL
#define gawk_sinl	sinl
#else
static inline AWKLDBL
gawk_sinl(AWKLDBL x)
{
	return sin( (double) x);
}
#endif

#ifdef HAVE_COSL 
#define gawk_cosl	cosl
#else
static inline AWKLDBL
gawk_cosl(AWKLDBL x)
{
	return cos( (double) x);
}
#endif

#ifdef HAVE_ATAN2L
#define gawk_atan2l	atan2l
#else
static inline AWKLDBL
gawk_atan2l(AWKLDBL y, AWKLDBL x)
{
	return atan2( (double) y, (double) x);
}
#endif

#ifdef HAVE_LOGL
#define gawk_logl	logl
#else
static inline AWKLDBL
gawk_logl(AWKLDBL x)
{
	return log( (double) x);
}
#endif

#ifdef HAVE_EXPL
#define gawk_expl	expl
#else
static inline AWKLDBL
gawk_expl(AWKLDBL x)
{
	return exp( (double) x);
}
#endif

#ifdef HAVE_FMODL
#define gawk_fmodl	fmodl
#else
static inline AWKLDBL
gawk_fmodl(AWKLDBL x, AWKLDBL y)
{
	return fmod( (double) x, (double) y);
}
#endif

#ifdef HAVE_STRTOLD
#define gawk_strtold	strtold
#else
static inline AWKLDBL
gawk_strtold(const char *str, char **endptr)
{
	return strtod(str, endptr);
}
#endif

#ifdef HAVE_POWL
#define gawk_powl	powl
#else
static inline AWKLDBL
gawk_powl(AWKLDBL x, AWKLDBL y)
{
	return pow( (double) x, (double) y);
}
#endif

#ifdef HAVE_SQRTL
#define gawk_sqrtl	sqrtl
#else
static inline AWKLDBL
gawk_sqrtl(AWKLDBL x)
{
	return sqrt( (double) x);
}
#endif


#if ! defined(PRINTF_HAS_LF_FORMAT)
#ifdef HAVE_FLOORL
#undef HAVE_FLOORL
#endif
#ifdef HAVE_CEILL
#undef HAVE_CEILL
#endif
#else	/* PRINTF_HAS_LF_FORMAT */

/*
 * XXX: have "%Lf" but no floorl() and/or ceill(). ceill() (or ceil() for
 * double) isn't really needed.
 */

#if ! (defined(HAVE_FLOORL) && defined(HAVE_CEILL))
#ifdef HAVE_FLOORL
#undef HAVE_FLOORL
#endif
#ifdef HAVE_CEILL
#undef HAVE_CEILL
#endif
#endif	/* ! (HAVE_FLOORL && HAVE_CEILL) */ 
#endif	/* PRINTF_HAS_LF_FORMAT */

#if ! defined(PRINTF_HAS_LF_FORMAT)
static int format_float_1(char *str, size_t size, const char *format, ...);
#else
#define format_float_1	snprintf
#endif

#if ! (defined(HAVE_FLOORL) && defined(HAVE_CEILL))
static AWKLDBL double_to_int(AWKLDBL);
#else

/* double_to_int --- convert double to int, used in several places */

static inline AWKLDBL
double_to_int(AWKLDBL x)
{
	return (x >= LDC(0.0)) ? floorl(x) : ceill(x);
}
#endif

#include "long_double.h"

#else	/* ! USE_LONG_DOUBLE */

static bool awkldbl_init(bltin_t **bltins);

numbr_handler_t awkldbl_hndlr = {
	awkldbl_init,
	NULL,
	NULL,
};

/* awkldbl_init --- initialization routine */

static bool
awkldbl_init(bltin_t **bltins)
{
	*bltins = NULL;
	return false;
}
#endif


numbr_handler_t *
get_ldbl_handler(char *arg)
{
#if defined(LDBLTEST) && LDBLTEST == 1
	extern numbr_handler_t float128_hndlr;
	if (arg != NULL && arg[0] == '1')
		return & float128_hndlr;
#endif
	return  & awkldbl_hndlr;
}
