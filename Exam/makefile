all : tuxquest clean

exam : Exam.tex Exam.pdf clean

tuxquest : src/tuxquest.c src/inventory.c src/inventory.h src/stats.c src/stats.h src/utils.c src/locations.c src/locations.h
	gcc -Wall -o tuxquest src/tuxquest.c
	make docs

Exam.pdf : 
	pdflatex Exam.tex

test : tuxquest
	echo "Testing tuxquest"
	# QUESTION 1 GOES HERE	
	./q1.sh



Doxyfile :
	doxygen -g

docs : Doxyfile
	doxygen Doxyfile

profile : src/tuxquest.c
	./q6.sh 1

coverage : src/tuxquest.c
	./q6.sh 2


clean : 
	rm -rf src/*.o *~ */*~ *.aux *.log *.out
