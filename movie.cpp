#include "movie.h"

using namespace std;

Movie::Movie(int _id, std::string _name, int _year, int _length, int _price, std::string _summary, std::string _director) 
	: comments() {
	id = _id;
	name = _name;
	year = _year;
	lenght = _lenght;
	price = _price;
	summary = _summary;
	director = _director;
	rate = 0;
	rater_count = 0;
	sales_publisher = 0;
}
