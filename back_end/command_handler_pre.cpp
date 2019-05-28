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


CommandHandler::CommandHandler(Network* _net, UI* _ui) : net(_net), ui(_ui) {}


void CommandHandler::check_request(std::vector<std::string> tokens) {
	check_action(tokens[0]);
	check_command(tokens[1]);
}


void CommandHandler::handle_post(vector<string> tokens) {
	string command = tokens[1];
	if(tokens.size() == 2 && command == COMMAND_MONEY){
		net->get_money_publisher();
		ui->show_fine_state();
		return;
	}
	check_divider(tokens[2]);
	map<string, string> param_map = make_param_map(make_param_vect(tokens, 3));
	if(command == COMMAND_SIGNUP) {
		signup(param_map);
		ui->show_fine_state();

	} else if(command == COMMAND_LOGIN) {
		login(param_map);
		ui->show_fine_state();

	} else if(command == COMMAND_FILM) {
		post_film(param_map);
		ui->show_fine_state();

	} else if(command == COMMAND_MONEY) {
		user_get_money(param_map);
		ui->show_fine_state();

	} else if(command == COMMAND_REPLIES) {
		post_reply(param_map);
		ui->show_fine_state();
		
	} else if(command == COMMAND_FOLLOWERS) {
		post_followers(param_map);
		ui->show_fine_state();
		
	} else if(command == COMMAND_BUY) {
		post_buy(param_map);
		ui->show_fine_state();
		
	} else if(command == COMMAND_RATE) {
		post_rate(param_map);
		ui->show_fine_state();
		
	} else if(command == COMMAND_COMMENTS) {
		post_comment(param_map);
		ui->show_fine_state();

	}

}


void CommandHandler::handle_get(vector<string> tokens) {
	string command = tokens[1];
	if(command == COMMAND_FOLLOWERS) {
		if(tokens.size() > 2)
			throw BadRequest();
		ui->show_followers();
		return;
	} else if(command == COMMAND_PUBLISHED) {
		map<string, string> param_map;
		if(tokens.size() > 2){
			check_divider(tokens[2]);
			param_map = make_param_map(make_param_vect(tokens, 3));
		}
		show_published(param_map);
	} else if(command == COMMAND_FILM) {
		map<string, string> param_map;
		if(tokens.size() > 2){
			check_divider(tokens[2]);
			param_map = make_param_map(make_param_vect(tokens, 3));
		}
		if(param_map.find(FILM_ID) == param_map.end()) {
			show_movies(param_map);
		} else {
			show_movie_data(param_map);
		}	
	} else if(command == COMMAND_PURCHASED) {
		map<string, string> param_map;
		if(tokens.size() > 2){
			check_divider(tokens[2]);
			param_map = make_param_map(make_param_vect(tokens, 3));
		}
		show_purchased(param_map);
	} else if(command == COMMAND_NOTIFICATIONS) {
		if(tokens.size() == 2){
			show_unread_notifs();
		} else {
			check_divider(tokens[3]);
			map<string, string> param_map = make_param_map(make_param_vect(tokens, 4));
			show_notifs(param_map);
		}
	}
}

void CommandHandler::handle_delete(vector<string> tokens) {
	string command = tokens[1];
	check_divider(tokens[2]);
	map<string, string> param_map = make_param_map(make_param_vect(tokens, 3));
	if(command == COMMAND_COMMENTS) {
		delete_comment(param_map);
		ui->show_fine_state();
	} else if(command == COMMAND_FILM) {
		delete_film(param_map);
		ui->show_fine_state();
	}
}

void CommandHandler::handle_put(vector<string> tokens) {
	string command = tokens[1];
	check_divider(tokens[2]);
	map<string, string> param_map = make_param_map(make_param_vect(tokens, 3));
	if(command == COMMAND_FILM) {
		put_films(param_map);
		ui->show_fine_state();
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

void CommandHandler::show_unread_notifs() {
	ui->show_unread_notifs();
}

void CommandHandler::show_notifs(std::map<std::string, std::string> param) {
	vector<string> list = {LIMIT};
	check_param_with_list(list, param);

	ui->show_notifs(param);

}

void CommandHandler::show_movie_data(std::map<std::string, std::string> param) {
	vector<string> list = {FILM_ID};
	check_param_with_list(list, param);

	ui->show_movie_data(param);

}

void CommandHandler::show_movies(std::map<std::string, std::string> param) {
	vector<string> list_max = {NAME, MIN_RATE, MIN_YEAR, PRICE, MAX_YEAR, DIRECTOR};
	check_is_in_list(list_max, param);

	ui->show_movies(param);

}

void CommandHandler::show_purchased(std::map<std::string, std::string> param) {
	vector<string> list_max = {NAME, MIN_YEAR, PRICE, MAX_YEAR, DIRECTOR};
	check_is_in_list(list_max, param);

	ui->show_purchased(param);

}

void CommandHandler::show_published(std::map<std::string, std::string> param) {
	vector<string> list_max = {NAME, MIN_RATE, MIN_YEAR, PRICE, MAX_YEAR, DIRECTOR};
	check_is_in_list(list_max, param);

	ui->show_published(param);
}

void CommandHandler::delete_film(std::map<std::string, std::string> param) {
	vector<string> list = {FILM_ID};
	check_param_with_list(list, param);

	net->delete_film(stoi(param[FILM_ID]));

}

void CommandHandler::delete_comment(std::map<std::string, std::string> param) {
	vector<string> list = {COMMENT_ID, FILM_ID};
	check_param_with_list(list, param);

	net->delete_comment(stoi(param[FILM_ID]), stoi(param[COMMENT_ID]));

}


void CommandHandler::put_films(std::map<std::string, std::string> param) {
	vector<string> list_min = {FILM_ID};
	vector<string> list_max = {FILM_ID, NAME, YEAR, LENGTH, SUMMARY, DIRECTOR};
	check_is_in_list(list_max, param);
	check_is_in_param(param, list_min);

	net->edit_movie(stoi(param[FILM_ID]), param);

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
	vector<string> list = {AMOUNT};
	check_param_with_list(list, param);

	net->get_money_user(stoi(param[AMOUNT]));

}

void CommandHandler::post_reply(std::map<std::string, std::string> param) {
	vector<string> list = {FILM_ID, COMMENT_ID, CONTENT};
	check_param_with_list(list, param);

	net->post_reply(stoi(param[FILM_ID]), stoi(param[COMMENT_ID]), param[CONTENT]);

}

void CommandHandler::post_followers(std::map<std::string, std::string> param) {
	vector<string> list = {USER_ID};
	check_param_with_list(list, param);

	net->post_followers(stoi(param[USER_ID]));

}

void CommandHandler::post_buy(std::map<std::string, std::string> param) {
	vector<string> list = {FILM_ID};
	check_param_with_list(list, param);
	net->buy_movie(stoi(param[FILM_ID]));

}

void CommandHandler::post_rate(std::map<std::string, std::string> param) {
	vector<string> list = {FILM_ID, SCORE};
	check_param_with_list(list, param);

	net->rate(stoi(param[FILM_ID]), stoi(param[SCORE]));

}

void CommandHandler::post_comment(std::map<std::string, std::string> param) {
	vector<string> list = {FILM_ID, CONTENT};
	check_param_with_list(list, param);

	net->post_comment(stoi(param[FILM_ID]), param[CONTENT]);

}

void CommandHandler::process_request(string command) {
	vector<string> tokens = break_into_tokens(command);
	check_request(tokens);
	string method = tokens[0];
	if(method == ACTION_POST) {
		handle_post(tokens);
	} else if(method == ACTION_GET) {
		handle_get(tokens);
	}
}