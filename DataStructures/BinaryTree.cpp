#include "BinaryTree.h"
#include <iostream>



//Constructor for BinaryTree, initiates treeRoot with nullptr
BinaryTree::BinaryTree() {
	this->treeRoot = nullptr;
}

//Destructor, initiates recursive memory cleanup 
BinaryTree::~BinaryTree() {
	destroyTree();
}

//Recursion through every leaf to manually delete it. Neccessary due to memory leaks if not done properly
void BinaryTree::destroyTree(TreeNode* leaf) {
	if (leaf != nullptr) {
		destroyTree(leaf->getLeftChild());
		destroyTree(leaf->getRightChild());
		delete(leaf);
		leaf = nullptr;
	}

}

//Begin the recursive destruction at the root. Will then do it for all leafs on the left, then on the right
void BinaryTree::destroyTree(void) {
	destroyTree(treeRoot);
}



void BinaryTree::insertValue(int newValue, TreeNode* leaf) {
	//See if the value to be added is smaller than the one in the leaf we're looking at
	if (newValue < leaf->getValue()) {
		//If it is smaller, we check if we already have a leaf left of that
		if (leaf->getLeftChild() != nullptr) {
			//If it is, start a recursion with the leftChild of our current Leaf
			insertValue(newValue, leaf->getLeftChild());
		}
		//If it is not however, we create a new Node and store the passed value inside

		else {
			leaf->setLeftChild(new TreeNode());
			leaf->getLeftChild()->setValue(newValue);
			/*This looks a little confusing, but is pretty simple:
			The value must be stored left of the current Leaf, but the lChild of our current leaf does not exist
			So we add a new Node as a leftChild of our CURRENT Node. A new node does not have children
			So the left and right Child of the leftChild of the CURRENT Node are nullpointers.*/

			//leaf->leftChild->leftChild = nullptr;
			//leaf->leftChild->rightChild = nullptr;
		}

	}

	/*Same thing as above, but this time, the new Value is greater than the one in the leaf we're looking at
	which means we have to add it into the Node to the right leaf of the current one
	If it is greater than the current one, and our rightChild is not equal to the nullpointer, we attempt to insert it there*/

	else if (newValue > leaf->getValue()) {
		if (leaf->getRightChild() != nullptr) {
			insertValue(newValue, leaf->getRightChild());
		}

		//If our rightChild is null however, we can just put a new Leaf in here and insert the value in it:
		else {
			leaf->setRightChild(new TreeNode());
			leaf->getRightChild()->setValue(newValue);

			//Again, a little confusing thing: Our rightChild does not exist, so we created it
			//We already assigned the value into it, so we need to make sure it does not have children, as it is a new leaf


			//leaf->rightChild->leftChild = nullptr;
			//leaf->rightChild->rightChild = nullptr;

		}
	}
	//Insertion completed.
}

/*We add a scope to the BinaryTree class in front of the return type because the structure Node belongs to the BinaryTree class
  Now let's find our Node with the correct Value!
*/
TreeNode* BinaryTree::findNodeByValue(int searchValue, TreeNode* leaf) {
	//Go through every leaf untill you either find the value or a nullptr
	//If we reach the end of the tree and do not find it, we return a nullptr

	//check the current one and then its children
	if (leaf != nullptr) {
		//If the value is at the current node, return it
		if (searchValue == leaf->getValue()) {
			return leaf;
		}
		//If the searchValue is smaller than the current one, try finding it at the leftChild
		if (searchValue < leaf->getValue()) {
			return findNodeByValue(searchValue, leaf->getLeftChild());
		}

		//And if it is bigger, at the rightChild
		if (searchValue > leaf->getValue()) {

			return findNodeByValue(searchValue, leaf->getRightChild());
		}

		else return nullptr;
		//search finished
	}
}


/*public version of insertValue
initiates recursive insertion of a value*/
void BinaryTree::insertValue(int newValue) {

	//If the treeRoot is null, create it and add the value to it
	if (treeRoot == nullptr) {
		treeRoot = new TreeNode();
		treeRoot->setValue(newValue);
		//	treeRoot->leftChild = nullptr;
		//	treeRoot->rightChild = nullptr;
	}

	//if it is not, start recursive insertion
	else {
		insertValue(newValue, treeRoot);
	}
}


//public version of findNodeByValue, starts recursive search at the rootNode
TreeNode* BinaryTree::findNodeByValue(int searchValue) {
	return findNodeByValue(searchValue, treeRoot);
}

//Find the highest value in the tree
TreeNode* BinaryTree::getMaxNode(TreeNode* root) {

	if (root == nullptr) {
		return nullptr;
	}

	else if (root->getRightChild() == nullptr) {
		return root;
	}

	else {
		return getMaxNode(root->getRightChild());
	}
}



//Find the lowest value in the tree
TreeNode* BinaryTree::getMinNode(TreeNode* root) {

	if (root == nullptr) {
		return nullptr;
	}

	else if (root->getLeftChild() == nullptr) {
		return root;
	}

	else {
		return getMinNode(root->getLeftChild());
	}
}



//The same for the actual values

int BinaryTree::getLowestValue(TreeNode* treeRoot) {
	return getMinNode(treeRoot)->getValue();
}

int BinaryTree::getHighestValue(TreeNode* treeRoot) {
	return getMaxNode(treeRoot)->getValue();
}



//Algorithm for removal of Nodes

bool BinaryTree::removeNode(int removeValue) {
	//if the root is null, we cant do anything here
	if (treeRoot == nullptr) {
		return false;
	}

	//If it exists, we check if we want to delete the root
	else {
		if (treeRoot->getValue() == removeValue) {
			//If it is, we create a temporary rootNode
			TreeNode* tempRoot = new TreeNode();
			//then add the actual treeRoot as a leftChild
			tempRoot->setValue(0);
			tempRoot->setLeftChild(treeRoot);


			//Up next we call TreeNode's remove method. See TreeNode.h

			TreeNode* deletedNode = treeRoot->removeNode(removeValue, tempRoot);
			treeRoot = tempRoot->getLeftChild();
			//ultimately, the treeRoot will be the LeftChild of our tempRoot
			if (deletedNode != nullptr) {
				//if the one we want to remove exists, we delete it
				delete deletedNode;
				deletedNode = nullptr;
				return true;
			}
			else //If it doesnt, we have failed
				return false;
		}

		//If the value we want to remove is not the treeRoot
		else {
			//The node to remove is gotten by TreeNode's removeNode method (see TreeNode.h)
			TreeNode* deletedNode = treeRoot->removeNode(removeValue, nullptr);


			if (deletedNode != nullptr) {
				//Free memory occupied by the node and set it to nullptr, to be safe.
				delete deletedNode;
				deletedNode = nullptr;
				return true;
			}
			//if it does not exist, we have failed
			else
				return false;
		}
	}
}

//Traversal algorithms
void BinaryTree::inOrderTraversal(TreeNode* start) {
	if (start == nullptr) return;
	else {
		inOrderTraversal(start->getLeftChild());
		printNode(start);
		inOrderTraversal(start->getRightChild());
	}

}

void BinaryTree::preOrderTraversal(TreeNode* start) {
	if (start == nullptr) return;
	else {
		printNode(start);
		preOrderTraversal(start->getLeftChild());
		preOrderTraversal(start->getRightChild());
	}
}

void BinaryTree::postOrderTraversal(TreeNode* start) {
	if (start == nullptr) return;
	else {
		postOrderTraversal(start->getLeftChild());
		postOrderTraversal(start->getRightChild());
		printNode(start);
	}
}

void BinaryTree::printNode(TreeNode* printMe) {
	if (printMe == nullptr) return;
	else std::cout << "Value of Node: " << printMe->getValue() << std::endl;
}


