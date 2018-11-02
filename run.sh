#!/bin/bash

MY_NM=".my_nm.result"
RL_NM=".rl_nm.result"

./ft_nm $@ > "$MY_NM" && nm $@ > "$RL_NM" | cat -e  && diff "$MY_NM" "$RL_NM"
