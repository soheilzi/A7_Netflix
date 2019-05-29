CC := g++ --std=c++11

BUILD_DIR=build_back

all : $(BUILD_DIR) Netflix test.out

$(BUILD_DIR):
	cd ..;mkdir -p $(BUILD_DIR);cd  ./back_end 

test.out : test.cpp
	$(CC) test.cpp -o test.out

Netflix : $(BUILD_DIR)/main.o $(BUILD_DIR)/notification.o $(BUILD_DIR)/notification_repos.o $(BUILD_DIR)/matrix.o $(BUILD_DIR)/sequence_generator.o $(BUILD_DIR)/user.o $(BUILD_DIR)/user_repos.o $(BUILD_DIR)/movie.o $(BUILD_DIR)/movie_repos.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/check_error.o $(BUILD_DIR)/network.o $(BUILD_DIR)/command_handler.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/ui.o
	cd ..;$(CC) $(BUILD_DIR)/main.o $(BUILD_DIR)/notification.o $(BUILD_DIR)/notification_repos.o $(BUILD_DIR)/matrix.o $(BUILD_DIR)/sequence_generator.o $(BUILD_DIR)/user.o $(BUILD_DIR)/user_repos.o $(BUILD_DIR)/movie.o $(BUILD_DIR)/movie_repos.o $(BUILD_DIR)/comment.o $(BUILD_DIR)/check_error.o $(BUILD_DIR)/network.o $(BUILD_DIR)/command_handler.o $(BUILD_DIR)/publisher.o $(BUILD_DIR)/ui.o -o Netflix

$(BUILD_DIR)/main.o : main.cpp config.h command_handler.h network.h exceptions.h ui.h
	$(CC) -c main.cpp -o ../$(BUILD_DIR)/main.o

$(BUILD_DIR)/notification.o : notification.cpp notification.h
	$(CC) -c notification.cpp -o ../$(BUILD_DIR)/notification.o

$(BUILD_DIR)/notification_repos.o : notification_repos.cpp notification_repos.h notification.h 
	$(CC) -c notification_repos.cpp -o ../$(BUILD_DIR)/notification_repos.o

$(BUILD_DIR)/sequence_generator.o : sequence_generator.cpp sequence_generator.h
	$(CC) -c sequence_generator.cpp -o ../$(BUILD_DIR)/sequence_generator.o

$(BUILD_DIR)/user.o : user.h user.cpp
	$(CC) -c user.cpp -o ../$(BUILD_DIR)/user.o

$(BUILD_DIR)/user_repos.o : user_repos.h user_repos.cpp config.h
	$(CC) -c user_repos.cpp -o ../$(BUILD_DIR)/user_repos.o

$(BUILD_DIR)/publisher.o : publisher.h publisher.cpp
	$(CC) -c publisher.cpp -o ../$(BUILD_DIR)/publisher.o

$(BUILD_DIR)/movie.o : movie.cpp movie.h check_error.h
	$(CC) -c movie.cpp -o ../$(BUILD_DIR)/movie.o

$(BUILD_DIR)/movie_repos.o : movie_repos.cpp movie_repos.h user.h
	$(CC) -c movie_repos.cpp -o ../$(BUILD_DIR)/movie_repos.o

$(BUILD_DIR)/comment.o : comment.cpp comment.h
	$(CC) -c comment.cpp -o ../$(BUILD_DIR)/comment.o

$(BUILD_DIR)/check_error.o : check_error.cpp check_error.h config.h
	$(CC) -c check_error.cpp -o ../$(BUILD_DIR)/check_error.o

$(BUILD_DIR)/command_handler.o : command_handler.cpp command_handler.h config.h
	$(CC) -c command_handler.cpp -o ../$(BUILD_DIR)/command_handler.o

$(BUILD_DIR)/network.o : network.cpp network.h config.h
	$(CC) -c network.cpp -o ../$(BUILD_DIR)/network.o

$(BUILD_DIR)/ui.o : ui.cpp ui.h config.h
	$(CC) -c ui.cpp -o ../$(BUILD_DIR)/ui.o

$(BUILD_DIR)/matrix.o : matrix.h matrix.cpp movie.h
	$(CC) -c matrix.cpp -o ../$(BUILD_DIR)/matrix.o


clean : 
	cd ..;rm -r build_back

