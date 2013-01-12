# ap_math.awk --- arbitrary-precision math functions

#
#	ap_sin		-- Compute sin(x)
#	ap_cos		-- Compute cos(x)
#	ap_atan2	-- Compute atan2(y, x)
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
# 	atan(1/x) = (x / (1 + x^2))    + (2/3) * (x / (1 + x^2)^2)
#	                               + (2*4/(3*5)) * (x / (1 + x^2)^3)
#	                               + (2*4*6/(3*5*7)) * (x / (1 + x^2)^4)  + ... 
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
		err = term /= xpow2_plus_one
		i += 2
		sum += term
		err = term / sum
	} while (err > __REL_ERROR__)

	return sign * sum
}

function setup_ap_math( \
		prec, curr_prec, digits, extra_prec)
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

	curr_prec = PREC
	extra_prec = 10		# temporarily raise precision by this amount; Why 10???

	# unlike PREC, `prec' is always a number 
	PREC = prec + extra_prec

	if (PREC != __PI_PREC__) {
		# compute PI only once for a given precision
		digits = int (PREC / 3.32193)
		__REL_ERROR__ = sprintf("5.0e-%d", digits) + 0
		__PI_PREC__ = PREC
		__PI_OVER_4__ = 4 * euler_atan_one_over(5) - euler_atan_one_over(239)
	}
	return curr_prec
}

#
# atan2(y, x) =	atan(y/x), 		x > 0
#             =	atan(y/x) + pi,		x < 0, y >= 0
#             =	atan(y/x) - pi,		x < 0, y < 0
#             =	pi/2,			x = 0, y > 0
#             =	-pi/2,			x = 0, y < 0
#             =	?			x = 0, y = 0
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
		return atan2(y, x)	# use builtin, returns +0 or -0
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
	# XXX: this assumes x >= 0

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
	fact = 2
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
#

function ap_sin(x,	\
		k, sign, y, sv, curr_prec)
{
	curr_prec = setup_ap_math()
	x = + x		# or x += 0.0 or x = x + 0.0 
	if (x == "+inf" + 0 || x == "-inf" + 0 ||
			x == "+nan" + 0 || x == "-nan" + 0)
		return "nan" + 0

	if (x < 0) {
		# sin(-x) = - sin(x)
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

	PREC = curr_prec
	return +sv;	# unary plus returns a number with current precision 
}

#
# Using Taylor series approximation for sin(x) for 0 <= x <= PI/4:
#	1 - x^2/2! + x^4/4! - ...
# for PI/4 < x < PI/2, use identity cos(x) = sin(PI/2 - x).
#


function ap_cos(x,	\
		k, sign, y, cv, curr_prec)
{
	curr_prec = setup_ap_math()

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

	PREC = curr_prec
	return +cv	# unary plus to apply current precision
}

function ap_atan2(y, x, \
		tv, curr_prec)
{
	curr_prec = setup_ap_math()
	tv = euler_atan2(y, x)

	PREC = curr_prec
	return +tv	# unary plus to apply current precision
}
