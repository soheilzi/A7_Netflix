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

int User::get_credit() {
	return money;
}

void User::buy(int price) {
	money -= price;
}

void User::set_movie(Movie* movie) {
	movies_bought[movie->get_id()] = movie;
}

string User::show() {
	return to_string(id) + " | " + username + " | " + email;
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

void User::delete_film(int film_id) {throw PermissionDenied();}

std::vector<std::vector<std::string>> User::get_followers_data_table() {throw BadRequest();}
std::vector<std::vector<std::string>> User::get_published_movie_data_table() {throw BadRequest();}

std::vector<std::vector<std::string>> User::get_purchased_movie_data_table() {
	vector<vector<string>> movies_data_table;
	cout<<"Number Movies Bought : "<<movies_bought.size()<<endl;
	for(const auto& elem : movies_bought) {
		movies_data_table.push_back(elem.second->get_data());
	}

	return movies_data_table;
}

std::vector<std::string> User::get_data() {
	vector<string> data;

	data.push_back(to_string(id));
	data.push_back(username);
	data.push_back(email);
	
	return data;
}

void User::add_follower(User* user) {
	throw BadRequest();
}
