#ifndef _BINARYTREE_H_
#define _BINARYTREE_H_
#include "TreeNode.h"

//class BinaryTree - implementation of a sorted BinaryTree with Integers

class BinaryTree {

protected:
	/*Deprecated struct for Node
	struct Node {
		int value;
		Node *leftChild;
		Node *rightChild;
	};*/



public:


	//Constructor Prototypes
	BinaryTree();
	~BinaryTree();

	//public prototypes for tree operation functions
	void insertValue(int newValue);
	TreeNode* findNodeByValue(int searchValue);
	void destroyTree();
	//public prototypes for getters
	TreeNode* getRoot() { return this->treeRoot; }
	TreeNode* getMinNode(TreeNode* root);
	TreeNode* getMaxNode(TreeNode* root);
	int getLowestValue(TreeNode* treeRoot);
	int getHighestValue(TreeNode* treeRoot);
	bool removeNode(int removeValue);

	//And the traversal functions to print the Tree
	void preOrderTraversal(TreeNode* start);
	void inOrderTraversal(TreeNode* start);
	void postOrderTraversal(TreeNode* start);


	void printNode(TreeNode* printMe);

private:
	//private prototypes for tree operations
	void destroyTree(TreeNode* leaf);
	void insertValue(int newValue, TreeNode* leaf);
	
	TreeNode* findNodeByValue(int searchValue, TreeNode* leaf);
	//private delclaration of the tree root
	TreeNode* treeRoot;

};


#endif