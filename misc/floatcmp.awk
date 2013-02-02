# floatcmp.awk --- check floating-point numbers for differences in
#	 sig digs.

BEGIN {
	if (ARGC < 3) {
		printf("Usage: gawk -M [-vTOL=1] -f floatcmp.awk file1 file2\n")
		exit(1)
	}

	PREC = 200

	# TOL -- allowable difference in significant digits 
	if (! TOL)
		TOL = 1

	file1 = ARGV[1]
	file2 = ARGV[2]
	line = 0
	while (1) {
		ret1 = (getline v1 < file1) 
		ret2 = (getline v2 < file2) 

		if (ret1 > 0 && ret2 > 0) {
			line++
			if ((v1 "") == (v2 ""))
				continue;
			e1 = index(v1, "e")
			e2 = index(v2, "e")
			if (e1 > 0 && e2 > 0 &&		# exclude nans and infinities
					substr(v1, e1) == substr(v2, e2)) { # same exponents
				sub(/e.*$/, "", v1)
				sub(/e.*$/, "", v2)
				sub(/\./, "", v1)
				sub(/\./, "", v2)

				# the following test requires arbitrary precision math.
				# PREC must be large enough to represent 33-digit (or more)
				# integers precisely.
				diff = v2 - v1
				if (diff <= TOL && diff >= -TOL) 
					continue
			}

			printf("%s %s differ: byte ?, line %d\n", file1, file2, line)
			exit(1)
		}

		if (ret1 == 0 && ret2 == 0)
			exit(0)
		if (ret1 < 0 || ret2 < 0) {
			printf("cmp: %s: %s\n", ret1 < 0 ? file1 : file2, ERRNO)
			exit(1)
		}
		printf("EOF on %s\n", ret1 == 0 ? file1 : file2)
		exit(1)
	}
}
