#include <iostream>
#include <string>
#include <vector>

#include "network.h"


using namespace std;

int main(int argc, char** argv) {
	Network net;
	CommandHandler cm(&net);
	string line;
	while(getline(cin, line)) {
		cm.prosses_request(line);
	}
}