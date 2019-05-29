#include "handlers.hpp"
#include "my_server.hpp"
#include "../back_end/network.h"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {  
	Network net;
    try {
        MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
        server.setNotFoundErrPage("static/404.html");
        server.get("/signup", new ShowPage("static/signup.html"));
        server.post("/signup", new SignupHandler(&net));

        server.get("/login", new ShowPage("static/login.html"));
        server.post("/login", new LoginHandler(&net));


        server.run();
    } catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
}
