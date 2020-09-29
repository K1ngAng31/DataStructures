#include "MovieTree.cpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
using namespace std;
int main(int argc, char *argv[])
{
  MovieTree movie;
  int choice = 0;
  string userInput = "";
  string str;
  bool done = false;
  ifstream moviefile(argv[1]);
  while(getline(moviefile, str))
  {
    stringstream ss(str);
    string rating;
    string name;
    string year;
    string ranking;
    getline(ss, ranking, ',');
    getline(ss, name, ',');
    getline(ss, year, ',');
    getline(ss, rating, ',');
    float convertRating = stof(rating);
    int convertYear = stoi(year);
    int convertRanking= stoi(ranking);
    movie.addMovieNode(convertRanking, name, convertYear, convertRating);
  }

  while(getline(cin, userInput))
  {
    if(choice == 0)
    {
      cout << "======Main Menu======" << endl;
      cout << "1. Find a movie" << endl;
      cout << "2. Query movies" << endl;
      cout << "3. Print the inventory" << endl;
      cout << "4. Average Rating of movies" << endl;
      cout << "5. Quit" << endl;
      choice++;
    }

    if(userInput =="1")
    {
      cout << "Enter title:" << endl;
      getline(cin, userInput);
      movie.findMovie(userInput);
      choice =0;
    }
    else if(userInput == "2")
    {
        float input;
        int num;
      cout << "Enter minimum rating:" << endl;
      cin >> input;
      cout << "Enter minimum year:" << endl;
      cin >> num;
      movie.queryMovies(input, num);
      choice =0;
    }
    else if(userInput == "3")
    {
      movie.printMovieInventory();
      choice =0;
    }
    else if(userInput == "4")
    {
      movie.averageRating();
      choice =0;
    }
    else if(userInput == "5")
    {
      cout << "Goodbye!" << endl;
      break;
    }
  }
}
