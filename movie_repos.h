#ifndef __movie_repos
#define __movie_repos

#include "movie.h"
#include "sequence_generator.h"
#include <vector>
#include <string>
#include <map>

class Movie_repos {
public:
	void add_movies()
private:
	SequenceGenerator id_generator;
	std::map<int, Movie*> movies;
};

#endif