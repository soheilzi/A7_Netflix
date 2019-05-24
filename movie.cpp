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
	avalable = true;
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

int Movie::get_rate() {
	return rate;
}

bool Movie::is_avalable() {
	return avalable;
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
}

void Movie::add_comment(std::string content, User* commenter) {
	comments.add_comment(content, commenter);
}

void Movie::delete_comment(int comment_id) {
	comments.delete_comment(comment_id);
}

std::vector<std::string> Movie::get_data() {
	vector<string> data;
	data.push_back(to_string(id));
	data.push_back(name);
	data.push_back(to_string(length));
	data.push_back(to_string(price));
	ostringstream _rate;
	_rate.precision(0);
	_rate << fixed << rate;
	data.push_back(_rate.str());
	data.push_back(to_string(year));
	data.push_back(director);

	return data;
}

std::vector<std::string> Movie::get_brief_data() {
	vector<string> data;

	if(avalable == false)
		return data;
	data.push_back(to_string(id));
	data.push_back(name);
	data.push_back(to_string(length));
	data.push_back(director);

	return data;
}

#define B_ID "id"
#define B_NAME "name"
#define B_DIRECTOR "director"
#define B_LENGTH "length"
#define B_YEAR "year"
#define B_SUMMARY "summary"
#define B_PRICE "price"
#define B_RATE "rate"

map<string, string> Movie::get_movie_base_data() {
	map<string, string> base_data;

	base_data[B_ID] = to_string(id);
	base_data[B_NAME] = name;
	base_data[B_DIRECTOR] = director;
	base_data[B_LENGTH] = to_string(length);
	base_data[B_YEAR] = to_string(year);
	base_data[B_SUMMARY] = summary;
	base_data[B_PRICE] = to_string(price);
	ostringstream _rate;
	_rate.precision(0);
	_rate << fixed << rate;
	base_data[B_RATE] = _rate.str();
	
	return base_data;
}

std::vector<std::vector<std::string>> Movie::get_comment_data() {
	return comments.get_comments_data();
}
void Movie::make_unavailable() {
	avalable = false;
}