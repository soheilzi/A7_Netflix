#include "user_repos.h"

using namespace std;

UserRepos::UserRepos() : id_generator() {
	users[ADMIN_USERNAME] = new User(0, ADMIN_USERNAME, ADMIN_PASSWORD, ADMIN_EMAIL, ADMIN_AGE);
}

User* UserRepos::add_user(std::string username, std::string password, std::string email, int age, bool publisher) {
	if(users.find(username) != users.end())
		throw DuplicateUser();
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

User* UserRepos::get_user_by_id(int id) {
	for(const auto& elem : users) {
		if(elem.second->get_id() == id)
			return elem.second;
	}
	throw BadRequest();
}

std::string UserRepos::get_username(int user_id) {
	for(const auto& elem : users) {
		if(elem.second->get_id() == user_id)
			return elem.second->get_username(); 
	}
	return "";
}