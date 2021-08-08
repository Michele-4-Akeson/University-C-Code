#!/bin/bash

cd testing
input_files=""


for file in * ;
do
   
    if [[ ! $file = *"."* ]] ; then
	files+="testing/$file "
	touch "$file.test"
    fi
    
done

cd ..
for file in $files ;
do
   
    echo "------------->$file<------------------"
    echo " "
    ./tuxquest < $file > "$file.test"
    diff "$file.test" "$file.output"
done

cd testing
rm *.test

