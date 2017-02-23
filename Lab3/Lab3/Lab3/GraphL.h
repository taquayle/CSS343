#pragma once
#include "NodeData.h"
/****************************************************************************/
/*	NAME:	Tyler Quayle													*/
/*	ASSIGN: Lab 3															*/
/*	FILE:	GraphL.h														*/
/****************************************************************************/

const int MAXNODES_L = 100;
class GraphL
{
public:
	GraphL();
	~GraphL();

	void buildGraph(ifstream&);
	
	void displayGraph();
	void depthFirstSearch();
private:
	struct EdgeNode;      // forward reference for the compiler 

	struct GraphNode {    // structs used for simplicity, use classes if desired 
		EdgeNode* edgeHead; // head of the list of edges 
		NodeData* data;     // data information about each node 
		bool visited;
	};
	struct EdgeNode {
		int adjGraphNode;  // subscript of the adjacent graph node 
		EdgeNode* nextEdge;
	};

	/* START Variables	*/
	GraphNode *adjList;
	int numberOfNodes;
	/* END Variables*/

	/* START Functions*/
	void deleteNode(int);
	bool insertEdge(int, int);
	void depthFirstSearchHelper(int);
	/* END Functions*/	
};

