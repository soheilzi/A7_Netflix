#include "user_repos.h"

using namespace std;

User* UserRepos::add_user(std::string username, std::string password, std::string email, int age) {
	if(users.find(username) != users.end())
		throw BadRequest();
	int id = id_generator.get_number();
	users[username] = new User(id, username, password, email, age);
	return users[username];
}

bool UserRepos::correct_user_and_pass(string username, string password) {
	return password == users[username]->get_password();
}

User* UserRepos::get_user(string username) {
	return users[username];
}