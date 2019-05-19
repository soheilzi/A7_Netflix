#include "ui.h"

using namespace std;

UI::UI(Network* _net) : net(_net) {}

void UI::show_followers() {
	vector<vector<string>> table = net->get_followers();
	int row_min_id;
	cout << "List of Followers" << endl;
	cout << FOLLOWERS_HEADER << endl;
	for(int i = 0; i < table.size(); i++) {
		row_min_id = find_row_min_id(table);
		show_follower_record(table[row_min_id]);
		table.erase(table.begin() + row_min_id);
	}
} 

int UI::find_row_min_id(std::vector<std::vector<std::string>> table) {
	int min = stoi(table[0][0]);
	for(int i = 0; i < table.size(); i++) {
		if(stoi(table[i][0]) < min)
			min = stoi(table[i][0]);
	}
	return min;
}
void UI::show_follower_record(std::vector<std::string> follower_record) {
	cout<<follower_record[0] << SPLITER << follower_record[1] << SPLITER << follower_record[2] << endl;
}