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

int User::get_id() {
	return id;
}

string User::show() {
	return to_string(id) + " | " + username + " | " + email;
}

void User::show_followers() {
	throw PermissionDenied();
}

void User::add_movie(Movie* movie) {
	throw PermissionDenied();
}

bool User::is_publisher() {
	return false;
}

bool User::published_movie(int id) {
	return false;
}

int User::calculate_debt(){}

void User::get_money(int _money) {
	money += _money;
	cout<<"money : "<<money<<endl;
}

void User::add_following(User* user) {
	following.push_back(user);
	cout<<"user added\n";
}

void User::send_notif(Notification* notif) {
	notifications.add_notif(notif);
}
