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
#include 

class Network {
public:
	Network();
	void signup_user(std::string email, std::string username, std::string password, int age, bool publisher = false);
	void login(std::string username, std::string password);
	void add_movie(std::string name, int year, int length, int price, std::string summary, std::string dirctor);
	void edit_movie(int id, std::map<std::string, std::string> parameters);
private:
	int money;
	User* user;
	MovieRepos movies;
	UserRepos users;
	bool login;
};

#endif