#ifndef __movie
#define __movie

#include <string>
#include "comment.h"
#include "config.h"
#include "user.h"

class User;

class Movie {
public:
	Movie(int _id, User* _publisher, std::string _name, int _year, int _length, int _price,
	 std::string _summary, std::string _director);
private:
	int id;

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