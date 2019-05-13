CC := g++ --std=c++11

all : Netflix test.out 

test.out : test.cpp
	$(CC) test.cpp -o test.out

Netflix : main.o notification.o notification_repos.o sequence_generator.o user.o user_repos.o movie.o movie_repos.o comment.o
	$(CC) main.o notification.o notification_repos.o sequence_generator.o user.o user_repos.o movie.o movie_repos.o comment.o -o Netflix

main.o : main.cpp config.h
	$(CC) -c main.cpp -o main.o

notification.o : notification.cpp notification.h
	$(CC) -c notification.cpp -o notification.o

notification_repos.o : notification_repos.cpp notification_repos.h notification.h 
	$(CC) -c notification_repos.cpp -o notification_repos.o

sequence_generator.o : sequence_generator.cpp sequence_generator.h
	$(CC) -c sequence_generator.cpp -o sequence_generator.o

user.o : user.h user.cpp
	$(CC) -c user.cpp -o user.o

user_repos.o : user_repos.h user_repos.cpp
	$(CC) -c user_repos.cpp -o user_repos.o

publisher.o : publisher.h publisher.cpp
	$(CC) -c publisher.cpp -o publisher.o

movie.o : movie.cpp movie.h
	$(CC) -c movie.cpp -o movie.o

movie_repos.o : movie_repos.cpp movie_repos.h
	$(CC) -c movie_repos.cpp -o movie_repos.o

comment.o : comment.cpp comment.h
	$(CC) -c comment.cpp -o comment.o


clean : 
	rm -r *.o