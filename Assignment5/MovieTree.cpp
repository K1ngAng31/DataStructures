#include "MovieTree.hpp"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

MovieTree::MovieTree()
{
  // setting any memeber functions to default
  root = nullptr;

}

MovieTree:: ~MovieTree()
{

  delete root;

}

// Helper function
MovieNode *traverse(string title, MovieNode *node)
{
  if(node == NULL)
  {
    return 0;
  }
  if(node -> title == title) // comparing title
  {
    return node;
  }
  else if(title < node -> title) // if title is not the same
  {
    return traverse(title, node -> leftChild);
  }
  else
  {
    return traverse(title, node -> rightChild);
  }
}
//Search function
MovieNode* MovieTree :: search(string title)
{
  MovieNode *node = traverse(title, root);
  return node;
}
void MovieTree::findMovie(string title)
{
  MovieNode *m = search(title);
  if(m == 0)
  {
    cout << "Movie not found." << endl;
    return;
  }
  cout << "Movie Info:" << endl;
  cout << "==================" << endl;
  cout << "Ranking:" << m ->ranking << endl;
  cout << "Title  :" << m -> title << endl;
  cout << "Year   :" << m -> year << endl;
  cout << "rating :" << m -> rating << endl;
  return;
}

void helpforPRINTMOVIE(MovieNode *help)
{
  if(help == NULL)
  {
    return;
  }
  else
  {
    helpforPRINTMOVIE(help -> leftChild);
    cout << "Movie: " << help -> title << " " << help -> rating << endl;
    helpforPRINTMOVIE(help -> rightChild);
  }
}
void MovieTree:: printMovieInventory()
{
  if(root == NULL)
  {
    return;
  }
  else
  {
    helpforPRINTMOVIE(root);
  }

}
void addMovieHelper(MovieNode* root, MovieNode* addNode);
void MovieTree:: addMovieNode(int ranking, string title,int year, float rating)
{
  MovieNode *addNode = new MovieNode;
  addNode -> ranking = ranking;
  addNode -> title = title;
  addNode -> year = year;
  addNode -> rating = rating;
  addNode -> leftChild = NULL;
  addNode -> rightChild = NULL;

  if(root == NULL)
  {
    root = addNode;
  }
  else
  {
    addMovieHelper(root, addNode);
  }
  //return root;
}

void addMovieHelper(MovieNode* root, MovieNode* addNode)
{
  if(addNode -> title < root -> title)
  {
    if(root -> leftChild != NULL)
    {
      addMovieHelper(root -> leftChild, addNode);
    }
    else
    {
      root -> leftChild = addNode;
    }
  }
  else
  {
    if(root -> rightChild != NULL)
    {
      addMovieHelper(root -> rightChild, addNode);
    }
    else
    {
      root -> rightChild = addNode;
    }
  }
}

void helpforQuery(MovieNode* root, float rating, int year)
{
  if(root == NULL)
  {
    return;
  }
  if(root -> rating >= rating && root-> year > year)
  {
    cout << root-> title <<"(" << root-> year << ") " << root-> rating << endl;
  }
  helpforQuery(root->leftChild, rating, year);
  helpforQuery(root->rightChild, rating, year);
}
void MovieTree:: queryMovies(float rating, int year)
{
  cout << "Movies that came out after " << year << " with rating at least " << rating << ":" << endl;
  helpforQuery(root,rating, year);
}
int cnt = 0;
float total(MovieNode *root)
{
  if(root == 0)
  {
    return 0;
  }
  cnt++;
  return (root->rating+total(root->leftChild)+total(root->rightChild));
}

void uniform(MovieNode *node)
{
  if(node == NULL) return;

  uniform(node -> leftChild);
  cout << "Movie: " << node -> title << " " << node -> rating << endl;
  uniform(node -> rightChild);
}
void MovieTree:: averageRating()
{
  float sum = total(root);
  float average = sum/cnt;
  if(cnt == 0)
  {
    average = 0;
  }
  cout << "Average rating:" << average << endl;
}
