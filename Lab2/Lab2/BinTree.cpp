#include "BinTree.h"

/****************************************************************************/
/*	NAME:		Tyler Quayle												*/
/*	LAB:		2															*/
/*	FILE:		BinTree.cpp													*/
/****************************************************************************/

/****************************************************************************/
/*	BinTree(): Defualt constructor, sets root to NULL						*/
/****************************************************************************/
BinTree::BinTree()
{
	root = NULL;
}

/****************************************************************************/
/*	BinTree(BinTree): Copy constructor, deep copy of the passed in tree		*/
/****************************************************************************/
BinTree::BinTree(const BinTree& copyTree)
{
   copyHelper(root, copyTree.root);
}
/*----------------------END CONSTRUCTOR FUNCTIONS---------------------------*/

/****************************************************************************/
/*	~BinTree(): Destructor, calls makeEmpty() clearing the BinTree			*/
/****************************************************************************/
BinTree::~BinTree()
{
	makeEmpty();
}



/****************************************************************************/
/*	insert(ins): gets passed in a node (ins), immedielty calls its Helper 	*/
/*	to insert into a binary tree 											*/
/****************************************************************************/
bool BinTree::insert(NodeData *ins)
{
	return insertHelper(root, ins);
}

/****************************************************************************/
/*	insertHelper(&curPtr, *dataptr): takes in the root of the tree and a 	*/
/*	nodeData ptr, if its larger the root it searches down the right side if */
/*	it's smaller it searches down left until empty leaf is found, returns   */
/*	true if empty found. If not found, dataPtr is equal to something in the */
/*	tree 																	*/
/*	CALLED BY: insert(NodeData)												*/
/****************************************************************************/
bool BinTree::insertHelper(Node *&curPtr, NodeData *dataptr)
{
   if (curPtr == NULL) 
   {
      Node* temp = new Node;    // exception is thrown if memory is not allocated
      temp->data = dataptr; 
      dataptr = NULL; 
      temp->left = temp->right = NULL;
      curPtr = temp; 
      return true;
   }
   else
   {
     if(*dataptr > *curPtr->data)
     {
       return insertHelper(curPtr->right, dataptr);
     }
     if(*dataptr < *curPtr->data)
     {
       return insertHelper(curPtr->left, dataptr);
     }
   }
   return false;
}
/*----------------------END INSERT FUNCTIONS--------------------------------*/

/****************************************************************************/
/*	operator==(const rhs): Gets the right tree and immediately calls the 	*/
/*	helper function, passing in the root along the way. Returns true if 	*/
/*	equalHelper is true														*/
/****************************************************************************/
bool BinTree::operator==(const BinTree &rhs) const
{
	return equalHelper(root, rhs.root);
}

/****************************************************************************/
/*	operator!=(const rhs): Gets the right tree and immediately calls then 	*/
/*	helper function, passing in the root along the way. Returns the opposite*/
/*	of whatever opertor== returns, since != is just the opposite of ==		*/
/****************************************************************************/
bool BinTree::operator!=(const BinTree &rhs) const
{
	return !(*this == rhs);
}

/****************************************************************************/
/*	equalHelper(left, right): Takes and recursively checks the tree, will   */
/*	return false if one node is NULL and the comparing node is not NULL 	*/
/*	or will return false if data values are unequal. If hits a leaf and 	*/
/*	still hasn't found unequal Nodes, returns true							*/
/*	CALLED BY: operator==													*/
/****************************************************************************/
bool BinTree::equalHelper(Node *left, Node* right) const
{
	/*	Leaf Found, return true		*/
	if (left == NULL && right == NULL)
	{
		return true;
	}

	if ((left == NULL) || (right == NULL))
	{
		return false;
	}

	if (*left->data != *right->data)
	{
		return false;
	}
	return	(equalHelper(left->left, right->left) &&
		equalHelper(left->right, right->right));
}
/*----------------------END EQUALITY FUNCTIONS------------------------------*/

/****************************************************************************/
/*	operator=(BinTree rhs): Gets the right BinTree (rhs), and checks to see */
/*	if they are uneqal (not being assigned to self), if they are not call 	*/
/*	copyHelper, otherwise they are equal. do nothing (return *this)			*/
/****************************************************************************/
BinTree& BinTree::operator=(const BinTree& rhs)
{
   if (this != &rhs)
   { 
      makeEmptyHelper(root);  // deallocate left-hand side
      copyHelper(root, rhs.root);  // copy right-hand side
   }
   return *this;
}

/****************************************************************************/
/*	copyHeler(&thisNode, copyNode): makes a DEEP copy of whatever copyNode 	*/
/*	->data is. This function copies recursively. 							*/
/*	CALLED BY: operator=, BinTree(BinTree)									*/
/****************************************************************************/
void BinTree::copyHelper(Node *&thisNode, Node *copyNode)
{
	if (copyNode != NULL)
	{
		thisNode = new Node;
		NodeData *temp = new NodeData(*copyNode->data);
		thisNode->data = temp;
		copyHelper(thisNode->left, copyNode->left);
		copyHelper(thisNode->right, copyNode->right);
	}
	else
	{
		thisNode = NULL;
	}
}
/*----------------------END ASSIGNMENT FUNCTIONS----------------------------*/

/****************************************************************************/
/*	retrieve(const &look, &found): gets what NodeData is being searched for */
/*	(Look) and the node that will be given the found value (found). calls 	*/
/*  it's helper function to get return value								*/
/****************************************************************************/
bool BinTree::retrieve(const NodeData &look, NodeData *&found)
{
	retrieveHelper(root, look, found);

	if (found != NULL)
	{
		return true;
	}

	return false;
}

/****************************************************************************/
/*	retrieveHelper(curPtr, &look, &found): Takes in current root(curPtr) and*/
/*	checks it agasint the information being looked for (look). If look and 	*/
/*	curPtr are equal, give found curPtr-data value. if curPtr is NULL set  	*/
/*	found to NULL and return false. Otherwise, look through tree 			*/
/*	CALLED BY: retrieve(const NodeData, Nodedata&)							*/
/****************************************************************************/
bool BinTree::retrieveHelper(Node* curPtr, const NodeData &look, NodeData* &found)
{
	if (curPtr == NULL) //Not Found
	{
		found = NULL;
		return false;
	}

	else if (look == *curPtr->data) //Item Found
	{
		found = curPtr->data;
		return true;
	}
	else if (look < *curPtr->data) //Check left
	{
		return retrieveHelper(curPtr->left, look, found);
	}
	else if (look > *curPtr->data) //Check right
	{
		return retrieveHelper(curPtr->right, look, found);
	}
}
/*----------------------END RETRIEVE FUNCTIONS------------------------------*/



/****************************************************************************/
/*	getHeight(const &look): Takes in the variable that the getHeightHelper  */
/*	looks for (look). Returns the value of getHeightHelper, which returns 	*/
/*	the value of maxDepth. Return->getHeightHelper->maxDepth				*/
/****************************************************************************/
int BinTree::getHeight(const NodeData &look) const
{
	return getHeightHelper(root, look);
}

/****************************************************************************/
/*	getHeightHelper(curPtr, &look): goes thru the tree recursively without  */
/*	using the binary tree attributes (since weare not allowed to know its a */
/*	binary tree), when it finds the correct node, it calls maxDepth from the*/
/*	found curPtr. Returning the value of maxDepth 							*/
/*	CALLED BY: getHeight()													*/
/****************************************************************************/
int BinTree::getHeightHelper(Node* curPtr, const NodeData &look) const
{
	if (curPtr == NULL)
	{
		return 0;
	}

	if (*curPtr->data == look)
	{
		/*	Find maxdepth from current node. not of entire tree */
		return maxDepth(curPtr);
	}

	return 	getHeightHelper(curPtr->left, look) +
		getHeightHelper(curPtr->right, look);
}

/****************************************************************************/
/*	maxDepth(curPtr): gets the maxDepth from the input node. Returning the 	*/
/*	highest number between left and right branches. if branches are equal 	*/
/*	returns the depth of the lTree											*/
/*	CALLED BY: getHeightHelper()											*/
/****************************************************************************/
int BinTree::maxDepth(Node* curPtr) const
{
	if (curPtr == NULL)
	{
		return 0;
	}

	else
	{
		int lDepth = maxDepth(curPtr->left);
		int rDepth = maxDepth(curPtr->right);

		if (lDepth > rDepth)
		{
			return(lDepth + 1);
		}

		/* rDepth is longer, or node is a Leaf*/
		if (lDepth <= rDepth)
		{
			return(rDepth + 1);
		}
	}
}




/****************************************************************************/
/*	bstreeToArray(bsArray[]): Takes in an Array of type NodeData, which is  */
/*	empty, then goes thru BinTree recursively In Order by calling its helper*/
/*	method, after helper fills array. Tree is destroyed						*/
/****************************************************************************/
void BinTree::bstreeToArray(NodeData *bsArray[])
{
	bsTreeToArrayHelper(root, bsArray);
	makeEmpty();
}

/****************************************************************************/
/*	bsTreeToArrayHelper(curPtr, bsArray[]): Called by bsTreeToArray    		*/
/*	gets depth of each side of the tree (left & right int), using those as  */
/*	index values for where to store the binary tree nodes within the array 	*/
/*	CALLED BY: bstreeToArray(NodeData [])									*/
/****************************************************************************/
int BinTree::bsTreeToArrayHelper(Node *&curPtr, NodeData *tempArray[])
{
	if(curPtr == NULL) 
	{
		return 0;
	}

	int left = bsTreeToArrayHelper(curPtr->left, tempArray);

   NodeData *temp; 
   temp = curPtr->data; 
   curPtr->data = NULL; 
   *(tempArray + left) = temp; 
   temp = NULL;  
   

	int right = bsTreeToArrayHelper(curPtr->right, tempArray + left + 1);
 
	return left + right + 1; 
}


/****************************************************************************/
/*	arrayToBSTree(bsArray[]): Given array of type NodeData, populates a new */
/*	tree by passing array to helper function. Checks to see if array is 	*/
/*	empty, if not, empties tree and finds last element in array before 		*/
/*	calling arrayToBSTreeHelper() 											*/
/****************************************************************************/
void BinTree::arrayToBSTree(NodeData *bsArray[])
{
	int endOfArray = 0;
	for (int i = 0; i < 100; i++)
	{
		if (bsArray[i] != NULL)
		{
			endOfArray++;
		}
	}
	arrayToBSTreeHelper(bsArray, root, 0, endOfArray - 1);
}

/****************************************************************************/
/*	arrayToBSTreeHelper(tempArray[], &curePtr, start, end): Recursively goes*/
/*	thru array by using start and end points to break array into smaller 	*/
/*	sections and inserting mid point of section into new root. This is quite*/
/*	similar to how a mergeSort algorithm works, just missing the sort 		*/
/*	CALLED BY: arrayToBSTree(NodeData[])									*/
/****************************************************************************/
void BinTree::arrayToBSTreeHelper(NodeData *tempArray[], const Node *curPtr, int start, int end) 
{
	if (start > end)
	{
		curPtr = NULL;
	}
	else
	{
		int mid = (start + end) / 2;

		NodeData *temp;
		temp = tempArray[mid];
		tempArray[mid] = NULL;

		insert(temp);

		arrayToBSTreeHelper(tempArray, curPtr, start, mid - 1);
		arrayToBSTreeHelper(tempArray, curPtr, mid + 1, end);
	}
}

/****************************************************************************/
/*	isEmpty(): Checks to see if root is null. if it is, returns true, it is */
/*	empty 																	*/
/*	CALLED BY: makeEmpty() 													*/
/****************************************************************************/
bool BinTree::isEmpty() const
{
	return (root == NULL);
}

/****************************************************************************/
/*	makeEmpty(): checks to see if tree is empty, if it is, calls helper 	*/
/*	function 																*/
/*	CALLED BY: arrayToBSTree(), bstreeToArray(), operator=()				*/
/****************************************************************************/
void BinTree::makeEmpty()
{
	makeEmptyHelper(root); //destroy entire BST
}

/****************************************************************************/
/*	makeEmptyHelper(): reursively goes goes thru the tree and deletes all 	*/
/*	nodes starting with the leaf nodes										*/
/*	CALLED BY: ~BinTree, makeEmpty()										*/
/****************************************************************************/
void BinTree::makeEmptyHelper(Node* &curPtr)
{
  if(curPtr != NULL)
  {
		makeEmptyHelper(curPtr->left);
		makeEmptyHelper(curPtr->right);
		delete curPtr->data;
		curPtr->data = NULL;
		delete curPtr;
		curPtr = NULL;
  }
}

/****************************************************************************/
/*	printInOrder(node, output): Called by the overloaded operator<<, ostream*/
/*	operator output takes the output value from nodedata, prints when after */
/*	printInOrder terminates. printInOrder recusively goes thru tree in left-*/
/*	root-right order. Known as In Order 									*/
/*	CALLED BY: operator<<(oStream, BinTree)									*/
/****************************************************************************/
void BinTree::printInOrder(Node *curPtr, ostream &output)
{
	if (curPtr == NULL)
	{
		return;
	}
	printInOrder(curPtr->left, output);

	output << *(curPtr->data) << " ";

	printInOrder(curPtr->right, output);
}



/****************************************************************************/
/*	operator<<(&output, outTree): calls outtree->printInOrder, which fills  */
/*	output with all node->data outupt. Then displays content of output 		*/
/****************************************************************************/
std::ostream & operator<<(std::ostream &output, BinTree &outTree)
{
	outTree.printInOrder(outTree.root, output);

	output << endl;

	return output;
}


/****************************************************************************/
/*	Following methods were given to us, pre-commented. So not adding my own */
/*	comments																*/
/****************************************************************************/
//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const {
	if (current != NULL) {
		level++;
		sideways(current->right, level);

		// indent for readability, 4 spaces per depth level 
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << *current->data << endl;        // display information of object
		sideways(current->left, level);
	}
}

