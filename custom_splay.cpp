#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;
struct Node {
	int data; // holds the key
	Node *parent; // pointer to the parent
	Node *left; // pointer to left child
	Node *right; // pointer to right child
};

typedef Node *NodePtr;

// class SplayTree implements the operations in Splay tree
class SplayTree {
private:
	NodePtr root;

	void preOrderHelper(NodePtr node) {
		if (node != nullptr) {
			cout<<node->data<<" ";
			preOrderHelper(node->left);
			preOrderHelper(node->right);
		} 
	}

	void inOrderHelper(NodePtr node) {
		if (node != nullptr) {
			inOrderHelper(node->left);
			cout<<node->data<<" ";
			inOrderHelper(node->right);
		} 
	}

	void postOrderHelper(NodePtr node) {
		if (node != nullptr) {
			postOrderHelper(node->left);
			postOrderHelper(node->right);
			cout<<node->data<<" ";
		} 
	}

	NodePtr searchTreeHelper(NodePtr node, int key) {
		if (node == nullptr || key == node->data) {
			return node;
		}

		if (key < node->data) {
			return searchTreeHelper(node->left, key);
		} 
		return searchTreeHelper(node->right, key);
	}

	void deleteNodeHelper(NodePtr node, int key) {
		NodePtr x = nullptr;
		NodePtr t, s;
		while (node != nullptr){
			if (node->data == key) {
				x = node;
			}

			if (node->data <= key) {
				node = node->right;
			} else {
				node = node->left;
			}
		}

		if (x == nullptr) {
			cout<<"Couldn't find key in the tree"<<endl;
			return;
		}
		split(x, s, t); // split the tree
		if (s->left){ // remove x
			s->left->parent = nullptr;
		}
		root = join(s->left, t);
		delete(s);
		s = nullptr;
	}

	void printHelper(NodePtr root, string indent, bool last) {
		// print the tree structure on the screen
	   	if (root != nullptr) {
		   cout<<indent;
		   if (last) {
		      cout<<"└────";
		      indent += "     ";
		   } else {
		      cout<<"├────";
		      indent += "|    ";
		   }

		   cout<<root->data<<endl;

		   printHelper(root->left, indent, false);
		   printHelper(root->right, indent, true);
		}
	}

	// rotate left at node x
	void leftRotate(NodePtr x) {
		NodePtr y = x->right;
		x->right = y->left;
		if (y->left != nullptr) {
			y->left->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->left) {
			x->parent->left = y;
		} else {
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}

	// rotate right at node x
	void rightRotate(NodePtr x) {
		NodePtr y = x->left;
		x->left = y->right;
		if (y->right != nullptr) {
			y->right->parent = x;
		}
		y->parent = x->parent;
		if (x->parent == nullptr) {
			this->root = y;
		} else if (x == x->parent->right) {
			x->parent->right = y;
		} else {
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}

	// splaying
	void splay(NodePtr x) {
		while (x->parent) {
			if (!x->parent->parent) {
				if (x == x->parent->left) {
					// zig rotation
					rightRotate(x->parent);
				} else {
					// zag rotation
					leftRotate(x->parent);
				}
			} else if (x == x->parent->left && x->parent == x->parent->parent->left) {
				// zig-zig rotation
				rightRotate(x->parent->parent);
				rightRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->right) {
				// zag-zag rotation
				leftRotate(x->parent->parent);
				leftRotate(x->parent);
			} else if (x == x->parent->right && x->parent == x->parent->parent->left) {
				// zig-zag rotation
				leftRotate(x->parent);
				rightRotate(x->parent);
			} else {
				// zag-zig rotation
				rightRotate(x->parent);
				leftRotate(x->parent);
			}
		}
	}

	// joins two trees s and t
	NodePtr join(NodePtr s, NodePtr t){
		if (!s) {
			return t;
		}

		if (!t) {
			return s;
		}
		NodePtr x = maximum(s);
		splay(x);
		x->right = t;
		t->parent = x;
		return x;
	}

	// splits the tree into s and t
	void split(NodePtr &x, NodePtr &s, NodePtr &t) {
		splay(x);
		if (x->right) {
			t = x->right;
			t->parent = nullptr;
		} else {
			t = nullptr;
		}
		s = x;
		s->right = nullptr;
		x = nullptr;
	} 

public:
	SplayTree() {
		root = nullptr;
	}

	// Pre-Order traversal
	// Node->Left Subtree->Right Subtree
	void preorder() {
		preOrderHelper(this->root);
	}

	// In-Order traversal
	// Left Subtree -> Node -> Right Subtree
	void inorder() {
		inOrderHelper(this->root);
	}

	// Post-Order traversal
	// Left Subtree -> Right Subtree -> Node
	void postorder() {
		postOrderHelper(this->root);
	}

	// search the tree for the key k
	// and return the corresponding node
	NodePtr searchTree(int k) {
		NodePtr x = searchTreeHelper(this->root, k);
		if (x) {
			splay(x);
		}
		return x;
	}

	// find the node with the minimum key
	NodePtr minimum(NodePtr node) {
		while (node->left != nullptr) {
			node = node->left;
		}
		return node;
	}

	// find the node with the maximum key
	NodePtr maximum(NodePtr node) {
		while (node->right != nullptr) {
			node = node->right;
		}
		return node;
	}

	// find the successor of a given node
	NodePtr successor(NodePtr x) {
		// if the right subtree is not null,
		// the successor is the leftmost node in the
		// right subtree
		if (x->right != nullptr) {
			return minimum(x->right);
		}

		// else it is the lowest ancestor of x whose
		// left child is also an ancestor of x.
		NodePtr y = x->parent;
		while (y != nullptr && x == y->right) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	// find the predecessor of a given node
	NodePtr predecessor(NodePtr x) {
		// if the left subtree is not null,
		// the predecessor is the rightmost node in the 
		// left subtree
		if (x->left != nullptr) {
			return maximum(x->left);
		}

		NodePtr y = x->parent;
		while (y != nullptr && x == y->left) {
			x = y;
			y = y->parent;
		}

		return y;
	}

	// insert the key to the tree in its appropriate position
	void insert(int key) {
		// normal BST insert
		NodePtr node = new Node;
		node->parent = nullptr;
		node->left = nullptr;
		node->right = nullptr;
		node->data = key;
		NodePtr y = nullptr;
		NodePtr x = this->root;

		while (x != nullptr) {
			y = x;
			if (node->data < x->data) {
				x = x->left;
			} else {
				x = x->right;
			}
		}

		// y is parent of x
		node->parent = y;
		if (y == nullptr) {
			root = node;
		} else if (node->data < y->data) {
			y->left = node;
		} else {
			y->right = node;
		}

		// splay the node
		splay(node);
	}

	NodePtr getRoot(){
		return this->root;
	}

	// delete the node from the tree
	void deleteNode(int data) {
		deleteNodeHelper(this->root, data);
	}

	// print the tree structure on the screen
	void prettyPrint() {
		printHelper(this->root, "", true);
	}

};

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    ifstream inputFile("tests/random_access_1000000.txt"); // Assuming input file name is input.txt
    // ofstream outputFile("output_splay_cus_2.csv"); // Output CSV file

    int N;
    inputFile >> N; // Read the number of operations
    int tt = 0;
    SplayTree mySet;
    vector<double> runTimes;
    double total = 0;
    for (int i = 0; i < N; ++i) {
        int op, value;
        inputFile >> op >> value;

        switch (op) {
            case 0: // Insert operation
            {
                // auto start = high_resolution_clock::now(); // Start measuring time
                mySet.insert(value);
                // auto stop = high_resolution_clock::now(); // Stop measuring time
                // auto ms_int = duration_cast<milliseconds>(stop - start);
                // /* Getting number of milliseconds as a double. */
                // duration<double, std::milli> ms_double = stop - start;
                // runTimes.push_back(ms_double.count());
                break;
            }
            case 1: // Find operation
            {
                auto start = high_resolution_clock::now(); // Start measuring time
                mySet.find(value);
                auto stop = high_resolution_clock::now(); // Stop measuring time
                auto ms_int = duration_cast<milliseconds>(stop - start);
                /* Getting number of milliseconds as a double. */
                // duration<double, std::milli> ms_double = stop - start;
                // total += ms_double.count();
                // tt++;
                break;
            }
            case 2: // Erase operation
            {
                // auto start = high_resolution_clock::now(); // Start measuring time
                // mySet.erase(value);
                // auto stop = high_resolution_clock::now(); // Stop measuring time
                // auto ms_int = duration_cast<milliseconds>(stop - start);
                // /* Getting number of milliseconds as a double. */
                // duration<double, std::milli> ms_double = stop - start;
                // runTimes.push_back(ms_double.count());
                break;
            }
            case 3: // Splay operation (Not implemented here)
                // Implement your splay operation
                break;
            default:
                cerr << "Invalid operation: " << op << endl;
        }
    }

    // Dump runtimes to CSV file

    // Close files
    inputFile.close();
    // cout << total * 1000.0 / tt;
    // cerr << "finish" << endl;
    return 0;
}
