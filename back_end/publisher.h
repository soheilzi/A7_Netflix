#ifndef __publisher
#define __publisher

#include "user.h"
#include "movie.h"
#include "config.h"

class Publisher : public User {
public:
	Publisher(int _id, std::string _username, std::string _password, std::string _email, int _age);
	virtual std::vector<std::vector<std::string>> get_followers_data_table();
	virtual std::vector<std::vector<std::string>> get_published_movie_data_table();
	virtual void add_movie(Movie*);
	virtual bool is_publisher();
	virtual bool published_movie(int id);
	virtual void delete_film(int film_id);
	virtual void add_follower(User* user);
	virtual void send_notif_to_followers();
private:
	std::vector<User*> followers;
	std::map<int, Movie*> movies;
};

#endif