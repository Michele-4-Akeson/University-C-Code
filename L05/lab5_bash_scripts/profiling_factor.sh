#!/bin/bash

profile(){
    numbers="40 79 240 300 999 4000"

    for num in $numbers;
    do
	filename_1="factors_0_$num.txt"
	filename_2="factors_1_$num.txt"

	if [ -f $filename_1 ] || [ -f $filename_2 ] ; then
	    rm $filename_1
	    rm $filename_2
        fi

	./factors 0 $num
	gprof factors > $filename_1

	./factors 1 $num
	gprof factors > $filename_2

	git add $filename_1 $filename_2
	

    done
    

    
}


profile



