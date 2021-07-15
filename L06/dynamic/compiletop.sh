#!/bin/bash

if [ $# -eq 0 ] ; then
    echo "please provide the path to the shared library, and state its purpose"
else
    arg=$1
    gcc -L$arg -Wl,-rpath=$arg -Wall -o top top.c -lLab6Part5
fi
