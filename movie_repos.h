#ifndef __movie_repos
#define __movie_repos

#include "movie.h"
#include <vector>
#include <string>
#include <map>

class Movie_repos {
public:
private:
	std::map<int, Movie*> movies;
};

#endif