#!/bin/bash

####################
#
# bash script to write, save and edit commands for L10 part3
#
#####################




finder() {
    cd ../lab10arch
    echo "directory before command executed"
    ls
    
    command=$1

    if [ $command -eq 1 ] ; then
	echo "command $command"
	find . -name '*.tex'
    elif [ $command -eq 2 ] ; then
	echo "command $command"
	find . -not -name 'Template.tex$' | find -name '*.tex'

    elif [ $command -eq 3 ] ; then
	find . -name "*.tex" | xargs wc -l
	
    fi


    git reset --hard

}






finder $1






