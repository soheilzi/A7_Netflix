#ifndef __movie
#define __movie

#include <string>
#include <exception>
#include <sstream>
#include "exceptions.h"
#include "comment.h"
#include "config.h"

class User;

class Movie {
public:
	Movie(int _id, User* _publisher, std::string _name, int _year, int _length, int _price,
	 std::string _summary, std::string _director);
	Movie();

	int get_id();
	int get_price();
	std::string get_name();
	User* get_publisher();
	std::vector<std::string> get_data();

	void set_score(int score);
	void edit_parts(std::string key, std::string val);
	void edit(std::map<std::string, std::string> parameters);
	int checkout_money();
	void add_reply_comment(int comment_id, std::string content);
	void make_sale();
	void add_comment(std::string content, User* commenter);
	void delete_comment(int comment_id);
private:
	int id;

	bool is_avalable;

	std::string name;
	std::string summary;
	std::string director;

	User* publisher;

	int length;
	int price;
	int year;

	int rater_count;
	float rate;

	int sales_publisher;

	CommentRepos comments;

};

#endif