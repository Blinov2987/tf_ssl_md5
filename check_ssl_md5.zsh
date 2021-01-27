#!/bin/zsh

if [[ "$1" == "" ]]; then
	echo -n "Enter path to ./ft_ssl_md5: "
	read -r ft_ssl_md5
else
	ft_ssl_md5=$1
fi

RED='\e[0;31m'

make -C $(dirname bt_ssl_md5)
for l in {1..10}; do
	FILENAME=.file_$l
	chars_amm=$(($RANDOM%5000))

	echo > $FILENAME
	for (( i = 1; i <= $chars_amm; i++ )); do
		arr[$i]=$(($RANDOM%256));
	done
	for (( i = 1; i <= $chars_amm; i++ )); do
		echo -n "\x$(printf %x ${arr[$i]})" >> $FILENAME
	done

	for cmd in {md5,sha256,sha512}; do
		o_openssl=$(openssl $cmd $FILENAME)
		o_ft_ssl_md5=$(./ft_ssl_md5 $cmd $FILENAME)
		if diff <(echo ${o_openssl// /}) <(echo ${o_ft_ssl_md5// /}); then; else
			echo "\n${RED}ERROR occured with file: $FILENAME"
			exit 1
		fi
	done
done
#rm -f .file_*
