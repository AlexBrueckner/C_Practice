
#include "BinaryTree.h"
#include <iostream>
#include <cstdlib>


using namespace std;

void main(void) {


	BinaryTree* tree = new BinaryTree();

	tree->insertValue(5);
	tree->insertValue(2);
	tree->insertValue(12);
	tree->insertValue(-4);
	tree->insertValue(3);

	tree->insertValue(9);
	tree->insertValue(21);
	tree->insertValue(19);
	tree->insertValue(25);
	
	cout << "---------In Order---------" << endl;
	tree->inOrderTraversal(tree->getRoot());
	cout << "---------Pre-Order---------" << endl;
	tree->preOrderTraversal(tree->getRoot());
	cout << "---------Post.Order---------" << endl;
	tree->postOrderTraversal(tree->getRoot());
	tree->removeNode(-4);

	cout << "Destroying tree..." << endl;
	tree->destroyTree();
	system("pause");
}