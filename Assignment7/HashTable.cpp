#include "HashTable.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


using namespace std;

int numUniquewords =0;

HashTable:: HashTable(int hashTableSize){
  //initialize memeber variables
  hashTable = new wordItem*[hashTableSize]; // initialize pointer array (wordItem)

  this -> hashTableSize = hashTableSize; // this will be assigning the table size

  numItems =0; // initialize count
  numCollisions = 0; // initialize count

  for(int i =0; i < hashTableSize; i++){
    hashTable[i] = nullptr;
  }
}

HashTable:: ~HashTable(){ //Leave empty
}

void HashTable:: addWord(string word){
  //int numUniquewords = 0;
  wordItem* newWord = new wordItem; // creating a new wordItem
  newWord -> word = word; //the newWord is pointing to the word to make the new word
  newWord -> next = nullptr; // anything that is next will be null

  // Now we will set 1 to be the newWord count
  newWord -> count = 1;
  int hash1 = getHash(word); // using memeber function getHash() to get the word

  // now we will traverse the index
  wordItem* temp1  = hashTable[hash1];
  if(temp1 != nullptr){
    // increment the count when temp1 isnt nullptr
    numCollisions += 1;
    // now we will attach the hash to the node
    newWord -> next = hashTable[hash1];
    hashTable[hash1] = newWord;
  }
  else{
    // we will add directly if temp1 is null
    hashTable[hash1] = newWord;
    // can't forget to increment
    numUniquewords += 1;
  }
  //also increment the number of word count
  numItems++;
}

bool HashTable:: isInTable(string word){
  wordItem* temp7 = searchTable(word);

  if(temp7 == nullptr) return false;
  else return true;
}

void HashTable::incrementCount(string word){
    wordItem* m = searchTable(word);
    if(m != NULL) m-> count++;
}
void sortArray(wordItem uniqueWords[], int length)
{
  // we will start by making a bool type
  bool second = false;
  // if the bool type is true, then the while loop will run
  while(!second){
    //since the we are in the while loop because bool type is true, we will change it
    second  =true;
    for(int i =0; i < length; i++){
      // we will create an if statement to be able to sort the array
      // if the point at a certain index is larger than the previous
      // it will sort the elements in decreasing order
      if(uniqueWords[i].count > uniqueWords[i - 1].count){
        wordItem move2;
        move2 = uniqueWords[i];
        uniqueWords[i] = uniqueWords[i - 1];
        uniqueWords[i -1] = move2;
        second =false;
      }
    }
  }
}
unsigned int HashTable:: getHash(string word){
  // here we will calculate the hash value of the word
  unsigned int hash3 = 5381; // using this because of DJB2
  int lengthHash = word.length(); // using this to get the length
  for(int i = 0; i < lengthHash; i++){
    hash3 =((hash3<<5) + hash3) + word[i];

    }
  hash3 = hash3 % hashTableSize; // dividing the hash number by the size of the hashTable
  return hash3;

}

wordItem* HashTable:: searchTable(string word){
  // using this function to search the word in the hash table
  wordItem* temp3 = hashTable[getHash(word)];

  // while loop
  while(temp3 != nullptr && temp3 -> word != word){
    temp3 =temp3 -> next;
  }
  // returing the wordItem
  return temp3;
}

void HashTable:: printTopN(int n){
  int ind = 0;
  int totalNumWords = getTotalNumWords();
  wordItem* narray;
  narray = new wordItem[numItems];

  for(int i =0; i <hashTableSize; i++){
    wordItem* temp = hashTable[i];
    while(temp != NULL && ind < numItems){
      narray[ind] = *temp;
      temp = temp -> next;
      ind++;
    }
  }
  sortArray(narray, numItems);
  for(int j =0; j< n; j++){
    float l = (float)narray[j].count/(float)totalNumWords;
    cout << fixed << setprecision(4) << l << " - " << narray[j].word << endl;
  }
}
int HashTable::getNumCollisions(){
  // will return the number of collisions in the hashtable
  return numCollisions;
}
int HashTable:: getNumItems(){
  // returns the total of unique words in the hash table
  return numItems;
}
int HashTable::getTotalNumWords(){
  // returns the number of number of words in the hash table
  int Twords = 0;// counter
  for(int i =0; i < hashTableSize; i++){
    if(hashTable[i] != NULL){
      wordItem* temp = hashTable[i];
      while(temp != NULL){
        Twords += temp -> count;
        temp = temp -> next;
      }
    }
  }
  return Twords;
}
