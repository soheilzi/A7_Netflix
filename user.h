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
	void add_following(User* user);
	void send_notif(Notification*);
	
	virtual void show_followers();
	virtual void add_movie(Movie*);
	virtual bool is_publisher();
	virtual bool published_movie(int id);
	virtual int calculate_debt();

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