#include "GraphM.h"
#include <math.h>
#include <climits> // Compiling on linux, needs CLimit since INT_MAX not known

/****************************************************************************/
/*	NAME:	Tyler Quayle													*/
/*	ASSIGN: Lab 3															*/
/*	FILE:	GraphM.cpp														*/
/****************************************************************************/


/****************************************************************************/
/*	GraphM(): default constructor, setting everything to INT_MAX (infinity)	*/
/*	checks to see if I==J, setrs equal to zero since origin and destination */
/*	are the same															*/
/****************************************************************************/
GraphM::GraphM()
{
	size = 0;
	for (int i = 0; i < MAXNODES_M; i++)
	{
		for (int j = 0; j < MAXNODES_M; j++)
		{
			C[i][j] = INT_MAX;		// Default to inf
			T[i][j].dist = INT_MAX; // Default to inf
			if (i == j)				// Distance to self is 0
			{
				T[i][j].dist = 0;
				C[i][j] = 0;
			}
			T[i][j].visited = false;
			T[i][j].path = 0;
		}
	}
}

/****************************************************************************/
/*	~GraphM(): Deconstructor, since no pointers, default					*/
/****************************************************************************/
GraphM::~GraphM()
{
}

/****************************************************************************/
/*	BuildGraph(inFile): takes in a txt file, gets first line indicating how	*/
/*	many vertices there are. Check the next lines for 0 0 0, indicating end */
/*	end of vertices cost.													*/
/****************************************************************************/
void GraphM::buildGraph(ifstream &inFile)
{
	int origin;
	int destin;
	int distance;

	inFile >> size;
	if (size > 0)
	{
		/* Get Names of Vertices */
		for (int i = 0; i <= size; i++)
		{
			data[i].setData(inFile);
		}
		for (;;)
		{
			inFile >> origin >> destin >> distance;	// get next 3 data points
													/*	Check for 0 0 0, indicating end of set	*/
			if ((origin == 0) && (destin == 0) && (distance == 0))
			{
				break; //Found end of set
			}

			/*	Lookout for EoF, shoudn't happen since 0 0 0 should come first */
			if (inFile.eof())
			{
				break; // no more lines of data
			}

			/* valid Line, check for valid numbers & insert */
			insertEdge(origin, destin, distance);
		}
	}
}

/****************************************************************************/
/*	insertEdge(Origin, Destin, Distance): checks input for validity before  */
/*	inserting into Cost Matrix.												*/
/*	Called By: buildgraph()													*/
/****************************************************************************/
bool GraphM::insertEdge(int origin, int destin, int distance)
{
	/*	Check for origin validity	*/
	if (origin <= 0 || origin > size)
	{
		//cerr << "Invalid Origin Vertice: " << origin;
		return false;
	}
	/*	Check for destination validity	*/
	if (destin <= 0 || destin > size)
	{
		//cerr << "Invalid Destination Vertice: " << destin;
		return false;
	}
	/*	Check for distance valdity	*/
	if (distance <= 0)
	{
		//cerr << "Invalid Distance: " << distance;
		return false;
	}
	
	/*	build adjacancy matrix	*/
	C[origin][destin] = distance;
	
	return true;
}

/****************************************************************************/
/*	removeEdge(Origin, Destin, Distance): checks input for validity before  */
/*	removing from Cost Matrix and Table matrix.								*/
/*	Called By: buildgraph()													*/
/****************************************************************************/
bool GraphM::removeEdge(int origin, int destin)
{
	/*	Check for origin validity	*/
	if (origin <= 0 || origin > size)
	{
		//cerr << "Invalid Origin Vertice: " << origin;
		return false;
	}
	/*	Check for destination validity	*/
	if (destin <= 0 || destin > size)
	{
		//cerr << "Invalid Destination Vertice: " << destin;
		return false;
	}
	
	C[origin][destin] = INT_MAX;
	T[origin][destin].path = 0;
	T[origin][destin].dist = INT_MAX;
	return true;
}

/****************************************************************************/
/*	findShortestPath(): Nested loops to look thru the C and T matrixes,looks*/
/*	for cheapest route by comparing distances. Greedy Algorithm				*/
/*	Called By: n/a															*/	
/****************************************************************************/
void GraphM::findShortestPath()
{
	int v = -1;
	int minValue = INT_MAX;

	/*	loop through all source */
	for (int source = 1; source <= size; source++)
	{ 
		/* clear all visited */
		resetVisit();

		/*	loop through adjacency matrix */
		for (int edge = 1; edge < size; edge++) 
		{

			/*	Find minimum distance node */
			v = findMinVert(source);

			/* No Minimum vertex found, iterate source */
			if (v == -1)
			{
				continue;
			}

			/*	mark V as visited */
			T[source][v].visited = true;

			/* loop through all edges 'w' of parent 'v' */
			for (int w = 1; w <= size; w++) 
			{
				if (C[v][w] != INT_MAX && T[v][w].visited == false) 
				{
					if (T[source][w].dist > T[source][v].dist + C[v][w])
					{
						/*	Update distance	*/
						T[source][w].dist = T[source][v].dist + C[v][w];
						T[source][w].path = v;
					}
				}
			}
		}
	}
}

/****************************************************************************/
/*	resetVisit(): goes through table matrix setting everything to false to	*/
/*	let findShortestPath() find correct paths, using T[][].path				*/
/*	Called By: findShortestPath()											*/
/****************************************************************************/
void GraphM::resetVisit()
{
	for (int i = 1; i <= size; i++)
	{
		for (int j = 1; j <= size; j++)
		{
			T[i][j].visited = false;
		}
	}
}

/****************************************************************************/
/*	findMinVert(checkSource): finds minimum unechecked value V, if not		*/
/*	checked yet, returns that value(min). If no unvisted minimum value is	*/
/*	found, return -1														*/
/*	Called By: findShortestPath()											*/
/****************************************************************************/
int GraphM::findMinVert(int checkSource) const {

	int min = -1;
	int minValue = INT_MAX;

	//loop through all edges to find min edge
	for (int edge = 1; edge <= size; edge++) 
	{
		//if path exists and less than minValue
		if ((T[checkSource][edge].dist < minValue) && !(T[checkSource][edge].visited))
		{
			minValue = T[checkSource][edge].dist;
			min = edge;
		}
	}
	return min;
}

/****************************************************************************/
/*	displayAll(): iterates through the T and C matrix to display all costs	*/
/*	and paths																*/
/****************************************************************************/
void GraphM::displayAll()
{

	cout << endl << "Description   | From  | To    | Cost  | Path";
	for (int i = 1; i <= size; i++)	// Origin loop
	{
		cout << endl << data[i] << endl;
		for (int j = 1; j <= size; j++) // Destination Loop
		{
			/* Check to see if distance to self */
			if (i != j)
			{
				cout << "\t\t" << i << "\t" << j;
				
				/* Check to see if distance was set */
				if (T[i][j].dist != INT_MAX)
				{
					cout << "\t" << T[i][j].dist << "\t";
					getPath(i, j, true);
					cout << endl;
				}
				/* No distance, or path, show ---- */
				else
				{
					cout << "\t---" << endl;
				}
			}
		}
		cout << endl;
	}
}

/****************************************************************************/
/*	display(origin, destin): checks to see if path exists from origin to	*/
/*	destin, if exists call getPath(), otherwise display --- NO PATH			*/
/****************************************************************************/
void GraphM::display(int origin, int destin)
{
	
	/*	Check for origin validity	*/
	if (origin <= 0 || origin > size)
	{
		//cerr << "\nInvalid Origin Vertice: " << origin << endl;
		return;
	}
	/*	Check for destination validity	*/
	if (destin <= 0 || destin > size)
	{
		//cerr << "\nInvalid Destination Vertice: " << destin << endl;
		return;
	}
	cout << endl << "Display | From Node | To Node | Cost |  Path" << endl;
	cout << "\t\t" << origin << "\t" << destin;
	
	if (T[origin][destin].dist != INT_MAX)
	{
		cout << "\t" << T[origin][destin].dist << "\t";
		getPath(origin, destin, true);
		cout << endl;
		getPath(origin, destin, false);
	}
	
	else
	{
		cout << "\t---\tNO PATH" << endl;
	}
	cout << endl;
}

/****************************************************************************/
/*	getPath(origin, destin, nameOrNum): recursively goes thru T matrix to	*/
/*	using each nodes path as the place to go next. nameOrNum tells method to*/
/*	display either the numbers or name of the paths							*/
/*	Called By: display() displayAll()										*/
/****************************************************************************/
void GraphM::getPath(const int origin, const int destin, bool nameOrNum) const
{
	if (origin != destin)
	{
		if (T[origin][destin].path != 0)
		{
			getPath(origin, T[origin][destin].path, nameOrNum);
		}
	}
	if (nameOrNum)
	{
		cout << destin << " ";
	}
	else
	{
		cout << data[destin] << endl;
	}
}