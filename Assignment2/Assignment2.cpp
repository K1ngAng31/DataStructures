#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

// creating a struct because we will want to store the words
// in a dynamically sized array of structs, hence the following;

struct wordItem
{
  //we will use the following to be able to store the unique words and its count
  string word;
  int count;
};

// The following functions and declaration of variables will be used
// throughout the code and are the functions required to be able use

void getStopWords(char *ignoreWordFileName, string ignoreWords[]);
bool isStopWord(string word, string ignoreWords[]);
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length);
void arraySort(wordItem uniqueWords[], int length);
void printTopN(wordItem uniqueWords[], int topN, int totalNumWords);
bool infoStruct(wordItem uniqueWords[], string single, int &index);
const int STOPwordsize = 50;
const int ArrayStartSize = 100;
wordItem *doubleArray(wordItem *uniqueWords, int &index, int &wordCount);

int main(int argc, char *argv[])
{

  string wordsToIgnore[STOPwordsize];
  getStopWords((char *) "ignoreWords.txt", wordsToIgnore);

  ifstream WordsStop;
  WordsStop.open(argv[2]);
  string linetext;
  int index1 = 0;
  int numDouble =0;
  int numWords = 100;
  int stop = 0;
  // now we create a dynamically allocated array
  // becasue we are going to be deleting the memory inside the
  // the array becasue it is memory that we dont longer need
  wordItem *uniqueWords =  new wordItem[ArrayStartSize];

  while (getline(WordsStop, linetext))
  {
    if(linetext.empty())
    {
      continue; // we are using this function because if it is empty
      // we want to jump to the next loop for neext iteration
    }
    else
    {
      stringstream words(linetext);
      string single;
      while (words >> single) // here we are using bitwise shift to
      // the right to modify the variables
      {
        bool answer = isStopWord(single, wordsToIgnore);
        if(answer == false)
        {
          stop++;
          bool answer2 = infoStruct(uniqueWords, single, index1);

          if(answer2 == false)
          {
            if(index1 == numWords)
            {
              uniqueWords = doubleArray(uniqueWords, index1, numWords);
              numDouble++;
            }
            uniqueWords[index1].word = single;
            uniqueWords[index1].count = 1;
            index1++;
          }
        }
      }
    }
  }
  arraySort(uniqueWords, index1);
  //printTopN(uniqueWords,1, 20);
  int tUW = getTotalNumberNonStopWords(uniqueWords, index1);

  cout << "Array doubled: " << numDouble << endl;
  cout << "#" << endl;
  cout << "Unique non-common words: " << index1 << endl;
  cout << "#" << endl;
  cout << "Total non-common words: " << tUW << endl;
  cout << "#" << endl;
  cout << "Probabilities of top " << argv[1] << " most frequent words " << endl;
  cout << "---------------------------------------" << endl;
  printTopN(uniqueWords,stoi(argv[1]),tUW );
  //cout << printTopN
}

// first we will create a helper function to see if any of the information is in the structs
bool infoStruct(wordItem uniqueWords[], string single, int &index)
{
  // will be using int & to accept address of variables to be used as a parameter

  // creating a for loop
  // it will go through the address of variable and see if the info is inside
  for(int i =0; i < index; i++)
  {
    //now use an if statement to be able to see if the element in the array is
    // equal to the string
    if(uniqueWords[i].word == single)
    {
      uniqueWords[i].count = uniqueWords[i].count +1;
      return true; // will reutnr true if statement is true
    }
  }
  // if for loop is no longer true it will return false
  return false;

}

// Now we create function that will be doubling the array
wordItem *doubleArray(wordItem *uniqueWords, int &index, int &wordCount)
{
  wordCount = wordCount*2;
  wordItem *tempArray = new wordItem[wordCount];
  for(int i =0; i < index; i++)
  {
    tempArray[i] = uniqueWords[i];
  }

  delete [] uniqueWords;
  return tempArray;
}
// This function reads the ignore word file and if it is open is adds the words
// to the vector of the string type
void getStopWords(char *ignoreWordFileName, string ignoreWords[])
{
  int move = 0; // this will be a counter to be able to move from word to word
  string store; //this will be a string that will store the words in the vector

  ifstream file; // opening the File
  file.open(ignoreWordFileName);

  // now creating an if statement
  if(file.is_open())// if the file is open it will read each line
  // and add the words to the vector as a reference
  {
    while(getline(file, store))
    {
      ignoreWords[move] = store;
      move++;
    }
  }
  // if the file does not open, error message will print out
  else
  {
    cout << "Failed to open " << ignoreWordFileName << endl;
  }
}

// Now we use the bool function to check if the word is a stop word from
// the ignore words
bool isStopWord(string word, string ignoreWords[])
{
  // we will start will the bool type being false
  // until it checks the word to see if it is stop word
  // if it is, bool will become true
  bool one = false;
  for(int i =0; i < 50; i++)// 50 is the max or 100?
  {
    if(word == ignoreWords[i])
    {
      one = true; // if the word is a stop word then one becomes true
      break; // using the break function to end to if statement
    }
    else
    {
      one = false; // if it is not, then one will stay fale;
    }
  }
  return one;
}

// The following function will be used to determine the number of words that
// are in the words array
int getTotalNumberNonStopWords(wordItem uniqueWords[], int length)
{
  int amountofWords = 0; // this is in charge of adding the unique words
  // will be using a for loop to iterate through the index and adds them
  for(int i =0; i < length; i++)
  {
    amountofWords = amountofWords + uniqueWords[i].count;
  }
  return amountofWords; // will return the amount of words
}

// now we will create the array sort function to sort the array of wordItem
void arraySort(wordItem uniqueWords[], int length)
{
  // we will start by making a bool type
  bool second = false;
  // if the bool type is true, then the while loop will run
  while(!second)
  {
    //since the we are in the while loop because bool type is true, we will change it
    second  =true;
    for(int i =0; i < length; i++)
    {
      // we will create an if statement to be able to sort the array
      // if the point at a certain index is larger than the previous
      // it will sort the elements in decreasing order
      if(uniqueWords[i].count > uniqueWords[i - 1].count)
      {
        wordItem move2;
        move2 = uniqueWords[i];
        uniqueWords[i] = uniqueWords[i - 1];
        uniqueWords[i -1] = move2;
        second =false;
      }
    }
  }
}

// now we will create the printTopN function which will be
//the top number of words
// in the array
// now we will create the printTopN function which will be
//the top number of words
// in the array
void printTopN(wordItem uniqueWords[],int topN, int totalNumWords)
{
  for(int i =0; i < topN; i++)
  {
    float l =((float)(uniqueWords[i].count))/(float)(totalNumWords);
    cout << fixed << setprecision(4) << l << " - " << uniqueWords[i].word << endl;
    // if(l > .01)
    // {
    // cout << setprecision(3) << l << " - " << uniqueWords[i].word << endl;
    // // this will print out the function by counting the counts and the number of top words
    // }
    // else if(l <.01)
    // {
    //     cout << setprecision(2) << l << " - " << uniqueWords[i].word << endl;
    // }
    // else
    // {
    //     if(l == .0100)
    //     cout <</* setprecision(4)*/ l << " - " << uniqueWords[i].word << endl;
    // }
  }
  return;
}
