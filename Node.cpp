#include "Node.h"
#include <iostream>
#include<fstream>
using namespace std;


Node* User_tail = NULL;
Node* Movie_tail = NULL;

Node::Node(int id, string name) : User_id(id),Movie_id(NULL), User_name(name),Movie_name(""), movie_year(NULL), next(NULL), prev(NULL) { }

Node::Node(int id, string title, int year) : User_id(NULL),Movie_id(id),User_name(""), Movie_name(title), movie_year(year), next(NULL), prev(NULL) { }

Node::Node()
{
}

Node::~Node() {}

void Node::setNext(Node* x) {
	this->next = x;
}

Node* Node::getNext() {
	return this->next;
}

void Node::setPrev(Node* prev) {
	this->prev = prev;
}

Node* Node::getPrev() {
	return this->prev;
}

void Node::setUserName(string x) {
	this->User_name = x;
}

string Node::getUserName() {
	return this->User_name;
}

void Node::setMovieName(string x) {
	this->Movie_name = x;
}

string Node::getMovieName() {
	return this->Movie_name;
}

void Node::setUserId(int x) {
	this->User_id = x;
}

int Node::getUserId() {
	return this->User_id;
}

void Node::setMovieId(int x) {
	this->Movie_id = x;
}

int Node::getMovieId() {
	return this->Movie_id;
}

void Node::setMovieYear(int x) {
	this->movie_year = x;
}

int Node::getMovieYear() {
	return this->movie_year;
}



LinkedList::LinkedList() {
}

// You can add movie node with this method and if you gave true parameters to it you can see proper linked list

Node* LinkedList::addMovieNode(Node* head,int movie_id,string movie_name,int movie_year,string condition,string argument) {

	ofstream fout; 
	fout.open(argument, ios::app);


	Node* exist = search(head, movie_id, "movie", argument);
	while (exist==NULL)
	{
		if (head == NULL )
		{
			head = new Node();
			Movie_tail = head;
			head->setNext(head);
			head->setPrev(head);
			head->setMovieName(movie_name);
			head->setMovieId(movie_id);
			head->setMovieYear(movie_year);
			if (condition!="return")
			{
				fout << "Movie " << movie_id << " has been added" << endl;
			}
			fout.close();
			return head;
		}
		else if(head->getMovieId() == NULL)
		{
			Movie_tail = head;
			head->setNext(head);
			head->setPrev(head);
			head->setMovieName(movie_name);
			head->setMovieId(movie_id);
			head->setMovieYear(movie_year);
			if (condition != "return")
			{
				fout << "Movie " << movie_id << " has been added" << endl;
			}
			fout.close();
			return head;
		}
		else if (Movie_tail->getNext() == head)
		{
			Movie_tail->setNext(new Node());
			(Movie_tail->getNext())->setPrev(Movie_tail);
			Movie_tail = Movie_tail->getNext();
			head->setPrev(Movie_tail);
			Movie_tail->setMovieName(movie_name);
			Movie_tail->setNext(head);
			Movie_tail->setMovieId(movie_id);
			Movie_tail->setMovieYear(movie_year);
			if (condition != "return")
			{
				fout << "Movie " << movie_id << " has been added" << endl;
			}
			fout.close();
			return head;
		}
		else
		{
			Movie_tail = Movie_tail->getNext();
		}
	}
	fout << "Movie "<< movie_id<<" already exists"<<endl;
	fout.close();
	return head;
}


//You can add users node and their checked_out movies node with this method and if you gave true parameters to it you can see proper linked list

Node* LinkedList::addUserMovieNode(Node* head, int user_id, string user_name,string movie_name, int movie_id,int movie_year,string condition,string argument) {
	ofstream fout; 
	fout.open(argument, ios::app);

	Node* exist = search(head, user_id, "user", argument);
	while (exist == NULL || condition == "admin")
	{
		if (head == NULL )
		{
			head = new Node();
			User_tail = head;
			head->setNext(head);
			head->setPrev(head);
			head->setUserName(user_name);
			head->setMovieName(movie_name);
			head->setUserId(user_id);
			head->setMovieId(movie_id);
			head->setMovieYear(movie_year);
			fout << "User " << user_id << " has been added"<<endl;
			fout.close();
			return head;
		}
		else if(head->getUserId()==NULL)
		{
			User_tail = head;
			head->setNext(head);
			head->setPrev(head);
			head->setUserName(user_name);
			head->setMovieName(movie_name);
			head->setUserId(user_id);
			head->setMovieId(movie_id);
			head->setMovieYear(movie_year);
			fout << "User " << user_id << " has been added" << endl;
			fout.close();
			return head;
		}
		else if(exist!=NULL && User_tail->getNext() == head && (user_id == exist->getUserId() && user_name == exist->getUserName()))
		{
			User_tail->setNext(new Node());
			(User_tail->getNext())->setPrev(User_tail);
			User_tail = User_tail->getNext();
			head->setPrev(User_tail);
			User_tail->setUserName(user_name);
			User_tail->setMovieName(movie_name);
			User_tail->setNext(head);
			User_tail->setUserId(user_id);
			User_tail->setMovieId(movie_id);
			User_tail->setMovieYear(movie_year);
			return head;
		}
		else if (User_tail->getNext() == head)
		{
			User_tail->setNext(new Node());
			(User_tail->getNext())->setPrev(User_tail);
			User_tail = User_tail->getNext();
			head->setPrev(User_tail);
			User_tail->setUserName(user_name);
			User_tail->setMovieName(movie_name);
			User_tail->setNext(head);
			User_tail->setUserId(user_id);
			User_tail->setMovieId(movie_id);
			User_tail->setMovieYear(movie_year);
			fout << "User " << user_id << " has been added" << endl;
			fout.close();
			return head;
		}
		else
		{
			cout << User_tail<<endl;
			cout << head<<"xxx"<<endl;
			User_tail = User_tail->getNext();
		}
	}
	fout << "User " << user_id << " already exists" << endl;
	fout.close();
	return head;
}


//You can search and find whatever you search with this method

Node* LinkedList::search(Node* head, int id,string ListName, string argument) {
	if (head != NULL) {
		Node* temp_Node = head;
		bool Repeat = false;
		while (true)
		{
			if(ListName=="user"){
				if (temp_Node->getUserId() == id)
				{
					return temp_Node;

				}
				else
				{
					temp_Node = temp_Node->getNext();
					if (Repeat)
					{
						break;
					}
					if (temp_Node==head)
					{
						Repeat = true;
					}
					
				}
			}

			if (ListName == "movie") {
				if (temp_Node->getMovieId() == id)
				{
					return temp_Node;
				}
				else
				{
					temp_Node = temp_Node->getNext();
					if (Repeat)
					{
						break;
					}
					if (temp_Node == head)
					{
						Repeat = true;
					}
				}
			}
		}
	}

	return NULL;

}

// You can delete nodes with this method

void LinkedList::deleteNode(Node* head, Node* n,string Listname, string argument)
{
	if (n == NULL)
	{
		return;
	}

	else if (head == n)
	{
		if (head->getNext() == head)
		{
			head->setMovieYear(NULL);
			head->setUserName("");
			head->setMovieName("");
			head->setNext(head);
			head->setMovieId(NULL);
			head->setUserId(NULL);
			return;
		}
		if (Listname =="user")
		{
			head->setUserName(head->getNext()->getUserName());
			head->setUserId(head->getNext()->getUserId());
			head->setMovieName(head->getNext()->getMovieName());
			head->setMovieId(head->getNext()->getMovieId());
			head->setMovieYear(head->getNext()->getMovieYear());
		}

		else if (Listname == "movie")
		{
			head->setMovieName(head->getNext()->getMovieName());
			head->setMovieId(head->getNext()->getMovieId());
			head->setMovieYear(head->getNext()->getMovieYear());
		}
		n = head->getNext();

		head->setNext(head->getNext()->getNext());

		free(n);

		return;
	}
	if (Listname=="user")
	{
		Node* prev = head;

		do {
			prev = prev->getNext();
		} while (prev->getNext() != head->getNext() && prev->getNext() != n);

		if (prev->getNext() == head)
		{
			return;
		}

		if (prev->getNext() == User_tail)
		{
			User_tail = prev;
		}

		prev->setNext(prev->getNext()->getNext());


		free(n);

		return;
	}
	else if (Listname == "movie") {
		Node* prev = head;

		do {
			prev = prev->getNext();
		} while (prev->getNext() != head->getNext() && prev->getNext() != n);

		if (prev->getNext() == head)
		{
			return;
		}

		if (prev->getNext() == Movie_tail)
		{
			Movie_tail = prev;
		}

		prev->setNext(prev->getNext()->getNext());


		free(n);

		return;
	}
	
}


