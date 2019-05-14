#include "check_error.h"

using namespace std;

bool is_number(std::string s) {
	for(int i = 0; i < s.length(); i++) {
		if(s[i] < '0' || s[i] > '9')
			return false;
	}
	return true;
}