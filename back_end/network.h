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
#include "matrix.h"

class Network {
public:
	Network();
	void signup_user(std::string email, std::string username, std::string password, int age, std::string publisher = _FALSE);
	void login_user(std::string username, std::string password);
	void add_movie(std::string name, int year, int length, int price, std::string summary, std::string dirctor);
	int get_credit();
	int get_sessionId();
	int make_sessionId();
	std::string get_username(int userId);
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
	void set_dir_filter(std::string director);
	void logout();
	bool publisher_is_logged();
	bool user_is_logged();
	bool user_owns_movie(int film_id);
	std::string get_dir_to_filter_by();
	std::vector<std::string> get_unread_notifs();
	std::vector<std::string> get_notifs(std::map<std::string, std::string> param);
	std::vector<std::vector<std::string>> get_followers();
	std::vector<std::vector<std::string>> get_published(std::map<std::string, std::string> param);
	std::vector<std::vector<std::string>> get_movies(std::map<std::string, std::string> param);
	std::vector<std::vector<std::string>> get_purchased(std::map<std::string, std::string> param);
	std::vector<std::vector<std::string>> get_movies_data(std::map<std::string, std::string> param);

	bool has_condition(std::string key, std::string value, std::vector<std::string> movie_record);
	bool filter_movie(std::vector<std::string> movie_record, std::map<std::string, std::string> param);
	std::vector<std::vector<std::string>> filter_movies(std::vector<std::vector<std::string>> movie_table, std::map<std::string, std::string> param);
	std::map<std::string, std::string> get_movie_base_data(int film_id);
	std::vector<std::vector<std::string>> get_comment_data(int film_id);
	std::vector<std::vector<std::string>> get_recommendation(int film_id);
private:
	int money;
	User* user;
	std::string dir_to_filter_by;
	std::map<int, User*> sessions;
	SequenceGenerator session_gen;
	std::map<User*, int> dept;
	bool signed_in;
	MovieRepos movies;
	UserRepos users;
	bool login;
	MatrixMovie graph;
};

#endif