/*
Joseph Zanini
cmps101 fall 2018
PA5
jzanini@ucsc.edu
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "List.h"
#include "Graph.h"

#define MAX_LEN 160

void printStrongs(FILE* out, Graph G, List s, int num);

int main(int argc, char* argv[]) {
	int n = 0;
	int vert1, vert2;
	int u, p;
	FILE *in, *out;
	Graph G = NULL;

	//check command line for correct number of arguments
	if (argc != 3) {
		printf("Usage: %s <input file> <output file>\n", argv[0]);
		exit(1);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL) {
		printf("Unable to open file %s for reading\n", argv[1]);
		exit(1);
	}

	if (out == NULL) {
		printf("Unable to open file %s for reading\n", argv[2]);
		exit(1);
	}

	//storing first value of file
	fscanf(in, "%d", &n);
	G = newGraph(n);

	while (fgetc(in) != EOF) {
		fscanf(in, "%d", &vert1);
		fscanf(in, "%d", &vert2);

		if (vert1 == 0 && vert2 == 0) {
			break;
		}

		addArc(G, vert1, vert2);
	}

	fprintf(out, "Adjacency list representation of G:\n");
	printGraph(out, G);

	List L = getVerts(G);

	DFS(G, L);

	Graph A = transpose(G);
	DFS(A, L);
	
	fprintf(out, "\nG contains %d strongly connected components:\n", getComps(A));
	printStrongs(out, A, L, getComps(A));

	freeList(&L);
	freeGraph(&G);

	fclose(in);
	fclose(out);
	
	return 0;
}

void printStrongs(FILE* out, Graph G, List s, int num) {
	int i;
	List* complistPtr = malloc((num + 1) * sizeof(List));

	for (i = 1; i < num + 1; i++) {
		complistPtr[i] = newList();
	}


	for (i = 1; i < num + 1; i++) {
		moveBack(s);
		while (getParent(G, get(s)) > 0) {
			prepend(complistPtr[i], get(s));
			movePrev(s);
			deleteBack(s);
		}

		prepend(complistPtr[i], get(s));
		movePrev(s);
		deleteBack(s);
	}

	for (i = 1; i < num + 1; i++) {
		fprintf(out, "Component %d: ", i);
		printList(out, complistPtr[i]);
		fprintf(out, "\n");
	}

	free(complistPtr);

	return;
}
