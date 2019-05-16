#include "check_error.h"

using namespace std;

bool is_number(std::string s) {
	for(int i = 0; i < s.length(); i++) {
		if(s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

void check_divider(std::string s) {
	if(s != DIVIDER)
		throw BadRequest();
}
void check_action(std::string s) {
	if(s != ACTION_PUT && s != ACTION_DELETE && s != ACTION_GET && s != ACTION_POST)
		throw BadRequest();
}
void check_command(std::string s) {
	if (s != COMMAND_SIGNUP && s != COMMAND_LOGIN && s != COMMAND_FILM && s != COMMAND_FOLLOWERS && 
		s != COMMAND_MONEY &&  s != COMMAND_REPLIES && s != COMMAND_COMMENTS && s != COMMAND_BUY && 
		s != COMMAND_RATE && s != COMMAND_PURCHASED && s != COMMAND_NOTIFICATIONS) {
		throw BadRequest();
	}
}