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
	if(/*s != ACTION_PUT && s != ACTION_DELETE && */ s != ACTION_GET && s != ACTION_POST)
		throw BadRequest();
}
void check_command(std::string s) {
	if (s != COMMAND_SIGNUP && s != COMMAND_LOGIN && s != COMMAND_FILM && s != COMMAND_FOLLOWERS && 
		s != COMMAND_MONEY &&  s != COMMAND_REPLIES && s != COMMAND_COMMENTS && s != COMMAND_BUY && 
		s != COMMAND_RATE && s != COMMAND_PURCHASED && s != COMMAND_NOTIFICATIONS && s != COMMAND_PUBLISHED &&
		s != COMMAND_PUT_FILM && s != COMMAND_DELETE_FILM && s != COMMAND_DELETE_COMMENT && s != COMMAND_LOGOUT) {
		throw BadRequest();
	}
}

void check_is_in_list(vector<string> list, map<string, string> param) {
	bool flag = false;
	for(const auto& elem : param) {
		for(int i = 0; i < list.size(); i++) {
			if(list[i] == elem.first){
				flag = true;
				break;
			}
		}
		if(flag == false)
			throw BadRequest();
		flag = false;
	}
}

void check_is_in_param(map<string, string> param, vector<string> list) {
	bool flag = false;
	for(int i = 0; i < list.size(); i++) {
		for(const auto& elem : param) {
			if(list[i] == elem.first){
				flag = true;
				break;
			}
		}
		if(flag == false)
			throw BadRequest();
		flag = false;
	}
}

void check_param_with_list(vector<string> list, map<string, string> param) {
	check_is_in_list(list, param);
	check_is_in_param(param, list);
}
