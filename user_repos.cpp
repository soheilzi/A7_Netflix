#include "user_repos.h"

using namespace std;

void UserRepos::add_user(std::string _username, std::string _password, std::string _email, int _age) {
	int id = id_generator.get_number();
	users[_username] = new User(id, _username, _password, _email, _age);
}

bool UserRepos::correct_user_and_pass(string username, string password) {
	return password == users[username]->get_password();
}