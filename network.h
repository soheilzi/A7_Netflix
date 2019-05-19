#ifndef __network
#define __network

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <exception>

#include "exceptions.h"
#include "config.h"
#include "user.h"
#include "user_repos.h"
#include "movie_repos.h"
#include "notification.h"

class Network {
public:
	Network();
	void signup_user(std::string email, std::string username, std::string password, int age, std::string publisher = _FALSE);
	void login_user(std::string username, std::string password);
	void add_movie(std::string name, int year, int length, int price, std::string summary, std::string dirctor);
	void edit_movie(int id, std::map<std::string, std::string> parameters);
	void get_money_publisher();
	void buy_movie(int film_id);
	void rate(int film_id, int score);
	void get_money_user(int amount);
	void post_reply(int film_id, int comment_id, std::string content);
	void post_followers(int id);
	void post_comment(int film_id, std::string content);
	void delete_film(int film_id);
	void delete_comment(int film_id, int comment_id);
	std::vector<std::vector<std::string>> get_followers();
	std::vector<std::vector<std::string>> get_published();
	
private:
	int money;
	User* user;
	MovieRepos movies;
	UserRepos users;
	bool login;
};

#endif