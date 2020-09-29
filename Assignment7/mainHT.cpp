#include "HashTable.hpp"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void getStopWords(char *ignoreWordFileName, HashTable &stopWordsTable)
{
  int count = 0; // making a counter
  string storeWord; // string to store words in the hash

  ifstream file; // opening the file
  file.open(ignoreWordFileName);

  if(file.is_open()){ //if the file is open
    while(getline(file, storeWord)){
      // add the words to the hashTable as a reference
      stopWordsTable.addWord(storeWord);
    }
    file.close(); // closing the file
  }
  else cout << "Failed to open " << ignoreWordFileName << endl;

}
bool isStopWord(string word, HashTable &stopWordsTable)
{
  return stopWordsTable.isInTable(word);
}

int main(int argc, char* argv[]){
  HashTable stopWordsTable(STOPWORD_TABLE_SIZE);
  HashTable uwTable(atoi(argv[4]));

  getStopWords(argv[3], stopWordsTable);

  ifstream fileIn;
  fileIn.open(argv[2]);
  if(fileIn.is_open()){
  string input;

    while(fileIn >> input){ // this will read all the words until the end of the file

      if(!isStopWord(input, stopWordsTable)){// check to see if word isStopWord or not

        if(uwTable.isInTable(input)){// if word is in hash table, increment count

          uwTable.incrementCount(input);
        }
        else{// else add word into the hash table

          uwTable.addWord(input);
        }
      }
    }
  }
  else cout << "Cannot open file input." << endl;
  uwTable.printTopN(atoi(argv[1]));
  cout << "#" << endl;
  cout << "Number of collisions: " << uwTable.getNumCollisions() << endl;
  cout << "#" << endl;
  cout << "Unique non-stop words: " << uwTable.getNumItems() << endl;
  cout << "#" << endl;
  cout << "Total non-stop words: " << uwTable.getTotalNumWords() << endl;
  return 0;
}
