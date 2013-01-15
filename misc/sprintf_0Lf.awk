#
#	sprintf_0Lf.awk -- format integers stored as long doubles and
#	don't have %Lf in (s)printf.
#	This test script handles integers < 2^64 even with 128-bit long doubles.
#	Requires both -M (for verification) and -B
#	Usage: echo "2^63 + 2^54 + 2^13" | ./gawk -B -f misc/sprintf_0Lf.awk
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

	isint = isinteger(pnum, W)
	if (isint) {
		if (! ap_isint)
			print "!!!!!!!!!MPFR says it is not an integer!!!!!!!!!"
		printf("%s (%s) is an integer\n", $0, sprintf("%0.34e", num))
		printf("sprintf_int64  :%c%s\n", sign, sprintf_int64(W))
		printf("arbitrary-prec :%s\n", ap_intval)
		printf("LDBL %%0.Lf     :%c%020d\n", sign, pnum)	# or garbage if no %Lf
	} else {
		if (ap_isint)
			print "!!!!!!!!!MPFR says it is an integer!!!!!!!!!"
		printf("%s (%s) is not an integer\n", $0, sprintf("%0.34e", num))
	}
}


function sprintf_int64(d,	d0, d1, d2, d3, d4, q, k)
{
	#
	# Binary to Decimal Conversion in Limited Precision - Douglas B. Jones
	# 	URL: homepage.cs.uiowa.edu/~jones/bcd/decimal.html
	#

	if (DEBUG) {
		for (k = 0; k < 4; k++) {
			if (d[k] > 65535)
				printf("d[%d] > 65535, this ain't right\n", k)
		}
		print "(16 MSB bits first):", d[3], "|", d[2], "|", d[1], "|", d[0]
	}

        d0 = 656 * d[3] + 7296 * d[2] + 5536 * d[1] + d[0];

        q = int(d0 / 10000);	# int() may call floorl(), but double version is good enough
	                        # in this case. This is only a consideration in the awk code,
				# not in the C translation.

        d0 = d0 - q * 10000;	# not using % operator, may not have fmodl()

        d1 = q + 7671 * d[3] + 9496 * d[2] + 6 * d[1];
        q = int(d1 / 10000);
        d1 = d1 - q * 10000;

        d2 = q + 4749 * d[3] + 42 * d[2];
        q = int(d2 / 10000);
        d2 = d2 - q * 10000;

        d3 = q + 281 * d[3];
        q = int(d3 / 10000);
        d3 = d3 - q * 10000;

        d4 = q;
	return sprintf("%4.4u%4.4u%4.4u%4.4u%4.4u", \
			d4, d3, d2, d1, d0); 	# don't need %Lf support here
}


function isinteger(x, D,	j, low, high)
{
	# Assume x >= 0

	#
	# XXX: x >= 2^LDBL_MANT_DIG
	# 	test using C-double is adequate at least in the range
	#  	2^LDBL_MANT_DIG <= x <= DBL_MAX; the integers have same
	#	representations. Here in awk code, we simply crap out.
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
			# then doing bit fiddling later.
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
#	# 	Consider extra additions and divisions, but less # of < comparisons.
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

	if (x == 0)
		return 1;
	if (x == 1) {
		if (and(D[0], 1)) {
			######## XXX: MAYBE ADDING A SECOND TIME ??? #######
			print "Opps! there may be a bug in code! D[0] = ", D[0] > "/dev/stderr"
			exit(1)
		}

		D[0]++
		return 1
	}

	return 0
} 
