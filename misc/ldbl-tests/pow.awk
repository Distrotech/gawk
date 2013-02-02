BEGIN {
	x1 = 0.1
	x2 = 131.4321211
	x3 = 1.1234567e100
}
{
	y1 = x1^$1
	y2 = x2^$1
	y3 = x3^$1
	# don't have -M IEEE emulation for 64-bit binary
	# need to replace huge values with infinities.
	# "quad" and 64-bit long double has same exponent range.
	# This does not effect the binary formats B0, B1

	save_PREC = PREC
	PREC = "quad"
	y1 += 0; y2 += 0; y3 += 0

	if (y1 <= 1.0e750) {
		printf("%*.*e\n", 0, DIG, y1)
	}
	if (y2 <= 1.0e750) {
		printf("%*.*e\n", 0, DIG, y2)
	}
	if (y3 <= 1.0e750) {
		printf("%*.*e\n", 0, DIG, y3)
	}
	PREC = save_PREC
}
