#include "publisher.h"

using namespace std;

Publisher::Publisher() {}

void Publisher::show_followers() {
	cout << "List of Followers" << endl;
	cout << FOLLOWERS_HEADER << endl;
	for(int i = 0; i < followers.size(); i++) {
		cout << i + 1 << DOT << followers[i].show() << endl;
	}
}