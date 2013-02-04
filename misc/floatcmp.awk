# floatcmp.awk --- check floating-point numbers for differences in sig digs.
#	-vMODE=[diff|plot] -- diff mode or output data suitable fro plotting
#	-vTOL=tol	-- ignore sig dig difference <= tol

BEGIN {
	if (! ("mpfr_version" in PROCINFO)) {
		print "floatcmp.awk: requires -M option" > "/dev/stderr"
		exit(1)
	} 
	if (ARGC < 3) {
		print "Usage: gawk -M [-vTOL=tol] [-vMODE=diff|plot] -f floatcmp.awk file1 file2" > "/dev/stderr"
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

		f1 = v1; f2 = v2;	# save originals for diff mode
		if (ret1 > 0 && ret2 > 0) {
			line++
			if ((v1 "") == (v2 ""))
				continue
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

			if (! MODE) {
				printf("%s %s differ: byte ?, line %d\n", file1, file2, line)
				exit(1)
			}
			if (MODE == "plot")
				printf("%d\t%d\n", line, diff)
			else {
				dig = length(v1)
				printf("%-*.*s %-*.*s %+*.*d\n", dig+7, dig+7, f1, dig+7, dig+7, f2, dig, dig, diff)
			}
       			continue
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
