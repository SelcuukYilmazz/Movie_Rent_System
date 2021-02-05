#include "LibrarySystem.h"
#include <iostream>
#include <fstream>
using namespace std;

Node* MovieList = NULL;
Node* UserMovies = NULL;
LinkedList linklist;

LibrarySystem::LibrarySystem() {}

LibrarySystem::LibrarySystem(string argument) :argument(argument) { };

LibrarySystem::~LibrarySystem()
{
}

//This method adds movies to movie library, movies have significant id's so you can find them easily with their id's

void LibrarySystem::addMovie(int movie_id,string movie_name, int movie_year){
	MovieList = linklist.addMovieNode(MovieList,movie_id,movie_name,movie_year,"", argument);
	return;
}

//This method deletes movies from users or library depending on where movie is

void LibrarySystem::deleteMovie(int movie_id) {



	ofstream fout; 
	fout.open(argument, ios::app);


	Node* delete_address = linklist.search(MovieList, movie_id,"movie", argument);
	if (delete_address==NULL)
	{
		delete_address = linklist.search(UserMovies, movie_id, "movie", argument);
		if (delete_address==NULL)
		{
			
			fout << "Movie "<<movie_id<<" does not exist"<<endl;
			fout.close();
			return;
		}
		else
		{
			fout << "Movie " << delete_address->getMovieId() << " has been checked out"<<endl;
			fout << "Movie " << delete_address->getMovieId() << " has been deleted" << endl;
			delete_address->setMovieId(NULL);
			delete_address->setMovieName("");
			delete_address->setMovieYear(NULL);
			fout.close();
			return;
		}
	}
	else
	{
		fout << "Movie " << delete_address->getMovieId() << " has not been checked out"<<endl;
	}
	fout << "Movie " << delete_address->getMovieId() << " has been deleted"<<endl;
	fout.close();
	linklist.deleteNode(MovieList, delete_address,"movie", argument);
	return;
}

// This method adds users to system. Each user can checkout movie and system saves it.

void LibrarySystem::addUser(int user_id, string user_name) {
	UserMovies = linklist.addUserMovieNode(UserMovies, user_id, user_name,"",NULL,NULL,"", argument);
	return;
}

// This method deletes user and all of his information from system

void LibrarySystem::deleteUser(int user_id) {
	ofstream fout;  
	fout.open(argument, ios::app);




	Node* delete_address = NULL;
	delete_address = linklist.search(UserMovies, user_id, "user", argument);
	if (delete_address == NULL)
	{
		fout << "User " << user_id << " does not exist" << endl;
		fout.close();
		return;
	}
	else
	{
		fout << "User " << delete_address->getUserId() << " has been deleted" << endl;
		fout.close();
	}
	do {
		delete_address = linklist.search(UserMovies, user_id, "user", argument);
		linklist.deleteNode(UserMovies, delete_address, "user", argument);
	} while (delete_address != NULL);
	return;
}

// This method checks out movies for users. You can take movies from movie library but if it wasn't there you can't take it.

void LibrarySystem::checkoutMovie(int movie_id, int user_id) {
	Node* transport_address = linklist.search(MovieList, movie_id,"movie", argument);
	Node* to = linklist.search(UserMovies, user_id, "user", argument);
	ofstream fout; 
	fout.open(argument, ios::app);
	if (transport_address ==NULL)
	{
		fout << "Movie " << movie_id << " does not exist for checkout" << endl;
		fout.close();
		return;
	}
	if (to == NULL)
	{
		fout << "User " << user_id << " does not exist for checkout" << endl;
		fout.close();
		return;
	}
	if (to->getMovieId()==NULL)
	{
		to->setMovieId(transport_address->getMovieId());
		to->setMovieName(transport_address->getMovieName());
		to->setMovieYear(transport_address->getMovieYear());
	}
	else
	{
		UserMovies = linklist.addUserMovieNode(UserMovies, to->getUserId(), to->getUserName(), transport_address->getMovieName(), transport_address->getMovieId(), transport_address->getMovieYear(),"admin", argument);
	}
	
	linklist.deleteNode(MovieList, transport_address, "movie", argument);
	fout << "Movie " << movie_id << " has been checked out by User " << user_id << endl;
	fout.close();
	return;
}

//You can see which user takes which movies ,his id and his name with this method 

void LibrarySystem::showUser(int user_id) {
	ofstream fout;  
	fout.open(argument, ios::app);



	Node* show_address = linklist.search(UserMovies, user_id, "user", argument);
	Node* temp_show_address = show_address;
	if (show_address == NULL)
	{
		fout << "User " << user_id << " does not exist"<<endl;
		fout.close();
		return;
	}
	fout <<"User id: "<< show_address->getUserId() << " User name: " << show_address->getUserName()<<endl;
	fout << "User " << show_address->getUserId() << " checked out the following Movies:"<<endl;
	if (show_address->getMovieId() != NULL) {
		fout << "Movie id - Movie name - Year" << endl;
	}
	do {
		if (show_address->getMovieId()!=NULL)
		{
			fout << show_address->getMovieId() << " " << show_address->getMovieName() << " " << show_address->getMovieYear() << endl;
		}
		show_address = linklist.search(show_address->getNext(), user_id, "user", argument);
	} while (show_address != temp_show_address);
	fout.close();
}

//You can use movies id's and see their information with this method

void LibrarySystem::showMovie(int movie_id) {

	ofstream fout;  
	fout.open(argument, ios::app);


	Node* show_address = linklist.search(MovieList, movie_id, "movie", argument);
	if (show_address!=NULL)
	{
		fout << movie_id<<" " << show_address->getMovieName() << " " << show_address->getMovieYear()<<" Not checked out"<<endl;
	}
	else
	{
		show_address = linklist.search(UserMovies, movie_id, "movie", argument);
		if (show_address!=NULL)
		{
			fout << movie_id<<" " << show_address->getMovieName() << " " << show_address->getMovieYear()<< " Checked out by User " << show_address->getUserId() <<endl;
		}
		else
		{
			fout << "Movie with the id " << movie_id << " does not exist"<<endl;
		}
	}
	fout.close();
}

//You can see all movies in our library and in our user's checkout with this method

void LibrarySystem::showAllMovies() {

	ofstream fout;  
	fout.open(argument, ios::app);


	if (MovieList != NULL) 
	{
		Node* show_address = MovieList;
		if(show_address->getMovieId()!=NULL){
			fout << show_address->getMovieId() << " " << show_address->getMovieName() << " " << show_address->getMovieYear() << " Not checked out" << endl;
		}
		show_address = MovieList->getNext();
		while (show_address != MovieList) 
		{
			fout << show_address->getMovieId() << " " << show_address->getMovieName() << " " << show_address->getMovieYear() <<" Not checked out"<< endl;
			show_address = show_address->getNext();
		}
	}
	if (UserMovies !=NULL)
	{
		Node* show_address = UserMovies;
		if (show_address->getMovieId()!=NULL)
		{
			fout << show_address->getMovieId() << " " << show_address->getMovieName() << " " << show_address->getMovieYear() << " Checked out by User " << show_address->getUserId() << endl;
		}
		show_address = show_address->getNext();
		while (show_address!=UserMovies)
		{
			if (show_address->getMovieId() != NULL)
			{
				fout << show_address->getMovieId() << " " << show_address->getMovieName() << " " << show_address->getMovieYear() << " Checked out by User " << show_address->getUserId() << endl;
			}
			show_address = show_address->getNext();
		}
	}
	fout.close();
	return;
}


// Users can return their checked out movies with this method

void LibrarySystem::returnMovie(int movie_id) {


	ofstream fout;  
	fout.open(argument, ios::app);


	Node* transport_address = linklist.search(UserMovies, movie_id, "movie", argument);
	if (transport_address != NULL)
	{

		if (transport_address->getMovieId() != NULL)
		{
			linklist.addMovieNode(MovieList,transport_address->getMovieId(), transport_address->getMovieName(), transport_address->getMovieYear(),"return", argument);
			transport_address->setMovieName("");
			transport_address->setMovieYear(NULL);
			transport_address->setMovieId(NULL);
			fout << "Movie " << movie_id << " has been returned" << endl;
		}
		fout.close();
		return;
	}
	else
	{
		transport_address = linklist.search(MovieList, movie_id, "movie", argument);
		if (transport_address==NULL)
		{
			fout << "Movie " << movie_id << " not exist in the library" << endl;
		}
		else
		{
			fout << "Movie " << movie_id << " has not been checked out" << endl;
		}
	}
	fout.close();
}
