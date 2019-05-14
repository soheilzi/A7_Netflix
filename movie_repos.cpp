#include "movie_repos.h"

using namespace std;

Movie* MovieRepos::add_movie(User* publisher, std::string name, int length, int year,
 int price, std::string summary, std::string director) {
	int id = id_generator.get_number();
	movies[id] = new Movie(id, publisher, name, year, length, price, summary, director);
}

void MovieRepos::edit_movie(int id, std::map<std::string, std::string> parameters) {
	movies[id]->edit(parameters);
}