/*
 * gawk_math.c - routines for replacement AWKLDBL math functions.
 */

/* 
 * Copyright (C) 2013 the Free Software Foundation, Inc.
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

static AWKLDBL
gawk_sinl(AWKLDBL x)
{
	return sin( (double) x);
}

static AWKLDBL
gawk_cosl(AWKLDBL x)
{
	return cos( (double) x);
}

static AWKLDBL
gawk_atan2l(AWKLDBL y, AWKLDBL x)
{
	return atan2( (double) y, (double) x);
}

static AWKLDBL
gawk_logl(AWKLDBL x)
{
	return log( (double) x);
}

static AWKLDBL
gawk_expl(AWKLDBL x)
{
	return exp( (double) x);
}

static AWKLDBL
gawk_fmodl(AWKLDBL x, AWKLDBL y)
{
	return fmod( (double) x, (double) y);
}

static AWKLDBL
gawk_powl(AWKLDBL x, AWKLDBL y)
{
	return pow( (double) x, (double) y);
}

static AWKLDBL
gawk_sqrtl(AWKLDBL x)
{
	return sqrt( (double) x);
}
