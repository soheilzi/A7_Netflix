#include "publisher.h"

using namespace std;

Publisher::Publisher(int _id, std::string _username, std::string _password, std::string _email, int _age)
	: User(_id, _username, _password, _email, _age) {}

vector<vector<string>> Publisher::get_followers_data_table() {
	vector<vector<string>> follower_data_table;
	for(int i = 0; i < followers.size(); i++) {
		follower_data_table.push_back(followers[i]->get_data());
	}

	return follower_data_table;
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

void Publisher::delete_film(int film_id) {
	movies.erase(film_id);
}