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
	void show_movies(std::map<std::string, std::string> param);
	void show_movie_data(std::map<std::string, std::string> param);
	void show_movie_comments(std::vector<std::vector<std::string>> comment_table);
	void show_movie_base(std::map<std::string, std::string> base_data);

	void show_table_movie(std::vector<std::vector<std::string>> table, std::map<std::string, std::string> param);

private:
	Network* net;
};

#endif