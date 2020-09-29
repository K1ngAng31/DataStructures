#include "PriorityQueue.hpp"
#include <iostream>
#include <string>

using namespace std;


PriorityQueue::PriorityQueue(int queueSize){
  // Initiate all class objects
  maxQueueSize = queueSize; // setting max size to int size
  currentQueueSize = 0; // # of group currently in the Prio Queue
  priorityQueue = new GroupNode[maxQueueSize]; // making node equal to array
}

PriorityQueue::~PriorityQueue(){
  //free all resources that object has acquired
  // free all memory
  maxQueueSize = 0; // setting evreything back to 0
  currentQueueSize =0; // setting evrything back to 0
  delete [] priorityQueue; // deleting all memory that was used for the array
  priorityQueue = nullptr; // setting array back to NULL
}

void PriorityQueue::enqueue(string _groupName, int _groupSize, int _cookingTime){
  // enqueue new group into priority queue
  if(!isFull()){
    GroupNode tempN;// this will be our groupNode to add to the end of queue
    tempN.groupName = _groupName;

    tempN.groupSize = _groupSize;

    tempN.cookingTime = _cookingTime;
    // this will added it to the end ofthe priorityQueue array
    priorityQueue[currentQueueSize] = tempN;
    currentQueueSize++; //increment eachtime
    //now calling the repairUpward function to repair repairUpward
    repairUpward(currentQueueSize - 1); //this will be at the laast index

  }
  //else statement if it is full
  else cout << "Heap full, cannot enqueue" << endl; return;
}

void PriorityQueue::dequeue(){
  //remove all the groups at the front of the priority queue
  if(!isEmpty()){
    //replacing the first index of the groupNode with the last node
    // in the priorityQueue
    priorityQueue[0] = priorityQueue[currentQueueSize -1];
    //decrementing the currentQueueSize
    currentQueueSize--;
    // using the repairDownward function
    repairDownward(0);
  }
  else {
    cout << "Heap empty, cannot dequeue" << endl;
    return;
  }
}

GroupNode PriorityQueue:: peek(){
  // return groupID of the group at the fron of the priority queue
  if(isEmpty()) cout << "Heap empty, nothing to peek" << endl;
  return priorityQueue[0];
}

bool PriorityQueue:: isFull(){
  // if queue is empty, return true
  // else return false
  if(currentQueueSize== maxQueueSize) return true;
  else return false;
}
bool PriorityQueue:: isEmpty(){
  // if queue is empty then return true
  // else return false
  if(currentQueueSize == 0) return true; // if empty
  else return false; // if not empty

}

/* PRIVATE FUNCTIONS */
void PriorityQueue::repairUpward(int nodeIndex){
  //be able to maintain the head properties by swapping node with the parent node
  // *IF NECESSARY*
  int nIndex;
  nIndex = nodeIndex; // setting a counter to use as nodeIndex
  int parent;
  parent = (nIndex - 1)/2; // function is from lecture notes to find the pos

  if(parent >= 0 && priorityQueue[parent].groupSize == priorityQueue[nIndex].groupSize && parent < maxQueueSize){
    if(priorityQueue[parent].cookingTime > priorityQueue[nIndex].cookingTime){
      nIndex = parent;
    }
  }
  if(parent >= 0 && priorityQueue[parent].groupSize > priorityQueue[nIndex].groupSize){
    nIndex = parent;
  }
  if(nIndex != nodeIndex){
    GroupNode swap;
    swap = priorityQueue[nodeIndex];
    priorityQueue[nodeIndex] = priorityQueue[nIndex];
    priorityQueue[nIndex] = swap;
    repairUpward(nIndex);
  }
}

void PriorityQueue::repairDownward(int nodeIndex){
  //be able to maintain heap properties by swapping node with child node
  // *IF NECESSARY*
  int cmp1;// int for first comparison = left child
  cmp1 = 2*nodeIndex+1; //function find the pos of first comparison
  int cmp2; // int for the second comparison = right child
  cmp2 = 2*nodeIndex+2; //function to find the pos second comparison
  int max;// int to know when the max is
  max = nodeIndex;//max will be nodeIndex when it is true

  /* NOW IF STATEMENTS FOR THE COMPARISONS */
  // 1st comparison using 2 if's to check edge cases
  if(cmp1 > nodeIndex && priorityQueue[cmp1].groupSize == priorityQueue[max].groupSize && cmp1 < maxQueueSize){
    if(priorityQueue[cmp1].cookingTime < priorityQueue[max].cookingTime){
      max = cmp1;
    }
  }
  // 2nd comparison using 2 if's to check edge cases
  else if(cmp2 > nodeIndex && priorityQueue[cmp2].groupSize == priorityQueue[max].groupSize && cmp2 < maxQueueSize){
    if(priorityQueue[cmp2].cookingTime < priorityQueue[max].cookingTime){
      max = cmp2;
    }
  }
  // 3rd comparison
  else if(cmp1 > nodeIndex && priorityQueue[cmp1].groupSize < priorityQueue[max].groupSize && cmp1< maxQueueSize -1){
    max = cmp1;
  }
  //last comparison?
  else if(cmp2 > nodeIndex && priorityQueue[cmp2].groupSize < priorityQueue[max].groupSize && cmp2 < maxQueueSize -1){
    max = cmp2;
  }
  //last check to see if nodeIndex does not = max;
  if(max != nodeIndex){
    GroupNode tempN;// creating a group node tempN
    tempN = priorityQueue[nodeIndex];// setting tempN = to the pQ at nodeIndex
    priorityQueue[nodeIndex] = priorityQueue[max];// setting the pQ pos equal to the max
    priorityQueue[max] = tempN;// making the max pos = to the temp node
    repairDownward(nodeIndex); // recurssively using the function for the max
  }
}
