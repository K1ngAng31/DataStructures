#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct User{ // here we are creating a struct to declare any public variables
  string username; //creating a string called username
  float gpa;// creating a float to be used for the gpa
  int age; // creating an int to be used for the age
};
void addUser(User users[], string _username, float _gpa, int _age, int length);
void printList(const User users[], int length);

int main(int argc, char *argv[]) // creating the main function
{
  if(argc != 4) // creating if statement to see if the file is taking enough arugments
  {
    cerr << "Error: incorrect number of arguments \n";
    // if file is not taking an apprpriate number of arguments it will print out the statement
  }
  else // else statement for if it does have the apprpriate amount of arguments
  {
    ifstream file;
    file.open(argv[1]); // using ifstream to be able to read into the file of out choice
    if(file.is_open()) // using if statement for if the file is opened
    {
      User user1[100];// using the struct class to create a user array of 100
      int some = 0; // creating an integer to be able to use as a position in the array
      string line;
      while(getline(file, line)) //using a while loop to use while the statement is true
      {
        stringstream sin(line); // using string stream to be able to act like we are reading from a string to a stream
        string temporaryUsername, temporaryGPA, temporaryAGE; // creating temporary strings to use for the getline
        getline(sin, temporaryUsername, ','); // getting a certain line from the string
        getline(sin, temporaryGPA, ',');// gettling a certain line from the string
        getline(sin, temporaryAGE, ','); // getting a certain line from the string
        float anewGPA = stof(temporaryGPA); // converting a string of number(s) into a float
        int anewAGE = stoi(temporaryAGE); // converting a string of integers to an intger

        addUser(user1, temporaryUsername, anewGPA, anewAGE, some); // filling in the array with what we want
        some++; // incrememnting some until the while loop is no longer necessary
      }
      file.close(); // closing the file

      ofstream ofile(argv[2], ios::out); // using ofstream to read data from a File

      for(int i=0; i < some; i++) // another for loop to iterate through
      {
        if(user1[i].gpa > stof(argv[3])) // if statement to go through the gpa array of users
        {
          ofile << user1[i].username << "," << user1[i].gpa << "," << user1[i].age <<endl;
          // here we are reading from the file but seperating it with a comma
        }
      }
      ofile.close(); // clsoign the ofstream file
      printList(user1, some); // calling out the function printList
    }
    else
    {
      cout << "Failed to open the file." << endl;
    }
  }
  return 0;
}

void addUser(User users[], string _username, float _gpa, int _age, int length)
{ // creating an add user function that won't print out anything
  for(int add = 0; add <=length; add++) // this for loop will work as the number of users is less then or equal to the length
  {
    users[length].username = _username; //here we are adding the user's name to the array
    users[length].gpa = _gpa; // adding the gpa to the user
    users[length].age = _age; // adding the age to the user
  }
  //return 0;

}

void printList(const User users[], int length)// creating a function that wiil be able to print out the list
{
  for(int p = 0; p < length; p++) // creating a for loop to be able to go through and print out the list until it is
  // no longer true
  {
    cout << users[p].username << " [" << users[p].gpa << "] age: " << users[p].age << endl;
    // printing out the username, gpa, and age
  }
}
