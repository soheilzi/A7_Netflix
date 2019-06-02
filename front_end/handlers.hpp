#ifndef __handlers
#define __handlers

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include "../server/server.hpp"
#include "../back_end/network.h"
#include "../back_end/config.h"

class SignupHandler : public RequestHandler {
public:
    SignupHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class LoginHandler : public RequestHandler {
public:
    LoginHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class LogoutHandler : public RequestHandler {
public:
    LogoutHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class ErrorHandler : public TemplateHandler {
public:
  ErrorHandler(std::string filePath);
  std::map<std::string, std::string> handle(Request *req);
};

class HomeHandler : public RequestHandler {
public:
    HomeHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class AddFilmHandler : public RequestHandler {
public:
    AddFilmHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class FilterHandler : public RequestHandler {
public:
    FilterHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class DeleteHandler : public RequestHandler {
public:
    DeleteHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class ProfileHandler : public RequestHandler {
public:
    ProfileHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class MoneyHandler : public RequestHandler {
public:
    MoneyHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class DetailHandler : public RequestHandler {
public:
    DetailHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};

class BuyHandler : public RequestHandler {
public:
    BuyHandler(Network*);
    Response *callback(Request *);
private:
    Network* net;
};
#endif