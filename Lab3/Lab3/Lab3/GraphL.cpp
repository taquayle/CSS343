#include "GraphL.h"

/****************************************************************************/
/*	NAME:	Tyler Quayle													*/
/*	ASSIGN: Lab 3															*/
/*	FILE:	GraphL.cpp														*/
/****************************************************************************/

/****************************************************************************/
/*	GraphL(): Defualt constructor, sets nnumberOfNodes to zero. otherwise	*/
/*	very boring																*/
/*	Called By: n/a															*/
/****************************************************************************/
GraphL::GraphL()
{
	numberOfNodes = 0;
}

/****************************************************************************/
/*	~GraphL(): if number of nodes never assigned, skips. Otherwise loops	*/
/*	thru the adjList and deletes all nodes by calling deleteNode until edge */
/*	head is NULL. Then deletes the list										*/
/*	Called By: n/a															*/
/****************************************************************************/
GraphL::~GraphL()
{
	if (numberOfNodes > 0)
	{
		for (int i = 0; i <= numberOfNodes; i++)
		{
			while (adjList[i].edgeHead != NULL)
			{
				deleteNode(i);
			}
			delete adjList[i].data;
			adjList[i].data = NULL;
		}

		numberOfNodes = 0;
		delete[] adjList;
		adjList = NULL;
	}
}

/****************************************************************************/
/*	deleteNode(atIndex): Deletes the edgeHead of the adjList at the atIndex	*/
/*	index. Edgehead next becomes the new edgeHead, ~GraphL will call until	*/
/*	this function until the edgeHead is NULL								*/
/*	Called By: ~GraphM() 													*/
/****************************************************************************/
void GraphL::deleteNode(int atIndex)
{
	EdgeNode *toDelete;

	toDelete = adjList[atIndex].edgeHead;
	adjList[atIndex].edgeHead = adjList[atIndex].edgeHead->nextEdge;

	toDelete->nextEdge = NULL;
	delete toDelete;
	toDelete = NULL;
}

/****************************************************************************/
/*	BuildGraph(inFile): takes in a txt file, gets first line indicating how	*/
/*	many vertices there are. Check the next lines for 0 0, indicating end	*/
/*	of vertices cost.														*/
/*	Called By: n/a															*/
/****************************************************************************/
void GraphL::buildGraph(ifstream &inFile)
{
	int origin;
	int destin;

	inFile >> numberOfNodes;
	if (numberOfNodes > 0)
	{
		adjList = new GraphNode[numberOfNodes + 1];

		/* Get Names of Vertices */
		for (int i = 0; i <= numberOfNodes; i++)
		{
			adjList[i].data = new NodeData;
			adjList[i].data->setData(inFile);
			adjList[i].visited = false;
			adjList[i].edgeHead = NULL;
		}
		for (;;)
		{
			inFile >> origin >> destin;	// get next 2 data points

			/*	Check for 0 0, indicating end of set	*/
			if ((origin == 0) && (destin == 0))
			{
				break; //Found end of set
			}

			/*	Lookout for EoF, shoudn't happen since 0 0 should come first */
			if (inFile.eof())
			{
				break; // no more lines of data
			}

			/* valid Line, check for valid numbers & insert */
			insertEdge(origin, destin);
		}
	}
}

/****************************************************************************/
/*	insertEdge(origin, destin): called by BuildGraph to insert into the adj	*/
/*	array. Checks if in range, places new edge at the head of the list and	*/
/*	so it's easier to output in display										*/
/*	Called By: buildGraph()													*/
/****************************************************************************/
bool GraphL::insertEdge(int origin, int destin)
{
	if (origin <= 0 || origin > numberOfNodes)
	{
		return false;
	}
	if (destin <= 0 || destin > numberOfNodes)
	{
		return false;
	}

	EdgeNode *temp = new EdgeNode; 
	temp->adjGraphNode = destin; 

	if (adjList[origin].edgeHead == NULL) //Empty List
	{
		temp->nextEdge = NULL; 
		adjList[origin].edgeHead = temp; 
	}
	else 
	{
		temp->nextEdge = adjList[origin].edgeHead;
		adjList[origin].edgeHead = temp;
	}
	temp = NULL;
	delete temp;
	temp = NULL;
	return true;
}

/****************************************************************************/
/*	displayGraph(): Displays the data names and the edges they have, loops	*/
/*	thru adjList displaying edges, if the GraphNode has any edge heads		*/
/*	Called By: n/a															*/
/****************************************************************************/
void GraphL::displayGraph()
{
	for (int i = 1; i <= numberOfNodes; i++)
	{
		cout << "NODE " << i << ":\t\t" << *adjList[i].data << endl;
		if (adjList[i].edgeHead != NULL)
		{
			/* Need a temp to traverse nodes, otherwise could destroy list	*/
			EdgeNode *temp; 
			temp = adjList[i].edgeHead;

			while (temp != NULL)
			{
				cout << "   edge " << i << " " << temp->adjGraphNode << endl;
				temp = temp->nextEdge;
			}
			delete temp; 
			temp = NULL;
		}
	}
}

/****************************************************************************/
/*	depthFirstSearch(): loops through the adjList, calling it's helper		*/
/*	function that recursively goes through the list looking for unvisited	*/
/*	nodes																	*/
/*	Called By: n/a															*/
/****************************************************************************/
void GraphL::depthFirstSearch()
{
	/* Needs to set everything to false in case this function is called more*/
	/* then once															*/	
	for (int i = 1; i < numberOfNodes; i++)
	{
		adjList[i].visited = false;
	}
	
	cout << endl <<"Depth First Search: ";

	for (int i = 1; i < numberOfNodes; i++)
	{
		if (!adjList[i].visited)
		{
			depthFirstSearchHelper(i);
		}
	}
	cout << endl;
}

/****************************************************************************/
/*	depthFirstSearchHelper(source): goes thru recursively the adjList at	*/
/*	index source. Finds an unvisted adjList node and follows this node until*/
/*	its null. Then 'jumps' back up to depthFirstSearch						*/
/*	Called By: 	depthFirstSearch()											*/
/****************************************************************************/
void GraphL::depthFirstSearchHelper(int source)
{
	adjList[source].visited = true;
	cout << source << " ";

	EdgeNode *temp = adjList[source].edgeHead;

	while (temp != NULL)
	{
		if (adjList[temp->adjGraphNode].visited == false)
		{
			depthFirstSearchHelper(temp->adjGraphNode);
		}
		temp = temp->nextEdge;
	}
	delete temp;
	temp = NULL;
}