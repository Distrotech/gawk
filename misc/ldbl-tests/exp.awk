{
	y = exp($1);

	# don't have -M IEEE emulation for 64-bit binary
	# need to replace huge values with infinities.
	# "quad" and 64-bit long double has same exponent range.
	# This does not effect the binary formats B0, B1

	save_PREC = PREC
	PREC = "quad"
	y += 0
	printf("%*.*e\n", 0, DIG, y)
	PREC = save_PREC
}
