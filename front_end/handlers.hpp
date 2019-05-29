#ifndef __handlers
#define __handlers

#include "../server/server.hpp"

class SignupHandler : public RequestHandler {
public:
    Response *callback(Request *);
};

#endif