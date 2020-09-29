/****************************************************************/
/*                   Assignment 3 Driver File                   */
/****************************************************************/
/* TODO: Implement menu options as described in the writeup     */
/****************************************************************/

#include "CountryNetwork.hpp"
#include <iostream>
#include <string>
// you may include more libraries as needed

using namespace std;

void displayMenu();

int main(int argc, char* argv[])
{
  CountryNetwork cNet;
  displayMenu();
  int choice;
  cin >> choice;
  while(choice !=9)
  {
    switch(choice)
    {
      case 1:
      {
        cNet.loadDefaultSetup();
        cNet.printPath();
        cout << endl;
        displayMenu();
        cin >> choice;
        break;
      }
      case 2:
      {
        cNet.printPath();
        cout << endl;
        displayMenu();
        cin >> choice;
        break;
      }
      case 3:
      {
        cout << "Enter name of the country to receive the message:";
        string country;
        cin.ignore();
        getline(cin, country);
        string msg;
        cout << endl << "Enter the message to send:" << endl;
        getline(cin, msg);
        cout << endl;
        cNet.transmitMsg(country, msg);
        cout << endl;
        displayMenu();
        cin >> choice;
        break;
      }
      case 4:
      {
        cout << "Enter a new country name:" << endl;
        cin.ignore();
        string name;
        getline(cin, name);
        cout << "Enter the previous country name (or First):" << endl;
        string before;
        getline(cin, before);
        if(before == "First")
        {
          cout << endl;
          cNet.insertCountry(NULL, name);
          cNet.printPath();
          cout << endl;
          displayMenu();
          cin >> choice;
          break;
        }
        else
        {
          Country *left;
          left = cNet.searchNetwork(before);
          cout << "TEST!" << endl;
          while (left == NULL)
          {
            cout << "TEST2"<< endl;
            cout << "INVALID country...Please enter a VALID previous country name:" << endl;
            getline(cin, before);
            if(before == "First")
            {
              cout << "FIRST" << endl;
              cout << endl;
              cNet.insertCountry(NULL, name);
              cNet.printPath();
              break;
            }
            left = cNet.searchNetwork(before);
          }
          if(before != "First")
          {
            cout << endl;
            cNet.insertCountry(left, name);
            cNet.printPath();
          }
        }
        cout << endl;
        displayMenu();
        cin >> choice;
        break;
      }
      case 5:
      {
        cout << "Enter a country name:" << endl;
        string name;
        cin.ignore();
        getline(cin, name);
        cNet.deleteCountry(name);
        cNet.printPath();
        cout << endl;
        displayMenu();
        cin >> choice;
        break;
      }
      case 6:
      {
        cNet.reverseEntireNetwork();
        cNet.printPath();
        cout << endl;
        displayMenu();
        cin >> choice;
        break;
      }
      case 7:
      {
        cNet.deleteEntireNetwork();
        cin >> choice;
        break;
      }
      case 8:
      {
        cout << "Quitting... cleaning up path: " << endl;
        cNet.printPath();
        cNet.deleteEntireNetwork();
        if(cNet.isEmpty() ==  true)
        {
          cout << "Path cleaned" << endl;
        }
        else if(cNet.isEmpty() == false)
        {
          cout << "Error: Path NOT cleaned" << endl;
        }
        cout << "Goodbye!" << endl;
        choice = 9;
        break;
      }
    }
  }
}

/*
 * Purpose: displays a menu with options
 */
void displayMenu()
{
    //cout << endl;
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build Network " << endl;
    cout << " 2. Print Network Path " << endl;
    cout << " 3. Transmit Message " << endl;
    cout << " 4. Add Country " << endl;
    cout << " 5. Delete Country " << endl;
    cout << " 6. Reverse Network" << endl;
    cout << " 7. Clear Network " << endl;
    cout << " 8. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
