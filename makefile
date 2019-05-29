CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build_front
BUILD_BACK_DIR=build_back
TEMPLATE_DIR=.template

all: back.out $(BUILD_DIR) myserver.out

back.out:
	cd ./back_end;make;cd ..

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/template_parser.o: utils/template_parser.cpp utils/template_parser.hpp utils/request.cpp utils/request.hpp utils/utilities.hpp utils/utilities.cpp
	$(CC) $(CF) -c utils/template_parser.cpp -o $(BUILD_DIR)/template_parser.o

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp utils/template_parser.hpp utils/template_parser.cpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: front_end/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp back_end/network.h
	$(CC) $(CF) -c front_end/handlers.cpp -o $(BUILD_DIR)/handlers.o

$(BUILD_DIR)/my_server.o: front_end/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c front_end/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: front_end/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp back_end/network.h
	$(CC) $(CF) -c front_end/main.cpp -o $(BUILD_DIR)/main.o

myserver.out: $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_BACK_DIR)/network.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_BACK_DIR)/check_error.o $(BUILD_BACK_DIR)/command_handler.o $(BUILD_BACK_DIR)/comment.o $(BUILD_BACK_DIR)/matrix.o $(BUILD_BACK_DIR)/movie_repos.o $(BUILD_BACK_DIR)/movie.o $(BUILD_BACK_DIR)/notification_repos.o $(BUILD_BACK_DIR)/notification.o $(BUILD_BACK_DIR)/publisher.o $(BUILD_BACK_DIR)/sequence_generator.o $(BUILD_BACK_DIR)/ui.o $(BUILD_BACK_DIR)/user_repos.o $(BUILD_BACK_DIR)/user.o
	$(CC) $(CF) $(BUILD_DIR)/my_server.o $(BUILD_DIR)/main.o $(BUILD_BACK_DIR)/network.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o $(BUILD_DIR)/template_parser.o $(BUILD_BACK_DIR)/check_error.o $(BUILD_BACK_DIR)/command_handler.o $(BUILD_BACK_DIR)/comment.o $(BUILD_BACK_DIR)/matrix.o $(BUILD_BACK_DIR)/movie_repos.o $(BUILD_BACK_DIR)/movie.o $(BUILD_BACK_DIR)/notification_repos.o $(BUILD_BACK_DIR)/notification.o $(BUILD_BACK_DIR)/publisher.o $(BUILD_BACK_DIR)/sequence_generator.o $(BUILD_BACK_DIR)/ui.o $(BUILD_BACK_DIR)/user_repos.o $(BUILD_BACK_DIR)/user.o -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) $(TEMPLATE_DIR) *.o *.out &> /dev/null
