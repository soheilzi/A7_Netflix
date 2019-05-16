#ifndef __user_repos
#define __user_repos

#include "user.h"
#include "publisher.h"
#include "sequence_generator.h"
#include <map>
#include <string>


class UserRepos {
public:
	User* get_user(std::string username);
	User* add_user(std::string _username, std::string _password, std::string _email, int _age, bool publisher);
	bool correct_user_and_pass(std::string _username, std::string _password);
private:
	SequenceGenerator id_generator;
	std::map<std::string, User*> users;
};

#endif