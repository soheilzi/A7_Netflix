#ifndef __network
#define __network

#include "config.h"
#include "user.h"
#include "user_repos.h"
#include "movie_repos.h"

class Network {
public:
	Network();
private:
	int money;
	User* user;
	MovieRepos movies;
	UserRepos users;
	bool login;
};

#endif