#ifndef __movie
#define __movie

#include <string>
#include <exception>
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
	void edit_parts(std::string key, std::string val);
	void edit(std::map<std::string, std::string> parameters);
	int checkout_money();
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