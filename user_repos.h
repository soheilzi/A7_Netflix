#ifndef __user_repos
#define __user_repos

#include "user.h"
#include "sequence_generator.h"
#include <map>
#include <string>


class UserRepos {
public:
	void add_user(std::string _username, std::string _password, std::string _email, int _age);
	bool correct_user_and_pass(std::string _username, std::string _password);
private:
	SequenceGenerator id_generator;
	std::map<std::string, User*> users;
};

#endif