#include "comment.h"


using namespace std;

Comment::Comment(int _id, std::string _content, User* _user) {
	user = _user;
	content = _content;
	id = _id;
	reply = "";
}

Comment::Comment(){}

string Comment::get_content() {
	return content;
}

string Comment::get_reply() {
	return reply;
}

User* Comment::get_user() {
	return user;
}

void Comment::set_reply(string _reply) {
	reply = _reply;
	cout<<"reply : "<<reply << " added" <<endl;
}



CommentRepos::CommentRepos() : id_generator() {}

void CommentRepos::reply(int id, std::string content) {
	if(comments.find(id) == comments.end())
		throw BadRequest();
	comments[id].set_reply(content);
}

void CommentRepos::add_comment(std::string content, User* user) {
	int id = id_generator.get_number();
	comments[id] = Comment(id, content, user);
}

void CommentRepos::delete_comment(int id) {
	comments.erase(id);
}