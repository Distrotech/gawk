# generate input data for tests
# gawk -M -vPREC=quad -f .. 

BEGIN {
	# 16000 almost LDBL_MAX_EXP or -LDBL_MIN_EXP

	for (i = -16000; i < -1000; i += 255.5)
		printf("%0.17e\n", 1.0*2^i)
	for (i = -1000; i < -100; i += 25.5)
		printf("%0.17e\n", 1.0*2^i)
	for (i = -100; i < -10; i += 2.5)
		printf("%0.17e\n", 1.0*2^i)
	for (i = -10; i < -1; i += 0.75)
		printf("%0.17e\n", 1.0*2^i)
	for (i = -1; i < 2.0; i += 0.1)
		printf("%0.17e\n", 2^i)
	for (i = 1; i < 10; i += 0.75)
		printf("%0.17e\n", 1.0 * 2^i)
	for (i = 10; i < 100; i += 2.5)
		printf("%0.17e\n", 1.0 * 2^i)
	for (i = 100; i < 1000; i += 25.5)
		printf("%0.17e\n", 1.0 * 2^i)
	for (i = 1000; i < 16000; i += 255.5)
		printf("%0.17e\n", 1.0 * 2^i)
}

