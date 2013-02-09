# fp_math.awk --- finite precision math functions

#
#	TODO:	* replace all usages of %, and int() or any other math builtin; and() is ok!.
#		  implement double_to_int() and remove floor/ceil.
#


#
# Machin's formula to compute pi (http://mathworld.wolfram.com/MachinsFormula.html):
#	pi / 4 = 4 acot(5) - acot(239)
#	      = 4 atan(1/5) - atan(1/239)
#
# Euler atan formula (http://mathworld.wolfram.com/InverseTangent.html):
#	atan(x) = (y/x) (1 + 2/3 y + (2·4)/(3·5) y^2 + (2·4·6)/(3·5·7) y^3 + ...)
# where
#	y = (x^2) / (1 + x^2) and -1 <= x <= 1
#
# Substituting x = 1/x, for x >= 1
# 	atan(1/x) = (x / (1 + x^2))    + (2/3) * (x / (1 + x^2)^2)
#	                               + (2*4/(3*5)) * (x / (1 + x^2)^3)
#	                               + (2*4*6/(3*5*7)) * (x / (1 + x^2)^4) + ...
#

function euler_atan_one_over(x,	\
		xpow2_plus_one, term, sum, i, sign, err)
{
	sign = 1
	if (x < 0) {
		sign = -1
		x = -x
	}

	xpow2_plus_one = x * x + 1
	term = x / xpow2_plus_one
	sum = term
	i = 0

	do {
		term *= (i + 2) / (i + 3)
		term /= xpow2_plus_one
		i += 2
		sum += term
		err = term / sum
	} while (err > __REL_ERROR__)

	return sign * sum
}

#
# atan2(y, x) =	atan(y/x), 		x > 0
#             =	atan(y/x) + pi,		x < 0, y >= 0
#             =	atan(y/x) - pi,		x < 0, y < 0
#             =	pi/2,			x = 0, y > 0
#             =	-pi/2,			x = 0, y < 0
#             =	?			x = 0, y = 0
#

function fp_atan2(y, x,	\
		sign, plus_inf, minus_inf)
{
	# Using Euler atan(1/x) and the identity:
	# 	atan(x) = - pi / 2 - atan(1/x),		x < 0
	#       	= pi / 2 - atan(1/x),		x > 0

	# detect all the "abnormal" cases first
	x = + x			# or x += 0.0 or x = x + 0.0
	y = + y
	if (isnan(x) || isnan(y))
		return __PLUS_NAN__

	if (y == __PLUS_INF__) {
		if (x == __MINUS_INF__)
			return 3 * __PI_OVER_4__
		else if (x == __PLUS_INF__)
			return __PI_OVER_4__
		else
			return 2 * __PI_OVER_4__
	} else if (y == __MINUS_INF__) {
		if (x == __MINUS_INF__)
			return - 3 * __PI_OVER_4__
		else if (x == __PLUS_INF__)
			return - __PI_OVER_4__
		else
			return - 2 * __PI_OVER_4__
	}

	if (x == __PLUS_INF__)
		return atan2(y, x)	# use builtin, returns +0 or -0
	if (x == __MINUS_INF__) {
		if (y >= 0)
			return 4 * __PI_OVER_4__
		# y < 0
		return - 4 * __PI_OVER_4__
	}

	if (x > 0) {
		if (y == 0)
			return atan2(y, x);	# use builtin; returns +0 or -0
		sign = 1
		if (y < 0) {
			sign = -1
			y = -y
		}
		if (y > x)
			return sign * (2 * __PI_OVER_4__ - euler_atan_one_over(y / x))
		return sign * euler_atan_one_over(x / y)
	}

	if (x < 0) {
		if (y == 0) {
			if (atan2(y, x) < 0)	# use builtin to detect sign
				return - 4 * __PI_OVER_4__
			return 4 * __PI_OVER_4__
		}

		if (y < 0) {
			y = -y
			x = -x
			if (y > x)
				return - 2 * __PI_OVER_4__ - euler_atan_one_over(y / x)
			return euler_atan_one_over(x / y) - 4 * __PI_OVER_4__
		}
		# y > 0
		x = -x
		if (y > x)
			return 2 * __PI_OVER_4__ + euler_atan_one_over(y / x)
		return - euler_atan_one_over(x / y) + 4 * __PI_OVER_4__
	}

	if (atan2(y, x) < 0)	# atan2(-0, -0)
		return - 4.0 * __PI_OVER_4__
	if (atan2(y, x) > 0)	# atan2(+0, -0)
		return 4.0 * __PI_OVER_4__
	return 0;	# atan2(+0, +0) or atan2(-0, 0)
}

#
#	Collect two terms in each iteration for the Taylor series:
#		sin(x) = (x - x^3/3!) + (x^5/5! - x^7/7!) + ...
#

function taylor_sin(x,	\
		i, fact, xpow2, xpow_odd, sum, term, err)
{
	# this assumes x >= 0
	if (x < 0) {
		print "taylor_sin: received x < 0 ! " > "/dev/stderr"
		exit(1)
	}

	if (x == 0)
		return x
	i = 3
	fact = 6	# 3!
	xpow2 = x * x
	xpow_odd = xpow2 * x
	sum = x - xpow_odd / fact

	do {
		fact *= (i + 1) * (i + 2)
		i += 2
		xpow_odd *= xpow2
		term = xpow_odd / fact

		fact *= (i + 1) * (i + 2)
		i += 2
		xpow_odd *= xpow2
		term -= xpow_odd / fact

		sum += term
		err = term / sum
	} while (err > __REL_ERROR__)

	return sum
}

#
#	Collect two terms in each iteration for the Taylor series:
#		cos(x) = (1 - x^2/2!) + (x^4/4! - x^6/6!)...
#

function taylor_cos(x,	\
		i, fact, xpow2, xpow_even, sum, term, err)
{
	if (x == 0)
		return 1

	i = 2
	fact = 2	# 2!
	xpow2 = x * x
	xpow_even = xpow2
	sum = 1 - xpow2 / fact

	do {
		fact *= (i + 1) * (i + 2)
		i += 2
		xpow_even *= xpow2
		term = xpow_even / fact

		fact *= (i + 1) * (i + 2)
		i += 2
		xpow_even *= xpow2
		term -= xpow_even / fact

		sum += term
		err = term / sum
	} while (err > __REL_ERROR__)

	return sum
}

#
# For 0 <= x <= PI/4, using Taylor series approximation for sin(x):
#	x - x^3/3! + x^5/5! - ...
#
# for PI/4 < x <= PI/2, use identity sin(x) = cos(PI/2 - x).
#

function fp_sin(x,	\
		k, sign, y, sv)
{
	x = + x		# or x += 0.0 or x = x + 0.0 
	if (isinf(x) || isnan(x))
		return __PLUS_NAN__
	if (x == 0)
		return x
	
	if (x < 0) {
		# sin(-x) = - sin(x)
		sign = -1
		x = -x
	} else
		sign = 1

	# range reduction -- 0 <= y <= pi / 4

	k = int(x / __PI_OVER_4__)
	sign *= ( int(k / 4) % 2 ? -1 : 1 )

	# XXX --- make sure y >= 0
	switch (k % 4) {
	case 0:	y = x - k * __PI_OVER_4__; sv = taylor_sin(y); break;
	case 1:	y = (k + 1) * __PI_OVER_4__ - x; sv = taylor_cos(y); break;
	case 2:	y = x - k * __PI_OVER_4__; sv = taylor_cos(y); break;
	case 3:	y = (k + 1) * __PI_OVER_4__ - x; sv = taylor_sin(y); break;
	}
	sv *= sign
	return sv; 
}

#
# Using Taylor series approximation for sin(x) for 0 <= x <= PI/4:
#	1 - x^2/2! + x^4/4! - ...
# for PI/4 < x < PI/2, use identity cos(x) = sin(PI/2 - x).
#

function fp_cos(x,	\
		k, sign, y, cv)
{
	x = + x		# or x += 0.0 or x = x + 0.0
	if (isinf(x) || isnan(x))
		return __PLUS_NAN__

	if (x < 0)	# cos(x) = cos(-x)
		x = -x
	if (x == 0)
		return 1.0

	# range reduction -- 0 <= y <= pi / 4

	k = int(x / __PI_OVER_4__)
	sign = ( int(k / 4) % 2 ? -1 : 1 )

	# XXX -- make sure y >= 0
	switch (k % 4) {
	case 0:	y = x - k * __PI_OVER_4__; cv = taylor_cos(y); break;
	case 1:	y = (k + 1) * __PI_OVER_4__ - x; cv = taylor_sin(y); break;
	case 2:	y = x - k * __PI_OVER_4__; cv = -taylor_sin(y); break;
	case 3:	y = (k + 1) * __PI_OVER_4__ - x; cv = -taylor_cos(y); break;
	}
	cv *= sign
	return cv
}

function isinf(x)
{
	x = + x 
	return x == __PLUS_INF__ || x == __MINUS_INF__
}

function isnan(x)
{
	x = + x 
	return x == __PLUS_NAN__ || x == __MINUS_NAN__
}

#################################################################
# Detecting a negative zero in gawk (signbit(x) in C where x is a signed 0):
# $ gawk 'BEGIN { x = -0.0; print atan2(0.0, x) == atan2(-0.0, x)}'
# 0
# $ gawk 'BEGIN { x = 0.0; print atan2(0.0, x) == atan2(-0.0, x)}'
# 1
#
#################################################################

function ispluszero(x)
{
	x = +x
	if (x != 0)
		return 0 
	return atan2(0.0, x) == atan2(-0.0, x)
}

function isminuszero(x)
{
	x = +x
	if (x != 0)
		return 0
	return ! (atan2(0.0, x) == atan2(-0.0, x))
}

#
# Newton-Raphson to calculate higher precision result from already known fixed
# precision value. This usually converges in 2 to 3 iterations.
#

function fp_sqrt(x,	\
		yn, err, last)
{
	if (isnan(x) || x == __PLUS_INF__)
		return x
	if (x == __MINUS_INF__ || x < 0)
		return __MINUS_NAN__	# set errno = EDOM for x < -0?
	if (x == 0)
		return x	# return +0 or -0

	if (x >= DBL_MIN && x <= DBL_MAX)
		yn = sqrt(x) 	# double-precision sqrt
	else {
		frac = frexpl(x, e);	# in [1, 2)
		exponent = e[0]
		if (and(exponent, 1) != 0) {
			frac /= 2
			exponent++
		}
		yn = sqrt(frac)
		exponent /= 2
		if (exponent >= 0)
			yn *= pow2(exponent)
		else
			yn /= pow2(-exponent)
	}

	do {
		last = yn
		yn = (yn + x / yn) \
				/ 2
		err = (yn - last) / yn
		if (err < 0)
			err = -err
	} while (err > __REL_ERROR__)
	return yn
}

# klog2 -- compute k * log2 without loss of precision 

function klog2(k, \
		i, three_pow, sum, err, term)
{
	#
	#	ln(2) = 2 * arctanh(2)
	#	      = 2 * ((1/3) + (1/3)^3 / 3 + (1/3)^5 / 5 + ..) 
	#

	# y = (x - 1) / (x + 1) => y = 1 / 3
	i = 1
	three_pow = 3
	sum = (2 * k) / 3
	do {
		three_pow *= 9
		i += 2
		term = (2 * k) / (three_pow * i)
		sum += term
		err = term / sum
	} while (err > __REL_ERROR__)
	return sum
}


function pow2(n, k)
{
	if (n <= 64)
		return __POW2__[n]
	for (k = 1; n > 64; n -= 64)
		k *= __POW2__[64]
	return k * __POW2__[n]
}


# the returned fraction is normalized in [1, 2) and NOT [0.5, 1)  
# exponent is in e[0]

function frexpl(x, e, \
		y, low, high, mid)
{
	# XXX -- (isnormal(x) && x > 0) is assumed to be true

	low = 0
	if (x > 2) {
		high = LDBL_MAX_EXP - 1
		while (low <= high) {
			mid = int ((low + high) / 2)
			y = x / pow2(mid)
			if (y > 2)
				low = mid + 1
			else
				high = mid - 1
		}
		x /= pow2(low)
		e[0] = low
	} else if (x < 1) {
		high = LDBL_MAX_EXP - 1
		while (low <= high) {
			mid = int ((low + high) / 2)
			y =  x * pow2(mid)
			if (y < 1)
				low = mid + 1
			else
				high = mid - 1
		}
		x *= pow2(low)
		e[0] = -low
	} else
		e[0] = 0

	if (x == 2) {
		x = 1
		e[0]++
	}
	return x	# x in [1, 2)
}


function fp_log(x,	\
		e, exponent, i, ypow2, ypow_odd, sum, err, term, sign)
{
	#
	#	ln(x) = 2 * arctanh(y)
	#	      = 2 * (y + y^3 / 3 + y^5 /5 + ..) where y = (x - 1) / (x + 1) 
	#
	x = +x
	if (isnan(x) || x == __PLUS_INF__)
		return x
	if (x == __MINUS_INF__ || x < 0)	# errno EDOM ?
		return __PLUS_NAN__
	if (x == 0)	# errno ERANGE ?
		return __MINUS_INF__
	
	if (x == 1)	# special case
		return 0
	if (x == 2)	# special case
		return __LOG2__

	x = frexpl(x, e)
	exponent = e[0]

	# arctanh(x) series has faster convergence when x is close to 1
	# range reduction -- 1/sqrt(2) <= x <= sqrt(2)
	if (x > __SQRT_2__ || x < __1_OVER_SQRT_2__) {
		x *= __1_OVER_SQRT_2__
		exponent += 0.5
	}

	y = (x - 1) / (x + 1)
	if (y == 0)	# tricky special case 
		return exponent * __LOG2__;

	sign = 1
	if (y < 0) {
		sign = -1
		y = -y
	}

	i = 1
	ypow2 = y * y
	ypow_odd = y
	sum = y

	do {
		ypow_odd *= ypow2
		i += 2
		term = ypow_odd / i
		sum += term
		err = term / sum
	} while (err > __REL_ERROR__)

	return sign * (sum = 2 * sum + exponent * __LOG2__)
}


function taylor_exp(x,	\
		xpow2, xpow_even, i, fact, cosh, sinh, err, term)
{
	# x < 1
	# cosh(x) = (exp(x) + exp(-x)) / 2 	-- faster convergence than exp(x)
	# sinh(x) = sqrt(cosh(x) * cosh(x) - 1)
	# exp(x) = cosh(x) + sinh(x)

	if (x == 0)
		return 1;
	xpow2 = x * x
	xpow_even = 1
	i = 0
	fact = 1
	cosh = 1

	do {
		fact *= (i + 1) * (i + 2)
		xpow_even *= xpow2
		term = xpow_even / fact
		i += 2
		cosh += term
		err  = term / cosh
	} while (err > __REL_ERROR__)

#	sinh = fp_sqrt(cosh * cosh - 1)	# sqrt is cheap
	z = cosh - 1.0
	sinh = z * fp_sqrt(1 + 2 / z)	
	return (sinh + cosh)
}


function fp_exp(x,	\
		y, exp_val, k, sign)
{
	x = +x
	if (isnan(x) || x == __PLUS_INF__)
		return x
	if (x == __MINUS_INF__)
		return 0

	if (x == 0)	# special case
		return 1
	sign = 1
	if (x < 0) {
		sign = -1
		x = -x
	}

	k = fp_floor(x / __LOG2__)

	# range reduction -- 0 < x < log(2) (0.693...)
	if (k == 0)
		exp_val = taylor_exp(x)
	else {
		y = x - klog2(k)
		exp_val = taylor_exp(y)
		exp_val *= pow2(k)
	}

	return sign < 0 ? (1 / exp_val) : exp_val
}

function isinteger(x)
{
	# assume != NaN or inf
	return fp_floor(x) == fp_ceil(x)
}

function isodd(x)
{
	# assume != NaN or inf
	# XXX -- not using % operator, either fmodl() is missing, or will get into
	#	situation like: fp_fmod() -> isodd() -> fp_fmod() ..

	return isinteger(x) && and(x, 1)
}

function iseven(x)
{
	# assume != NaN or inf
	return isinteger(x) && ! and(x, 1)
}

function fp_abs(x)
{
	# assume != NaN or inf
	return x < 0 ? -x : x
}

function fp_pow(x, y,	\
		i, result, sign)
{
	x = +x
	y = +y
	if ((! isnan(x) && x == 1) || (! isnan(y) && y == 0))
		return 1
	if (isnan(x) || isnan(y))
		return __PLUS_NAN__

	# x or y not NaN
	if (isinf(x)) {
		if (x == __PLUS_INF__) {
			if (y < 0)
				return 0
			if (y > 0)
				return __PLUS_INF__
		}
		# x == -inf
		if (y < 0) {
			if (! isinf(y) && isodd(y))
				return -0.0
			return 0
		}
		if (y > 0) {
			if (! isinf(y) && isodd(y))
				return __MINUS_INF__
			return __PLUS_INF__
		}
		# y == 0 handled above
	} else {
		# x isn't infinity
		if (x < 0 && ! isinf(y) && ! isinteger(y))
			return __PLUS_NAN__

		if (isinf(y)) {
			if (x == -1)
				return 1
			# x == +1 handled above
			if (fp_abs(x) < 1) {
				if (y == __MINUS_INF__)
					return __PLUS_INF__
				return 0
			}
			# fp_abs(x) > 1)
			if (y == __MINUS_INF__)
				return 0
			return __PLUS_INF__
		}
		# y isn't infinity
		if (x == 0 && y > 0) {
			if (isodd(y))
				return x	# +0 or -0
			else
				return 0
		}
		if (x == 0 && y < 0) {
			if (isodd(y)) {
				# HUGE_VALL with same sign as x
				if (ispluszero(x))
					return __PLUS_INF__
				return __MINUS_INF__
			}
			# + HUGE_VALL
			return __PLUS_INF__ 
		}
		# x == 0 && y == 0 handled above 
	}

	if (x < 0) {
		# y is integer, and != 0
		# gawk has special code to handle this; can return junk!
		# XXX: move the special code (at least for x < 0) in gawk_powl instead?
		result = x
		sign = 1
		if (y < 0) {
			sign = -1
			y = -y
		}
		for (i = 1; i < y; i++)
			result *= x
		return sign > 0 ? result : 1 / result
	}

	# x^y =  exp(y * log(x)), x > 0
	return fp_exp(y * fp_log(x))
}


function fp_floor(x,	d)
{
	x = +x
	if (isnan(x) || isinf(x) || x == 0)
		return x
	d = sprintf("%d", x) + 0
	if (x == d || x > 0)
		return d
	return d - 1
}

function fp_ceil(x,	d)
{
	x = +x
	if (isnan(x) || isinf(x) || x == 0)
		return x
	d = sprintf("%d", x) + 0
	if (x == d || x < 0)
		return d
	return d + 1
}

function fp_fmod(x, y, \
		zx, ex, zy, ey, exy, signx, txy, ty)
{
	x = +x
	y = +y
	if (isnan(x) || isnan(y) \
			|| isinf(x) || y == 0)		# errno = EDOM ?
		return __PLUS_NAN__
	if (x == 0)
		return x	# +0 or -0
	if (isinf(y))
		return x

	signx = 1
	if (x < 0) {
		signx = -1
		x = -x
	}

	if (y < 0)
		y = -y

	# x > 0, y > 0

	zy = frexpl(y, e)
	ey = e[0]

	zx = frexpl(x, e)
	ex = e[0]

	exy = ex - ey
	while (exy > 1) {
		while (zx < z1 && exy > 0) {
			zx *= 2;
			ex--;
		}
		if (exy < 0)
			break
		zx -=  zy

		if (exy >= 1024) {
			# avoid overflow in 2^n computation
			txy = exy
			ty = y  
			while (txy >= 1024) {
				ty *= pow2ld(1024)
				txy -= 1024
			}
			x -= pow2ld(txy) * ty
		} else	
			x -= pow2ld(exy) * y
	}

	while (x > y)
		x -= y

	if (signx > 0) {
		if (x < 0)
			x += y
	} else {
		x = -x
		if (x > 0)
			x -= y
	}
	return x
}



# fixprec -- fixes "0.18e" output

function fixprec(str, numdigs, \
		sign, j, exponent, sigdigs, lastdig, nextdig)
{
	if (str ~ /^[-+]?(nan|inf)/)
		return str
	if (! numdigs)
		numdigs = LDBL_DIG
	if (str ~ /^[-+]?0[\.]/)
		return str
	sign = ""
	if (str ~ /^-/) {
		sign = "-"
		str = substr(str, 2)
	} else if (str ~ /^+/) {
		sign = "+"
		str = substr(str, 2)
	}
	sub(/\./, "", str)

	if ((j = index(str, "e-")) > 0) {
		exponent = substr(str, j + 2)
		exponent--
		exponent = sprintf("e-%02d", exponent)
	} else if ((j = index(str, "e+")) > 0) {
		exponent = substr(str, j + 2)
		exponent++
		exponent = sprintf("e+%02d", exponent)
	}
	sigdigs = substr(str, 1, numdigs)
	lastdig = substr(str, numdigs, 1) + 0
	nextdig = substr(str, numdigs + 1, 1) + 0

	# XXX: Don't use % to test even or odd, may not have fmodl() !
	if (nextdig > 5 || (nextdig == 5 && and(lastdig, 1) != 0))
		sub(/[0-9]$/, lastdig + 1, sigdigs)
	return sign "0." sigdigs exponent
}


BEGIN {
	# define some constants

	LDBL_DIG = 33
	# relative error < 5 X 10^-k for rounding to k significant digits
	__REL_ERROR__ = 5.0e-35
	LDBL_MAX_EXP = 16384
	LDBL_MANT_DIG = 113
	DBL_MAX = 1.7976931348623157e+308
	DBL_MIN = 2.2250738585072014E-308

	# We can read hex/octal numbers without using strtod/strtodl
	if (0x10000000000000000 == 0x10000000000000001) {
		# x86 long double
		LDBL_MANT_DIG = 64
		LDBL_DIG = 18
		__REL_ERROR__ = 5.0e-20
	} else if (0x400000000000000000000000000 == 0x400000000000000000000000001) {
		# double-double
		LDBL_MANT_DIG = 106
		LDBL_DIG = 31
		LDBL_MAX_EXP = 309
	}

	__PLUS_INF__ = "+inf" + 0
	__MINUS_INF__ = "-inf" + 0
	__PLUS_NAN__ = "+nan" + 0
	__MINUS_NAN__ = "-nan" + 0

	__SQRT_2__ = fp_sqrt(2)
	__1_OVER_SQRT_2__ = 1 / __SQRT_2__
	__LOG2__ = klog2(1)	# cannot use fp_log()
	__PI_OVER_4__ = 4 * euler_atan_one_over(5) - euler_atan_one_over(239)

	# pre-calculate 2^0 - 2^64
	__POW2__[0] = 1
	for (i = 1; i <= 64; i++)
		__POW2__[i] = __POW2__[i - 1] * 2
}
