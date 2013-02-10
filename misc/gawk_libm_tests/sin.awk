$1 >= 0x100000000 {
	#
	# The code in rem_pio2.c (Payne and Hanek Reduction Algorithm)       
	# provides only C-double precision.        
	#
	printf("%0.15e\n", sin($1))
	next
}
{
	printf("%*.*e\n", 0, DIG, sin($1))
}
