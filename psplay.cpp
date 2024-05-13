#include <bits/stdc++.h>
using namespace std;
using namespace std::chrono;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k) : key(k), left(nullptr), right(nullptr) {}
};

class SplayTree {
private:
    Node* __root;

    // Zig rotation
    Node* zig(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;
        return y;
    }

    // Zag rotation
    Node* zag(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;
        return y;
    }

    // Splay operation
    Node* splay(Node* root, int key) {
        if (root == nullptr || root->key == key)
            return root;

        if (root->key > key) {
            if (root->left == nullptr) return root;
            if (root->left->key > key) {
                root->left->left = splay(root->left->left, key);
                root = zig(root);
            } else if (root->left->key < key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = zag(root->left);
            }
            return (root->left == nullptr) ? root : zig(root);
        } else {
            if (root->right == nullptr) return root;
            if (root->right->key > key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = zig(root->right);
            } else if (root->right->key < key) {
                root->right->right = splay(root->right->right, key);
                root = zag(root);
            }
            return (root->right == nullptr) ? root : zag(root);
        }
    }

    // Helper function to insert a key
    Node* insert(Node* root, int key) {
        if (root == nullptr)
            return new Node(key);
        
        root = splay(root, key);

        if (root->key == key)
            return root;

        Node* newRoot = new Node(key);

        if (root->key > key) {
            newRoot->right = root;
            newRoot->left = root->left;
            root->left = nullptr;
        } else {
            newRoot->left = root;
            newRoot->right = root->right;
            root->right = nullptr;
        }

        return newRoot;
    }

    // Helper function to search for a key
    Node* search(Node* root, int key) {
        return splay(root, key);
    }

public:
    // Constructor
    SplayTree() {
        __root = nullptr;
    }

    // Insert method
    void insert(int key) {
        __root = insert(__root, key);
    }

    // Find method
    bool find(int key) {
        __root = search(__root, key);
        return __root != nullptr && __root->key == key;
    }
};

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    ifstream inputFile("tests/gradual_access_100000.txt"); // Assuming input file name is input.txt
    ofstream outputFile("output_splay_cus.csv"); // Output CSV file

    int N;
    inputFile >> N; // Read the number of operations

    SplayTree mySet;
    vector<double> runTimes;

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
                duration<double, std::milli> ms_double = stop - start;
                runTimes.push_back(ms_double.count());
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
    outputFile << "Operation,Runtime (s)\n";
    for (size_t i = 0; i < runTimes.size(); ++i) {
        outputFile << i << "," << runTimes[i] << "\n";
    }

    // Close files
    inputFile.close();
    outputFile.close();

    cerr << "finish" << endl;
    return 0;
}
