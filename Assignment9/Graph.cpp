#include "Graph.hpp"
#include <iostream>
#include <vector>
#include <queue>
#include <stack>


using namespace std;

Graph:: Graph(){//constructor
}

Graph::~Graph(){//destructor
}

void Graph:: addVertex(string cityName){
  bool check = false;
  //go through the size of the vector vertices
  for(int i =0; i < vertices.size(); i++){
    // will check if there is a new vertex there
    // and if it is there then
    if(vertices[i].name == cityName){
      //if there make variable true
      check = true;
      // if there print name vertex
      cout << vertices[i].name << endl;
    }
  }
  //now when vertex is not there do
  if(check == false){
    //will create verte struct
    vertex vert;
    //will assign the values to meembers to the struct vertex
    vert.name = cityName;
    vert.visited = false;
    // add new vertex to vertices
    vertices.push_back(vert);
  }
}
void Graph::addEdge(string v1, string v2, int distance){
  //go through the size of the vector vertices
  for(int i =0; i < vertices.size(); i++){
    //will check for v1 in the list
    if(vertices[i].name == v1){
      //if it is there then go through the size of the vector
      for(int j =0; j < vertices.size(); j++){
        //also check if v2 is present in the list
        if(vertices[j].name == v2 && i != j){
          // create vertex object
          Edge edg;
          //now assign the vertices;
          edg.v = &vertices[j];
          // now assign the distance
          edg.distance = distance;
          // and add a new edge to the vertices vector
          vertices[i].Edges.push_back(edg);
        }
      }
    }
  }
}

void Graph:: printDFT(){
  setAllVerticesUnvisited();
  for(unsigned int i =0; i < vertices.size(); i++){
    if(vertices[i].visited == false){
      DFT_traversal(&vertices[i]);
    }
  }
}
void Graph::DFT_traversal(vertex* v){
  cout << v -> name << endl;
  v -> visited = true;
  for(unsigned int i= 0; i < v->Edges.size(); i++){
    if(!v->Edges[i].v->visited){
      DFT_traversal(v->Edges[i].v);
    }
  }
}

void Graph::printBFT(){
  setAllVerticesUnvisited();
  for(unsigned int i =0; i < vertices.size(); i++){
    if(vertices[i].visited == false){
      BFT_traversal(&vertices[i]);
    }
  }
}
void Graph::BFT_traversal(vertex *v){
  queue<vertex*>q;
  v->visted = true;
  q.push(v);
  while(!q.empty()){
    v = q.front();
    q.pop();
    cout << v -> name << endl;
    for(unsigned int i =0; i < v-> Edges.size(); i++){
      if(!v-> Edges[i].v->visited){
        v->Edges[i].v->visited = true;
        q.push(vp>Edges[i].v);
      }
    }
  }
}

void Graph:: setAllVerticesUnvisited(){
  for(unsigned int i =0; i < vertices.size(); i++){
    vertices[i].visited = false;
  }
}

vertex* Graph::findVertex(string name){
  vertex *begin;
  for(int i =0; i < (int)vertices.size();i++){
    vertices[i].visited = false;
    if(vertices[i].name == name){
      begin = &vertices[i];
    }
  }
  return begin;
}
void Graph:: displayEdges(){
  for(unsigned int i =0; i < vertices.size(); i++){
    cout << vertices[i].name << "-->";
    for(unsigned int j=0; j < vertices[i].Edges.size(); j++){
      cout << vertices[i].Edges[j].v->name<<" " << "(" << vertices[i].Edges[j].distance << " miles)";
      if(j != vertices[i].Edges.size() -1){
        cout << "***";
      }
    }
    cout << endl;
  }
}
