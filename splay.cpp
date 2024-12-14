#include <bits/stdc++.h>
using namespace std;

using splay_key = int;

struct Node {
    Node *parent, *child[2] = {nullptr, nullptr};
    splay_key key;

    void set_child(int index, Node *child_node) {
        child[index] = child_node;

        if (child_node)
            child_node->parent = this;
    }

    int parent_index() const {
        return parent == nullptr ? -1 : int(this == parent->child[1]);
    }
};

struct SplayTree {
    Node *root = nullptr;

    Node *set_root(Node *x) {
        if (x) 
            x->parent = nullptr;

        return root = x;
    }

    void rotate_up(Node *x) {
        Node *p, *gp;

        p = x->parent;
        gp = p->parent;

        static int index;
        index = x->parent_index();

        if (gp) {
            gp->set_child(p->parent_index(), x);
        } else {
            set_root(x);
        }

        p->set_child(index, x->child[!index]);
        x->set_child(!index, p);
    }

    void splay(Node *x) {
        while (x != root) {
            if (x->parent != root)
                rotate_up(x->parent_index() == x->parent->parent_index() ? x->parent : x);

            rotate_up(x);
        }
    }

    void insert(splay_key key) {
        Node *x = new Node();
        x->key = key;

        if (root == nullptr) {
            set_root(x);
            return;
        }

        static Node *current, *previous;
        current = root, previous = nullptr;
        static int depth;
        depth = 0;

        while (current != nullptr) {
            previous = current;
            depth++;
            current = current->child[current->key < x->key];
        }

        previous->set_child(int(previous->key < x->key), x);

        // if (depth > 300)
            splay(x);
    }

    Node *lower_bound(const splay_key &key) {
        static Node *current, *answer;
        current = root, answer = nullptr;

        int depth = 0;

        while (current != nullptr) {
            depth++;
            if (current->key < key) {
                current = current->child[1];
            } else {
                answer = current;
                current = current->child[0];
            }
        }

        // if (depth > 300)
            splay(answer);

        return answer;
    }
};

using namespace std::chrono;

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    ifstream inputFile("tests/cache_access.txt"); // Assuming input file name is input.txt
    // ofstream outputFile("cache_splay.csv"); // Output CSV file

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
                mySet.lower_bound(value);
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

    return 0;
}