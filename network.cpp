#include "network.h"

using namespace std;

Network::Network() {
	money = DEFAULT_NET_MONEY
	login = false;
}

void Network::signup_user(std::string email, std::string username, std::string password, int age, bool publisher = false) {
	user = users.add_user(username, password, email, age);
}

void Network::login(string username, string password) {
	if(users.correct_user_and_pass(username, password)) {
		user = users.get_user(username); 
	} else {
		throw BadRequest();
	}
}

void Network::add_movie(std::string name, int year, int length, int price, std::string summary, std::string director) {
	if(!user->is_publisher())
		throw PermissionDenied()
	Movie* temp = movies.add_movie(user, name, length, year, price, summary, director);
	user->add_movie(temp);
}