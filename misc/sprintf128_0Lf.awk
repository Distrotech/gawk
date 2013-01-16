#
#	sprintf128_0Lf.awk -- format integers stored as long doubles and
#	don't have %Lf in (s)printf.
#	This test script handles integers < 2^113 i.e. 128-bit long doubles.
#	Requires -M -vPREC=113 (or -B if have 128-bit long doubles)
#
#	Usage:
#
#	$ echo "2^113-1" | ./gawk -M -vPREC=113 -f sprintf128_0Lf.awk
#	2^113-1 (1.03845937170696552570609926584401910e+34) is an integer
#	sprintf_int128 :10384593717069655257060992658440191
#	arbitrary-prec :10384593717069655257060992658440191
#	floor = 10384593717069655257060992658440191
#	ceil  = 10384593717069655257060992658440191
#	$ echo "2^113" | ./gawk -M -vPREC=113 -f sprintf128_0Lf.awk
#	2^113 (1.03845937170696552570609926584401920e+34) is an integer
#	sprintf_int128 :10384593717069655257060992658440192
#	arbitrary-prec :10384593717069655257060992658440192
#	floor = 10384593717069655257060992658440192
#	ceil  = 10384593717069655257060992658440192
#	$ echo "2^113+1" | ./gawk -M -vPREC=113 -f sprintf128_0Lf.awk
#	2^113+1 (1.03845937170696552570609926584401920e+34) is an integer
#	sprintf_int128 :10384593717069655257060992658440192 ***
#	arbitrary-prec :10384593717069655257060992658440193 
#	floor = 10384593717069655257060992658440192	***
#	ceil  = 10384593717069655257060992658440192	***
#

BEGIN {
	# Only need 113 for 128-bit long double.

	LDBL_MANT_DIG = 128
	POW2[0] = 1
	for (i = 1; i <= LDBL_MANT_DIG; i++)
		POW2[i] = POW2[i - 1] * 2	
}

{
	#
	# Compare apples to apples, setting PREC=128;
	#

	eval = sprintf("./gawk -M -vPREC=128 'BEGIN { printf(\"%%0.40e\", %s); print \"\";\
		printf(\"%%035d\", %s); print \"\";\
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

	isint = isinteger(pnum, W)
	if (isint) {
		if (! ap_isint)
			print "!!!!!!!!!MPFR says it is not an integer!!!!!!!!!"
		printf("%s (%s) is an integer\n", $0, sprintf("%0.35e", num))
		printf("sprintf_int128 :%c%s\n", sign, sprintf_int128(W))
		printf("arbitrary-prec :%s\n", ap_intval)
	} else {
		if (ap_isint)
			print "!!!!!!!!!MPFR says it is an integer!!!!!!!!!"
		printf("%s (%s) is not an integer\n", $0, sprintf("%0.35e", num))
	}

#
#	Don't have %Lf ! 
#	printf("floor = %d\n", floor(num))
#	printf("ceil  = %d\n", ceil(num))
#
	# use MPFR to format floor(), ceil() returned value
	eval = sprintf("./gawk -M -vPREC=128 'BEGIN { printf(\"%%d\", %s); print \"\";\
		printf(\"%%d\", %s); print \"\"; }'", floor(num), ceil(num))
	eval | getline floor_val
	eval | getline ceil_val
	close(eval)

	print "floor =", floor_val
	print "ceil  =", ceil_val
}


function sprintf_int128(chunk,		d0, d1, d2, d3, d4, q, k, dec_base)
{
	#
	# Binary to Decimal Conversion in Limited Precision - Douglas B. Jones
	# URL: homepage.cs.uiowa.edu/~jones/bcd/decimal.html
	#

	#
	# Results from the application of the idea in the article to the 128-bit conversion
	# problem:
	#
	# Divide a 128-bit number into 32-bit chunks, and use 10,000,000 as the
	# working decimal base. This gives us 7 digits per chunk, and 35 total decimal digits.
	# Using the notations used in the article,
	#
	#	a3 = 79228162 n3
	#	a2 = 5142643 n3 + 184467 n2
	#	a1 = 3400832 n3 + 4407370 n2 + 429 n1
	#	a0 = 3585223950336 n3 + 9551616 n2 + 4967296 n1 + 1 n0
	#
	#	n3, n2, n1 and n0 are the 32-bit chunks, n3 represents the most
	#	significant 32 bits. Assuming these chunks are at their maximum possible
	#	value, which is 2^32: 
	#
	#	UINT64_MAX = 18446744073709551616
	#	a3        <= 340282364712189952
	#	a2        <= 22879763232194560
	#	a1        <= 33537814771531776
	#	a0        <= 15398481973785556680704
	#	c1        <= 1539848197378555
	#	c2        <= 3507766296
	#	c3        <= 2287976673
	#
	#	c1, c2 and c3 are carries from one digit position to the next
	#	(results from integer divisions by the decimal base; see below).
	#
	#	The maximum value of a0 is > UINT64_MAX. If we restrict n3 to be
	#	in the range 0 < n3 < 2^17, corresponding to the 113-bit precision available
	#	from a 128-bit long double, we instead get these upper bounds:
	#
	#	UINT64_MAX = 18446744073709551616
	#	a3        <= 10384593649664
	#	a2        <= 792953788694528
	#	a1        <= 18931798306193408
	#	a0        <= 532280730126909440
	#	c1        <= 53228073012
	#	c2        <= 1893185153
	#	c3        <= 79295568
	#
	# 	We can use 64-bit signed or unsigned long type! QED.
	#
	#	All these numbers calculated using the script misc/bin2dec.awk. 
	#
 

	dec_base = 10000000

	if (DEBUG) {
		for (k = 0; k < 4; k++) {
			if (chunk[k] > 4294967296)
				printf("chunk[%d] > 4294967296, this ain't right\n", k)
		}
		print "(32 MSB bits first):", chunk[3], "|", chunk[2], "|", chunk[1], "|", chunk[0]
	}

        d0 = 3585223950336 * chunk[3] + 9551616 * chunk[2] + 4967296 * chunk[1] + chunk[0];

        q = int(d0 / dec_base);	# int() may call floorl(), but double version is good enough
	                        # in this case. This is only a consideration in the awk code,
				# not in the C translation.

        d0 = d0 - q * dec_base;	# not using % operator, may not have fmodl()

        d1 = q + 3400832 * chunk[3] + 4407370 * chunk[2] + 429 * chunk[1];
        q = int(d1 / dec_base);
        d1 = d1 - q * dec_base;

        d2 = q + 5142643 * chunk[3] + 184467 * chunk[2];
        q = int(d2 / dec_base);
        d2 = d2 - q * dec_base;

        d3 = q + 79228162 * chunk[3];
        q = int(d3 / dec_base);
        d3 = d3 - q * dec_base;

        d4 = q;
	return sprintf("%7.7u%7.7u%7.7u%7.7u%7.7u", \
			d4, d3, d2, d1, d0); 	# don't need %Lf support here
}

function floor(x,	d, sign, chunk, isint)
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
		printf("number %0.35e is too big (> %0.35e), bailing out\n", x, POW2[LDBL_MANT_DIG] - 1)
		exit(1);
	}

	isint = isinteger(x, chunk)

	# d is long double type
	d = chunk[3] * POW2[96] + chunk[2] * POW2[64] + chunk[1] * POW2[32] + chunk[0]

	if (isint)	# d == x
		return sign * d
	return (sign > 0) ? d : -d - 1
}


function ceil(x,	d, sign, chunk, isint)
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
		printf("number %0.35e is too big (> %0.35e), bailing out\n", x, POW2[LDBL_MANT_DIG] - 1)
		exit(1);
	}

	isint = isinteger(x, chunk)
	# d is long double type
	d = chunk[3] * POW2[96] + chunk[2] * POW2[64] + chunk[1] * POW2[32] + chunk[0]

	if (isint)	# d == x
		return sign * d
	return (sign > 0) ? d + 1 : -d
}


function isinteger(x, D,	j, low, high)
{
	# x >= 0

	if (x >= POW2[LDBL_MANT_DIG]) {
		printf("number %0.40e is too big (> %0.40e), bailing out\n", x, 2^LDBL_MANT_DIG - 1)
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
			# Easier to seperate the 128 bits into 32-bit chunks now
			# then bit fiddling later.
			#	| D[3] | D[2] | D[1] | D[0]  |
			#	|<------- x (128 bits) ----->|
			#

			if (low <= 32) { D[0] += POW2[low - 1] }
			else if (low <= 64) { D[1] += POW2[low - 33] }
			else if (low <= 96) { D[2] += POW2[low - 65] }
			else { D[3] += POW2[low - 97] }
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

