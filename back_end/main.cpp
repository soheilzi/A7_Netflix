#include <iostream>
#include <string>
#include <vector>

#include "network.h"
#include "ui.h"
#include "command_handler.h"
#include "exceptions.h"
#include "config.h"

using namespace std;

int main(int argc, char** argv) {
	Network net;
	UI ui(&net);
	CommandHandler cm(&net, &ui);
	string line;
	while(getline(cin, line)) {
		try{
			if(line == "")
				continue;
			cm.process_request(line);
		} catch(BadRequest ex) {
			cout << BADREQUEST << endl;
		} catch(PermissionDenied ex) {
			cout << PERMISSIONDENIED << endl; 
		} catch(NotFound ex) {
			cout << NOTFOUND << endl;
		}
	}
}