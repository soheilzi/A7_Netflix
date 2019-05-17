#include "movie_repos.h"
#include <iostream>
using namespace std;

MovieRepos::MovieRepos() : id_generator() {}

Movie* MovieRepos::add_movie(User* publisher, std::string name, int length, int year,
 int price, std::string summary, std::string director) {
	int id = id_generator.get_number();
	movies[id] = new Movie(id, publisher, name, year, length, price, summary, director);
	return movies[id];
}

void MovieRepos::edit_movie(int id, std::map<std::string, std::string> parameters) {
	movies[id]->edit(parameters);
}

void MovieRepos::add_reply_comment(int film_id, int comment_id, std::string content) {
	if(movies.find(film_id) == movies.end())
		throw BadRequest();
	movies[film_id]->add_reply_comment(comment_id, content);
}