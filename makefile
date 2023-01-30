all: list_main.o list_functions.o list_errors.o
	g++ -Wall -Wextra list_main.o list_functions.o list_errors.o -o start
	./start

list_functions.o: list_functions.cpp list_functions.h
	g++ -Wall -Wextra -c list_functions.cpp -o list_functions.o

list_errors.o: list_errors.cpp list_errors.h
	g++ -Wall -Wextra -c list_errors.cpp -o list_errors.o

list_main.o: main.cpp
	g++ -Wall -Wextra -c main.cpp -o list_main.o

clean:
	rm list_errors.o list_functions.o list_main.o start
