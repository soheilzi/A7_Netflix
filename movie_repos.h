#ifndef __movie_repos
#define __movie_repos

#include "movie.h"
#include "sequence_generator.h"
#include <vector>
#include <string>
#include <map>

class MovieRepos {
public:
	Movie* add_movie(User* publisher, std::string name, int length, int year, int price, std::string summary, std::string director);
private:
	SequenceGenerator id_generator;
	std::map<int, Movie*> movies;
};

#endif