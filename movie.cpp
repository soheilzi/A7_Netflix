#include "movie.h"
#include "check_error.h"

using namespace std;

Movie::Movie() {}

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

void Movie::edit_parts(string key, string val) {
	if(key == NAME_CHANGE) {
		name = val;

	} else if(key == LENGTH_CHANGE) {
		if(!is_number(val))
			throw BadRequest();
		length = stoi(val);

	} else if(key == YEAR_CHANGE) {
		if(!is_number(val))
			throw BadRequest();
		year = stoi(val);

	} else if(key == SUMMARY_CHANGE) {
		summary = val;

	} else if(key == DIRECTOR_CHANGE) {
		director = val;

	}

}

void Movie::edit(std::map<std::string, std::string> parameters) {
	for(const auto& elem : parameters) {
		edit_parts(elem.first, elem.second);
	}
}

int Movie::get_id() {
	return id;
}