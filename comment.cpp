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

std::vector<std::string> Comment::get_full_data() const {
	vector<string> data;

	data.push_back(to_string(id));
	data.push_back(content);
	data.push_back(reply);

	return data;
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
	cout<<"comment with id : "<<id << "and content : "<< content<<endl;
}

void CommentRepos::delete_comment(int comment_id) {
	if(comments.find(comment_id) == comments.end())
		throw BadRequest();
	comments.erase(comment_id);
	cout<<"comment with id : "<<comment_id <<" erased\n";
}

std::vector<std::vector<std::string>> CommentRepos::get_comments_data() {
	std::vector<std::vector<std::string>> comments_data;
	for(const auto& elem : comments) {
		comments_data.push_back(elem.second.get_full_data());
	}
	return comments_data;
}