#ifndef __user
#define __user

#include <string>
#include <vector>
#include <map>

#include "exceptions.h"
#include "config.h"
#include "movie.h"
#include "notification_repos.h"

class User {
public:
	User(int _id, std::string _username, std::string _password, std::string _email, int _age);
	User();
	std::string show();
	std::string get_username();
	std::string get_password();
	int get_id();

	void get_money(int _money);
	void buy(int price);
	void set_movie(Movie*);

	std::vector<std::string> get_data();
	int get_credit();
	void add_following(User* user);
	void send_notif(Notification*);
	std::vector<std::vector<std::string>> get_purchased_movie_data_table();
	std::vector<std::string> get_unread_notifs();
	std::vector<std::string> get_notifs(int limit);
	
	virtual void delete_film(int film_id);
	virtual std::vector<std::vector<std::string>> get_followers_data_table();
	virtual std::vector<std::vector<std::string>> get_published_movie_data_table();
	virtual void add_movie(Movie*);
	virtual bool is_publisher();
	virtual bool published_movie(int id);
	virtual int calculate_debt();
	virtual void add_follower(User* user);

protected:
	std::string username;
	std::string password;
	std::string email;
	int age;

	int id;

	int money;

	std::vector<User*> following;
	
	std::map<int, Movie*> movies_bought;

	NotificationRepos notifications;
};

#endif