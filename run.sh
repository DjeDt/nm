#!/bin/bash

printf "REAL NM HERE :\n"
nm $@
printf "\n\nMINE NM HERE :\n"
./ft_nm $@
