#include "user_repos.h"

using namespace std;

User* UserRepos::add_user(std::string username, std::string password, std::string email, int age, bool publisher) {
	if(users.find(username) != users.end())
		throw BadRequest();
	int id = id_generator.get_number();
	if(publisher)
		users[username] = new Publisher(id, username, password, email, age);
	else
		users[username] = new User(id, username, password, email, age);

	return users[username];
}

bool UserRepos::correct_user_and_pass(string username, string password) {
	if(users.find(username) != users.end())
		return password == users[username]->get_password();
	return false;

}

User* UserRepos::get_user(string username) {
	return users[username];
}