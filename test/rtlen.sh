#! /bin/sh

if [ "$AWK" = "" ]
then
	echo $0: You must set AWK >&2
	exit 1
fi

$AWK 'BEGIN {printf "0\n\n\n1\n\n\n\n\n2\n\n"; exit}' | $AWK 'BEGIN {RS=""}; {print length(RT)}'
