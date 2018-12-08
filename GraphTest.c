/*
Joseph Zanini
cmps101 fall 2018
PA5
jzanini@ucsc.edu
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "Graph.h"
#include "List.h"

void printStrongs(Graph G, List s, int num);

int main(int argc, char* argv[]) {

	Graph g = newGraph(1);

	printf("new Graph size: %d\n", getSize(g));
	printf("new Graph order: %d\n", getOrder(g));
	printf("new Graph parent: %d\n", getParent(g, 2));
	printf("new Graph discovery: %d\n", getDiscover(g, 2));
	printf("new Graph finish: %d\n", getFinish(g, 2));

	freeGraph(&g);

	g = newGraph(8);

	addArc(g, 1, 2);
	addArc(g, 2, 3);
	addArc(g, 3, 4);
	addArc(g, 4, 3);
	addArc(g, 4, 8);
	addArc(g, 8, 8);
	addArc(g, 5, 1);
	addArc(g, 5, 6);
	addArc(g, 6, 7);
	addArc(g, 7, 8);
	addArc(g, 7, 6);
	addArc(g, 2, 5);
	addArc(g, 2, 6);
	addArc(g, 3, 7);

	printf("new Graph size: %d\n", getSize(g));
	printf("new Graph order: %d\n", getOrder(g));
	//printf("new Graph time: %d\n", getTime(g));


	//upTime(g);
	//upTime(g);

	//printf("new Graph time: %d\n", getTime(g));

	List s = getVerts(g);

	for (moveFront(s); index(s) >= 0; moveNext(s)) {
		printf("\ns : %d", get(s));
	}

	printf("\n");

	DFS(g, s);

	for (moveFront(s); index(s) >= 0; moveNext(s)) {
		printf("\ns : %d", get(s));
	}

	printf("\n");

	//printf("new Graph time: %d\n", getTime(g)); 
	//profesor tontalo said not to use this method in lecture.
	printf("new Graph comps: %d\n", getComps(g));

	Graph A = transpose(g);
	DFS(A, s);
	printf("\nnew Graph comps: %d\n", getComps(A));

	for (moveFront(s); index(s) >= 0; moveNext(s)) {
		printf("\ns : %d", get(s));
	}

	printf("\n");

	printStrongs(A, s, getComps(A));

	printf("\n");

	return 0;
}

void printStrongs(Graph G, List s, int num) {
	//int spot = length(s);
	int count = 0;
	int i, j;

	for (i = 0; i < num + 0; i++) {
		moveBack(s);

		//printf("\n mb : ");
		while (getParent(G, get(s)) > 0) {
			count++;
			//printf("%d ", get(s));
			movePrev(s);
		}

		//if (count == 0) {
			//printf("%d ", get(s));
		//}

		//printf("\ncount : %d", count);

		//printf("%d ", get(s));
		//spot = spot - count;
		printf("\n%d : ", i + 1);

		if (count == 0) {
			printf("%d ", get(s));
		}

		while(index(s) > 0) {
			printf("%d ", get(s));
			moveNext(s);
		}

		for (j = 0; j < count + 1; j++) {
			deleteBack(s);
		}

		printf("\n");

		count = 0;
	}

	return;
}









