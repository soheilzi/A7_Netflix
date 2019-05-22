using namespace std;

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

void check_is_in_list(vector<string> list, map<string, string> param) {
	bool flag = false;
	for(const auto& elem : param) {
		for(int i = 0; i < list.size(); i++) {
			if(list[i] == elem.first){
				flag = true;
				break;
			}
		}
		if(flag == false)
		flag = false;
	}
}

void check_is_in_param(map<string, string> param, vector<string> list) {
	bool flag = false;
	for(int i = 0; i < list.size(); i++) {
		for(const auto& elem : param) {
			if(list[i] == elem.first){
				flag = true;
				break;
			}
		}
		if(flag == false) 
		flag = false;
	}
}

int main() {
	map <string, string> param;
	param["name"] == "golam";
	param["age"] == "gm";
	param["lenght"] == "olam";

	vector<string> list ={"name" , "age", "lenght", "koko"};

	check_is_in_param(param, list);
	check_is_in_list(list, param);

}