#! /bin/sh

if [ "$AWK" = "" ]
then
	echo $0: You must set AWK >&2
	exit 1
fi

$AWK 'BEGIN {printf "0"; exit}' | $AWK 'BEGIN {RS=""}; {print length(RT)}'
$AWK 'BEGIN {printf "0\n"; exit}' | $AWK 'BEGIN {RS=""}; {print length(RT)}'
$AWK 'BEGIN {printf "0\n\n"; exit}' | $AWK 'BEGIN {RS=""}; {print length(RT)}'

