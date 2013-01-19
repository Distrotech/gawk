#	bin2dec.awk --- Calculate the magic numbers in: 
#		Binary to Decimal Conversion in Limited Precision - Douglas B. Jones
# 		URL: homepage.cs.uiowa.edu/~jones/bcd/decimal.html
#
#	Usage: ./gawk -M -f misc/bin2dec.awk
#

BEGIN {
	UINT32_MAX = 4294967296
	UINT64_MAX = 18446744073709551616

	N = 4 	# number of chunks

##	64-bit integers
#	CHUNK_SIZE = CHUNK3_SIZE = 16
#	DEC_BASE = 10000	# 4 decimal digits per chunk, 20 total

##	96-bit integers
#	CHUNK_SIZE = CHUNK3_SIZE = 24
#	DEC_BASE = 10000000	# 7 decimal digits per chunk, 35 total

#	128-bit integers
	CHUNK_SIZE = 32
	CHUNK3_SIZE = 17        # the useful size of the first (MSB) chunk <= CHUNK_SIZE
	                        # 17 + 32 + 32 + 32 = 113, precision of real 128-bit double
	DEC_BASE = 10000000	# 7 decimal digits per chunk, 35 total

######################################################

	CHUNK_MAX = 2^CHUNK_SIZE
	CHUNK3_MAX = 2^CHUNK3_SIZE

	print "CHUNK_SIZE = ", CHUNK_SIZE
	print "N = ", N
	print "DEC_BASE = ", DEC_BASE

	# powers of 2^CHUNK_SIZE
	POWER_2_C[0] = 1
	for (i = 1; i < N; i++)
		POWER_2_C[i] = 2 ^(CHUNK_SIZE * i)

	# powers of DEC_BASE
	POWER_BASE[0] = 1
	for (i = 1; i < N; i++)
		POWER_BASE[i] = DEC_BASE^i

	coeff[N-1][N-1] = int(POWER_2_C[N-1] / POWER_BASE[N-1])
	for (i = N-2; i >= 0; i--) {
		for (k = N-1; k >= i; k--) {
			coeff[i][k] = int(POWER_2_C[k]/POWER_BASE[i])
			for (m = 1; m <= k - i; m++)
				coeff[i][k] -= POWER_BASE[m] * coeff[m + i][k]
		}
	}

	for (i = N - 1; i >= 0; i--) {
		for (j = N - 1; j >= i; j--) {
			printf("%d ", coeff[i][j])
		}
		print "";
	}

	print "----- a0, a1, a2, a4 upper bounds -----"
	print "UINT32_MAX =", UINT32_MAX
	print "UINT64_MAX =", UINT64_MAX
	for (i = N - 1; i >= 0; i--) {
		a[i] = 0;
		for (j = N - 1; j >= i; j--) {
			if (j == 3)
				a[i] += coeff[i][j] * CHUNK3_MAX
			else
				a[i] += coeff[i][j] * CHUNK_MAX
		}
		printf("a%d        <= %d\n", i, a[i])
	}

	print "----- c1, c2, c3 upper bounds -----"
	c[0] = 0
	for (i = 1; i < N; i++) {
		c[i] = (a[i - 1] + c[i - 1])/ DEC_BASE
		printf("c%d        <= %d\n", i, c[i])
	}
}
