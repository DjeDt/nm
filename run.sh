#!/bin/sh

MY_NM=".my_nm.result"
RL_NM=".rl_nm.result"


if [ "$1" = "python" ] ; then
	python3 bin/unit_test.py --nm --recursive bin/custom_tests/{32,64,lib_stat,fat,fat_lib,corrupt} /usr/lib/ /usr/bin /usr/local/bin
	exit $?
fi

./ft_nm $@ > "$MY_NM" ; nm $@ > "$RL_NM" | cat -e && diff "$MY_NM" "$RL_NM"

if [ $? -ne 0 ] ; then
	wc -l "$MY_NM"
	wc -l "$RL_NM"
else
	echo "output is identical (:"
fi
