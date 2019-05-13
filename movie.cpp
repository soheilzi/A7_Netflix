#include "movie.h"

using namespace std;

Movie::Movie(int _id, User* _publisher, std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director) 
	: comments() {
	publisher = _publisher; 
	id = _id;
	name = _name;
	year = _year;
	length = _length;
	price = _price;
	summary = _summary;
	director = _director;
	rate = 0;
	rater_count = 0;
	sales_publisher = 0;
	is_avalable = true;
}

Movie::Movie() {}