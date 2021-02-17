#!/bin/zsh

if [[ "$1" == "" ]]; then
	echo -n "Enter path to ./ft_ssl_md5: "
	read -r ft_ssl_md5
else
	ft_ssl_md5=$1
fi

RED='\e[0;31m'

#make -C $(dirname bt_ssl_md5)
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

	#for cmd in {des,des-ecb,des-cfb,des-ofb}; do
    cmd=des3
    cmd2=des-ede3-cbc
#	  o_pass=123
    o_pass=$(($RANDOM%494455879982))
    echo $o_pass
	  o_salt=444
	  o_iv=1122334455667788
		o_openssl=$(openssl $cmd2 -a -in $FILENAME -pass pass:$o_pass -S $o_salt -iv $o_iv)
		o_ft_ssl_md5=$(./cmake-build-debug/ft_ssl_md5 $cmd -a -i $FILENAME -p $o_pass -s $o_salt -v $o_iv)
		if diff <(echo ${o_openssl// /}) <(echo ${o_ft_ssl_md5// /}); then; else
			echo "\n${RED}ERROR occured with file: $FILENAME"
			exit 1
		fi
	#done
done
rm -f .file_*
