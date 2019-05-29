#include "handlers.hpp"

using namespace std;

SignupHandler::SignupHandler(Network* _net) : RequestHandler(), net(_net) {} 

Response* SignupHandler::callback(Request *req) {
    string username = req->getBodyParam("username");
    string password1 = req->getBodyParam("pwd1");
    string password2 = req->getBodyParam("pwd2");
    string email = req->getBodyParam("email");
    int age = stoi(req->getBodyParam("Age"));
    string publisher = "false";
    if(req->getBodyParam("publisher") == "on")
        publisher = "true";

    if(!(password1 == password2)) {
        Response *res = Response::redirect("/login");
        return res;
    }
    try {
        net->signup_user(email, username, password1, age, publisher);
        int cookie = net->make_sessionId();
        Response *res = Response::redirect("/");
        res->setSessionId(to_string(cookie));
        return res;
    } catch (Logedin ex){
        Response *res = Response::redirect("/logedin_error");
        return res;
    }
}
LoginHandler::LoginHandler(Network* _net) : RequestHandler(), net(_net) {}

Response* LoginHandler::callback(Request *req) {
    string username = req->getBodyParam("username");
    string password = req->getBodyParam("password");
}