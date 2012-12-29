/*
 * long_double.h - math functions and replacements with long double arguments.
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

#ifdef HAVE_SINL
#define gawk_sinl	sinl
#else
static inline long double
gawk_sinl(long double x)
{
	return sin( (double) x);
}
#endif

#ifdef HAVE_COSL 
#define gawk_cosl	cosl
#else
static inline long double
gawk_cosl(long double x)
{
	return cos( (double) x);
}
#endif

#ifdef HAVE_ATAN2L
#define gawk_atan2l	atan2l
#else
static inline long double
gawk_atan2l(long double y, long double x)
{
	return atan2( (double) y, (double) x);
}
#endif

#ifdef HAVE_LOGL
#define gawk_logl	logl
#else
static inline long double
gawk_logl(long double x)
{
	return log( (double) x);
}
#endif

#ifdef HAVE_EXPL
#define gawk_expl	expl
#else
static inline long double
gawk_expl(long double x)
{
	return exp( (double) x);
}
#endif

#ifdef HAVE_FMODL
#define gawk_fmodl	fmodl
#else
static inline long double
gawk_fmodl(long double x, long double y)
{
	return fmod( (double) x, (double) y);
}
#endif

#ifdef HAVE_STRTOLD
#define gawk_strtold	strtold
#else
static inline long double
gawk_strtold(const char *str, char **endptr)
{
	return strtod(str, endptr);
}
#endif

#ifdef HAVE_FLOORL
#define gawk_floorl	floorl
#else
static inline long double
gawk_floorl(long double x)
{
	return floor( (double) x);
}
#endif

#ifdef HAVE_CEILL
#define gawk_ceill	ceill
#else
static inline long double
gawk_ceill(long double x)
{
	return ceil( (double) x);
}
#endif

#ifdef HAVE_POWL
#define gawk_powl	powl
#else
static inline long double
gawk_powl(long double x, long double y)
{
	return pow( (double) x, (double) y);
}
#endif

#ifdef HAVE_SQRTL
#define gawk_sqrtl	sqrtl
#else
static inline long double
gawk_sqrtl(long double x)
{
	return sqrt( (double) x);
}
#endif
