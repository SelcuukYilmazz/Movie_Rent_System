// CMakeProject1.cpp : Defines the entry point for the application.
//

#include"Node.h"
#include"LibrarySystem.h"
#include <fstream>
#include <iostream>


using namespace std;

int main(int argc, char** argv)
{
	LibrarySystem lib(argv[2]);
	string myText;
	string prev_command = "";








	ofstream ofs;
	ofs.open(argv[2], ofstream::out | ofstream::trunc);
	ofs.close();

	ofstream fout;
	fout.open(argv[2], ios::app);











	fout<< "===Movie Library System===" << endl;

	ifstream MyReadFile(argv[1]);

	while (getline(MyReadFile, myText)) {
		int finish = myText.find("\t");
		string command = myText.substr(0, finish);
		if (command != prev_command)
		{
			fout <<endl<< "===" << command << "() method test===" << endl;
			prev_command = command;
		}
		if (command == "addUser")
		{
			command = myText.substr(finish+1);
			finish = command.find("\t");
			int Id = stoi(command.substr(0, finish));
			command = command.substr(finish+1);
			string Name = command;
			lib.addUser(Id,Name);

		}
		else if(command == "addMovie")
		{
			command = myText.substr(finish+1);
			finish = command.find("\t");
			int Id = stoi(command.substr(0, finish+1));
			command = command.substr(finish+1);
			finish = command.find("\t");
			string Name = command.substr(0,finish);
			int Year = stoi(command.substr(finish+1));
			lib.addMovie(Id, Name, Year);
		}
		else if (command =="deleteMovie") 
		{
			command = myText.substr(finish+1);
			int Id = stoi(command);
			lib.deleteMovie(Id);
		}
		else if (command == "deleteUser") 
		{
			command = myText.substr(finish+1);
			int Id = stoi(command);
			lib.deleteUser(Id);
		}
		else if (command == "checkoutMovie") 
		{
			command = myText.substr(finish+1);
			finish = command.find("\t");
			int Movie_Id = stoi(command.substr(0, finish));
			command = command.substr(finish+1);
			int User_Id = stoi(command);
			lib.checkoutMovie(Movie_Id, User_Id);
		}
		else if (command == "showUser") 
		{
			command = myText.substr(finish+1);
			int User_Id = stoi(command);

			lib.showUser(User_Id);

		}
		else if (command == "showMovie") 
		{
			command = myText.substr(finish+1);
			int Movie_Id = stoi(command);

			lib.showMovie(Movie_Id);
		}
		else if (command == "showAllMovie") 
		{
			fout <<"Movie id - Movie name - Year - Status"<<endl;
			lib.showAllMovies();
		}
		else if (command == "returnMovie") 
		{
			command = myText.substr(finish+1);
			int Movie_Id = stoi(command);
			lib.returnMovie(Movie_Id);
		}
	}

	MyReadFile.close();
	fout.close();
	
}
