#include "publisher.h"

using namespace std;

Publisher::Publisher(int _id, std::string _username, std::string _password, std::string _email, int _age)
	: User(){}

void Publisher::show_followers() {
	cout << "List of Followers" << endl;
	cout << FOLLOWERS_HEADER << endl;
	for(int i = 0; i < followers.size(); i++) {
		cout << i + 1 << DOT << followers[i]->show() << endl;
	}
}

void add_movie(Movie* movie) {
	movies[movie->get_id()] = movie;
}

bool is_publisher() {
	return true;
}