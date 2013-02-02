# Split log2 into two parts -- a high part which is exactly representable
#	with less than the float-precision and a variable precision low part.
#		log2 = log2_high + log2_low
#
#	Extra precision calculation with limited precision float:
#		r = x - q * log2,	q is an integer
#		  = (x - q * log2_high) - q * log2_low
#	if the high part has M bits, the integer q should have less than
#	(float_prec - M) non-zero leading bits.

# Usage: $ gawk -M -f splitlog2.awk

BEGIN {
	PREC = 300	# at least 64 + 113 (+ few more) 

	y = log(2)
	printf("log2       = %0.36f\n", y)

	PREC = 32
	log2_high = next_down(y)	# exactly representable with 32 bits

	PREC = 300
	log2_low = (y - log2_high)

	printf("log2_high  = %0.36f\n", log2_high)
	printf("log2_low   = %0.36e\n", log2_low)

	# test case with 128-bit long double
	print "--- test calculation: r = x - q * log2 ---"
	PREC = 113
	ROUND_MODE = "N"

	log2_high += 0	# float precision 
	log2_low += 0	# Ditto

	x = "501.0"
	x += 0
	q = int(x / log(2.0))

	# calculate with float precision
	printf("regular math   : %0.32e\n", x - q * log(2)) 

	# calculate with more precision
	printf("high-prec math : %0.32e\n", (x - q * log2_high) - q * log2_low)

	# extra precision with ap float
	PREC = 300
	printf("ap math        : %0.32e\n", x - q * log(2))
}
