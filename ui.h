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
	void show_published_movie_record(std::vector<std::string> movie_record, int row_num);
	void show_published(std::map<std::string, std::string> param);

	bool filter_by_condition(std::map<std::string, std::string> param, std::vector<std::string> movie_record);
	bool filter_movie(std::string key, std::string value, std::vector<std::string> movie_record); 
private:
	Network* net;
};

#endif