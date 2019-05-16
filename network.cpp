#include "network.h"

using namespace std;

Network::Network() {
	money = DEFAULT_NET_MONEY;
	login = false;
}

void Network::signup_user(std::string email, std::string username, std::string password, int age, string publisher) {
	cout<<"user added\n";
	bool publisher_flag;
	if(publisher == _FALSE){
		publisher_flag = false;
	} else {
		publisher_flag = true;
	}
	user = users.add_user(username, password, email, age, publisher_flag);
}

void Network::login_user(string username, string password) {
	if(users.correct_user_and_pass(username, password)) {
		user = users.get_user(username); 
		cout<<"login was a succece\n";
	} else {
		throw BadRequest();
	}
}

void Network::add_movie(std::string name, int year, int length, int price, std::string summary, std::string director) {
	if(!user->is_publisher())
		throw PermissionDenied();
	Movie* temp = movies.add_movie(user, name, length, year, price, summary, director);
	user->add_movie(temp);
}

void Network::edit_movie(int id, std::map<std::string, std::string> parameters) {
	if(!user->published_movie(id))
		throw PermissionDenied();
	movies.edit_movie(id, parameters);
}