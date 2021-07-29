
CC = gcc
FLAGS = -Wall


main : src/main.c build/student.o build/course.o documentation documentation/docs docs
	scripts/make_helper.sh
	cd build; $(CC) $(FLAGS) ../src/main.c student.o course.o -o $@


student.o : src/student.c
	scripts/make_helper.sh
	cd build; $(CC) $(FLAGS) -c ../$<

course.o : src/course.c
	scripts/make_helper.sh
	cd build; $(CC) $(FLAGS) -c ../$<

documentation :
	scripts/make_helper.sh

Doxyfile :
	doxygen -g

docs : Doxyfile
	doxygen Doxyfile

clean :
	rm -rf build




