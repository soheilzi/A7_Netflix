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

void UI::show_fine_state() {
	cout<<FINE_STATE<<endl;
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

void UI::show_notifications(std::vector<std::string> notifs) {
	cout<<NOTIFICATIONS_HEADER <<endl;
	for(int i = 0; i < notifs.size(); i++) {
		cout<<i + 1<<". "<< notifs[i]<<endl;
	}
}

void UI::show_unread_notifs() {
	vector<string> notifs = net->get_unread_notifs();
	show_notifications(notifs);
}

void UI::show_notifs(std::map<std::string, std::string> param) {
	vector<string> notifs = net->get_notifs(param);
	show_notifications(notifs);
}

void UI::show_published(std::map<std::string, std::string> param) {
	vector<vector<string>> table = net->get_published(param);
	show_table_movie(table, param);
}

void UI::show_purchased(std::map<std::string, std::string> param) {
	vector<vector<string>> table = net->get_purchased(param);
	show_table_movie(table, param);

}

void UI::show_movies(std::map<std::string, std::string> param) {
	vector<vector<string>> table = net->get_movies_data(param);
	show_table_movie(table, param);
}

void UI::show_movie_base(map<string, string> base_data) {
	cout<<"Details of Film " << base_data[B_NAME] << endl;
	cout<<"Id = "<<base_data[B_ID]<<endl;
	cout<<"Director = "<<base_data[B_DIRECTOR]<<endl;
	cout<<"Length = " << base_data[B_LENGTH] << endl;
	cout<<"Year = " << base_data[B_YEAR] << endl;
	cout<<"Summary = " << base_data[B_SUMMARY] << endl;
	cout<<"Rate = " << base_data[B_RATE] << endl;
	cout<<"Price = " << base_data[B_PRICE] << endl;

	cout<<endl;
}

void UI::show_movie_comments(std::vector<std::vector<std::string>> comment_table) {
	cout<<COMMENT_TITLE<<endl<<endl;
	for(int i = 0; i < comment_table.size(); i++) {
		cout<<comment_table[i][COMMENT_IDD]<<". "<<comment_table[i][COMMENT_MESSAGE]<<endl;
		if(!(comment_table[i][COMMENT_REPLY] == ""))
			cout<<comment_table[i][COMMENT_IDD]<<".1. "<<comment_table[i][COMMENT_REPLY]<<endl;
	}
	if(comment_table.size() != 0)
		cout<<endl<<endl;
}

void UI::show_movie_recommendations(std::vector<std::vector<std::string>>& recommendation) {
	cout<<RECOMMENDATION_TITLE<<endl<<RECOMMENDATION_HEADER<<endl;
	for(int i = 0; i < recommendation.size(); i++) {
		cout<<i + 1 <<". "
			<<recommendation[i][R_ID]<<SPLITER
			<<recommendation[i][R_NAME]<<SPLITER
			<<recommendation[i][R_LENGTH]<<SPLITER
			<<recommendation[i][R_DIRECTOR]<<endl;
	}
}

void UI::show_movie_data(std::map<std::string, std::string> param) {
	map<string, string> base_data = net->get_movie_base_data(stoi(param[FILM_ID]));
	vector<vector<string>> comment_data = net->get_comment_data(stoi(param[FILM_ID]));
	vector<vector<string>> recommendation = net->get_recommendation();
	show_movie_base(base_data);
	show_movie_comments(comment_data);
	show_movie_recommendations(recommendation);
}