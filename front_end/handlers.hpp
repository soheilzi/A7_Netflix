#ifndef __handlers
#define __handlers

#include <string>
#include <iostream>
#include "../server/server.hpp"
#include "../back_end/network.h"

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

#endif