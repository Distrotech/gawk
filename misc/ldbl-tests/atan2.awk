BEGIN {
	x1 = 0.1
	x2 = 131.4321211
	x3 = 1.1234567e100
}
{
	r1 = atan2(x1, $1)
	rm1 = atan2(-x1, $1)
	t1 = atan2($1, x1)
	tm1 = atan2($1, -x1)
	r2 = atan2(x2, $1)
	rm2 = atan2(-x2, $1)
	t2 = atan2($1, x2)
	tm2 = atan2($1, -x2)
	r3 = atan2(x3, $1)
	rm3 = atan2(-x3, $1)
	t3 = atan2($1, x3)
	tm3 = atan2($1, -x3)

	# don't have -M IEEE emulation for 64-bit binary
	# need to replace huge values with infinities.
	# "quad" and 64-bit long double has same exponent range.
	# This does not effect the binary formats B0, B1

	save_PREC = PREC
	PREC = "quad"
	r1 += 0; r2 += 0; r3 += 0
	t1 += 0; t2 += 0; t3 += 0
	rm1 += 0; rm2 += 0; rm3 += 0
	tm1 += 0; tm2 += 0; tm3 += 0

	printf("%*.*e\n", 0, DIG, r1)
	printf("%*.*e\n", 0, DIG, rm1)
	printf("%*.*e\n", 0, DIG, t1)
	printf("%*.*e\n", 0, DIG, tm1)
	printf("%*.*e\n", 0, DIG, r2)
	printf("%*.*e\n", 0, DIG, rm2)
	printf("%*.*e\n", 0, DIG, t2)
	printf("%*.*e\n", 0, DIG, tm2)
	printf("%*.*e\n", 0, DIG, r3)
	printf("%*.*e\n", 0, DIG, rm3)
	printf("%*.*e\n", 0, DIG, t3)
	printf("%*.*e\n", 0, DIG, tm3)
	PREC = save_PREC
}
