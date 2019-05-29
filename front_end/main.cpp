#include "handlers.hpp"
#include "my_server.hpp"
#include <iostream>

using namespace std;

int main(int argc, char **argv) {
    try {
        MyServer server(argc > 1 ? atoi(argv[1]) : 5000);
        server.setNotFoundErrPage("static/404.html");
        server.get("/signup", new ShowPage("static/signup.html"));
        server.post("/signup", new SignupHandler());
        server.run();
    } catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
}
