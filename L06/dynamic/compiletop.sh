#!/bin/bash

if [ $# -eq 0 ] ; then
    echo "please provide the path to the shared library. This will allow the link to locate your library for compliation of your executable"
else
    arg=$1
    gcc -L$arg -Wl,-rpath=$arg -Wall -o top top.c -lLab6Part5
fi
