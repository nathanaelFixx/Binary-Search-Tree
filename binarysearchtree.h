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

#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "binarynode.h"
#include <iostream>

using namespace std;

template<class ItemType>
class BinarySearchTree {
public:
	// constructor, empty tree
	BinarySearchTree();

	// constructor, tree with root
	explicit BinarySearchTree(const ItemType& rootItem);

	// copy constructor
	BinarySearchTree(const BinarySearchTree<ItemType>& source);

	// destructor
	virtual ~BinarySearchTree();

	// true if no nodes
	bool isEmpty() const;

	// 0 if empty, 1 if only root, otherwise
	// max height of subtrees + 1
	int getHeight();

	// number of nodes and data in tree
	int getNumberOfNodes() const;

	// add a new item
	// return true if succesasfull
	// false if item already in tree or some other reason to fail
	bool add(const ItemType& item);

	// true if item is in tree
	bool contains(const ItemType& item) const;

	// dispaly a sideways ascii representation of tree
	void displaySideways() const;

	// inorder traversal: left-root-right
	// takes a function that takes a single parameter of ItemType
	// the function can modify the data in tree, but the
	// tree structure is not changed
	void inorderTraverse(void visit(ItemType&));

	// create dynamic array, copy all the items to the array
	// and then read the array to re-create this tree
	void rebalance();

	// delete all nodes in tree and set root to nullptr
	void clear();

	// given an array of length n
	// create this tree to have all items in that array
	// with the minimum height
	BinaryNode<ItemType> * readTree(ItemType arr[], int n);

	// trees are equal if they have the same structure
	// AND the same item values at all the nodes
	bool operator==(BinarySearchTree<ItemType> &other);

	// not == to each other
	bool operator!=(const BinarySearchTree<ItemType> &other);

private:
	// root of the tree
	BinaryNode<ItemType>* rootPtr{ nullptr };

	// find the node with given val, helper function for contains
	bool findNode(BinaryNode<ItemType>* subTreePtr, const ItemType& 
		target, bool & found) const;

	// helper function for displaySideways to work recursively
	void sideways(BinaryNode<ItemType>* current, int level) const;

	// copies data from one tree to another, helper function for
	// copy constructor
	BinaryNode<ItemType> * makeCopy(const BinaryNode<ItemType> * source)
		const;

	// returns the length of the longest branch + 1, helper function
	// for getHeight
	int height(BinaryNode<ItemType> * root);

	// iterates through tree and deletes all the nodes, helper function
	// for clear and destructor
	void deleteAll(BinaryNode<ItemType> * root);

	// puts each item in a tree into an array
	// helper function for rebalance
	void sendToArray(BinaryNode<ItemType> * root, ItemType * bArray,
		 int & index);

	// takes each element from an ordered array and puts it into a
	// balanced tree, helper function for rebalance
	BinaryNode<ItemType> * balance(ItemType * bArray, int beg, int end);

	// iterates through the two trees that are passed into it and compares
	// the items in each node, helper function for "==" and "!="
	bool checkEquals(BinaryNode<ItemType> * root, BinaryNode<ItemType>
		 * other, bool &isEqual);

	// takes items from an ordered array and puts them in a tree, helper
	// function for read tree  
	BinaryNode<ItemType> * balanceArray(ItemType arr[], int beg, int end);

	// calls a given function on each node of a tree, helper function for
	// inorderTraverse
	void callFunction(BinaryNode<ItemType> * root, void visit(ItemType&));

	// for getNumberOfNodes
	int nodeCount = 0;

	// for rebalance
	ItemType * bArray;
};

#include "binarysearchtree.cpp"

#endif // BINARYSEARCHTREE_H

