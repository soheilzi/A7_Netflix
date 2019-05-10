CC := g++ --std=c++11

all : Netflix test.out 

test.out : test.cpp
	$(CC) test.cpp -o test.out

Netflix : main.o 
	$(CC) main.o -o Netflix

main.o : main.cpp config.h
	$(CC) -c main.cpp -o main.o

clean : 
	rm -r *.o