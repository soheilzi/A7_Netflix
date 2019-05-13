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
	
	virtual void show_followers();

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