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
	Movie* get_movie(int film_id);
	void edit_movie(int id, std::map<std::string, std::string> parameters);
	void add_reply_comment(int film_id, int comment_id, std::string content);	
	int get_worth(int film_id);
	void rate(int film_id, int score);
	void post_comment(int film_id, std::string content, User* commenter);
	void delete_comment(int film_id, int comment_id);
	void make_unavailable(int film_id);

	bool is_forbiden(int id, std::vector<int> forbiden_id);

	int get_price(int film_id);
	std::string get_name(int film_id);
	User* get_publisher(int film_id);

	void check_film_id(int film_id);

	std::vector<std::vector<std::string>> get_published_movie_data_table();
	std::map<std::string, std::string> get_movie_base_data(int film_id);
	std::vector<std::vector<std::string>> get_comment_data(int film_id);
	int find_best(std::vector<int>& forbiden_id);
private:
	SequenceGenerator id_generator;
	std::map<int, Movie*> movies;
};

#endif