#ifndef __check_error
#define __check_error

#include <string>
#include <vector>
#include <map>
#include "config.h"
#include "exceptions.h"

bool is_number(std::string);

void check_divider(std::string s);
void check_action(std::string s);
void check_command(std::string s); 

#endif