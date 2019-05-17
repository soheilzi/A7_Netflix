#include "publisher.h"

using namespace std;

Publisher::Publisher(int _id, std::string _username, std::string _password, std::string _email, int _age)
	: User(_id, _username, _password, _email, _age) {}

void Publisher::show_followers() {
	cout << "List of Followers" << endl;
	cout << FOLLOWERS_HEADER << endl;
	for(int i = 0; i < followers.size(); i++) {
		cout << i + 1 << DOT << followers[i]->show() << endl;
	}
}

void Publisher::add_movie(Movie* movie) {
	movies[movie->get_id()] = movie;
}

bool Publisher::is_publisher() {
	return true;
}

bool Publisher::published_movie(int id) {
	return movies.find(id) != movies.end();
}

int Publisher::calculate_debt() {
	int debt = 0;
	for(const auto& elem : movies) {
		debt += elem.second->checkout_money();
	} 
	return debt;
}