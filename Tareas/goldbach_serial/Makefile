goldbach: goldbach_serial.c
	gcc -g -Wall -Wextra goldbach_serial.c -o goldbach
	
valgrind: goldbach_serial.c
	valgrind --tool=memcheck ./goldbach
