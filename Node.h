#pragma once
#include <cstddef>
#include <string>

class Node
{
private:
	std::string User_name;
	std::string Movie_name;
	int User_id;
	int Movie_id;
	int movie_year;
	Node* next;
	Node* prev;
public:
	Node();
	~Node();
	Node(int User_id, std::string User_name);
	Node(int Movie_id, std::string Movie_name, int year);
	Node(int User_id,int Movie_id, std::string User_name,std::string Movie_name, int year);
	void setUserName(std::string Username);
	std::string getUserName();
	void setMovieName(std::string Moviename);
	std::string getMovieName();
	void setNext(Node* next);
	Node* getNext();
	void setPrev(Node* prev);
	Node* getPrev();
	void setUserId(int Id);
	int getUserId();
	void setMovieId(int Id);
	int getMovieId();
	void setMovieYear(int Movie_Year);
	int getMovieYear();

};

class LinkedList
{
public:
	LinkedList();
	Node* addMovieNode(Node* head,int movie_id, std::string movie_name,int movie_year,std::string condition,std::string argument);
	Node* addUserMovieNode(Node* head, int user_id, std::string user_name, std::string movie_name, int movie_id, int movie_year,std::string condition,std::string argument);
	Node* search(Node* head, int id, std::string ListName,std::string argument);
	void deleteNode(Node* head, Node* n,std::string Listname,std::string argument);

};


