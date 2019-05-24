#include "matrix.h"

using namespace std;

MatrixMovie::MatrixMovie() {}

bool MatrixMovie::movie_exists(Movie* movie) {
	for(int i = 0; i < movies_added.size(); i++) 
		if(movies_added[i] == movie)
			return true;
	return false;
}	

void MatrixMovie::add_movie(Movie* movie) {
	if(movie_exists(movie))
		return;
	for(int i = 0; i < movies_added.size(); i++) {
		matrix[movie][movies_added[i]] = 0;
		matrix[movies_added[i]][movie] = 0;
	}
	matrix[movie][movie] = 0;
	movies_added.push_back(movie);
}

void MatrixMovie::make_relation(Movie* m1, Movie* m2) {
	if(!movie_exists(m1) || !movie_exists(m2))
		throw BadRequest();
	matrix[m1][m2]++;
	matrix[m2][m1]++;
}

void MatrixMovie::make_relation(std::vector<Movie*> nodes, Movie* m) {
	for(int i = 0; i < nodes.size(); i++) {
		make_relation(nodes[i], m);
	}
}

void MatrixMovie::print_matrix() {
	cout<<"Number : "<<movies_added.size()<<endl;
	for(int i = 0; i < movies_added.size(); i++) {
		for(int j = 0; j < movies_added.size(); j++) {
			cout<<matrix[movies_added[i]][movies_added[j]]<<" ";
		}
		cout<<endl;
	}
}

bool is_selected(std::vector<Movie*> selected, Movie* m){
	for(int i = 0; i < selected.size(); i++)
		if(selected[i] == m)
			return true;
	return false;
}

Movie* MatrixMovie::get_top(Movie* movie, std::vector<Movie*> selected) {
	int max = -1;
	Movie* max_add = 0;
	for(int i = 0; i < movies_added.size(); i++) {
		if(!is_selected(selected, movies_added[i]) && matrix[movie][movies_added[i]] > max && movies_added[i] != movie) {
			max = matrix[movie][movies_added[i]];
			max_add = movies_added[i];
		}
	}
	if(max == -1)
		return 0;
	return max_add;
}

std::vector<Movie*> MatrixMovie::sort_top(Movie* movie) {
	vector<Movie*> selected;
	for(int i = 0; i < movies_added.size(); i++) {
		if(get_top(movie, selected) == 0)
			break;
		selected.push_back(get_top(movie, selected));
	}
	return selected;
}

std::vector<std::vector<std::string>> MatrixMovie::get_recommendation(Movie* movie, User* user) {
	std::vector<Movie*> recom_movies = sort_top(movie);
	vector<vector<string>> recommendation;
	for(int i = 0; i < recom_movies.size() && recommendation.size() < 4; i++) {
		if(recom_movies[i]->get_brief_data().size() != 0 && !(user->owns_movie(recom_movies[i])))
			recommendation.push_back(recom_movies[i]->get_brief_data());
	}
	return recommendation;
}