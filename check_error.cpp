#include "check_error.h"

using namespace std;

bool is_number(std::string s) {
	for(int i = 0; i < s.length(); i++) {
		if(s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}

#define DIVIDER "?"

#define ACTION_POST "POST"
#define ACTION_GET "GET"
#define ACTION_DELETE "DELETE"
#define ACTION_PUT "PUT"

#define COMMAND_SIGNUP "signup"
#define COMMAND_LOGIN "login"
#define COMMAND_FILM "films"
#define COMMAND_FOLLOWERS "followers"
#define COMMAND_MONEY "money"
#define COMMAND_REPLIES "replies"
#define COMMAND_COMMENTS "comments"
#define COMMAND_BUY "buy"
#define COMMAND_RATE "rate"
#define COMMAND_PURCHASED "purchased"
#define COMMAND_NOTIFICATIONS "notifications"

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