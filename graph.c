#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

//Johannes Ferm

nod *create_nod(int x) //creating node
{
	nod *ny = malloc(sizeof(nod)); //mallocing and setting struct variables 
	ny->edgeback = NULL;
	ny->edgefrwd = NULL;
	ny->vertexnmbr = x;
	return ny;
}

list *create_list() //creating list
{
	list *l = malloc(sizeof(list)); //mallocing and setting l->first
	l->first = NULL;
	return l;
}

graph *create_graph(int n) //function to create graph
{
	graph *g = malloc(sizeof(graph)); //malloc graph
	g->firstnodes = malloc(sizeof(list)); //malloc list
	g->size = n; //set size
	int i = 1;
	int nmbr = 1;
	while(i <= n) //for each node
	{
		g->firstnodes[i] = *create_list(); //create an adjacency list
		g->firstnodes[i].first = create_nod(nmbr); //and create the first node in the adjacency list
		i++;
		nmbr++;
	}
	return g; //return the graph
}

int add_after(list *l, int value) //funktion för att lägga till nod sist, omskriven(Helper function to create lists, stolen/taken from one of my own previous
{                                  //assignments)
	nod *ny = malloc(sizeof(nod)); //skapa ny nod
	ny->vertexnmbr = value;
	nod *temp = l->first;		   //temporär nod som pekar på huvudet
	if(ny == NULL)				   //om det inte gick att skapa noden
		return 0;
		
	if(l->first == NULL)		   //om listan är tom, denna if behövs mest för att sätta l->initial->adjR till NULL
	{							   //(det skulle säkert kunna göras någon annanstans, tex innan man kallar på funktionen.
		l->first = ny;
		l->first->edgefrwd = NULL;
		return 1;
	}
	else                           //om listan inte tom
	{
		while(temp->edgefrwd != NULL)  //stega fram till slutet av listan
		{
			temp = temp->edgefrwd;
		}
		temp->edgefrwd = ny;		   //sätt in den nya noden
		ny->edgefrwd = NULL;		   //sätt "slutet" till NULL
		ny->edgeback = temp;
		return 1;
	}
}

int getNumVertices(graph *G) //getting amount of vertices
{
	int i = 1;
	int count = 0;
	while(G->firstnodes[i].first != NULL) //find how many adjacency lists we have, which is the answer to number of vertices
	{
		count++;
		i++;
	}
	return count;
}

int getNumEdges(graph *G) //getting amount of edges
{
	int i = 1;
	int edges = 0;
	nod *temp;
	while(i <= G->size) //loop through all nodes
	{
		temp = G->firstnodes[i].first;
		while(temp != NULL && temp->edgefrwd != NULL) //and all nodes in the adjacency lists for all nodes
		{
			edges++; //increment edges
			temp = temp->edgefrwd;
		}
		i++;
	}
	if(G->firstnodes[1].first->edgefrwd->edgeback == NULL) //Here I've assumed that we don't mix undirected and directed edges in a graph
		return edges;
	else
		return edges / 2; //for undirected graphs
}

list getNeighbors(graph *g, nod *x)
{
	int i = 1;
	nod *temp;
	while(1 <= g->size) //finding the right adjacency list
	{
		temp = g->firstnodes[i].first;
		if(temp == x)
		{
			break;
		}
		i++;
	}
	return g->firstnodes[i]; //return it
}

list *getDirNeighbors(graph *g, int index) //get all neighbors for directed graph, combination of the out and in solutions
										   //(wasn't sure if it was allowed but if it is you can also call out and in functions to create one big list)
{										   //testing has been added in graphtest.c as well. 
	list *N = create_list();
	int i = 1;
	nod *temp;
	while(g->firstnodes[i].first != NULL)
	{
		if(i == index)
		{
			i++;
			continue;
		}
		temp = g->firstnodes[i].first;
		while(temp != NULL)
		{
			if(temp->vertexnmbr == index)
				add_after(N, i);					//helper function from previous course used here, only used to make the list with InNeighbors
			temp = temp->edgefrwd;
		}
		i++;
	}
	temp = g->firstnodes[index].first->edgefrwd;
	while(temp != NULL)
	{
		add_after(N, temp->vertexnmbr);
		temp = temp->edgefrwd;
	}
	return N;
}
	

list getOutNeighbors(graph *g, nod *x) //getting outgoing neighbors
{
	int i = 0;
	nod *temp;
	while(1 <= g->size) //loop through all nodes
	{
		temp = g->firstnodes[i].first; //when we find the right node, break
		if(temp == x)
			break;
		i++;
	}
	return g->firstnodes[i]; //return adjacency list for that node
}

list *getInNeighbors(graph *g, int index) //getting in neighbors
{
	list *N = create_list();
	int i = 1;
	nod *temp;
	while(g->firstnodes[i].first != NULL)
	{
		if(i == index)	//if we're on the adjacency list for the node we're looking for the neighbors to
		{
			i++;
			continue;
		}
		temp = g->firstnodes[i].first;
		while(temp != NULL)
		{
			if(temp->vertexnmbr == index)			//adding to list if the node is in another nodes adjacency list
				add_after(N, i);					//helper function from previous course used here, only used to make the list with InNeighbors
			temp = temp->edgefrwd;
		}
		i++;
	}
	return N;
}
		

void addDirEdge(graph *g, int index, int vertexnr)
{
	nod *ny = malloc(sizeof(nod));
	ny->vertexnmbr = vertexnr;
	nod *temp = g->firstnodes[index].first;
	while(temp->edgefrwd != NULL) //finding last spot in adjacency list
	{
		temp = temp->edgefrwd;
	}
	temp->edgefrwd = ny; //adding the new node last
	ny->edgeback = NULL; 
	ny->edgefrwd = NULL;
}

void addEdge(graph * g, int index, int vertexnr) //same as adding a directed edge
{
	nod *temp = g->firstnodes[index].first;
	nod *ny = malloc(sizeof(nod));
	ny->vertexnmbr = vertexnr;
	while(temp->edgefrwd != NULL)
	{
		temp = temp->edgefrwd;
	}
	temp->edgefrwd = ny;
	ny->edgeback = temp; //but setting the edgeback as well
}	

void addEdgeW(graph * g, int index, int vertexnr, int w) //same as other edge functions
{
	nod *ny = malloc(sizeof(nod));
	ny->vertexnmbr = vertexnr;
	ny->weight = w;	//but adding weight
	nod *temp = g->firstnodes[index].first;
	while(temp->edgefrwd != NULL)
	{
		temp = temp->edgefrwd;
	}
	temp->edgefrwd = ny;
	ny->edgeback = temp;
}

void addDirEdgeW(graph *g, int index, int vertexnr, int w) //same as other edge functions
{
	nod *ny = malloc(sizeof(nod));
	ny->vertexnmbr = vertexnr;
	ny->weight = w; //but adding weight
	nod *temp = g->firstnodes[index].first;
	while(temp->edgefrwd != NULL)
	{
		temp = temp->edgefrwd;
	}
	temp->edgefrwd = ny; 
	ny->edgeback = NULL; 
	ny->edgefrwd = NULL;
}

void print_list(list *l) //printing an adjacency list
{
	nod *temp = l->first;
	while(temp != NULL) //loop through the adjacency list
	{	
		if((temp->edgefrwd != NULL) && (temp->edgefrwd->edgeback == NULL)) //if we have a directed edge
			printf("%d->", temp->vertexnmbr); //print with arrow
		else
		{
			if(temp->edgefrwd == NULL) //if we're on the last node in list
				printf("%d", temp->vertexnmbr); //print without '-' or '->'
			else                                //if temp->edgefrwd != NULL && temp->edgeback != NULL, meaning if we have an undirected edge
				printf("%d-", temp->vertexnmbr); //print with just a line
		}
		temp = temp->edgefrwd;
	}
	printf("\n");
}

void print_listW(list *l) //printing weighted adjacency list, exactly the same as regular but printing with the weight in parenthesis
{
	nod *temp = l->first;
	while(temp != NULL)
	{	
		if((temp->edgefrwd != NULL) && (temp->edgefrwd->edgeback == NULL))
			printf("%d(%d)->", temp->vertexnmbr, temp->weight);
		else
		{
			if(temp->edgefrwd == NULL)
				printf("%d(%d)", temp->vertexnmbr, temp->weight);
			else
				printf("%d(%d)-", temp->vertexnmbr, temp->weight);
		}
		temp = temp->edgefrwd;
	}
	printf("\n");
}
	

void print_graph(graph *g) //print the graph
{
	int i = 1;
	while(i <= g->size) //loop through all nodes
	{
		printf("Adjacency list for vertex %d: ", i);
		print_list(&g->firstnodes[i]); //and print their adjacency lists
		i++;
	}
}

void print_graphW(graph *g) //printing weighted graphs
{
	int i = 1;
	while(i <= g->size)
	{
		printf("Adjacency list for vertex %d: ", i);
		print_listW(&g->firstnodes[i]); //use weighted print function instead of regular
		i++;
	}
}

int hasEdge(graph *g, int index, int vertexnr) //check if there's an edge
{
	nod *temp = g->firstnodes[index].first;
	while(temp != NULL) //loop through adjacency list of source
	{
		if(temp->vertexnmbr == vertexnr) //if we find destination, return 1
			return 1;
		temp = temp->edgefrwd;
	}
	return 0;
}
