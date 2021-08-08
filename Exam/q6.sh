#!/bin/bash



profile(){
 
    filename="testing/fullAdventure"
    gcc -pg -o tuxquest src/tuxquest.c
    ./tuxquest < $filename
    gprof tuxquest > tuxquest.txt



}


coverage(){
    filename="testing/fullAdventure"
    gcc -fprofile-arcs -ftest-coverage -o tuxquest src/tuxquest.c
    ./tuxquest < $filename
    gcov src/tuxquest.c

    cat src/tuxquest.c.gcov
    mv src/tuxquest.c.gcov  "../tq.gcov"

}


if [ $1 -eq 1 ] ; then
    profile
    
elif [ $1 -eq 2 ] ; then
    coverage

fi  
