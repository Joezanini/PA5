/*
Joseph Zanini
cmps101 fall 2018
PA5
jzanini@ucsc.edu
*/

#include<stdio.h>
#include<stdlib.h>
#include "Graph.h"
#include "List.h"

//private Node Object
typedef struct GraphObj {
	List* listPtr;
	char* color;
	int* p;
	int* d;
	int size;
	int order;
	int* finish;
} GraphObj;

//typedef GraphObj* Graph;

/*** Constructors-Destructors ***/

//newGraph()
// Returns reference to a new empty Graph object.
Graph newGraph(int n) {
	int i;

	Graph G = malloc(sizeof(GraphObj));
	G->listPtr = malloc((n + 1) * sizeof(List)); //declaring array of Lists

	//allocating new empty lists in the array.
	for(i = 0; i < n + 1; i++) {
		//List temp = newList();
		G->listPtr[i] = newList();
	}

	//vertex propery arrays for DFS
	G->color = NULL;
	G->p = NULL;
	G->d = NULL;
	G->size = 0;
	G->order = n;
	G->finish = NULL;

	return(G);
}

//freeGraph()
// Frees all heap memory associagted with *pG, and sets *pG to NULL.
void freeGraph(Graph* pG) {

	if ((*pG)->color != NULL) {
		free((*pG)->color);
        (*pG)->color = NULL;
    }

    if ((*pG)->d != NULL) {
        free((*pG)->d);
        (*pG)->d = NULL;
    }

    if ((*pG)->p != NULL) {
        free((*pG)->p);
        (*pG)->p = NULL;
    }

    if ((*pG)->finish != NULL) {
    	free((*pG)->finish);
    	(*pG)->finish = NULL;
    }

    if ((*pG)->listPtr != NULL) {
    	free((*pG)->listPtr);
    	(*pG)->listPtr =NULL;
    }


    if (pG != NULL && *pG != NULL) {
        free(*pG);
        *pG = NULL;
     }

     return;
}

/*** Access functions ***/

//getOrder()
// Returns the value at the order.
// Pre: G != NULL
int getOrder(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getOrder() on a NULL Graph pointer\n");
		exit(1);
	}
	return(G->order);
}

//getSize()
// Returns the size of the Graph object.
// Pre: G != NULL
int getSize(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getSize() on a NULL Graph pointer\n");
		exit(1);
	}
	return(G->size);
}


//getParent()
// Returns the value of the parent of u.
// Pre: G != NULL and (1 <= u < getOrder())
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getParent() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getParent() on a out of bounds vertex\n");
		exit(1);
	}

	if (G->p != NULL) {
		return(G->p[u]);
	} else {
		return(NIL);
	}
}

//getDiscover()
// Returns the value of the discovery time to the node u
// Pre: G != NULL 
// pre: getOrder() > u >= 1
int getDiscover(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getDiscovery() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getDiscovery() on a out of bounds vertex\n");
		exit(1);
	}

	if (G->d != NULL) {
		return(G->d[u]);
	} else {
		return(UNDEF);
	}
}

//getFinish()
// Returns the value of the finish time to the node u
// Pre: G != NULL 
// pre: getOrder() > u >= 1
int getFinish(Graph G, int u) {
	if (G == NULL) {
		printf("Graph Error: calling getFinish() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getFinish() on a out of bounds vertex\n");
		exit(1);
	}

	if (G->finish != NULL) {
		return(G->finish[u]);
	} else {
		return(UNDEF);
	}
}


// addEdge()
// Insert a new edge joining u to v and v to u
// Pre: 1<= u <= getOrder(G) and  1<= v <= getOrder(G)
// and G != NULL
void addEdge(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling getEdge() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getEdge() on a out of bounds vertex u\n");
		exit(1);
	}

	if (v < 1 && v > getOrder(G)) {
		printf("Graph Error: calling getEdge() on a out of bounds vertex v\n");
		exit(1);
	}

	insertOrdered(G->listPtr[u], v);
	insertOrdered(G->listPtr[v], u);
	G->size ++;
	return;
}

//addArc()
// inserts a directed edge between 2 vertices
// pre: getOrder() > u >= 1
// pre: getOrder() > v >= 1
void addArc(Graph G, int u, int v) {
	if (G == NULL) {
		printf("Graph Error: calling getArc() on a NULL Graph pointer\n");
		exit(1);
	}

	if (u < 1 && u > getOrder(G)) {
		printf("Graph Error: calling getArc() on a out of bounds vertex u\n");
		exit(1);
	}

	if (v < 1 && v > getOrder(G)) {
		printf("Graph Error: calling getArc() on a out of bounds vertex v\n");
		exit(1);
	}

	insertOrdered(G->listPtr[u], v);
	G->size++;
}

//DFS()
//Depth First Search
void DFS(Graph G, List s) {
	int i;
	int time = 0;
	int n = getOrder(G);

	if (G == NULL) {
		printf("Graph Error: calling DFS() on a NULL Graph pointer\n");
		exit(1);
	}

	G->color = malloc((n + 1) * sizeof(char));
	G->p = malloc((n + 1) * sizeof(int));
	G->d = malloc((n + 1) * sizeof(int));
	G->finish = malloc((n + 1) * sizeof(int));


	for (i = 1; i < n + 1; i++) {
		G->color[i] = 'w';
		G->d[i] = UNDEF;
		G->finish[i] = UNDEF;
		G->p[i] = NIL;
	}

	List temp = copyList(s);

	for (moveFront(temp); index(temp) >= 0; moveNext(temp)) {
		i = get(temp);
		deleteBack(s);
		if (G->color[i] == 'w') {
			visitDFS(G, s, i, &time);
		}
	}

	
	return;
}

void visitDFS(Graph G, List s, int u, int* time) {
	int vert;
	*time = *time + 1;
	G->d[u] = *time;
	//printf("\n discovered %d  at time : %d", u, *time);
	G->color[u] = 'g';

	for (moveFront(G->listPtr[u]); index(G->listPtr[u]) >= 0; 
		moveNext(G->listPtr[u])) {
		vert = get(G->listPtr[u]);
		
		if (G->color[vert] == 'w') {
			G->p[vert] = u;
			visitDFS(G, s, vert, &*time);
		}
	}

	G->color[u] = 'b';
	*time = *time + 1;
	G->finish[u] = *time;
	//printf("\n finished %d  at time : %d", u, *time);
	prepend(s, u);

	return;
}

//getVerts()
// creates a list of vertices for Dfs
List getVerts(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling getVerts() on a NULL Graph pointer\n");
		exit(1);
	}


	List A = newList();
	int i;
	int n = getOrder(G) + 1;

	for (i = 1; i < n; i ++) {
		if (!isEmpty(G->listPtr[i])) {
			append(A, i);
		}
	}

	return(A);
}

//getComps()
// returns number of stongly connected 
// components
int getComps(Graph G) {
	int i;
	int count = 0;
	int n = getOrder(G) + 1;

	for (i = 1; i < n; i++) {
		if (getParent(G, i) < 0) {
			count++;
		}
	}

	return(count);
}

//printGraph()
// prints the adjacency List representation
//of a Graph Object to a output file.
void printGraph(FILE* out, Graph G) {
	int i;
	int stop = getOrder(G);

	if (G == NULL) {
		printf("Graph Error: calling printGraph() on a NULL Graph pointer\n");
		exit(1);
	}

	for (i = 1; i <= stop; i++) {
		fprintf(out, "%d: ", i);
		for (moveFront(G->listPtr[i]); index(G->listPtr[i]) >= 0; 
			moveNext(G->listPtr[i])) {
			fprintf(out, "%d", get(G->listPtr[i]));
			fprintf(out, "%s", " ");
		}
		fprintf(out, "%s\n", " ");
	}
	return;
}

//copyGraph()
Graph copyGraph(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling printGraph() on a NULL Graph pointer\n");
		exit(1);
	}
	int i, j;
	Graph A = newGraph(getOrder(G));


	for (i = 1; i < getOrder(G) + 1; i++) {
		for (moveFront(G->listPtr[i]); index(G->listPtr[i]) >= 0; 
			moveNext(G->listPtr[i])) {
			j = get(G->listPtr[i]);
			addArc(A, i, j);
		}
	}

	return(A);
}

//transpose(Graph)
Graph transpose(Graph G) {
	if (G == NULL) {
		printf("Graph Error: calling printGraph() on a NULL Graph pointer\n");
		exit(1);
	}
	int i, j;
	Graph A = newGraph(getOrder(G));


	for (i = 1; i < getOrder(G) + 1; i++) {
		for (moveFront(G->listPtr[i]); index(G->listPtr[i]) >= 0; 
			moveNext(G->listPtr[i])) {
			j = get(G->listPtr[i]);
			addArc(A, j, i);
		}
	}

	return(A);
}













