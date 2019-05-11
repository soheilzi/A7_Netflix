#ifndef __movie
#define __movie

#include <string>
#include "comment.h"

class Movie {
public:
private:
	int id;

	std::string name;
	std::string summary;
	std::string director;
	int length;
	int price;
	int year;

	Comment_repos comments;

	float score;

	int sale_publisher;
};

#endif