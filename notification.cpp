#include "notification.h"

using namespace std;

Notification::Notification() {
	read = false;
}

bool Notification::is_read() {
	return read;
}

void Notification::mark_as_read(){
	read = true;
}

Notif_from_publisher::Notif_from_publisher(std::string _publisher_name, int _publisher_id) : Notification() {
	publisher_name = _publisher_name;
	publisher_id = _publisher_id;
}

Notif_from_user::Notif_from_user(std::string _user_name, int _user_id, string _film_name, int _film_id) : Notification() {
	user_name = _user_name;
	user_id = _user_id;
	film_name = _film_name;
	film_id = _film_id;
}


Notif_reply_comment::Notif_reply_comment(std::string _publisher_name, int _publisher_id)
	: Notif_from_publisher(_publisher_name, _publisher_id) {}

Notif_new_film::Notif_new_film(std::string _publisher_name, int _publisher_id)
	: Notif_from_publisher(_publisher_name, _publisher_id) {}



Notif_movie_sale::Notif_movie_sale(std::string _user_name, int _user_id, string _film_name, int _film_id)
	: Notif_from_user(_user_name, _user_id, _film_name, film_id) {cout<<"soled\n";}

Notif_movie_rate::Notif_movie_rate(std::string _user_name, int _user_id, string _film_name, int _film_id)
	: Notif_from_user(_user_name, _user_id, _film_name, film_id) {}

Notif_movie_comment::Notif_movie_comment(std::string _user_name, int _user_id, string _film_name, int _film_id)
	: Notif_from_user(_user_name, _user_id, _film_name, film_id) {}

Notif_new_follower::Notif_new_follower(std::string _user_name, int _user_id)
	: Notif_from_user(_user_name, _user_id, "", 0) {}


string Notif_reply_comment::get_notif() {
	read = true;
	return "Publisher " + publisher_name + " with id " + to_string(publisher_id) + "reply to your comment.";
}

string Notif_new_film::get_notif() {
	read = true;
	return "Publisher " + publisher_name + " with id " + to_string(publisher_id) + "register new film.";
}

string Notif_movie_sale::get_notif() {
	read = true;
	return "User " + user_name + " with id " + to_string(user_id) + " buy your film " + film_name + " with id " + to_string(film_id) + ".";
}

string Notif_movie_rate::get_notif() {
	read = true;
	return "User " + user_name + " with id " + to_string(user_id) + " rate your film " + film_name + " with id " + to_string(film_id) + ".";
}

string Notif_movie_comment::get_notif() {
	read = true;
	return "User " + user_name + " with id " + to_string(user_id) + " comment on your film " + film_name + " with id " + to_string(film_id) + ".";
}

string Notif_new_follower::get_notif() {
	read = true;
	return "User " + user_name + " with id " + to_string(user_id) + " follow you.";
}
