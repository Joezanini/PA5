#------------------------------------------------------------------------------
# Makefile for CMPS 101 Programming Assignment 5
#
#       make                   makes FindComponents
#       make Graph        makes Graph
#------------------------------------------------------------------------------

FindComponents : FindComponents.o Graph.o List.o
	gcc -o FindComponents FindComponents.o Graph.o List.o

FindComponents.o : FindComponents.c List.h
	gcc -c -std=c99 -Wall FindComponents.c

Graph: Graph.o List.o
	gcc -o Graph Graph.o List.o

Graph.o : Graph.c List.h
	gcc -c -std=c99 -Wall Graph.c

List.o : List.c List.h
	gcc -c -std=c99 -Wall List.c

clean :
	rm -f FindComponents Graph FindComponents.o Graph.o List.o
