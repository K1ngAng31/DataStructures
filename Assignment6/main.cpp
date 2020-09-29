#include "MovieTree.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

int main(int argc, char* argv[])
{
  MovieTree movie;
  int option = 0;
  string uInput = "";
  string str;
  ifstream moviefile(argv[1]);
  while(getline(moviefile, str))
  {
    stringstream ss(str);
    string ranking;
    string name;
    string year;
    string rating;
    getline(ss, ranking, ',');
    getline(ss, name, ',');
    getline(ss, year, ',');
    getline(ss, rating, ',');
    int convertRanking = stoi(ranking);
    int convertYear = stoi(year);
    float convertRating = stof(rating);
    movie.addMovie(convertRanking, name, convertYear, convertRating);
  }
  while(getline(cin, uInput))
  {
    if(option == 0)
    {
      cout << "=====Main Menu=====" << endl;
      cout << "1. Print the inventory" << endl;
      cout << "2. Delete a movie" << endl;
      cout << "3. Quit" << endl;
      option++;
    }
    if(uInput == "1")
    {
      movie.printMovieInventory();
      option = 0;
    }
    else if(uInput == "2")
    {
      cout << "Enter title:" << endl;
      getline(cin, uInput);
      movie.deleteMovie(uInput);
      option = 0;
    }
    else if(uInput == "3")
    {
      cout << "Goodbye!" << endl;
      break;
    }
  }
}
