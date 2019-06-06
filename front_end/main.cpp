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

        server.post("/logout", new LogoutHandler(&net));

        server.get("/", new HomeHandler(&net));
        server.post("/", new FilterHandler(&net));

        server.get("/addFilm", new ShowPage("static/add_film.html"));
        server.post("/addFilm", new AddFilmHandler(&net));

        server.get("/error", new ErrorHandler("static/error.html"));

        server.post("/deleteMovie", new DeleteHandler(&net));

        server.get("/profile", new ProfileHandler(&net));
        server.post("/profile", new MoneyHandler(&net));

        server.post("/viewMovie", new DetailHandler(&net));

        server.post("/buyFilm", new BuyHandler(&net));

        server.post("/comment", new CommentHandler(&net));

        server.post("/rate", new RateHandler(&net));

        server.run();
    } catch (Server::Exception e) {
        cerr << e.getMessage() << endl;
    }
}
