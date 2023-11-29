#pragma once
#include <memory>
#include <stack>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

template<typename T>
class RedBlackTree {
public:
	struct Node {
		Node* parent;
		Node* left;
		Node* right;
		bool isBlack;
		char childType;
		unsigned int key;
		T data;

		Node(Node* p, Node* l, Node* r, bool iB, char chT, unsigned int k, const T& dt) : parent(p), left(l), right(r), isBlack(iB), childType(chT), key(k), data(dt) {  };
		~Node() {
			parent = nullptr;
			left = nullptr;
			right = nullptr;
		}
	};


private:
	Node* root;
	unsigned int size;


public:
	RedBlackTree()noexcept : root(nullptr), size(0) {  };
	void Add(const T& dt) {
		auto isUncleRed = [](Node* nd) {
			if (nd->childType == 'L') {
				if (nd->parent->right == nullptr || nd->parent->right->isBlack)
					return false;
				return true;
			}
			else
			{
				if (nd->parent->left == nullptr || nd->parent->left->isBlack)
					return false;
				return true;
			}
		};


		if (root == nullptr) {
			root = new Node(nullptr, nullptr, nullptr, true, 'R', size, dt);
			++size;
		}
		else
		{
			Node* p = root;
			Node* tempChild = nullptr;
			Node* tempParent = nullptr;
			Node* tempGrandparent = nullptr;
			bool added = false;
			bool duplicate = false;

			while (!added) {
				if (dt < p->data) {
					if (p->left != nullptr) {
						p = p->left;
					}
					else {
						++size;
						p->left = new Node(p, nullptr, nullptr, false, 'L', size, dt);
						tempChild = p->left;
						added = true;
					}
				}
				else if (dt > p->data) {
					if (p->right != nullptr) {
						p = p->right;
					}
					else {
						++size;
						p->right = new Node(p, nullptr, nullptr, false, 'P', size, dt);
						tempChild = p->right;
						added = true;
					}
				}
				else {
					added = true;
					duplicate = true;
				}
					
			}

			if (!duplicate) {
				if (size > 2) {
					tempParent = tempChild->parent;
					if (!tempParent->isBlack) {
						while (tempParent != root) {


							if (tempParent->left != nullptr && !tempParent->left->isBlack)
								tempChild = tempParent->left;
							else if (!tempParent->right->isBlack)
								tempChild = tempParent->right;
							else
								break;

							if (isUncleRed(tempParent)) {
								tempParent->isBlack = true;
								tempParent->parent->isBlack = false;
								if (tempParent->childType == 'L')
									tempParent->parent->right->isBlack = true;
								else
									tempParent->parent->left->isBlack = true;							
							}
							else
							{
								if (tempParent->childType == 'L') {
									if (tempChild->childType == 'L')//LL
									{
										tempGrandparent = tempParent->parent;
										RightRotation(tempParent, tempGrandparent);

										bool isBlackTemp = tempGrandparent->isBlack;
										tempGrandparent->isBlack = tempParent->isBlack;
										tempParent->isBlack = isBlackTemp;
									}
									else //LR
									{
										tempGrandparent = tempParent->parent;
										LeftRotation(tempChild, tempParent);
										RightRotation(tempChild, tempGrandparent);

										bool isBlackTemp = tempGrandparent->isBlack;
										tempGrandparent->isBlack = tempChild->isBlack;
										tempChild->isBlack = isBlackTemp;
									}
								}
								else
								{
									if (tempChild->childType == 'L') //RL
									{
										tempGrandparent = tempParent->parent;
										RightRotation(tempChild, tempParent);										
										LeftRotation(tempChild, tempGrandparent);

										bool isBlackTemp = tempGrandparent->isBlack;
										tempGrandparent->isBlack = tempChild->isBlack;
										tempChild->isBlack = isBlackTemp;

									}
									else //RR
									{
										tempGrandparent = tempParent->parent;
										LeftRotation(tempParent, tempGrandparent);

										bool isBlackTemp = tempGrandparent->isBlack;
										tempGrandparent->isBlack = tempParent->isBlack;
										tempParent->isBlack = isBlackTemp;
									}
								}

							}					
							if (tempParent->parent == nullptr || tempParent->parent->parent == nullptr || tempParent->parent->parent->isBlack)
								break;

							tempParent = tempParent->parent->parent;
						}
					}
					root->isBlack = true;
				}

			}
			tempChild = nullptr;
			tempParent = nullptr;
			tempGrandparent = nullptr;
			p = nullptr;
		}
	}

	Node* Search(const T& data) {
		auto Comp = [&](const T& ob1, const T& ob2) {return ob1 - ob2; };
		bool found = false;
		if (root == nullptr)
			return nullptr;

		Node* temp = root;

		while ((temp != nullptr) && !found) {
			if (Comp(data, temp->data) < 0)
				temp = temp->left;


			else if (Comp(data, temp->data) > 0)
				temp = temp->right;

			else
				found = true;
		}
		return temp;
	}

	void Pre_Order() {
		Node* temp = nullptr;
		std::stack<Node*> nodes;


		nodes.push(root);
		cout << "(key, value)\n\n";
		while (!nodes.empty()) {
			temp = nodes.top();
			cout << "(" << temp->key << ", " << temp->data << ")" << endl;
			nodes.pop();

			if (temp->right != nullptr)
				nodes.push(temp->right);
			if (temp->left != nullptr)
				nodes.push(temp->left);
		}

		temp = nullptr;
	}
	void In_Order(const Node* rt) {
		if (rt != nullptr) {
			In_Order(rt->left);
			cout << "(" << rt->key << ", " << rt->data << ")" << endl;
			In_Order(rt->right);
		}
		return;
	}

	void Clear() {
		std::stack <Node*> nodes;
		Node* temp = nullptr;
		nodes.push(root);


		while (!nodes.empty()) {
			temp = nodes.top();

			if (temp->left != nullptr)
				nodes.push(temp->left);

			else if (temp->right != nullptr)
				nodes.push(temp->right);

			else {
				nodes.pop();

				if (temp->childType == 'L')
					temp->parent->left = nullptr;

				else if (temp->childType == 'P')
					temp->parent->right = nullptr;

				delete temp;
			}


		}

		size = 0;
		temp = nullptr;
		root = nullptr;
	}

	string toString() {
		if (size <= 0)
			return "size: 0";

		std::ostringstream str;
		std::stack<Node*> nodes;
		Node* temp = nullptr;
		auto ifExists = [&](Node* n) {
			string msg = "NULL";

			if (n != nullptr)
				return std::to_string(n->key);

			return msg;
		};
		auto printColor = [&](Node* n) {

			if (n->isBlack)
				return "\033[34mblack\033[0m";
			else
				return "\x1B[31mred\033[0m";
		};

		nodes.push(root);

		if (size < 21) {
			str << "Binary search tree \n size: " << size << "\n{\n\n";
			while (!nodes.empty()) {
				temp = nodes.top();
				str << "   ( " << temp->key << ": [ " << printColor(temp) << ", p: " << ifExists(temp->parent) << ", l : " << ifExists(temp->left) << ", r : " << ifExists(temp->right) << "] data: " << temp->data <<", Typ dziecka: "<< temp->childType << " )\n";
				nodes.pop();

				if (temp->right != nullptr)
					nodes.push(temp->right);

				if (temp->left != nullptr)
					nodes.push(temp->left);

			}
		}
		else {
			int lim = 20;
			str << "Binary search tree (first 20 nodes) \n size: " << size << "\n{\n\n";

			while (!nodes.empty() && lim > 0) {
				temp = nodes.top();
				str << "   ( " << temp->key << ": [ " << printColor(temp) << " p: " << ifExists(temp->parent) << ", l : " << ifExists(temp->left) << ", r : " << ifExists(temp->right) << "] data: " << temp->data << " )\n";
				nodes.pop();

				if (temp->right != nullptr)
					nodes.push(temp->right);

				if (temp->left != nullptr)
					nodes.push(temp->left);

				--lim;
			}
		}



		temp = nullptr;
		str << "\n }\n";
		return str.str();
	}	

	void LeftRotation(Node* childNode, Node* parentNode) {
		char help = parentNode->childType;
		if (parentNode->parent != nullptr) {
			if(parentNode->childType == 'L')
				parentNode->parent->left = childNode;
			else
				parentNode->parent->right = childNode;
		}
			

		if (childNode->left != nullptr) {
			parentNode->right = childNode->left;
			childNode->left->parent = parentNode;
			childNode->left->childType = 'P';
		}
		else
			parentNode->right = nullptr;

		childNode->left = parentNode;
		childNode->parent = parentNode->parent;

	
		parentNode->parent = childNode;
		parentNode->childType = 'L';

		childNode->childType = help;

		if (childNode->childType == 'R')
			root = childNode;		
	
	}
	void RightRotation(Node* childNode, Node* parentNode) {
		char help = parentNode->childType;
		if (parentNode->parent != nullptr) {
			if (parentNode->childType == 'L')
				parentNode->parent->left = childNode;
			else
				parentNode->parent->right = childNode;
		}

		if (childNode->right != nullptr) {
			parentNode->left = childNode->right;
			childNode->right->parent = parentNode;
			childNode->right->childType = 'L';
		}
		else
			parentNode->left = nullptr;

		childNode->right = parentNode;
		childNode->parent = parentNode->parent;
		
		parentNode->parent = childNode;
		parentNode->childType = 'P';

		childNode->childType = help;

		if (childNode->childType == 'R')
			root = childNode;
		
	}

	Node* getRoot() {
		return root;
	}
	int getHeight(Node* root) {
		if (root == nullptr)
			return 0;

		int lH = getHeight(root->left);
		int lR = getHeight(root->right);

		return std::max(lH, lR) + 1;

	}
	int getSize() {
		return size;
	}

};