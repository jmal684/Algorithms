#include <memory>
#include <stack>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;
using std::string;

template<typename T>
class BinarySearchTree {
public:
	struct Node {
		Node* parent;
		Node* left;
		Node* right;
		char childType;
		unsigned int key;
		T data;

		Node(Node* p, Node* l, Node* r, char ch, unsigned int k, const T& dt) : parent(p), left(l), right(r), childType(ch), key(k), data(dt) {  };
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
	BinarySearchTree() noexcept : root(nullptr), size(0) {};
	~BinarySearchTree() {};

	void Add(const T& dt) {
		unsigned int steps = 0;
		if (root != nullptr) {
			Node* p = root;
			bool added = false;

			while (!added) {
				if (dt < p->data) {
					if (p->left != nullptr) {
						p = p->left;
						++steps;
					}
					else {
						++size;
						++steps;
						p->left = new Node(p, nullptr, nullptr, 'L', size, dt);


						added = true;
					}
				}
				else if (dt > p->data) {
					if (p->right != nullptr) {
						p = p->right;
						++steps;
					}
					else {
						++size;
						++steps;
						p->right = new Node(p, nullptr, nullptr, 'P', size, dt);

						added = true;
					}
				}
				else
					added = true;

			}
			if (size < 4) {
				p = nullptr;
			}
			

		}
		else {
			++size;

			root = new Node(nullptr, nullptr, nullptr, 'R', size, dt);
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
	void Delete(const T& data) {
		if (size <= 0)
			return;

		Node* temp = Search(data);
		if (temp == nullptr) {
			cout << "ERROR: Node can't be found" << endl;
			return;
		}

		auto findPrece = [](Node* begin) {
			Node* max = begin->left;
			while (max->right != nullptr) {
				max = max->right;
			}
			return max;
		};
		auto nodeDegree = [](Node* node) {
			if (node->left != nullptr && node->right != nullptr)
				return 2;
			else if (node->left == nullptr && node->right == nullptr)
				return 0;
			else
				return 1;
		};

		switch (nodeDegree(temp)) {
		case 0:
			if (temp->childType == 'L')
				temp->parent->left = nullptr;
			else if (temp->childType == 'P')
				temp->parent->right = nullptr;
			else
			{
				root = nullptr;

			}


			--size;
			delete temp;
			break;

		case 1:
			if (temp->left != nullptr)
			{
				if (temp->parent != nullptr) {
					if (temp->childType == 'L') {
						temp->left->parent = temp->parent;
						temp->parent->left = temp->left;
					}
					else {
						temp->parent->right = temp->left;
						temp->left->parent = temp->parent;
						
					}
						

				}
				else
				{
					temp->left->parent = nullptr;
					root = temp->left;
				}

				temp->left->childType = temp->childType;			
				

			}
			else {
				if (temp->parent != nullptr) {
					if (temp->childType == 'L') {
						temp->right->parent = temp->parent;
						temp->parent->left = temp->right;
						
					}
					else {
						temp->parent->right = temp->right;
						temp->right->parent = temp->parent;
						
					}


				}
				else {
					temp->right->parent = nullptr;
					root = temp->right;
				}
					

				temp->right->childType = temp->childType;
			}
	
			--size;
			delete temp;
			break;


		case 2:
			Node * predecessor = findPrece(temp);

			if (temp->left == predecessor) {
				temp->left = nullptr;
				predecessor->right = temp->right;
				temp->right->parent = predecessor;

				if (temp->parent != nullptr) {
					predecessor->parent = temp->parent;
					if (temp->childType == 'L')
						temp->parent->left = predecessor;
					else if (temp->childType == 'P')
						temp->parent->right = predecessor;

				}
				else
					predecessor->parent = nullptr;

				predecessor->childType = temp->childType;
				
			}
			else
			{
				if (predecessor->left != nullptr) {
					predecessor->parent->right = predecessor->left;
					predecessor->left->parent = predecessor->parent;
					predecessor->left->childType = predecessor->childType;

				}
				else
					predecessor->parent->right = nullptr;	

				predecessor->left = temp->left;
				temp->left->parent = predecessor;
				predecessor->right = temp->right;
				temp->right->parent = predecessor;
				

				if (temp->parent != nullptr) {
					predecessor->parent = temp->parent;
					if (temp->childType == 'L')
						temp->parent->left = predecessor;
					else if (temp->childType == 'P')
						temp->parent->right = predecessor;

				}
				else
					predecessor->parent = nullptr;

				predecessor->childType = temp->childType;
			}

			if (temp->childType == 'R'){
				root = predecessor;
			}
			


			--size;
			delete temp;
			predecessor = nullptr;
			break;
		}

		temp = nullptr;


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

	int getHeight(Node* root) {
		if (root == nullptr)
			return 0;

 		int lH = getHeight(root->left);
		int lR = getHeight(root->right);

		return std::max(lH, lR) + 1;

	}
	string toString() {
		if (size <= 0)
			return "size: 0\n height: 0";

		std::ostringstream str;
		std::stack<Node*> nodes;
		Node* temp = nullptr;
		auto ifExists = [&](Node* n) {
			std::string msg = "NULL";

			if (n != nullptr)
				return std::to_string(n->key);

			return msg;
		};

		nodes.push(root);

		if (size < 21) {
			str << "Binary search tree \n size: " << size << "\n height: " << getHeight(root) << "\n{\n\n";
			while (!nodes.empty()) {
				temp = nodes.top();
				str << "   ( " << temp->key << ": [p: " << ifExists(temp->parent) << ", l : " << ifExists(temp->left) << ", r : " << ifExists(temp->right) << "] data: " << temp->data << " childT: "<<temp->childType<<" )\n";
				nodes.pop();

				if (temp->right != nullptr)
					nodes.push(temp->right);

				if (temp->left != nullptr)
					nodes.push(temp->left);

			}
		}
		else {
			int lim = 20;
			str << "Binary search tree (first 20 nodes) \n size: " << size << "\n height: " << getHeight(root) << "\n{\n\n";

			while (!nodes.empty() && lim > 0) {
				temp = nodes.top();
				str << "   ( " << temp->key << ": [p: " << ifExists(temp->parent) << ", l : " << ifExists(temp->left) << ", r : " << ifExists(temp->right) << "] data: " << temp->data << ")\n";
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

	Node* getRoot() {
		return root;
	}
	int getSize() {
		return size;
	}

	T get_min_node_data() {
		Node* temp = root;

		while (temp->left != nullptr && temp != nullptr) {			
			temp = temp->left;
		}
		return temp->data;
	}



};
