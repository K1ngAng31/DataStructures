#include "MovieTree.hpp"
#include <iostream>
#include <string>

using namespace std;


MovieTree::MovieTree()
{//intializing any memeber variables of the class
  root = NULL;
}
// Function to delete all memory that has
// been allocate
void DeleteMemory(TreeNode* &node)
{
    if(node == nullptr)return;
    else
    {
      DeleteMemory(node -> leftChild);
      LLMovieNode* temp = node -> head;

      DeleteMemory(node -> rightChild);
      while(node -> head -> next != NULL)
      {
        temp = node -> head -> next;
        delete node -> head -> next;
        node -> head -> next = temp -> next;
      }
      delete node -> head;
      node -> leftChild = NULL;
      node -> rightChild = NULL;
      node -> parent = NULL;
      delete node;
    }
}
MovieTree:: ~MovieTree()
{//freeing all memory that was allocated
  DeleteMemory(root);
  root = NULL
}
// printing the movies with any given letter
// in alphabetical order
// creating a printMovieInventory helper function
void HELPprintMovieInventory(TreeNode* node)
{
  if(node == NULL) return;

  else
  {
    if(node != nullptr)
    {
      HELPprintMovieInventory(node -> leftChild);
      LLMovieNode *current = node -> head;
      cout << "Movies starting with letter: " << node -> titleChar << endl;
      while(current != NULL)
      {
        cout << " >> " << current -> title << " " << current -> rating << endl;
        current = current -> next;
      }
      HELPprintMovieInventory(node -> rightChild);
    }
  }
}
void MovieTree::printMovieInventory()
{
    if(root == NULL)return;
    else HELPprintMovieInventory(root);
}
/*
For the add movie function we will make
a helper function to add movies
*/
TreeNode* searchNode(char character, TreeNode *n)
{
  if(n == NULL) return 0;
  if(n -> titleChar == character) return n;
  else if(character < n -> titleChar) return searchNode(character, n -> leftChild);
  else return searchNode(character, n -> rightChild);
}
void inOrder(LLMovieNode* head)
{
  LLMovieNode* tNode = NULL;
  LLMovieNode* tHead = head;
  LLMovieNode* tNext = head -> next;
  while(tNext != NULL)
  {
    if(tHead-> title > tNext -> title){
      tNode = tHead;
      tHead = tNext;
      tNode -> next = tNode -> next-> next;
      tHead -> next = tNode;
      tNext = tHead -> next;
    }
    else{
      tHead = tHead -> next;
      tNext = tNext-> next;
    }
  }
}

void aMHelper(TreeNode* root, TreeNode* addMovie);
void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
  LLMovieNode* addMovie = new LLMovieNode;
  addMovie -> ranking = ranking;
  addMovie -> title = title;
  addMovie -> year = year;
  addMovie -> rating = rating;
  char charc = title.at(0);
  TreeNode *newN = new TreeNode;
  newN ->titleChar = charc;
  newN -> leftChild = NULL;
  newN -> rightChild = NULL;

  if(root == NULL){
    root = newN;
    newN -> head = addMovie;
    return;
  }
  TreeNode *node = searchNode(charc, root);
  if(node == NULL){
    aMHelper(root, newN);
    newN -> head = addMovie;
  }
  else
  {
    //LLMovieNode *current = node -> head;
    if(node -> head == 0 || node -> head -> title >addMovie -> title)
    {
      addMovie -> next = node -> head;
      node -> head = addMovie;
      return;
    }
    else
    {
      LLMovieNode *current = node -> head;
      while(current -> next != 0 && current -> next -> title < addMovie -> title)
      {
        current = current -> next;
      }
      addMovie -> next = current -> next;
      current -> next = addMovie;
    }
  }
}
void aMHelper(TreeNode* root, TreeNode* addMovie)
{
  if(root == NULL){
    root = addMovie;
    return;
  }
  if(addMovie ->titleChar < root -> titleChar){
    if(root -> leftChild != NULL){
      aMHelper( root -> leftChild, addMovie);
    }
    else{
      root-> leftChild = addMovie;
    }
  }
  else{
    if(root -> rightChild != NULL){
      aMHelper(root -> rightChild, addMovie);
    }
    else{
      root -> rightChild = addMovie;
    }
  }
}
/*
helper functions to delete movies
*/
// Helper function

// TreeNode* smallTree(TreeNode *node)
// {
//   if(node -> leftChild != NULL){
//     smallTree(node -> leftChild);
//   }
//   return node;
// }
TreeNode* searchTN(TreeNode *node, string title)
{
  char fl = title.front();
  if(node == NULL) return nullptr;

  else if(node -> titleChar == fl) return node;

  else if(fl < node -> titleChar && node -> leftChild != NULL){
    return searchTN(node -> leftChild, title);
  }
  else if(fl > node -> titleChar && node -> rightChild != NULL){
    return searchTN(node -> rightChild, title);
  }
  return nullptr;
}
LLMovieNode* searchLL(LLMovieNode *node, string title)
{
  LLMovieNode * currMovie = node;
  while(currMovie != NULL){
    if(currMovie -> title == title)return currMovie;

    currMovie = currMovie -> next;
  }
  return nullptr;
}
// TreeNode* treeM(TreeNode* node)
// {
//   if(node -> leftChild != NULL){
//     treeM(node -> leftChild);
//   }
//   return node;
// }
TreeNode* minValue(TreeNode* cNode)
{
  if(cNode -> leftChild == NULL)
  {
    return cNode;
  }
  return minValue(cNode -> leftChild);
}


TreeNode* eraseAll(TreeNode *currNode, char c)
{
  if(currNode == NULL)
  {
    return NULL;
  }
  else if(c < currNode->titleChar)
  {
    currNode->leftChild = eraseAll(currNode->leftChild, c);
  }
  else if(c > currNode->titleChar)
  {
    currNode->rightChild = eraseAll(currNode->rightChild, c);
  }
  else
  {
    if(currNode->leftChild == NULL && currNode->rightChild == NULL)
    {
      delete currNode;
      return NULL;
    }
    else if(currNode->leftChild == NULL)
    {
      TreeNode *temp = currNode;
      currNode = currNode->rightChild;
      delete temp;
    }
    else if(currNode->rightChild == NULL)
    {
      TreeNode *temp = currNode;
      currNode = currNode->leftChild;
      delete temp;
    }
    else
    {
      TreeNode *temp = minValue(currNode->rightChild);
      currNode->titleChar = temp->titleChar;
      currNode -> head = temp -> head;
      currNode->rightChild = eraseAll(currNode->rightChild, temp->titleChar);
    }
  }
  return currNode;
}
//
// void deleteMovieHelper(TreeNode *tNode, TreeNode *root)
// {
//   bool isRoot = tNode == root;
//   // using the "?" expression to return a value if it holds true, vice versa
//   bool left = isRoot ? false : (tNode -> parent -> leftChild == tNode);
//
//   if(!tNode -> leftChild and !tNode -> rightChild){
//     if(left and !isRoot){
//       tNode -> parent -> leftChild = nullptr;
//     }
//     else if(!left and !isRoot) tNode -> parent -> leftChild = nullptr;
//     delete tNode;
//     tNode = nullptr;
//   }
//   else if(tNode -> rightChild){
//     TreeNode * min = smallTree(tNode -> rightChild);
//     tNode -> titleChar = min -> titleChar;
//     tNode -> head = min -> head;
//     deleteMovieHelper(min, root);
//   }
//   else if(tNode -> leftChild){
//     if(left and !isRoot){
//       tNode -> parent -> leftChild = tNode -> leftChild;
//     }
//     else if(!left and !isRoot){
//       tNode -> parent -> rightChild = tNode -> leftChild;
//     }
//     tNode -> leftChild -> parent = tNode -> parent;
//     delete tNode;
//   }
// }

void MovieTree:: deleteMovie(string title)
{
  TreeNode *titleNode = searchTN(root, title);
  if(titleNode != NULL)
  {
    LLMovieNode *mNode = searchLL(titleNode -> head, title);
    if(mNode != NULL)
    {
      if(title == titleNode -> head-> title && titleNode ->head -> next == NULL)
      {
        char c = title.at(0);
      eraseAll(root, c);

      delete mNode;
      }
      else
      {
        if(title == titleNode -> head -> title)
        {
          LLMovieNode  *curr = titleNode -> head;
          titleNode -> head = titleNode -> head -> next;
          delete curr;
        }
        else
        {
          LLMovieNode *currM = titleNode -> head;
          LLMovieNode *prev;
          while(currM != NULL)
          {
            if(currM == mNode)
            {
              break;
            }
            prev = currM;
            currM = currM -> next;
          }
          prev -> next = mNode -> next;
          delete mNode;
        }
      }
    }
  else
    {
      cout << "Movie: " << title << " not found, cannot delete." << endl;
    }
  }
  else
  {
    cout << "Movie: " << title << " not found, cannot delete." << endl;
  }
}
// above function is original function i had, tried to make a newer one
// one to rewrite the and get all the edge cases

void deleteMovie(TreeNode* node, string title)
{
  if(r == 0)
  {
    cout << "Movie: " << title << " not found, cannot delete." << endl;
    return;
  }
  LLMovieNode* nodetemp = node -> head;
  if(nodetemp -> title[0] == title[0]) // tree node is correct letter
  {
    if(nodetemp -> next == NULL)
    {
      if(node -> leftChild == 0 && node -> rightChild == 0) // no children
      {
        delete node -> head;
        node ->head = NULL;
        if(node -> parent -> leftChild == node)
        {
          node -> parent -> leftChild = NULL;
          delete node;
          node = NULL;
        }
        else if(node -> parent -> rightChild == node)
        {
          node -> parent -> rightChild = NULL;
          delete node;
          node = NULL;
        }
      }
      else if(node -> leftChild != 0 && node -> rightChild == 0)// no right node
      {
        delete node -> head;
        node -> head =NULL;
        if(node -> parent -> leftChild == node)
        {
          node -> parent -> leftChild = node -> leftChild;
          delete node;
          node = NULL;
        }
        else if(node -> parent -> rightChild == node)
        {
          node -> parent -> rightChild = node -> rightChild;
          delete node;
          node = NULL;
        }
      }
      else if(node -> leftChild == 0 && node -> rightChild != 0)// no left node
      {
        delete node -> head;
        node -> head = NULL;
        if(node -> parent -> leftChild == r)
        {
          node -> parent -> leftChild = node -> rightChild;
          node -> rightChild -> parent = node -> parent;
          delete node;
          node = NULL;
        }
        else if(node -> leftChild != 0 && node -> rightChild != 0)
        {
          node -> parent -> rightChild = node -> rightChild;
          delete node;
          node = NULL;
        }
      }
      else if(node -> leftChild != 0 && node -> rightChild != 0)// if both nodes have children
      {
        TreeNode* to_replace = minValue(node -> rightChild);
        //cout << to_replace -> head -> title << endl;
        node -> head = to_replace -> head;
        // cout << node -> head -> title << endl;
        node -> titleChar = to_replace -> titleChar;
        deleteMovie(node -> rightChild, to_replace -> head -> title);
        // cout << node -> head -> title << endl;
      }
    }
    else
    {
      LLMovieNode* previous = nodetemp;
      while(nodetemp != NULL)
      {
        if(nodetemp -> title == title && nodetemp == node -> head)// movie at the head node
        {
          node -> head = nodetemp -> next;
          delete nodetemp;
          nodetemp = NULL;
          return;
        }
        else if(nodetemp -> title == title) // movie after the head node
        {
          previous -> next = nodetemp -> next;
          delete nodetemp;
          nodetemp = NULL;
          return;
        }
        else
        {
          previous = nodetemp;
          nodetemp =nodetemp -> next;
        }
      }
      if(nodetemp == NULL)// movie not found
      {
        cout << "Movie: " << title << " not found, cannot delete." << endl;
        return;
      }
    }
  }
  else if(title[0] < nodetemp -> title[0])// search left node
  {
    deleteMovie(node -> leftChild, title);
    return;
  }
  else if(title[0] > nodetemp -> title[0])// search right node
  {
    deleteMovie(node -> rightChild, title);
    return;
  }
}

void MovieTree::deleteMovie(string title)
{
    deleteMovie1(root, title);
}
/* ==================================================== */
/*                        NEW CODE                      */
/*  =================================================== */
#include "MovieTree.hpp"
#include <iostream>

MovieTree::MovieTree()
{
root = nullptr;
}

void pmHelper(TreeNode *node)
{
  if(node == nullptr)return;
  else
  {
    if(node != nullptr)
    {
      pmHelper(node ->leftChild);
      LLMovieNode *nde = node -> head;
      cout << "Movies starting with letter: " << node -> titleChar <<endl;
      while(nde != nullptr)
      {
        cout << " >> " << nde->title << " " << nde->rating << endl;
        nde = nde -> next;
      }
      pmHelper(node-> rightChild);
    }
  }
}
void MovieTree::printMovieInventory()
{
  if(root == nullptr)return;
  else
  {
    pmHelper(root);
  }
}
TreeNode* searchMovie(char character, TreeNode *aNode)
{
  if(aNode == NULL) return 0;
  if(aNode -> titleChar == character) return aNode;
  else if(character < aNode -> titleChar) return searchMovie(character, aNode -> leftChild);
  else return searchMovie(character, aNode -> rightChild);
}
void addMovieHelper(TreeNode* root, TreeNode* addMovie);
void MovieTree::addMovie(int ranking, string title, int year, float rating)
{
  LLMovieNode* addMovie = new LLMovieNode;
  addMovie -> ranking = ranking;
  addMovie -> title = title;
  addMovie -> year = year;
  addMovie -> rating = rating;
  char charc = title.at(0);

  if(root == NULL){
    TreeNode *newNode = new TreeNode;
    newNode -> titleChar = charc;
    newNode -> leftChild = NULL;
    newNode -> rightChild = NULL;
    root = newNode;
    newNode -> head = addMovie;
    return;
  }
  TreeNode *node1 = searchMovie(charc, root);
  if(node1 == NULL)
  {
    TreeNode *newNode = new TreeNode;
    newNode ->titleChar = charc;
    newNode -> leftChild = NULL;
    newNode -> rightChild = NULL;
    addMovieHelper(root, newNode);
    newNode -> head = addMovie;
  }
  else
  {
    if (node1->head ==nullptr)
    {
      addMovie->next =node1->head;
      node1->head = addMovie;
      return;
    }
    else if (node1->head->title > addMovie->title)
    {
      addMovie->next = node1->head;
      node1->head = addMovie;
    }
    else
    {
      LLMovieNode* current = node1->head;
      while(current->next != nullptr && current->next->title < addMovie->title)
      {
        current = current->next;
      }
      addMovie->next = current->next;
      current->next = addMovie;
    }
  }
}
void addMovieHelper(TreeNode* root, TreeNode* addMovie)
{
  if(addMovie ->titleChar < root -> titleChar)
  {
    if(root -> leftChild != NULL)
    {
      addMovieHelper( root -> leftChild, addMovie);
    }
    else
    {
      root-> leftChild = addMovie;
      addMovie->parent = root;
    }
  }
  else
  {
    if(root -> rightChild != NULL){
      addMovieHelper(root -> rightChild, addMovie);
    }
    else
    {
      root -> rightChild = addMovie;
      addMovie->parent = root;
    }
  }
}
TreeNode *minimumNode(TreeNode *node2)
{
  TreeNode *curr = node2;
  while(curr->leftChild != nullptr)
  {
    curr = curr ->leftChild;
  }
  return curr;
}
TreeNode *deleteTree(TreeNode *node3, char title)
{
  if(node3 == nullptr)
  {
    return node3;
  }
  if(node3->leftChild != nullptr && title < node3->titleChar)
  {
    node3->leftChild = deleteTree(node3->leftChild, title);
    return node3;
  }
  else if(node3->rightChild != nullptr && title > node3->titleChar)
  {
    node3->rightChild = deleteTree(node3->rightChild, title);
    return node3;
  }
  if(node3->leftChild != nullptr && node3->rightChild != nullptr)
  {
    TreeNode* mini = minimumNode(node3->rightChild);
    node3->titleChar = mini->titleChar;
    node3->head = mini->head;
    node3->rightChild = deleteTree(node3->rightChild,mini->titleChar);
  }
  else if(node3->leftChild !=nullptr)
  {
    TreeNode* another = node3->leftChild;
    delete node3;
    return another;
  }
  else if(node3->rightChild != nullptr)
  {
    TreeNode* one = node3->rightChild;
    delete node3;
    return one;
  }
  else
  {
    delete node3;
    return nullptr;
  }
  return node3;
}
TreeNode *searchDeleteTree(TreeNode *node4, string title)
{
  if(node4 == nullptr)
  {
    cout << "Movie: " << title << " not found, cannot delete." << endl;
    return node4;
  }
  LLMovieNode *temp = node4->head;
  LLMovieNode *prev = nullptr;
  while(temp !=nullptr && temp->title != title)
  {
    prev = temp;
    temp = temp->next;
  }
  if(temp == node4->head)
  {
    node4->head = temp->next;
    delete temp;
    temp = nullptr;
  }
  else if(temp->next == nullptr && temp->title == title)
  {
    prev->next = nullptr;
    delete temp;
    temp = nullptr;
  }
  else
  {
    prev->next = temp ->next;
    delete temp;
    temp = nullptr;
  }
  return node4;
}
void MovieTree::deleteMovie(string title)
{
  TreeNode *node5 = searchMovie(title[0], root);
  searchDeleteTree(node5, title);
  if(node5 && node5->head == nullptr)
  {
    root = deleteTree(root, title[0]);
    return;
  }
}
MovieTree::~MovieTree()
{
  while(root!= nullptr)
  {
    deleteMovie(root->head->title);
  }
    root = nullptr;
}
