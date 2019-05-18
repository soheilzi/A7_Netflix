#include "network.h"

using namespace std;

Network::Network() {
	money = DEFAULT_NET_MONEY;
	login = false;
}

void Network::signup_user(std::string email, std::string username, std::string password, int age, string publisher) {
	cout<<"user added\n";
	bool publisher_flag;
	if(publisher == _FALSE){
		publisher_flag = false;
	} else {
		publisher_flag = true;
	}
	user = users.add_user(username, password, email, age, publisher_flag);
}

void Network::login_user(string username, string password) {
	if(users.correct_user_and_pass(username, password)) {
		user = users.get_user(username); 
		cout<<"login was a success\n";
	} else {
		throw BadRequest();
	}
}

void Network::add_movie(std::string name, int year, int length, int price, std::string summary, std::string director) {
	if(!user->is_publisher())
		throw PermissionDenied();
	Movie* temp = movies.add_movie(user, name, length, year, price, summary, director);
	user->add_movie(temp);
}

void Network::edit_movie(int id, std::map<std::string, std::string> parameters) {
	if(!user->is_publisher())
		throw PermissionDenied();
	if(!user->published_movie(id))
		throw PermissionDenied();
	movies.edit_movie(id, parameters);
}

void Network::get_money_publisher() {
	if(!user->is_publisher())
		throw PermissionDenied();
	int debt = user->calculate_debt();
	cout<<"net money : "<<money<<endl<<"debt : "<<debt<<endl;
	money -= debt;
	user->get_money(debt);
}

void Network::get_money_user(int amount) {
	user->get_money(amount);
}

void Network::post_reply(int film_id, int comment_id, std::string content) {
	if(!user->is_publisher())
		throw PermissionDenied();
	if(!user->published_movie(film_id))
		throw PermissionDenied();
	movies.add_reply_comment(film_id, comment_id, content);
}

void Network::post_followers(int id) {
	User* temp = users.get_user_by_id(id);
	if(!temp->is_publisher())
		throw BadRequest();
	user->add_following(temp);
	temp->send_notif(new Notif_new_follower(user->get_username(), user->get_id()));
}

void Network::buy_movie(int film_id) {
	int price = movies.get_price(film_id);
	if(user->get_credit() < price)
		throw BadRequest();
	user->buy(price);
	movies.buy_movie(film_id);
	movies.get_publisher(film_id)->send_notif(new Notif_movie_sale(user->get_username(), user->get_id(), movies.get_name(film_id), film_id));
}

void Network::rate(int film_id, int score) {
	if(score > 10 || score < 0)
		throw BadRequest();
	movies.rate(film_id, score);
}