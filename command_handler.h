#ifndef __command_handler
#define __command_handler

#include <string>
#include <map>
#include <vector>

#include "network.h"

class CommandHandler {
public:
	CommandHandler(Network* _net);
	void process_request(std::string command);
	void check_request(std::vector<std::string> tokens);
private:
	Network* net;
};

std::vector<std::string> break_into_tokens(std::string command);

#endif