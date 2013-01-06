# repl_math.awk --- arbitrary-precision math functions

#
#	repl_sin	-- Compute sin(x)
#	repl_cos	-- Compute cos(x)
#	repl_atan2	-- Compute atan2(y, x)
#

#
# Machin's formula to compute pi (http://mathworld.wolfram.com/MachinsFormula.html):
#	pi / 4 = 4 acot(5) - acot(239)
#	      = 4 atan(1/5) - atan(1/239)
#
# Euler atan formula (http://mathworld.wolfram.com/InverseTangent.html):
#	atan(x) = (y/x) (1 + 2/3 y + (2·4)/(3·5) y^2 + (2·4·6)/(3·5·7) y^3 +...)
# where
#	y = (x^2) / (1 + x^2) and -1 <= x <= 1
#
# Substituting x = 1/x, for x >= 1
# 	atan(1/x) = (1 / (1 + x^2))    + (2/3) * (1 / (1 + x^2)^2)
#	                               + (2*4/(3*5)) * (1 / (1 + x^2)^3)
#	                               + (2*4*6/(3*5*7)) * (1 / (1 + x^2)^4)  + ... 
#

function euler_atan_one_over(x,	\
		xpow2_plus_one, term, sum, i, err)
{
	xpow2_plus_one = x * x + 1
	term = x / xpow2_plus_one
	sum = term
	i = 0
	err = 1.0

	while (err > __EPSILON__) {
		term *= (i + 2) / (i + 3)
		err = term /= xpow2_plus_one
		i += 2
		sum += term
		if (err < 0)
			err = -err
	}
	return sum
}

function setup_repl_math( \
		prec, digits, extra_prec)
{
	switch (PREC) {
	case "half":	prec = 11; break;
	case "single":	prec = 24; break;
	case "double":	prec = 53; break;
	case "quad":	prec = 113; break;
	case "oct":	prec = 237; break;
	default:	prec = PREC + 0;
	}

	if (prec <= 0) {
		# double or long double ?
		print "PREC value not specified" > "/dev/stderr"
		exit(1)
	}
	__SAVE_PREC__ = PREC
	extra_prec = 10
	prec += extra_prec	# temporarily raise precision
	if (prec != __PI_PREC__) {
		# compute PI only once for a given precision
		digits = int ((prec - extra_prec) / 3.32193)
		__EPSILON__ = sprintf("1.0e-%d", digits + 2) + 0
		__PI_OVER_4__ = 4 * euler_atan_one_over(5) - euler_atan_one_over(239)
		__PI_PREC__ = prec
	}
}

#
# atan2(y, x) =	atan(y/x), 		x > 0
#             =	atan(y/x) + pi,		x < 0, y >= 0
#             = atan(y/x) - pi,		x < 0, y < 0
#             = pi/2,			x = 0, y > 0
#             = -pi/2,			x = 0, y < 0
#             = ?			x = 0, y = 0
#

function euler_atan2(y, x,	\
		sign, plus_inf, minus_inf)
{
	# Using Euler atan(1/x) and the identity:
	# 	atan(x) = - pi / 2 - atan(1/x),		x < 0
	#       	= pi / 2 - atan(1/x),		x > 0

	plus_inf = "+inf" + 0
	minus_inf = "-inf" + 0

	# detect all the "abnormal" cases first
	x = + x			# or x += 0.0 or x = x + 0.0
	y = + y
	if (x == "+nan" + 0 || x == "-nan" + 0 ||
			y == "+nan" + 0 || y == "-nan" + 0)
		return "nan" + 0

	if (y == plus_inf) {
		if (x == minus_inf)
			return 3 * __PI_OVER_4__
		else if (x == plus_inf)
			return __PI_OVER_4__
		else
			return 2 * __PI_OVER_4__
	} else if (y == minus_inf) {
		if (x == minus_inf)
			return - 3 * __PI_OVER_4__
		else if (x == plus_inf)
			return - __PI_OVER_4__
		else
			return - 2 * __PI_OVER_4__
	}

	if (x == plus_inf)
		return atan2(y, x)	# use builtin, -0 or -0
	if (x == minus_inf) {
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
	} else if (x < 0) {
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

	# x == +0/-0 and y == +0/-0
	return atan2(y, x);	# use builtin
}


function taylor_sin(x,	\
		i, fact, xpow2, xpow_odd, sum, term, sign, err)
{
	i = 1
	fact = 1
	xpow2 = x * x
	xpow_odd = x
	sum = x
	sign = 1
	err = 1.0

	while (err > __EPSILON__) {
		fact *= (i + 1) * (i + 2)
		i += 2
		xpow_odd *= xpow2
		sign *= -1
		err = term = xpow_odd / fact  * sign
		sum += term
		if (err < 0)
			err = -err
	}
	return sum
}

function taylor_cos(x,	\
		i, fact, xpow2, xpow_even, sum, term, sign, err)
{
	i = 0
	fact = 1
	xpow2 = x * x
	xpow_even = 1
	sum = 1
	sign = 1
	err = 1.0

	while (err > __EPSILON__) {
		fact *= (i + 1) * (i + 2)
		i += 2
		xpow_even *= xpow2
		sign *= -1
		err = term = xpow_even / fact * sign
		sum += term
		if (err < 0)
			err = -err
	}
	return sum
}

#
# For 0 <= x <= PI/4, using Taylor series approximation for sin(x):
#	x - x^3/5! + x^5/7! - ...
#
# for PI/4 < x <= PI/2, use identity sin(x) = cos(PI/2 - x).
#
#

function repl_sin(x,	\
		k, sign, y, sv)
{
	setup_repl_math()
	x = + x		# or x += 0.0 or x = x + 0.0 
	if (x == "+inf" + 0 || x == "-inf" + 0 ||
			x == "+nan" + 0 || x == "-nan" + 0)
		return "nan" + 0

	if (x < 0) {
		# sin(x) = - sin(x)
		sign = -1
		x = -x
	} else
		sign = 1

	# range reduction -- 0 <= y <= pi / 4

	k = int(x / __PI_OVER_4__)
	sign *= ( int(k / 4) % 2 ? -1 : 1 )
	switch (k % 4) {
	case 0:	y = x - k * __PI_OVER_4__; sv = taylor_sin(y); break;
	case 1:	y = (k + 1) * __PI_OVER_4__ - x; sv = taylor_cos(y); break;
	case 2:	y = x - k * __PI_OVER_4__; sv = taylor_cos(y); break;
	case 3:	y = (k + 1) * __PI_OVER_4__ - x; sv = taylor_sin(y); break;
	}
	sv *= sign

	PREC = __SAVE_PREC__
	return +sv;	# unary plus returns a number with current precision 
}

#
# Using Taylor series approximation for sin(x) for 0 <= x <= PI/4:
#	1 - x^2/2! + x^4/4! - ...
# for PI/4 < x < PI/2, use identity cos(x) = sin(PI/2 - x).
#


function repl_cos(x,	\
		k, sign, y, cv)
{
	setup_repl_math()

	x = + x		# or x += 0.0 or x = x + 0.0
	if (x == "+inf" + 0 || x == "-inf" + 0 ||
			x == "+nan" + 0 || x == "-nan" + 0)
		return "nan" + 0

	if (x < 0)	# cos(x) = cos(-x)
		x = -x

	# range reduction -- 0 <= y <= pi / 4

	k = int(x / __PI_OVER_4__)
	sign = ( int(k / 4) % 2 ? -1 : 1 )
	switch (k % 4) {
	case 0:	y = x - k * __PI_OVER_4__; cv = taylor_cos(y); break;
	case 1:	y = (k + 1) * __PI_OVER_4__ - x; cv = taylor_sin(y); break;
	case 2:	y = x - k * __PI_OVER_4__; cv = -taylor_sin(y); break;
	case 3:	y = (k + 1) * __PI_OVER_4__ - x; cv = -taylor_cos(y); break;
	}
	cv *= sign

	PREC = __SAVE_PREC__
	return +cv	# unary plus to apply current precision
}

function repl_atan2(y, x, \
		tv)
{
	setup_repl_math()
	tv = euler_atan2(y, x)

	PREC = __SAVE_PREC__
	return +tv	# unary plus to apply current precision
}
