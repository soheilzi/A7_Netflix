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

int Movie::checkout_money() {
	int temp = sales_publisher;
	sales_publisher = 0;
	return temp;
}

void Movie::add_reply_comment(int comment_id, std::string content) {
	comments.reply(comment_id, content);
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

#define WEAK_RATE 5
#define STRONG_RATE 8

#define WEAK_SALE .8
#define MEDIOM_SALE .9
#define STRONG_SALE .95

void Movie::make_sale() {
	float _rate = rate / (float)rater_count;
	if(_rate < WEAK_RATE){
		sales_publisher += price * WEAK_SALE;
	} else if(_rate >= WEAK_RATE && _rate < STRONG_RATE) {
		sales_publisher += price * MEDIOM_SALE;
	} else if(_rate >= STRONG_RATE) {
		sales_publisher += price * STRONG_SALE;
	}	
}

int Movie::get_id() {
	return id;
}

int Movie::get_price() {
	return price;
}

std::string Movie::get_name() {
	return name;
}

User* Movie::get_publisher() {
	return publisher;
}

void Movie::set_score(int score) {
	rater_count++;
	rate += score;
	cout<<"scored\n";
}

void Movie::add_comment(std::string content, User* commenter) {
	comments.add_comment(content, commenter);
}