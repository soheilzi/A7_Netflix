#include "network.h"
#include "config.h"

using namespace std;

Network::Network() {
	money = DEFAULT_NET_MONEY;
	login = false;
	signed_in = false;
}

void Network::signup_user(std::string email, std::string username, std::string password, int age, string publisher) {
	bool publisher_flag;
	if(publisher == _FALSE){
		publisher_flag = false;
	} else {
		publisher_flag = true;
	}
	user = users.add_user(username, password, email, age, publisher_flag);
	signed_in = true;
}

void Network::login_user(string username, string password) {
	if(users.correct_user_and_pass(username, password)) {
		user = users.get_user(username); 
		signed_in = true;
	} else {
		throw BadRequest();
	}
}

void Network::add_movie(std::string name, int year, int length, int price, std::string summary, std::string director) {
	if(!signed_in)
		throw PermissionDenied();
	if(!user->is_publisher())
		throw PermissionDenied();
	Movie* temp = movies.add_movie(user, name, length, year, price, summary, director);
	user->add_movie(temp);
	graph.add_movie(temp);
	user->send_notif_to_followers();
}

void Network::edit_movie(int id, std::map<std::string, std::string> parameters) {
	if(!signed_in)
		throw PermissionDenied();
	if(!user->is_publisher())
		throw PermissionDenied();
	if(!user->published_movie(id))
		throw PermissionDenied();
	movies.edit_movie(id, parameters);
}

void Network::get_money_publisher() {
	if(!signed_in)
		throw PermissionDenied();
	if(!user->is_publisher())
		throw PermissionDenied();
	int debt = user->calculate_debt();
	money -= debt;
	user->get_money(debt);
}

void Network::get_money_user(int amount) {
	if(!signed_in)
		throw PermissionDenied();
	user->get_money(amount);
}

void Network::post_reply(int film_id, int comment_id, std::string content) {
	if(!signed_in)
		throw PermissionDenied();
	if(!user->is_publisher())
		throw PermissionDenied();
	if(!user->published_movie(film_id))
		throw PermissionDenied();
	movies.add_reply_comment(film_id, comment_id, content);
	user->send_notif(new Notif_reply_comment(movies.get_publisher(film_id)->get_username(), movies.get_publisher(film_id)->get_id()));
}

void Network::post_followers(int id) {
	if(!signed_in)
		throw PermissionDenied();
	User* temp = users.get_user_by_id(id);
	if(!temp->is_publisher())
		throw BadRequest();
	temp->add_follower(user);
	user->add_following(temp);
	temp->send_notif(new Notif_new_follower(user->get_username(), user->get_id()));
}

void Network::buy_movie(int film_id) {
	if(!signed_in)
		throw PermissionDenied();
	int price = movies.get_price(film_id);
	if(user->get_credit() < price)
		throw BadRequest();
	cout<<1<<"--------------------"<<endl;
	graph.print_matrix();
	graph.make_relation(user->get_purchased_movie(), movies.get_movie(film_id));
	graph.print_matrix();
	user->buy(price);
	user->set_movie(movies.get_movie(film_id));
	movies.buy_movie(film_id);
	movies.get_publisher(film_id)->send_notif(new Notif_movie_sale(user->get_username(), user->get_id(), movies.get_name(film_id), film_id));
}

void Network::rate(int film_id, int score) {
	if(!signed_in)
		throw PermissionDenied();
	if(score > 10 || score < 0)
		throw BadRequest();
	if(!user->owns_movie(film_id))
		throw PermissionDenied();
	movies.rate(film_id, score);
	movies.get_publisher(film_id)->send_notif(new Notif_movie_rate(user->get_username(), user->get_id(), movies.get_name(film_id), film_id));
}

void Network::post_comment(int film_id, std::string content) {
	if(!signed_in)
		throw PermissionDenied();
	if(!user->owns_movie(film_id))
		throw PermissionDenied();
	movies.post_comment(film_id, content, user);
	movies.get_publisher(film_id)->send_notif(new Notif_movie_comment(user->get_username(), user->get_id(), movies.get_name(film_id), film_id));
}

void Network::delete_film(int film_id) {
	if(!signed_in)
		throw PermissionDenied();
	if(!user->is_publisher())
		throw PermissionDenied();
	if(!user->published_movie(film_id))
		throw PermissionDenied();
	user->delete_film(film_id);
	movies.make_unavailable(film_id);
}

void Network::delete_comment(int film_id, int comment_id) {
	if(!signed_in)
		throw PermissionDenied();
	movies.check_film_id(film_id);
	if(!user->is_publisher())
		throw PermissionDenied();
	if(!user->published_movie(film_id))
		throw PermissionDenied();
	movies.delete_comment(film_id, comment_id);
}

std::vector<std::vector<std::string>> Network::get_followers() {
	if(!signed_in)
		throw PermissionDenied();
	if(!user->is_publisher())
		throw PermissionDenied();
	return user->get_followers_data_table();
}

std::vector<std::vector<std::string>> Network::get_published(std::map<std::string, std::string> param) {
	if(!signed_in)
		throw PermissionDenied();
	if(!user->is_publisher())
		throw PermissionDenied();

	return filter_movies(user->get_published_movie_data_table(), param);
}

std::vector<std::vector<std::string>> Network::get_purchased(std::map<std::string, std::string> param) {
	if(!signed_in)
		throw PermissionDenied();
	return filter_movies(user->get_purchased_movie_data_table(), param);
}

std::vector<std::vector<std::string>> Network::get_movies_data(std::map<std::string, std::string> param) {
	if(!signed_in)
		throw PermissionDenied();
	return filter_movies(movies.get_published_movie_data_table(), param);
}

bool Network::has_condition(std::string key, std::string value, std::vector<std::string> movie_record) {
	if(key == NAME) {
		if(!(movie_record[1] == value))
			return false;
	} else if(key == PRICE) {
		if(stoi(movie_record[2]) != stoi(value))
			return false;
	} else if(key == MIN_YEAR) {
		if(stoi(movie_record[3]) < stoi(value))
			return false;
	} else if(key == MIN_RATE) {
		if(stoi(movie_record[4]) < stoi(value))
			return false;
	} else if(key == MAX_YEAR) {
		if(stoi(movie_record[5]) > stoi(value))
			return false;
	} else if(key == DIRECTOR) {
		if(!(movie_record[6] == value))
			return false;
	}
	return true;
}

bool Network::filter_movie(std::vector<std::string> movie_record, std::map<std::string, std::string> param) {
	for(const auto& elem : param) {
		if(!has_condition(elem.first, elem.second, movie_record))
			return false;
	}
	return true;
}

std::vector<std::vector<std::string>> Network::filter_movies(std::vector<std::vector<std::string>> movie_table, std::map<std::string, std::string> param) {
	vector<vector<string>> filtered;
	for(int i = 0; i < movie_table.size(); i++) {
		if(filter_movie(movie_table[i], param))
			filtered.push_back(movie_table[i]);
	}
	return filtered;
}

std::map<std::string, std::string> Network::get_movie_base_data(int film_id) {
	if(!signed_in)
		throw PermissionDenied();
	return movies.get_movie_base_data(film_id);
}

std::vector<std::vector<std::string>> Network::get_comment_data(int film_id) {
	if(!signed_in)
		throw PermissionDenied();
	return movies.get_comment_data(film_id);
}

std::vector<std::vector<std::string>> Network::get_recommendation(int film_id) {
	if(!signed_in)
		throw PermissionDenied();
	return graph.get_recommendation(movies.get_movie(film_id), user);
}

std::vector<std::string> Network::get_unread_notifs() {
	if(!signed_in)
		throw PermissionDenied();
	return user->get_unread_notifs();
}

std::vector<std::string> Network::get_notifs(std::map<std::string, std::string> param) {
	if(!signed_in)
		throw PermissionDenied();
	return user->get_notifs(stoi(param[LIMIT]));
}