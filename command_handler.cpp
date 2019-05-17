#include "command_handler.h"
#include "check_error.h"

#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

vector<string> break_into_tokens(string command) {
	istringstream iss(command);
	vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};	
	return tokens;
}

std::map<string, string> make_param_map(std::vector<std::string> param) {
	if(param.size() % 2 == 1)
		throw BadRequest();
	map<string, string> temp;
	for(int i = 0; i < param.size(); i += 2) {
		temp[param[i]] = param[i + 1];
	}
	return temp;
}

std::vector<std::string> make_param_vect(std::vector<std::string> tokens, int start) {
	vector<string> temp;
	for(int i = start; i < tokens.size(); i++) {
		temp.push_back(tokens[i]);
	}
	return temp;
}


CommandHandler::CommandHandler(Network* _net) : net(_net) {}


void CommandHandler::check_request(std::vector<std::string> tokens) {
	check_action(tokens[0]);
	check_command(tokens[1]);
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


void CommandHandler::handle_post(vector<string> tokens) {
	string command = tokens[1];
	if(tokens.size() == 2 && command == COMMAND_MONEY){
		net->get_money_publisher();
		return;
	}
	check_divider(tokens[2]);
	map<string, string> param_map = make_param_map(make_param_vect(tokens, 3));
	if(command == COMMAND_SIGNUP) {
		signup(param_map);

	} else if(command == COMMAND_LOGIN) {
		login(param_map);

	} else if(command == COMMAND_FILM) {
		post_film(param_map);

	} else if(command == COMMAND_MONEY) {
		user_get_money(param_map);

	} else if(command == COMMAND_REPLIES) {
		post_reply(param_map);
		
	} else if(command == COMMAND_FOLLOWERS) {
		post_follow(param_map);
		
	} else if(command == COMMAND_BUY) {
		post_buy(param_map);
		
	} else if(command == COMMAND_RATE) {
		post_rate(param_map);
		
	} else if(command == COMMAND_COMMENTS) {
		post_comment(param_map);

	}

}
#define USERNAME "username"
#define NAME "name"
#define EMAIL "email"
#define PASSWORD "password"
#define FILM_ID "film_id"
#define SCORE "score"
#define CONTENT "content"
#define AGE "age"
#define PUBLISHER "publisher"
#define YEAR "year"
#define LENGTH "length"
#define PRICE "price"
#define SUMMARY "summary"
#define DIRECTOR "director"
#define COMMENT_ID "comment_id"
#define USER_ID "user_id"
#define AMOUNT "amount"


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

void CommandHandler::signup(std::map<std::string, std::string> param) {
	if ( param.find(PUBLISHER) != param.end()){
	vector<string> list = {EMAIL, USERNAME, PASSWORD, AGE, PUBLISHER};
	check_param_with_list(list, param);

	net->signup_user(param[EMAIL], param[USERNAME], param[PASSWORD], stoi(param[AGE]), param[PUBLISHER]);

	}else{
	vector<string> list = {EMAIL, USERNAME, PASSWORD, AGE};
	check_param_with_list(list, param);

	net->signup_user(param[EMAIL], param[USERNAME], param[PASSWORD], stoi(param[AGE]));

	}
}

void CommandHandler::login(std::map<std::string, std::string> param) {
	vector<string> list = {USERNAME, PASSWORD};
	check_param_with_list(list, param);

	net->login_user(param[USERNAME], param[PASSWORD]);

}

void CommandHandler::post_film(std::map<std::string, std::string> param) {	
	vector<string> list = {NAME, YEAR, LENGTH, PRICE, SUMMARY, DIRECTOR};
	check_param_with_list(list, param);

	net->add_movie(param[NAME], stoi(param[YEAR]), stoi(param[LENGTH]), stoi(param[PRICE]), param[SUMMARY], param[DIRECTOR]);

}

void CommandHandler::user_get_money(std::map<std::string, std::string> param) {
	
}

void CommandHandler::post_reply(std::map<std::string, std::string> param) {
	vector<string> list = {FILM_ID, COMMENT_ID, CONTENT};
	check_param_with_list(list, param);

	net->post_reply(stoi(param[FILM_ID]), stoi(param[COMMENT_ID]), param[CONTENT]);

}

void CommandHandler::post_follow(std::map<std::string, std::string> param) {

}

void CommandHandler::post_buy(std::map<std::string, std::string> param) {

}

void CommandHandler::post_rate(std::map<std::string, std::string> param) {

}

void CommandHandler::post_comment(std::map<std::string, std::string> param) {

}


void CommandHandler::handle_get(vector<string> tokens) {
	
}

void CommandHandler::handle_delete(vector<string> tokens) {
	
}

void CommandHandler::handle_put(vector<string> tokens) {
	
}

void CommandHandler::process_request(string command) {
	vector<string> tokens = break_into_tokens(command);
	check_request(tokens);
	string method = tokens[0];
	if(method == ACTION_POST) {
		handle_post(tokens);
	} else if(method == ACTION_GET) {
		handle_get(tokens);
	} else if(method == ACTION_DELETE) {
		handle_delete(tokens);
	} else if(method == ACTION_PUT) {
		handle_put(tokens);
	}
}