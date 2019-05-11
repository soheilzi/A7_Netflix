CC := g++ --std=c++11

all : Netflix test.out 

test.out : test.cpp
	$(CC) test.cpp -o test.out

Netflix : main.o notification.o notification_repos.o
	$(CC) main.o notification.o notification_repos.o -o Netflix

main.o : main.cpp config.h
	$(CC) -c main.cpp -o main.o

notification.o : notification.cpp notification.h
	$(CC) -c notification.cpp -o notification.o

notification_repos.o : notification_repos.cpp notification_repos.h notification.h 
	$(CC) -c notification_repos.cpp -o notification_repos.o

clean : 
	rm -r *.o