/****************************************************************/
/*                CountryNetwork Implementation                 */
/****************************************************************/
/* TODO: Implement the member functions of class CountryNetwork */
/*     This class uses a linked-list of Country structs to      */
/*     represet communication paths between nations             */
/****************************************************************/

#include "CountryNetwork.hpp"

using namespace std;

/*
 * Purpose: Constructer for empty linked list
 * @param none
 * @return none
 */
CountryNetwork::CountryNetwork()
{
  // head = new Country;
  // head -> next =  NULL;
  // int count = 0;
}


/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool CountryNetwork::isEmpty()
{
  bool type1 = false;
  if(head == NULL)
  {
    return true;
  }
  else
  {
    return type1;
  }

}

/*
 * Purpose: Add a new Country to the network
 * between the Country *previous and the Country that follows it in the network.
 * @param previous name of the Country that comes before the new Country
 * @param countryName name of the new Country
 * @return none
 */
void CountryNetwork::insertCountry(Country* previous, string countryName)
{
  //next = previous; // setting the current node to head
  //int count =0;
  if(previous == NULL)
  {
    Country *newC = new Country;
    newC -> name = countryName;
    newC -> next = head;
    head = newC;
    cout << "adding: " << countryName << " (HEAD)" << endl;
  }
  else
  {
    Country *newC = new Country;
    newC -> name = countryName;
    newC -> next = head;
    newC -> next = previous -> next;
    previous -> next = newC;
    cout << "adding: " << countryName << " (prev: " << previous -> name << ")" << endl;
    return;
  }
}


/*
 * Purpose: delete the country in the network with the specified name.
 * @param countryName name of the country to delete in the network
 * @return none
 */
//  void deleteCountry(string ​countryName​); ​// Beware of edge cases
// ➔ Use the member function ​searchNetwork​ to find the node
// with name ​countryName​,
// then delete it. If there is no node with name ​countryName​,
// print ​"Country does not exist.
 void CountryNetwork::deleteCountry(string countryName)
{
  int count = 0; // setting a counter to be able to increment
  if(head == NULL) // if statement
  {
    return;
  }
  if(head -> name == countryName) // if statement points to name and = country name
  {
    Country *now = head; // referencing the stuct for a new pointer
    head = head -> next; // if head, then head = head to be deleted
    delete now;
  }
  else // if all other is not true than else
  {
    Country *now1; // new reference
    Country *prev; // new reference
    prev = head;
    now1 = prev -> next;
    while(now1 != 0) // if new refernce is not NULL
    {
      if(now1 -> name == countryName) // doing the same thing as before
      {
        count++;
        prev ->next = now1 -> next;
        delete now1;
      }
      prev =now1;
      now1 = now1 -> next;
    }
    if(count == 0) // if counter does = 0
    {
      cout << "Country does not exist." << endl;
    }
  }
}


/*
 * Purpose: populates the network with the predetermined countries
 * @param none
 * @return none
 */
void CountryNetwork::loadDefaultSetup()
{
  if (head != NULL) {
      deleteEntireNetwork();
  }
  insertCountry(NULL, "United States");
  insertCountry(head, "Canada");
  insertCountry(head ->next, "Brazil");
  insertCountry(head ->next ->next, "India");
  insertCountry(head ->next -> next ->next, "China");
  insertCountry(head ->next -> next -> next -> next, "Australia");

}


/*
 * Purpose: Search the network for the specified country and return a pointer to that node
 * @param countryName name of the country to look for in network
 * @return pointer to node of countryName, or NULL if not found
 * @see insertCountry, deletecountry
 */
Country* CountryNetwork::searchNetwork(string countryName)
{
  Country *temp = head;
  while(temp)
  {
    if(temp-> name == countryName)
    {
      return temp;
    }
  temp = temp -> next;
  }
  return NULL;
}


/*
 * Purpose: deletes all countries in the network starting at the head country.
 * @param none
 * @return none
 */
void CountryNetwork::deleteEntireNetwork()
{
  Country *ptr = head;
  while(ptr!= NULL)
  {
    cout << "deleting: " << ptr -> name << endl;
    Country *temp1 = ptr;
    ptr = temp1 -> next;
    delete temp1;
  }
  cout << "Deleted network" << endl;
  head = NULL;
}


/*
 * Purpose: Transmit a message across the network to the
 *   receiver. Msg should be stored in each country it arrives
 *   at, and should increment that country's count.
 * @param receiver name of the country to receive the message
 * @param message the message to send to the receiver
 * @return none
 */
void CountryNetwork::transmitMsg(string receiver, string message)
{
  Country *new3;
    new3 = head;

    if(new3 == 0) // this will check to see if the list is empty
    {
      cout << "Empty list" << endl;
    }
    while(new3 != 0)
    {
      if(new3 -> name == receiver)
      {
        new3 -> message = message;
        new3 -> numberMessages = new3 ->numberMessages +1;
        cout << new3-> name << " [# messages received: "<< new3 -> numberMessages << "] received: " << new3 -> message << endl;
        return;
      }
      new3 -> message = message;
      new3 -> numberMessages = new3 -> numberMessages +1;
      cout << new3 ->name << " [# messages received: "<< new3 ->numberMessages << "] received: " << new3 ->message << endl;
      new3 = new3 -> next;
    }
}


/*
 * Purpose: prints the current list nicely
 * @param ptr head of list
 */
void CountryNetwork::printPath()
{
  cout << "== CURRENT PATH ==" << endl;
  Country *temp = head;
  if(temp == NULL)
  {
    cout << "nothing in path" << endl;
    cout << "===" << endl;
    return;
  }

  else
  {
    while(temp != NULL)
    {
      cout << temp -> name << " -> ";
      temp = temp -> next;
    }
    cout << "NULL" << endl <<  "===" << endl;
  }
  //cout << "===" << endl;
}


/*
 * Purpose: reverse the entire network t
 * @param ptr head of list
 */
void CountryNetwork::reverseEntireNetwork()
{
  Country *prev1;
  prev1 = NULL;
  Country *now;
  now = head;
  Country *next;
  next =  NULL;

  while(now != NULL)
  {
    next = now -> next;
    now -> next = prev1;
    prev1 = now;
    now = next;
  }
  head = prev1;

}
