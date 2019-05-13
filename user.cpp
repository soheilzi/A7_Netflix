#include "user.h"

using namespace std;

User::User() {}

User::User(int _id, std::string _username, std::string _password, std::string _email, int _age) {
	id  = _id;
	username = _username;
	password = _password;
	email = _email;
	age = _age;
	money = DEFAULT_START_MONEY;
}

string User::get_username() {
	return username;
}

string User::get_password() {
	return password;
}

string User::show() {
	return to_string(id) + " | " + username + " | " + email;
}

void User::show_followers() {
	throw PermissionDenied();
}