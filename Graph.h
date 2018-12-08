/*
Joseph Zanini
cmps101 fall 2018
PA5
jzanini@ucsc.edu
*/

#ifndef _Graph_H_INCLUDED
#define _Graph_H_INCLUDED
#define UNDEF -1
#define NIL -2

#include "List.h"

//Exported type
typedef struct GraphObj* Graph;

/*** Constructors-Destructors ***/

//newGraph()
// Returns reference to a new empty Graph object.
Graph newGraph(int n);

//freeGraph()
// Frees all heap memory associagted with *pG, and sets *pG to NULL.
void freeGraph(Graph* pG);

/*** Access functions ***/

//getOrder()
// Returns the value at the order.
// Pre: G != NULL
int getOrder(Graph G);

//getSize()
// Returns the size of the Graph object.
// Pre: G != NULL
int getSize(Graph G);

//getTime() 
//returns global time attribte of graph
// for discovery and finished arrays
int getTime(Graph G);


//upTime()
//increments time as needed
//for dfs
void upTime(Graph G);

//getVerts()
// creates a list of vertices for Dfs
List getVerts(Graph G);

//getComps()
// returns number of stongly connected 
// components
int getComps(Graph G);

//getParent
// Returns the value of the parent of u.
// Pre: G != NULL 
// pre: getOrder() > u >= 1
int getParent(Graph G, int u);

//getDiscovery()
// Returns the value of the discovery time to the node u
// Pre: G != NULL 
// pre: getOrder() > u >= 1
int getDiscover(Graph G, int u);


//getFinish()
// Returns the value of the finish time to the node u
// Pre: G != NULL 
// pre: getOrder() > u >= 1
int getFinish(Graph G, int u);

/*** Manipulation procedures ***/


//addEdge()
// inserts an edge between 2 vertices
// pre: getOrder() > u >= 1
// pre: getOrder() > v >= 1
void addEdge(Graph G, int u, int v);

//addArc()
// inserts a directed edge between 2 vertices
// pre: getOrder() > u >= 1
// pre: getOrder() > v >= 1
void addArc(Graph G, int u, int v);

//DFS()
//Depth First Search
void DFS(Graph G, List s);

//visit()
//DFS helper
void visitDFS(Graph G, List s, int u, int* time);

/*** Other operations ***/

//transpose(Graph)
Graph transpose(Graph G);

//copyGraph()
Graph copyGraph(Graph G);

//printGraph()
// prints the adjacency List representation
//of a Graph Object to a output file.
void printGraph(FILE* out, Graph G);

#endif












