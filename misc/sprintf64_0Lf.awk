#
#	sprintf64_0Lf.awk -- format integers stored as long doubles and
#	don't have %Lf in (s)printf. This test script handles integers < 2^64.
#	Requires both -M (for verification) and -B
#	Usage:
#		echo "2^63 + 2^54 + 2^13" | ./gawk -B -f misc/sprintf_0Lf.awk
#

BEGIN {
	# 113 for 128-bit long double, but can only get 64-bit ints.
	LDBL_MANT_DIG = 64
	POW2[0] = 1
	for (i = 1; i <= LDBL_MANT_DIG; i++)
		POW2[i] = POW2[i - 1] * 2
}

{
	#
	# Compare apples to apples, setting PREC=64; With real 128-bit long doubles,
	# one probably should use PREC=quad or 113.
	# %0.34e ain't the right format but then ..
	#

	eval = sprintf("./gawk -M -vPREC=64 'BEGIN { printf(\"%%0.34e\", %s); print \"\";\
		printf(\"%%020d\", %s); print \"\";\
		printf(\"%%d\", int(%s) == %s + 0); print \"\"}'", $0, $0, $0, $0)
	eval | getline num
	eval | getline ap_intval
	eval | getline ap_isint
	close(eval)

	pnum = num + 0
	sign = ""
	if (pnum < 0) {
		pnum = -pnum
		sign = "-"
	}

	isint = isinteger(pnum, chunk16)
	if (isint) {
		if (! ap_isint)
			print "!!!!!!!!!MPFR says it is not an integer!!!!!!!!!"
		printf("%s (%s) is an integer\n", $0, sprintf("%0.34e", num))
		printf("sprintf_int64  :%c%s\n", sign, sprintf_int64(chunk16))
		printf("arbitrary-prec :%s\n", ap_intval)
		printf("LDBL %%0.Lf     :%c%020d\n", sign, pnum)	# or garbage if no %Lf
	} else {
		if (ap_isint)
			print "!!!!!!!!!MPFR says it is an integer!!!!!!!!!"
		printf("%s (%s) is not an integer\n", $0, sprintf("%0.34e", num))
	}

#
#	Don't have %Lf ! 
#	printf("floor = %d\n", floor(num))
#	printf("ceil  = %d\n", ceil(num))
#
	# use MPFR to format floor(), ceil() returned values
	eval = sprintf("./gawk -M -vPREC=64 'BEGIN { printf(\"%%d\", %s); print \"\";\
		printf(\"%%d\", %s); print \"\"; }'", floor(num), ceil(num))
	eval | getline floor_val
	eval | getline ceil_val
	close(eval)

	print "floor =", floor_val
	print "ceil  =", ceil_val
}


function sprintf_int64(chunk,	d0, d1, d2, d3, d4, q, k, dec_base)
{
	#
	# Binary to Decimal Conversion in Limited Precision - Douglas B. Jones
	# URL: homepage.cs.uiowa.edu/~jones/bcd/decimal.html
	#

	dec_base = 10000

	if (DEBUG) {
		for (k = 0; k < 4; k++) {
			if (chunk[k] > 65535)
				printf("chunk[%d] > 65535, this ain't right\n", k)
		}
		print "(16 MSB bits first):", chunk[3], "|", chunk[2], "|", chunk[1], "|", chunk[0]
	}

        d0 = 656 * chunk[3] + 7296 * chunk[2] + 5536 * chunk[1] + chunk[0];

        q = int(d0 / dec_base);	# int() may call floorl(), but double version is good enough
	                        # in this case. This is only a consideration in the awk code,
				# not in the C translation.

        d0 = d0 - q * dec_base;	# not using % operator, may not have fmodl()

        d1 = q + 7671 * chunk[3] + 9496 * chunk[2] + 6 * chunk[1];
        q = int(d1 / dec_base);
        d1 = d1 - q * dec_base;

        d2 = q + 4749 * chunk[3] + 42 * chunk[2];
        q = int(d2 / dec_base);
        d2 = d2 - q * dec_base;

        d3 = q + 281 * chunk[3];
        q = int(d3 / dec_base);
        d3 = d3 - q * dec_base;

        d4 = q;
	return sprintf("%4.4u%4.4u%4.4u%4.4u%4.4u", \
			d4, d3, d2, d1, d0); 	# don't need %Lf support here
}


function floor(x,	d, sign, chunk)
{
	x = +x

#
#	if (isnan(x) || isinf(x) || x == 0)
#		return x

	sign = 1
	if (x < 0) {
		sign = -1
		x = -x
	}

	#
	# For x >= 2^LDBL_MANT_DIG, use floor for C-double. Bailing out here.
	#

	if (x >= POW2[LDBL_MANT_DIG]) {
		printf("number %0.34e is too big (> %0.34e), bailing out\n", x, 2^64 - 1)
		exit(1);
	}

	isinteger(x, chunk)

	# d is long double type
	d = chunk[3] * POW2[48] + chunk[2] * POW2[32] + chunk[1] * POW2[16] + chunk[0]

	if (d == x)
		return sign * d
	return (sign > 0) ? d : -d - 1
}


function ceil(x,	d, sign, chunk)
{
	x = +x

#
#	if (isnan(x) || isinf(x) || x == 0)
#		return x

	sign = 1
	if (x < 0) {
		sign = -1
		x = -x
	}

	#
	# For x >= 2^LDBL_MANT_DIG, use ceil for C-double. Bailing out here.
	#

	if (x >= POW2[LDBL_MANT_DIG]) {
		printf("number %0.34e is too big (> %0.34e), bailing out\n", x, 2^64 - 1)
		exit(1);
	}

	isinteger(x, chunk)
	# d is long double type
	d = chunk[3] * POW2[48] + chunk[2] * POW2[32] + chunk[1] * POW2[16] + chunk[0]

	if (d == x)
		return sign * d
	return (sign > 0) ? d + 1 : -d
}


function isinteger(x, D,	j, low, high)
{
	# Assume x >= 0

	#
	# FIXME --  x >= 2^LDBL_MANT_DIG; C-double test is adequate, these integers have same representations.
	#	output maybe incorrect anyway.
	#

	if (x >= POW2[LDBL_MANT_DIG]) {
		printf("number %0.34e is too big (> %0.34e), bailing out\n", x, 2^64 - 1)
		exit(1);
	}

	D[0] = D[1] = D[2] = D[3] = 0
 
	# binary search
	high = LDBL_MANT_DIG - 1
	while (x >= 2) {
		low = 0
		while (low <= high) {
			mid = int((low + high) / 2)
			if (x < POW2[mid])
				high = mid - 1
			else
				low = mid + 1
		}

		if (x < POW2[low]) {
			x -= POW2[low - 1]

			#
			# Easier to seperate the 64 bits into 16-bit chunks now
			# then bit fiddling later.
			#	| D[3] | D[2] | D[1] | D[0] |
			#	|<------- x (64 bits) ----->|
			#

			if (low <= 16) { D[0] += POW2[low - 1] }
			else if (low <= 32) { D[1] += POW2[low - 17] }
			else if (low <= 48) { D[2] += POW2[low - 33] }
			else { D[3] += POW2[low - 49] }
		}

		high = low
	}

#
#	# XXX -- O(n^2) vs. O(n * log(n))  -- how much do we really gain?
#	# 	Consider extra additions and divisions, but lower # of < comparisons.
#
#	while (x >= 2) {
#		for (j = 1; j <= LDBL_MANT_DIG; j++) {
#			if (x < POW2[j]) {
#				x -= POW2[j - 1]
#				break
#			}
#		}
#	}
#

	if (x >= 1) {
		D[0]++
		x -= 1
	}
	return (x == 0)
}

