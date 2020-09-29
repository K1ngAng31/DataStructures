#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

using namespace std;

int insertIntoSortedArray(int myArray[], int numEntries, int newValue)
{
  for(int a =0; a < numEntries; a++)// making a for loop because it will iterate through
  // to store the integers of the array into a an int
  {
    if(myArray[a] > newValue) // making an if statement to do the previous
    {
      int temporary; // making a new intger that will equal the stored values in the array
      temporary = myArray[a];
      myArray[a] = newValue;
      newValue = temporary;
    }
  }
  myArray[numEntries] = newValue; // making the stored array values in the equal the newvalue

  for(int b = 0; b <= numEntries; b++) // making a for loop to be able to iterate through an if and else
  // statement to be able to seperate the values and sort the array
  {
    if(b == 0) // if the value is equal to 0 then it will print out the array at that value
    {
      cout << myArray[b];
    }
    else if(b > 0) // if the value is greater than 0, it will print out the value in the array,
    // and then sort the value by also being seperated by a comma
    {
      cout << "," << myArray[b];
    }
  }
  cout << endl;
  return numEntries; // once it foes through both for loops it will just reaturn the entries that it has
}

int main(int argc, char* argv[])
{
  int anewTempValue =0; // creating a temporary value
  int anewNumEntries =0; // creating a temporary numEntries
  int tempArray[100]; // creating a temporary array that will allow for up to 100 values be stored in the array

  for(int c =0; c < 100; c++) // creatng a for loop to itterate through the array of values
  {
    tempArray[c] = 0;
  }
  string filename = argv[1]; // creating a string file and equal it to an array
  ifstream fin;//("numbers.txt"); // using ifstream to be able to wrtie into the file
  fin.open(filename); // opening the file
  if(fin.is_open()) // making an if statement to declare what happens if the file is open
  {
    string line; // maiing another string to be used for getline
    while(getline(fin, line))// making a while loop to be used while getline is true
    {
      int value = stoi(line); // making a string to an integer to be stored in the new integer
      anewTempValue = value;
      insertIntoSortedArray(tempArray, anewNumEntries, anewTempValue);
      anewNumEntries++; // incrementing anewNumEntries until there are no more
    }
    fin.close(); // closing the file

  }
  else // if the if statement is not true, else will cout the following:
    {
      cout << "Failed to open the file." << endl;
      return 0;
    }
    //fin.close();
    return 0; // will 0 over all
}
