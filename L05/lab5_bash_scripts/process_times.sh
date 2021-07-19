#!/bin/bash


#######################
##
## Michele Akeson (400027379)
## Date: July 12, 2021
##
#######################



##
## HELPER FUNCTIONS
##


display_times() {
    ## run() executes linear, binary, and fibbonaci search algorithems for each
    ## of the required inputs, and stores the resulting search number and $time output
    ## in a .txt file to be processed
    
    numbers="1 4 22 37 22906 53757 112591 361940 475713 893766 996637 996639 996652 -996652"
    filename=$1
    touch $filename
    for num in $numbers;
    do
	echo ""
	echo $num
	
	time ./search 0 $num

	echo ""

	time ./search 1 $num

	echo ""
	
	time ./search 2 $num
	
    done

    #cat $filename
    
}



run() {
    ## run() executes linear, binary, and fibbonaci search algorithems for each
    ## of the required inputs, and stores the resulting search number and $time output
    ## in a .txt file to be processed
    
    numbers="1 4 22 37 22906 53757 112591 361940 475713 893766 996637 996639 996652 -996652"
    filename=$1
    touch $filename
    for num in $numbers;
    do
	echo "linear search $num" >> $filename
	{ time ./search 0 $num sleep 1; } 2>&1 |  cat >> $filename #code taken from stackoverflow: {time sleep 1; } 2>&1 | cat > output_file.txt

	echo "binary search $num" >> $filename
	{ time ./search 1 $num sleep 1; } 2>&1 |  cat >> $filename #code taken from stackoverflow: {time sleep 1; } 2>&1 | cat > output_file.txt

	echo "fibonacci search $num" >> $filename
	{ time ./search 2 $num sleep 1; } 2>&1 |  cat >> $filename #code taken from stackoverflow: {time sleep 1; } 2>&1 | cat > output_file.txt
	
    done

    #cat $filename
    
}


filter_times(){
    ## filter_times() creates a file of name $output_file.txt which
    ## stores only the search type, number, and real time value
    ## to be used in creating the final "timing_results.csv" file
    
    filename=$1
    output_file=$2
    
    if [ -f $output_file ] ; then
	rm $output_file
	touch $output_file
    fi
    
    while read line;
    do

	# requires [[  ]] to do substring check
	echo $line
	if [[ $line == *"linear"* ]]; then
	    echo $line >> $output_file
	    
        elif [[ $line == *"binary"* ]]; then
	    echo $line >> $output_file
	    
        elif [[ $line == *"fibonacci"* ]]; then
	    echo $line >> $output_file
	    
        elif [[ $line == *"real"* ]] ; then
	    echo $line >> $output_file
        fi
	
    done < $filename
    
    # cat $output_file
    rm $filename
}
    
   


real_times() {
    filename=$1
    output_file=timing_results.csv
    
    if [ -f $output_file ] ; then
	rm $output_file
	touch $output_file
    fi

    echo "Search Value  Linear Search  Binary Search  Fibonacci Search  Notes" >> $output_file
    add_line=""
    spacing="           "
    
    while read line;
    do
        if [[ $line == *"linear"* ]] ; then
	    echo $add_line >> $output_file
	    number=${line:13}
	    add_line="$number, $spacing "
	elif [[ $line == *"binary"* ]] ; then
	    echo "remove binary header"
	    
	elif [[ $line == *"fibonacci"* ]] ; then
	    echo "remove fibbonacci header"
       
	else
	    add_line+="$line, $spacing"
        fi

    done < $filename
    cat $output_file
    rm $filename
}








##
## MAIN SCRIPT
##

if [ $1 -eq 1 ] ; then
    echo "creating timing_results.csv"
    run search_times.txt
    filter_times search_times.txt org_times.txt
    real_times org_times.txt
    
elif [ $1 -eq 2 ] ; then
    echo "double checking searh times"
    display_times

fi
    

