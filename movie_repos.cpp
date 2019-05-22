#include "movie_repos.h"
#include <iostream>
#include "user.h"
using namespace std;

MovieRepos::MovieRepos() : id_generator() {}

Movie* MovieRepos::add_movie(User* publisher, std::string name, int length, int year,
 int price, std::string summary, std::string director) {
	int id = id_generator.get_number();
	movies[id] = new Movie(id, publisher, name, year, length, price, summary, director);
	return movies[id];
}

void MovieRepos::edit_movie(int film_id, std::map<std::string, std::string> parameters) {
	check_film_id(film_id);
	movies[film_id]->edit(parameters);
}

void MovieRepos::add_reply_comment(int film_id, int comment_id, std::string content) {
	check_film_id(film_id);
	movies[film_id]->add_reply_comment(comment_id, content);
}

std::vector<std::vector<std::string>> MovieRepos::get_published_movie_data_table() {
	vector<vector<string>> movies_data_table;
	for(const auto& elem : movies) {
		if(elem.second->is_avalable()){
			movies_data_table.push_back(elem.second->get_data());
		}
	}

	return movies_data_table;
}

bool MovieRepos::is_forbiden(int id, std::vector<int> forbiden_id) {
	for(int i = 0; i < forbiden_id.size(); i++) {
		if(forbiden_id[i] == id)
			return true;
	}
	return false;
}

int MovieRepos::find_best(std::vector<int>& forbiden_id) {
	int best_rate = -1;
	int best_id;
	for(const auto& elem : movies) {
		if(elem.second->get_rate() > best_rate && elem.second->is_avalable() && !is_forbiden(elem.first, forbiden_id)) {
			best_rate = elem.second->get_rate();
			best_id = elem.first;
		}
	}
	forbiden_id.push_back(best_id);
	return best_id;
}

std::vector<std::vector<std::string>> MovieRepos::get_recommendation() {
	vector<vector<string>> recommendation;
	vector<int> forbiden_id;
	for(int i = 0; i < 4 && i < movies.size(); i++) {
		int best_id = find_best(forbiden_id);
		if(movies.find(best_id) != movies.end())
			recommendation.push_back(movies[best_id]->get_brief_data());
	}
	return recommendation;
}

Movie* MovieRepos::get_movie(int film_id) {
	check_film_id(film_id);
	return movies[film_id];
}

std::map<std::string, std::string> MovieRepos::get_movie_base_data(int film_id) {
	check_film_id(film_id);
	return movies[film_id]->get_movie_base_data();
}

std::vector<std::vector<std::string>> MovieRepos::get_comment_data(int film_id) {
	return movies[film_id]->get_comment_data();
}

int MovieRepos::get_price(int film_id) {
	check_film_id(film_id);
	return movies[film_id]->get_price();
}

std::string MovieRepos::get_name(int film_id) {
	check_film_id(film_id);
	return movies[film_id]->get_name();
}

User* MovieRepos::get_publisher(int film_id) {
	check_film_id(film_id);
	return movies[film_id]->get_publisher();
}

void MovieRepos::buy_movie(int film_id) {
	check_film_id(film_id);
	movies[film_id]->make_sale();
}

void MovieRepos::rate(int film_id, int score) {
	check_film_id(film_id);
	movies[film_id]->set_score(score);
}

void MovieRepos::check_film_id(int film_id) {
	if(movies.find(film_id) == movies.end() || movies[film_id]->is_avalable() == false)
		throw NotFound();
}

void MovieRepos::post_comment(int film_id, std::string content, User* commenter) {
	check_film_id(film_id);
	movies[film_id]->add_comment(content, commenter);
}

void MovieRepos::delete_comment(int film_id, int comment_id) {
	check_film_id(film_id);
	movies[film_id]->delete_comment(comment_id);
}

void MovieRepos::make_unavailable(int film_id) {
	check_film_id(film_id);
	movies[film_id]->make_unavailable();
}