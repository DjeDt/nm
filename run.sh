#!/bin/sh

MY_NM=".my_nm.result"
RL_NM=".rl_nm.result"

MY_OTOOL=".my_otool.result"
RL_OTOOL=".rl_otool.result"

MY_RET=0
RL_RET=0

if [ "$1" = "python" ] ; then
	python3 bin/unit_test.py --nm --recursive bin/custom_tests/{32,64,lib_stat,fat,fat_lib,corrupt} /usr/lib/ /usr/bin /usr/local/bin
	exit $?
fi

ERROR=0
if [ "$1" = "nm" ] || [ "$1" = "otool" ] ; then
	for arg in $@ ; do
		if  [ "$arg" != "nm" ] || [ "$arg" != "otool" ] ; then
			printf "[%s] :" $arg
		   	if [ "$1" = "nm" ] ; then
				./ft_nm "$arg" > "$MY_NM"
				MY_RET=$?
		  		nm "$arg" > "$RL_NM"
				RL_RET=$?
				diff "$MY_NM" "$RL_NM"
			fi
			if [ "$1" = "otool" ] ; then
				./ft_otool "$arg" > "$MY_OTOOL"
				MY_RET=$?
				otool -t "$arg" > "$RL_OTOOL"
				RL_RET=$?
				diff "$MY_OTOOL" "$RL_OTOOL"
			fi
			if [ $RL_RET != 0 ] ; then
				ERROR=$((ERROR + 1))
				ARR_ERR+=("$arg")
			else
				printf " output is identical (:\n"
			fi
		fi
	done
	if [ $ERROR > 0 ] ; then
		echo "\nThere is $ERROR errors :("
		for error in ${ARR_ERR[@]} ; do
			echo "$error"
		done
	fi
fi
else
	echo "usage: ./run.sh [nm/otool/python] <file>\n"
fi
