#ifndef __publisher
#define __publisher

#include "user.h"
#include "movie.h"
#include "config.h"

class Publisher : public User {
public:
private:
	std::vector<User*> followers;
	std::map<int, Movie*> movies;
};

#endif