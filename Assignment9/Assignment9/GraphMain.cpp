#include "Graph.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;

int main(int argc, const char *argv[])
{
  Graph gra; //creating Graph object
  ifstream FileIn; //in
  FileIn.open(argv[1]);
  if(!FileIn.is_open())
  {
    cout << "File failed to open" << endl;
  }
  else
  {
    vector<string>cityN;
    string s1;
    string s;
    getline(FileIn, s);
    stringstream ll1(s);
    while(getline(ll1, s1, ',')){
      if(s1 != "cities"){
        gra.addVertex(s1);
      }
      cityN.push_back(s1);
    }
    while(getline(FileIn, s)){
      string c;
      string d1;
      int d = 0;
      stringstream ss(s);
      getline(ss, c, ',');
      int ind = 1;
      while(getline(ss, d1, ','))
      {
        d = stoi(d1);
        if(d >0)
        {
          gra.addEdge(c, cityN[ind], d);
          cout << " ... Reading in " << c << " -- " << cityN[ind] << " -- " << d << endl;
        }
        ind++;
      }
    }
    cout << "------------------------------ " << endl << "Breadth First Traversal" << endl << "------------------------------" << endl;
    gra.printBFT();
    cout << "------------------------------ " << endl << "Depth First Traversal" << endl << "------------------------------" << endl;
    gra.printDFT();
    cout << "------------------------------ " << endl << "Display Edges" << endl << "------------------------------" << endl;
    gra.displayEdges();
  }
  return 0;
}
