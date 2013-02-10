# Usage gawk -B -f ldblint128.awk

BEGIN {
	for (i = -9.0; i < 2.0; i++) {
		j = i
		if (j >= 0.0)
			j = " + " j
		else {
			j = -j
			j = " - " j
		}
		printf("2^113%s = %d\n", j, 2^113 + i)
	}
}
