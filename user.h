#ifndef __user
#define __user

#include <string>
#include <vector>

class User {
public:
private:
	std::vector<User*> following;
	int money;
}

#endif