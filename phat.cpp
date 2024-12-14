#include <bits/stdc++.h>
using namespace std;

using splay_key = int;

struct Node {
    Node *parent, *child[2] = {nullptr, nullptr};
    splay_key key;
    int size = 1;

    void set_child(int index, Node *child_node) {
        child[index] = child_node;

        if (child_node)
            child_node->parent = this;
    }

    int parent_index() const {
        return parent == nullptr ? -1 : int(this == parent->child[1]);
    }

    void join() {
        size = 1 + (child[0] ? child[0]->size) + (child[1] ? child[1]->size);
    }
};

struct SplayTree {
    int SPLAY_DEPTH = 0;
    long long total_depth = 0;
    int size = 0;
    
    Node *root = nullptr;

    Node *set_root(Node *x) {
        if (x) 
            x->parent = nullptr;

        return root = x;
    }

    // log2(size of the tree) * 2
    int get_depth_threshold() {
        return max(4, (31 - __builtin_clz(size)) << 1);
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

        x->join();
    }

    void insert(splay_key key) {
        size++;
        SPLAY_DEPTH = get_depth_threshold();
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

        if (depth > SPLAY_DEPTH)
            splay(x);

        for (Node *node = x; node != nullptr; node = node->parent)
            node->join();
    }

    Node *lower_bound(const splay_key &key) {
        static Node *current, *answer;
        current = root, answer = nullptr;

        static int depth;
        depth = 0;

        while (current != nullptr) {
            depth++;
            if (current->key < key) {
                current = current->child[1];
            } else {
                answer = current;
                current = current->child[0];
            }
        }

        if (depth > SPLAY_DEPTH) {
            splay(answer);
        }

        total_depth += depth;
        return answer;
    }

    Node *find(const splay_key &key) {
        static Node *current, *answer;
        current = root, answer = nullptr;

        static int depth;
        depth = 0;

        while (current != nullptr) {
            depth++;
            if (current->key < key) {
                current = current->child[1];
            } else {
                answer = current;
                current = current->child[0];
            }
        }

        if (depth > SPLAY_DEPTH) {
            splay(answer);
        }
        return answer;
    }

    Node *node_at_index(int index) {
        if (index < 0 || index >= size())
            return nullptr;

        static Node *current = root;
        static int depth = 0, left_size = 0;

        while (current != nullptr) {
            left_size = get_size(current->child[0]);
            depth++;

            if (index == left_size) {
                if (depth > SPLAY_DEPTH) {
                    splay(current);
                }

                return current;
            }

            if (index < left_size) {
                current = current->child[0];
            } else {
                current = current->child[1];
                index -= left_size + 1;
            }
        }

        assert(false);
    }
};


using namespace std::chrono;

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    ifstream inputFile("tests/random_access_1000000.txt"); // Assuming input file name is input.txt

    int N;
    inputFile >> N; // Read the number of operations

    SplayTree mySet;
    vector<double> runTimes;

    vector<int> initOrder;
    vector<int> findQueries;

    for (int i = 0; i < N; ++i) {
        int op, value;
        inputFile >> op >> value;

        switch (op) {
            case 0: // Insert operation
            {
                // auto start = high_resolution_clock::now(); // Start measuring time
                mySet.insert(value);
                initOrder.push_back(value);
            
                break;
            }
            case 1: // Find operation
            {
                findQueries.push_back(value);
                // auto start = high_resolution_clock::now(); // Start measuring time
                // mySet.lower_bound(value);
                // auto stop = high_resolution_clock::now(); // Stop measuring time
                // auto ms_int = duration_cast<milliseconds>(stop - start);
                // /* Getting number of milliseconds as a double. */
                // duration<double, std::milli> ms_double = stop - start;
                // runTimes.push_back(ms_double.count());
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

    auto eval = [&]() {
        for (int x : initOrder)
            mySet.find(x);

        for (int x : findQueries) {
            auto start = high_resolution_clock::now(); // Start measuring time
            mySet.node_at_index(x);
            auto stop = high_resolution_clock::now(); // Stop measuring time
            auto ms_int = duration_cast<milliseconds>(stop - start);
            /* Getting number of milliseconds as a double. */
            duration<double, std::milli> ms_double = stop - start;
            runTimes.push_back(ms_double.count());
        }
    };

    for (int i = 0; i < 10; i++) eval();

    double total = 0.0;
    for (size_t i = 0; i < runTimes.size(); ++i) {
        total += runTimes[i];
    }

    cout << fixed << setprecision(10) << "avg = " << total * 1000.0 / runTimes.size() << endl;
    // Close files
    inputFile.close();

    return 0;
}