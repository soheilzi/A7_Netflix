#include "command_handler.h"

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

void CommandHandler::process_request(string command) {
	vector<string> tokens = break_into_tokens(command);
	
}