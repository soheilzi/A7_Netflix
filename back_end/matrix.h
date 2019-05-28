#ifndef __matrix
#define __matrix

#include <map>
#include <vector>
#include <iostream>
#include "user.h"
#include "movie.h"
#include "exceptions.h"

class MatrixMovie {
public:
	MatrixMovie();
	void add_movie(Movie* movie);
	void make_relation(Movie* m1, Movie* m2);
	void make_relation(std::vector<Movie*> nodes, Movie* m);
	std::vector<Movie*> sort_top(Movie* movie);
	bool movie_exists(Movie* movie);
	std::vector<std::vector<std::string>> get_recommendation(Movie*, User* user);
	void print_matrix();
	Movie* get_top(Movie* movie, std::vector<Movie*> selected);
private:
	std::vector<Movie*> movies_added;
	std::map<Movie*, std::map<Movie*, int>> matrix;
};

#endif