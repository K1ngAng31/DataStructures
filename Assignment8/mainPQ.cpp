#include "PriorityQueue.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;


int main(int argc, char const *argv[]) {
  int tcTime =0;
  int arg1 = stoi(argv[1]);
  PriorityQueue PQ(arg1);

  cout << "============Main Menu============" << endl;
  cout << "1. Get group information from file" << endl;
  cout << "2. Add a group to Priority Queue" << endl;
  cout << "3. Show next group in the queue" << endl;
  cout << "4. Serve Next group" << endl;
  cout << "5. Serve Entire Queue" << endl;
  cout << "6. Quit" << endl;

  int userOption = 0;
  string userChoice = "";
  while(getline(cin, userChoice))
  {
    userOption = stoi(userChoice);
    if(userOption == 1)
    {
      string nameFile;
      cout << "Enter a filename: " << endl;
      cin >> nameFile;
      ifstream fileIn;
      fileIn.open(nameFile);

      if(!fileIn.is_open()){
        cout << "ERROR: file failed to open" << endl;
      }
      else{
        string a1;
        while(getline(fileIn, a1)){
          if(!PQ.isFull()){
            stringstream ss(a1);
            string NameofGroup;
            string SizeofGroup;
            string Cooktime;
            getline(ss, NameofGroup, ' ');
            getline(ss, SizeofGroup, ' ');
            getline(ss, Cooktime, ' ');
            int groupSize = stoi(SizeofGroup);
            int cookingTime = stoi(Cooktime);
            PQ.enqueue(NameofGroup, groupSize, cookingTime);
          }
          else{
            cout << "Heap full, cannot enqueue" << endl;
            break;
          }
        }
      }
    }
    if(userOption == 2)
    {
      string NameofGroup;
      string SizeofGroup;
      string Cooktime;
      cout << "Enter Group Name:" << endl;
      getline(cin, NameofGroup);
      cout << "Enter Group Size:" << endl;
      getline(cin, SizeofGroup);
      cout << "Enter Estimated Cooking Time:" << endl;
      getline(cin, Cooktime);
      int groupSize = stoi(SizeofGroup);
      int cookingTime = stoi(Cooktime);
      if(!PQ.isFull()){
        PQ.enqueue(NameofGroup, groupSize, cookingTime);
      }
      else{
        cout << "Heap full, cannot enqueue" << endl;
      }
    }
    if(userOption == 3)
    {
      if(PQ.isEmpty()){
        cout << "Heap empty, nothing to peek" << endl;
      }
      else{
        cout << "Group Name: " << PQ.peek().groupName << endl;
        cout << "Group Size: " << PQ.peek().groupSize << endl;
        cout << "Group Time: " << PQ.peek().cookingTime << endl;
      }
    }
    if(userOption == 4)
    {
      if(!PQ.isEmpty()){
        tcTime += PQ.peek().cookingTime;
        cout << "Group Name: " << PQ.peek().groupName << " - Total Cook Time for the Group: " << tcTime << endl;
        PQ.dequeue();
      }
      else{
        cout << "Heap empty, cannot dequeue" << endl;
      }
    }
    if(userOption == 5)
    {
      if(PQ.isEmpty()){
        cout << "Heap empty, cannot dequeue" << endl;
      }
      else{
        while(!PQ.isEmpty()){
          tcTime += PQ.peek().cookingTime;
          cout << "Group Name: " << PQ.peek().groupName << "- Total Cook Time for the Group: " << tcTime << endl;
          PQ.dequeue();
        }
      }
    }
    if(userOption == 6)
    {
      cout << "Goodbye!" << endl;
      break;
    }
    cout << "============Main Menu============" << endl;
    cout << "1. Get group information from file" << endl;
    cout << "2. Add a group to Priority Queue" << endl;
    cout << "3. Show next group in the queue" << endl;
    cout << "4. Serve Next group" << endl;
    cout << "5. Serve Entire Queue" << endl;
    cout << "6. Quit" << endl;
  }
  return 0;
}
