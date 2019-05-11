#ifndef __user
#define __user

#include <string>
#include <vector>
#include <map>

#include "config.h"
#include "movie.h"
#include "notification.h"

class User {
public:
protected:
	std::string user_name;
	std::string password;
	std::string email;
	int age;

	int id;

	int money;

	std::vector<User*> following;
	
	std::map<int, Movie*> movies_bought;

	Notification_repos notifications;
};

#endif