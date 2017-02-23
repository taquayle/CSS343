#pragma once

/****************************************************************************/
/*	NAME:		Tyler Quayle												*/
/*	LAB:		2															*/
/*	FILE:		BinTree.h 													*/
/****************************************************************************/


#include "NodeData.h"
class BinTree
{
	friend std::ostream& operator<<(std::ostream&, BinTree&);

public:
	BinTree();
	BinTree(const BinTree&);
	~BinTree();

	bool insert(NodeData*);

	/*	OVERLOADS		*/
	bool operator==(const BinTree&) const;
	bool operator!=(const BinTree&) const;
	BinTree& operator=(const BinTree&);
	/********************/

	bool retrieve(const NodeData &, NodeData* &);
	int getHeight(const NodeData &) const;

	void bstreeToArray(NodeData*[]);	//Convert BinTree to array, in-order
	void arrayToBSTree(NodeData*[]);	//Convert array to BinTree

	bool isEmpty() const;				
	void makeEmpty();		// Deletes Tree Recursively						

	/*	PROVIDED BY PROF	*/
	void displaySideways() const;			

	/************************/
private:
	struct Node
	{
		Node *right;
		Node *left;
		NodeData *data;
	};

	Node *root;

	/****************************************************************************/
	/*	Following methods are all helper functions used for recursion			*/
	/****************************************************************************/
	bool insertHelper(Node*&, NodeData*);	
	void copyHelper(Node*&, Node*);		
	void makeEmptyHelper(Node*&); 
	bool retrieveHelper(Node*, const NodeData &, NodeData* &); 
	int getHeightHelper(Node*, const NodeData &) const;
	bool equalHelper(Node*, Node*) const; 
	int bsTreeToArrayHelper(Node*&, NodeData *[]); 
	void arrayToBSTreeHelper(NodeData*[], const Node*, int, int);
	/**	END: Helper Functions**/

	int maxDepth(Node*) const; /* Created so that getHeightHelper can find node depth from the found node*/

	void printInOrder(Node*, ostream &output); /* Called by operator<<, prints In-Order, ostream passed by ref */
	/*	PROVIDED BY PROF	*/
	void sideways(Node*, int) const;			// provided below, helper for displaySideways()
												/************************/
};

