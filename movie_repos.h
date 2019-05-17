#ifndef __movie_repos
#define __movie_repos

#include "movie.h"
#include "sequence_generator.h"
#include "exceptions.h"
#include <vector>
#include <string>
#include <map>

class MovieRepos {
public:
	MovieRepos();
	Movie* add_movie(User* publisher, std::string name, int length, int year, int price, std::string summary, std::string director);
	void edit_movie(int id, std::map<std::string, std::string> parameters);
	void add_reply_comment(int film_id, int comment_id, std::string content);
private:
	SequenceGenerator id_generator;
	std::map<int, Movie*> movies;
};

#endif