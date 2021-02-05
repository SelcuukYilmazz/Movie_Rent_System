#pragma once
#include <string>
#include"Node.h"


class LibrarySystem {

public:
	std::string argument;
	LibrarySystem();
	LibrarySystem(std::string argument);
	~LibrarySystem();

	void addMovie(int movie_id, std::string movie_name, int movie_year);
	void deleteMovie(int movie_id);
	void addUser(int user_id, std::string user_name);
	void deleteUser(int user_id);
	void checkoutMovie(int movie_id, int user_id);
	void showUser(int user_id);
	void showMovie(int movie_id);
	void showAllMovies();
	void returnMovie(int movie_id);

};