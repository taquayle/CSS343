#pragma once
#include "NodeData.h"
#include <fstream>

/****************************************************************************/
/*	NAME:	Tyler Quayle													*/
/*	ASSIGN: Lab 3															*/
/*	FILE:	GraphM.h														*/
/****************************************************************************/


static const int MAXNODES_M = 100;

class GraphM
{
public:
	GraphM();
	~GraphM();

	void buildGraph(ifstream&);
	bool insertEdge(int, int, int);
	bool removeEdge(int, int);
	void findShortestPath();

	void displayAll();
	void display(int, int);

private:
	struct TableType {
		bool visited;          // whether node has been visited
		int dist;              // shortest distance from source known so far
		int path;              // previous node in path of min dist
	};

	void getPath(const int, const int, bool) const; // Display path, bool makes it display name or number
	int findMinVert(int) const; // Find minimum vert
	void resetVisit(); // Reset all nodes to unvisited

	NodeData data[MAXNODES_M];              // data for graph nodes 
	int C[MAXNODES_M][MAXNODES_M];            // Cost array, the adjacency matrix
	int size;                             // number of nodes in the graph
	TableType T[MAXNODES_M][MAXNODES_M];      // stores visited, distance, path

};

