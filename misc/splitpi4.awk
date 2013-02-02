# Split pi/4 into two parts
#	pi_4 = pi_4_high (exact 32-bit)+ pi_4_med (exact 32-bit) +  pi_4_low
#

# $ gawk -M -f splitpi4.awk

BEGIN {
	PREC = 500 

	y = atan2(1, 0) / 2;	# N.B.: integer constants not floats e.g 1.0

	PREC = 32
	pi_4_high = next_down(y)	# exactly representable with 32 bits

	PREC = 500
	y1 = (y - pi_4_high) / 2^32
	PREC = 32
	pi_4_med = next_down(y1)

	PREC = 500
	pi_4_low = (y1 - pi_4_med) / 2^32

	pi_4_med *= 2^32
	pi_4_low *= 2^64

	pi = pi_4_high + pi_4_med + pi_4_low

	printf("pi_4    = %0.112b\n", y)
	printf("pi_4(3) = %0.112b\n", pi)
	printf("pi_4_h  = %0.31b\n", pi_4_high)
	printf("pi_4_m  = %0.31b\n", pi_4_med)
	printf("pi_4_l  = %0.112b\n", pi_4_low)

	printf("pi_4_high  = %0.36f\n", pi_4_high)
	printf("pi_4_med   = %0.36e\n", pi_4_med)
	printf("pi_4_low   = %0.36e\n", pi_4_low)
}

BEGIN {
	# test

	z[0] = "501"
	z[1] = "1.11121e+04"
	z[2] = "1.2172831e+07"
	z[3] = "1.13131311113e+09"
	z[4] = "3.373e+09"
	z[5] = "8.0e+09"
	z[6] = "9.1314152e21"

	print "--- test (PREC=113): r = x - q * (pi/4) ---"
	PREC = 113
	ROUND_MODE = "N"
	pi_h = pi_4_high + 0.0
	pi_m = pi_4_med + 0.0
	pi_l = pi_4_low + 0.0

	for (ii = 0; ii < length(z); ii++) {
		PREC = 113
		x = z[ii];
		x += 0.0
		pi_4 = atan2(1, 0) / 2
		q = int(x / pi_4)

		printf("x = %0.10e, q = %d\n", x, q)

		# calculate with float precision
		printf("regular math   : %0.32e\n", x - q * pi_4) 

		# calculate with more precision
		r = x - q * pi_h
		r -= q * pi_m
		r -= q * pi_l
		printf("high-prec math : %0.32e\n", r)

		# extra precision with ap float
		PREC = 500
		pi_4 = atan2(1, 0) / 2 
		r = x - q * pi_4
		printf("ap math        : %0.32e\n", r)
	}
}

BEGIN {
	print "--- test (PREC=64): r = x - q * (pi/4) ---"
	PREC = 64
	ROUND_MODE = "N"
	pi_h = pi_4_high + 0
	pi_m = pi_4_med + 0
	pi_l = pi_4_low + 0

	for (ii = 0; ii < length(z); ii++) {
		PREC = 64
		x = z[ii];
		x += 0.0

		pi_4 = atan2(1, 0) / 2
		q = int(x / pi_4)
		printf("x = %0.10e, q = %d\n", x, q)

		r = x - q * pi_4
		# calculate with float precision
		printf("regular math   : %0.17e\n", r) 

		# calculate with more precision
		r = x - q * pi_h
		r -= q * pi_m
		r -= q * pi_l
		printf("high-prec math : %0.17e\n", r)

		# extra precision with ap float
		PREC = 500
		pi_4 = atan2(1, 0) / 2 
		r = x - q * pi_4
		printf("ap math        : %0.17e\n", r)
	}
}
