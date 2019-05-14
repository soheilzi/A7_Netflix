using namespace std;

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>

int main() {
	string sentence = "And I feel fine...";
	istringstream iss(sentence);
	vector<string> tokens{istream_iterator<string>{iss}, istream_iterator<string>{}};
    for(int i = 0; i < tokens.size(); i++)
    	cout<< tokens[i]<<endl;
}