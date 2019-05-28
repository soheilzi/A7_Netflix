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
void check_param_with_list(std::vector<std::string> list, std::map<std::string, std::string> param);
void check_is_in_param(std::map<std::string, std::string> param, std::vector<std::string> list);
void check_is_in_list(std::vector<std::string> list, std::map<std::string, std::string> param);

#endif