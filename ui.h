#ifndef __ui_
#define __ui_

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "network.h"
#include "config.h"

class UI {
public:
	UI(Network* _net);
	void show_followers();
	int find_row_min_id(std::vector<std::vector<std::string>>);
	void show_follower_record(std::vector<std::string> follower_record, int row_num);
private:
	Network* net;
};

#endif