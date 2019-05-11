#ifndef __notif
#define __notif

#include <string>
#include <iostream>

class Notification {
public:
	Notification();
	bool is_read();
	virtual std::string get_notif() = 0;
protected:
	bool read;
};

class Notif_from_publisher : public Notification {
public:
	Notif_from_publisher(std::string _publisher_name, int _publisher_id);
	virtual std::string get_notif() = 0;
protected:
	std::string publisher_name;
	int publisher_id;
};

class Notif_from_user : public Notification {
public:
	Notif_from_user(std::string _user_name, int _user_id, std::string film_name, int film_id);
	virtual std::string get_notif() = 0;
protected:
	std::string user_name;
	int user_id;
	std::string film_name;
	int film_id;
};

class Notif_reply_comment : public Notif_from_publisher {
public:
	Notif_reply_comment(std::string _publisher_name, int _publisher_id);
	virtual std::string get_notif();
};

class Notif_new_film : public Notif_from_publisher {
public:
	Notif_new_film(std::string _publisher_name, int _publisher_id);
	virtual std::string get_notif();
};

class Notif_movie_sale : public Notif_from_user {
public:
	Notif_movie_sale(std::string _user_name, int _user_id, std::string _film_name, int _film_id);
	virtual std::string get_notif();
};

class Notif_movie_rate : public Notif_from_user {
public:
	Notif_movie_rate(std::string _user_name, int _user_id, std::string _film_name, int _film_id);
	virtual std::string get_notif();
};

class Notif_movie_comment : public Notif_from_user {
public:
	Notif_movie_comment(std::string _user_name, int _user_id, std::string _film_name, int _film_id);
	virtual std::string get_notif();
};



#endif