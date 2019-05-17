#ifndef __comment
#define __comment

#include <map>
#include <vector>
#include <string>
#include <iostream>
#include "sequence_generator.h"
#include "exceptions.h"
#include "config.h"

class User;

class Comment {
public:
	Comment(int _id, std::string _content, User* _user);
	Comment();
	void set_reply(std::string _reply);

	std::string get_content();
	std::string get_reply();
	User* get_user();
private:
	std::string content;
	std::string reply;
	int id;
	User* user;
};

class CommentRepos {
public:
	CommentRepos();
	void reply(int id, std::string content);
	void add_comment(std::string content, User* user);
	void delete_comment(int id);
private:
	SequenceGenerator id_generator;
	std::map<int, Comment> comments;
};

#endif