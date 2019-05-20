#include "ui.h"
#include <iomanip>

using namespace std;

UI::UI(Network* _net) : net(_net) {}

void UI::show_followers() {
	vector<vector<string>> table = net->get_followers();
	cout << "List of Followers" << endl;
	cout << FOLLOWERS_HEADER << endl;
	int row_min_id;
	int table_size = table.size();
	for(int i = 0; i < table_size; i++) {
		row_min_id = find_row_min_id(table);
		show_follower_record(table[row_min_id], i + 1);
		table.erase(table.begin() + row_min_id);
	}
} 

int UI::find_row_min_id(std::vector<std::vector<std::string>> table) {
	int min_index = 0;
	int min = stoi(table[0][0]);
	for(int i = 0; i < table.size(); i++) {
		if(stoi(table[i][0]) < min){
			min = stoi(table[i][0]);
			min_index = i;
		}
	}
	return min_index;
}
void UI::show_follower_record(std::vector<std::string> follower_record, int row_num) {
	cout<< row_num << ". ";
	cout<< follower_record[0] << SPLITER << follower_record[1] << SPLITER << follower_record[2] << endl;
}

void UI::show_published_movie_record(std::vector<std::string> movie_record, int row_num) {
	cout<< row_num << ". ";
	cout<< movie_record[0] << SPLITER << movie_record[1] << SPLITER << movie_record[2] << SPLITER << movie_record[3] << SPLITER << movie_record[4] << SPLITER << movie_record[5] << SPLITER << movie_record[6] <<endl;
}

void UI::show_table_movie(std::vector<std::vector<std::string>> table, std::map<std::string, std::string> param) {
	cout << MOVIE_DATA_HEADER << endl;
	int row_min_id;
	int row = 1;
	int table_size = table.size();
	for(int i = 0; i < table_size; i++) {
		row_min_id = find_row_min_id(table);
		show_published_movie_record(table[row_min_id], i + 1);
		table.erase(table.begin() + row_min_id);
	}
}

void UI::show_published(std::map<std::string, std::string> param) {
	vector<vector<string>> table = net->get_published(param);
	show_table_movie(table, param);
}

void UI::show_movies(std::map<std::string, std::string> param) {
	vector<vector<string>> table = net->get_movies_data(param);
	show_table_movie(table, param);
}