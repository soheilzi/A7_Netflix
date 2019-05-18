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
	void buy_movie(int film_id);
	void rate(int film_id, int score);
	void post_comment(int film_id, std::string content, User* commenter);

	int get_price(int film_id);
	std::string get_name(int film_id);
	User* get_publisher(int film_id);

	void check_film_id(int film_id);
private:
	SequenceGenerator id_generator;
	std::map<int, Movie*> movies;
};

#endif