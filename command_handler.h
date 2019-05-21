#ifndef __command_handler
#define __command_handler

#include <string>
#include <map>
#include <vector>

#include "network.h"
#include "ui.h"
#include "config.h"
#include "exceptions.h"

class CommandHandler {
public:
	CommandHandler(Network* _net, UI* _ui);
	void process_request(std::string command);
	void check_request(std::vector<std::string> tokens);
	void handle_post(std::vector<std::string> tokens);
	void handle_get(std::vector<std::string> tokens);
	void handle_put(std::vector<std::string> tokens);
	void handle_delete(std::vector<std::string> tokens);

	void signup(std::map<std::string, std::string> param);
	void login(std::map<std::string, std::string> param);
	void post_film(std::map<std::string, std::string> param);
	void user_get_money(std::map<std::string, std::string> param);
	void post_reply(std::map<std::string, std::string> param);
	void post_followers(std::map<std::string, std::string> param);
	void post_buy(std::map<std::string, std::string> param);
	void post_rate(std::map<std::string, std::string> param);
	void post_comment(std::map<std::string, std::string> param);

	void put_films(std::map<std::string, std::string> param);

	void delete_film(std::map<std::string, std::string> param);
	void delete_comment(std::map<std::string, std::string> param);

	void show_published(std::map<std::string, std::string> param);
	void show_purchased(std::map<std::string, std::string> param); 
	void show_movies(std::map<std::string, std::string> param);
	void show_movie_data(std::map<std::string, std::string> param);
private:
	Network* net;
	UI* ui;
};

std::vector<std::string> break_into_tokens(std::string command);
std::map<std::string, std::string> make_param_map(std::vector<std::string> tokens);
std::vector<std::string> make_param_vect(std::vector<std::string> tokens, int start);
bool is_in_list(std::vector<std::string> list, std::map<std::string, std::string> param);

#endif