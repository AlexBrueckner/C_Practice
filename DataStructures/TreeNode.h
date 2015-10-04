#ifndef _TREENODE_H_
#define _TREENODE_H_


#include <iostream>

class TreeNode {

private:

	TreeNode* leftChild;
	TreeNode* rightChild;
	int value;



public:


	//Getters, Setters, a Constructor and a Destructor


	int getMinValue() {
		if (leftChild == nullptr) return this->value;
		else return leftChild->getMinValue();
	}
	TreeNode() { this->value = 0; this->leftChild = nullptr; this->rightChild = nullptr; }
	~TreeNode() { std::cout << "Destroyed node with value " << this->getValue() << " successfully!" << std::endl; }
	TreeNode* getLeftChild() { return this->leftChild; }
	TreeNode* getRightChild() { return this->rightChild; }
	int getValue() { return this->value; }
	void setValue(int value) { this->value = value; }
	void setRightChild(TreeNode* rightChild) { this->rightChild = rightChild; }
	void setLeftChild(TreeNode* leftChild) { this->leftChild = leftChild; }


	//removes a node with a given value and parent
	TreeNode* removeNode(int removeValue, TreeNode* parentNode) {

		//if the value we want to remove is smaller than this value, we check for a leftChild
		//and call the method again for the Child of this node
		if (removeValue < this->value) {
			if (leftChild != nullptr) {
				return leftChild->removeNode(removeValue, this);
			}
			//if it doesnt exist, we return null
			else return nullptr;
		}

		//if the value is greater than this value, we look at the rightChild of this node
		else if (removeValue > this->value) {
			//If it exists, attempt removeNode with this Node as a parent
			if (rightChild != nullptr) {
				return rightChild->removeNode(removeValue, this);
			}
			//if it doesnt exist, we return null
			else return nullptr;
		}


		//If the node has two children, it gets a little bit tricky:
		//We will want to replace the value of this node with the minimum value in the tree
		else {
			if (leftChild != nullptr && rightChild != nullptr) {
				this->value = rightChild->getMinValue();
				//then we attempt to remove the rightChild
				return rightChild->removeNode(this->value, this);
			}
			//however, if we are the leftChild of the node we want to remove, the leftChild of our parent node
			//will be the leftChild of this node if it exists, or the right Child if it does not exist
			else if (parentNode->getLeftChild() == this) {

				parentNode->setLeftChild((leftChild != nullptr) ? leftChild : rightChild);
				return this;
			}

			//If we are the rightChild of our parent, we'll check if we have a leftChild

			else if (parentNode->getRightChild() == this) {
				//If we have a valid leftChild, the rightChild of our Parent will be the leftChild of this Node
				//If it does not exist, the rightChild of our parentNode will be the rightChild of this Node
				parentNode->setRightChild((leftChild != nullptr) ? leftChild : rightChild);
				return this;
			}
		}
	} //done!



};
#endif