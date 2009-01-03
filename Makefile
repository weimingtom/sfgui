all:
	g++ `ls *.cpp` -o exec -Wall -W -Werror -ansi -pedantic -g -lsfml-graphics -lsfml-window -lsfml-system
clean:
	rm *.o
	rm exec
