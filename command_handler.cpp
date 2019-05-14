#include "command_handler.h"
#include "check_error.h"

#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

CommandHandler::CommandHandler(Network* _net) : net(_net) {}

vector<string> break_into_tokens(string command) {
	istringstream iss(command);
	vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};	
	return tokens;
}

void CommandHandler::check_request(std::vector<std::string> tokens) {
	check_action(tokens[0]);
	check_command(tokens[1]);
	check_divider(tokens[2]);
}

void CommandHandler::process_request(string command) {
	vector<string> tokens = break_into_tokens(command);
	check_request(tokens);

}