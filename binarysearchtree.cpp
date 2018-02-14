//_____________________________________________________________________________
// By: Nathanael Fixx
//
// BinarySearchTree class
// Creates a BST to store values
// Uses BinaryNode which holds the data
// Uses templates to store any type of data
// binarysearchtreee.cpp file is included at the bottom of the .h file
// binarysearchtreee.cpp is part of the template, cannot be compiled separately
// functions included in this class allow for creation of a binary search tree
// with or without data, copying of BinarySearchTrees, checking if trees are
// empty, getting height of trees, getting the number of nodes in trees
// adding nodes to the tree, checking if the tree contains a specific value,
// displaying the tree, traversing the tree in order, rebalancing the tree,
// deleting the tree, and creating a tree from an array. The operators "=="
// and "!=" are also overloaded.
//_____________________________________________________________________________

#include <iostream>
#include "binarysearchtree.h"
#include <algorithm>

//_____________________________________________________________________________
// Default constructor
//
// rootPtr is set to NULL
//_____________________________________________________________________________
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree() {
	this->rootPtr = NULL;
}

//_____________________________________________________________________________
// Constructor
//
// Creates a root node and sets its item equal to the item that was passed in.
//_____________________________________________________________________________
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const ItemType& rootItem) {

	BinaryNode<ItemType> * temp = new BinaryNode<ItemType>(rootItem);
	rootPtr = temp;
	nodeCount++;
}

//_____________________________________________________________________________
// Copy constructor
//
// Calls the helper function makeCopy
//_____________________________________________________________________________
template<class ItemType>
BinarySearchTree<ItemType>::BinarySearchTree(const BinarySearchTree<ItemType>&
 source) {
	
	// private variable for keeping track of the # of nodes 
	nodeCount = source.nodeCount;
	rootPtr = makeCopy(source.rootPtr);

}

//_____________________________________________________________________________
// isEmpty
//
// Checks if rootPtr is equal to NULL, if it is, returns true. If not, returns
// false.
//_____________________________________________________________________________
template<class ItemType>
bool BinarySearchTree<ItemType>::isEmpty() const {
	if (rootPtr == NULL)
		return true;
	return false;
}

//_____________________________________________________________________________
// getHeight
//
// If the tree is empty, returns 0. If tree has just a root, returns 1. Else
// calls the helper function height
//_____________________________________________________________________________
template<class ItemType>
int BinarySearchTree<ItemType>::getHeight() {
	
	// checks if empty
	if (rootPtr == NULL) {
		return 0;
	}
	
	// if just one node
	if (rootPtr->getLeftChildPtr() == NULL && 
		rootPtr->getRightChildPtr() == NULL) {
		
		return 1;
	}

	// any other case
	return height(rootPtr);
}

//_____________________________________________________________________________
// getNumberOfNodes
//
// returns the nodeCount variable
//_____________________________________________________________________________
template<class ItemType>
int BinarySearchTree<ItemType>::getNumberOfNodes() const {

	return nodeCount;
}

//_____________________________________________________________________________
// add
//
// First, checks if the item is already in the tree. If it is, returns false.
// Then the node is added to the right or left side depending on whether it
// is bigger or smaller than the root.
//_____________________________________________________________________________
template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType& item) {
	
	// checks if the item is already in the tree
	if (this->contains(item)) {
		return false;
	}
	
	// if tree is empty
	if (rootPtr == NULL) {
		rootPtr = new BinaryNode<ItemType>;
		rootPtr->setItem(item);
		nodeCount++;
		return true;
	}

	BinaryNode<ItemType> * add = new BinaryNode<ItemType>(item);
	
	    // if thee has no leaves
	if (rootPtr->getLeftChildPtr() == NULL &&
		 rootPtr->getRightChildPtr() == NULL) {

		// if item needs to go on the left side
		if (item < rootPtr->getItem()) {
			rootPtr->setLeftChildPtr(add);
			nodeCount++;
			return true;
		}

		// if item needs to go on the right side
		if (item > rootPtr->getItem()) {
			rootPtr->setRightChildPtr(add);
			nodeCount++;
			return true;
		}
	}

	// if item needs to go in the first left leaf
	if (rootPtr->getLeftChildPtr() == NULL) {
		if (item < rootPtr->getItem()) {
			rootPtr->setLeftChildPtr(add);
			nodeCount++;
			return true;
		}
	} 

	// if item needs to go in the first right leaf
	if (rootPtr->getRightChildPtr() == NULL) {
		if (item > rootPtr->getItem()) {
			rootPtr->setRightChildPtr(add);
			nodeCount++;
			return true;
		}
	}

	// for any other situation
	BinaryNode<ItemType> * current;
	
	// decides which branch of the tree to go down 
	if (item < rootPtr->getItem()) {
		current = rootPtr->getLeftChildPtr();
	}

	else {
		current = rootPtr->getRightChildPtr();
	}

	BinaryNode<ItemType> * prev = rootPtr;

	// moves down the tree trying to find the right spot
	while (current != NULL) {

		if (item < current->getItem()) {
			prev = current;
			current = current->getLeftChildPtr();
		}
		else if (item > current->getItem()) {
			prev = current;
			current = current->getRightChildPtr();
		}
	}

	// places the new node in the correct spot
	if (item < prev->getItem()) {
		prev->setLeftChildPtr(add);
		nodeCount++;
		delete current;
		return true;
	}
	if (item > prev->getItem()) {
		prev->setRightChildPtr(add);
		nodeCount++;
		delete current;
		return true;
	}
	else
	delete current;
	return false;

}

//_____________________________________________________________________________
// Clear
//
// Checks if the rootPtr is not equal to NULL and then calls the helper
// function deleteAll. Also resets nodecount
//_____________________________________________________________________________
template<class ItemType>
void BinarySearchTree<ItemType>::clear() {

	// if tree is empty
	if (rootPtr == NULL)
		return;

	//helper function
	deleteAll(rootPtr);
	nodeCount = 0;
	rootPtr = NULL;
}

//_____________________________________________________________________________
// Contains
//
// Checks if the item in rootPtr is equal to the item that was passes in. If
// it is not, it calls the helper function findNode. Returns true if findNode
// returns true, false if findNode returns false.
//_____________________________________________________________________________
template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType& item) const {

	bool found = false;
	
	// tree can't contain the node if it doesn't have any nodes
	if (nodeCount == 0) {
		return false;
	}

	// checks if root contains the item
	if (rootPtr->getItem() == item) {
		return true;
	}

	// calls helper function
	findNode(rootPtr, item, found);

	if (found == true)
		return true;
	else
		return false;
}

//_____________________________________________________________________________
// findNode
//
// Helper function for contains. Recursively checks each of the nodes to see if
// their items match the item that was passed in. If if does the variable found
// is changed to true.
//_____________________________________________________________________________ 
template<class ItemType>
bool BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* subTreePtr,
 	const ItemType& target, bool & found) const {

	if (subTreePtr == NULL) {
		return false;
	}

	//if the desired item is found, the found variable is set to true
	if (subTreePtr->getItem() == target) {
		found = true;
		return true;
	}

	findNode(subTreePtr->getLeftChildPtr(), target, found);
	findNode(subTreePtr->getRightChildPtr(), target, found);
	return true;
}

//_____________________________________________________________________________
// Inorder Traverse
//
// Checks to see if the tree is not empty, and then calls the function
// callFunction
//_____________________________________________________________________________
template<class ItemType>
void BinarySearchTree<ItemType>::inorderTraverse(void visit(ItemType&))
{
	// empty tree
	if (rootPtr == NULL)
		return;

	// helper function
	callFunction(rootPtr, visit);
}

//_____________________________________________________________________________
// Rebalance
// 
// Creates a dynamic array of the size nodeCount and passes that to the
// sendToArray function which sorts the array. The sorted array is then sent to
// the balance helper function
//_____________________________________________________________________________
template<class ItemType>
void BinarySearchTree<ItemType>::rebalance() {
	int index = 0;
	
	// creates array with enough space for all of the nodes
	bArray = new ItemType[nodeCount];

	// helper function
	sendToArray(rootPtr, bArray, index);

	// variables for the balance function
	int beg = 0;
	int end = nodeCount - 1;

	// deletes the tree that rootPtr was pointing to 	
	deleteAll(rootPtr);
	rootPtr = NULL;
	
	// sets rootPtr equal to the tree that is returned from the balance
	// helper function
	rootPtr = balance(bArray, beg, end);
	delete[] bArray;
}

//_____________________________________________________________________________
// readTree
//
// This function should read in an array, and use that array to create a
// balanced tree. Sets the variables beg and end to the correct values and 
// then calls the balanceArray helper function.
//_____________________________________________________________________________
template<class ItemType>
BinaryNode<ItemType> * BinarySearchTree<ItemType>::readTree
	(ItemType arr[], int n) {

	int beg = 0;
	int end = n - 1;

	// sets rootPtr equal to the tree that is returned from the
	// balanceArray function
	
	deleteAll(rootPtr);
	rootPtr = NULL;	

	rootPtr = balanceArray(arr, beg, end);
	nodeCount = end + 1;
	
	return rootPtr;
}

//_____________________________________________________________________________
// Display Sideways
// 
// Used to display the tree. Calls the sideways helper function.
//_____________________________________________________________________________
template<class ItemType>
void BinarySearchTree<ItemType>::displaySideways() const {
	
	// helper function
	sideways(rootPtr, 0);
}

//_____________________________________________________________________________
// Sideways
//
// Recursively goes to each node of the tree and outputs it to the console
// window.
//_____________________________________________________________________________
template<class ItemType>
void BinarySearchTree<ItemType>::sideways(BinaryNode<ItemType>* current,
 int level) const {
	
	if (current != NULL) {
		level++;
		sideways(current->getRightChildPtr(), level);

		// indent for readability, 4 spaces per depth level
		for (int i = level; i >= 0; i--) {
			cout << "    ";
		}

		cout << current->getItem() << endl;        // display information of object
		sideways(current->getLeftChildPtr(), level);
	}
}

//_____________________________________________________________________________
// Operator ==
//
// This function checks if two trees are equal. It first checks if they are
// both NULL and then if they have the same count. It then calls the
// checkEquals helper function.
//_____________________________________________________________________________
template<class ItemType>
bool BinarySearchTree<ItemType>::operator==(BinarySearchTree<ItemType>
	 &other) {

	// checks if both trees are empty
	if (rootPtr == NULL && other.rootPtr == NULL)
		return true;

	// checks if nodeCounts are different
	if (other.nodeCount != nodeCount)
		return false;

	// checks if rootPtr values are different
	if (other.rootPtr->getItem() != rootPtr->getItem())
		return false;

	bool isEqual = true;
	BinaryNode<ItemType> * current;
	current = other.rootPtr;

	//helper function
	checkEquals(rootPtr, current, isEqual);

	if (isEqual == true)
		return true;
	else
		return false;
}

//_____________________________________________________________________________
// Operator !=
//
// This function checks if two trees are not. It first checks if they are
// both NULL and then if they have the same count. It then calls the
// checkEquals helper function.
//_____________________________________________________________________________
template<class ItemType>
bool BinarySearchTree<ItemType>::operator!=(const BinarySearchTree<ItemType>&
	 other) {

	// checks if trees are both empty	
	if (rootPtr == NULL && other.rootPtr == NULL)
		return false;

	// checks if nodeCounts are not equal	
	if (other.nodeCount != nodeCount)
		return true;

	// checks if the rootPtr values are not equal
	if (other.rootPtr->getItem() != rootPtr->getItem())
		return true;

	bool isEqual = true;
	BinaryNode<ItemType> * current;
	current = other.rootPtr;

	checkEquals(rootPtr, current, isEqual);

	if (isEqual == true)
		return false;
	else
		return true;
}

//_____________________________________________________________________________
// Make Copy
// 
// Helper function for copy constructor. Makes a new node and sets that node
// equal to a node that contains the same information as a node from the source
// tree. This is repeated recursively until all of the nodes have been copied.
//_____________________________________________________________________________
template<class ItemType>
BinaryNode<ItemType> * BinarySearchTree<ItemType>::makeCopy(const
	 BinaryNode<ItemType> * source) const
{


	BinaryNode<ItemType> * dest = NULL;

	if (source != NULL) {
		dest = new BinaryNode<ItemType>(source->getItem());
		dest->setLeftChildPtr(makeCopy(source->getLeftChildPtr()));
		dest->setRightChildPtr(makeCopy(source->getRightChildPtr()));
	}

	return dest;
}

//_____________________________________________________________________________
// Height
//
// Helper function for getHeight. Recursively steps through each node of the
// tree and returns the longest branch length plus one.
//_____________________________________________________________________________
template<class ItemType>
int BinarySearchTree<ItemType>::height(BinaryNode<ItemType>* root)
{
	int leftHeight;
	int rightHeight;

	if (root == NULL)
		return 0;

	leftHeight = height(root->getLeftChildPtr());
	rightHeight = height(root->getRightChildPtr());

	return max(leftHeight, rightHeight) + 1;
}

//_____________________________________________________________________________
// Delete All
//
// Helper function for destructor and clear. Recursively goes through the tree
// until it reaches the end of a branch. It then deletes the nodes.
//_____________________________________________________________________________
template<class ItemType>
void BinarySearchTree<ItemType>::deleteAll(BinaryNode<ItemType>* root)
{
	if (root == NULL) {
		return;
	}

	deleteAll(root->getLeftChildPtr());
	deleteAll(root->getRightChildPtr());

	delete root;
	root = NULL;
}

//_____________________________________________________________________________
// Send to Array
//
// Helper function for rebalance. Uses inorder traversal to put each item from
// the tree into a dynamic array.
//_____________________________________________________________________________
template<class ItemType>
void BinarySearchTree<ItemType>::sendToArray(BinaryNode<ItemType>* root,
	 ItemType * bArray, int & index)
{
	if (root == NULL)
		return;

	sendToArray(root->getLeftChildPtr(), bArray, index);

	bArray[index] = root->getItem();
	index++;

	sendToArray(root->getRightChildPtr(), bArray, index);

}

//_____________________________________________________________________________
// Balance
// 
// Creates a balanced tree from an array. Helper function for rebalance. 
// Recursively finds the midpoint of the array and sets that as the root of
// the root.
//_____________________________________________________________________________
template<class ItemType>
BinaryNode<ItemType> * BinarySearchTree<ItemType>::balance(ItemType * bArray,
	 int beg, int end)
{
	if (beg > end) {
		return NULL;
	}

	// calculating the mid value
	int mid = (beg + end) / 2;
	BinaryNode<ItemType> * root = new BinaryNode<ItemType>(bArray[mid]);

	root->setLeftChildPtr(balance(bArray, beg, mid - 1));
	root->setRightChildPtr(balance(bArray, mid + 1, end));

	return root;

}

//_____________________________________________________________________________
// Check Equals
//
// Helper function for == and != recursively visits each node of the the two
// trees. If it finds two nodes in the same position that have different values
// it sets isEqual to false.
//_____________________________________________________________________________
template<class ItemType>
bool BinarySearchTree<ItemType>::checkEquals(BinaryNode<ItemType>* root,
	 BinaryNode<ItemType>* other, bool &isEqual)
{
	// if both nodes are NULL, the nodes are equal
	if (root == NULL && other == NULL)
		return true;

	// if one of the nodes is NULL, but the other isn't, the nodes
	// are not equal 
	if (root == NULL || other == NULL) {
		isEqual = false;
		return false;
	}

	// if the items are not equal, the nodes are not equal
	if (root->getItem() != other->getItem())
		isEqual = false;

	checkEquals(root->getLeftChildPtr(), other->getLeftChildPtr(),
		 isEqual);
	checkEquals(root->getRightChildPtr(), other->getRightChildPtr(),
		 isEqual);
	return false;
}

//_____________________________________________________________________________
// Balance Array
//
// Helper function for read tree. Recursively finds the midpoint of an array
// and sets it equal to the root (or subroot) of a tree.
//_____________________________________________________________________________
template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::balanceArray(ItemType arr[],
	 int beg, int end)
{
	if (beg > end) {
		return NULL;
	}

	int mid = (beg + end) / 2;
	BinaryNode<ItemType> * root = new BinaryNode<ItemType>(arr[mid]);

	root->setLeftChildPtr(balance(arr, beg, mid - 1));
	root->setRightChildPtr(balance(arr, mid + 1, end));

	return root;
}

//_____________________________________________________________________________
// Call Function
//
// Helper function for inorderTraverse. Recursively visits each node and calls
// the passed-in function on each item.
//_____________________________________________________________________________
template<class ItemType>
void BinarySearchTree<ItemType>::callFunction(BinaryNode<ItemType>* root,
	 void visit(ItemType&))
{
	if (root != NULL) {
		
		callFunction(root->getLeftChildPtr(), visit);
		ItemType item = root->getItem();

		// function that was passed into this function
		visit(item);
		
		callFunction(root->getRightChildPtr(), visit);
	}
}


//_____________________________________________________________________________
// Destructor
// 
// checks if the tree is empty, or if the tree only has one node and then calls
// the deleteAll function.
//_____________________________________________________________________________
template<class ItemType>
BinarySearchTree<ItemType>::~BinarySearchTree() {

	// if tree is empty
	if (rootPtr == NULL)
		return;

	// if tree only has one node
	if (nodeCount == 1) {
		delete rootPtr;
		nodeCount = 0;
		rootPtr = NULL;
		return;
	}

	// any other case
	deleteAll(rootPtr);
	nodeCount = 0;
	rootPtr = NULL;

}