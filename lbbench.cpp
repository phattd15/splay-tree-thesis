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
    int SPLAY_DEPTH = 0;
    int splay_count = 0;
    long long total_depth = 0;
    int size = 0;
    
    Node *root = nullptr;

    Node *set_root(Node *x) {
        if (x) 
            x->parent = nullptr;

        return root = x;
    }

    // log2(size of the tree) * (1.5 ~ 2.0)
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
            splay(answer), splay_count++;
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

        splay(answer);
        return answer;
    }
};

using namespace std::chrono;

void bench(const string tname) {
    ifstream inputFile(tname); 
        int N;
        inputFile >> N;
        SplayTree mySet;
        vector<double> runTimes;
        vector<int> findQueries;
        vector<int> initOrder;

        for (int i = 0; i < N; i++) {
            int op, value;
            inputFile >> op >> value;

            switch (op) {
                case 0: // Insert operation
                {
                    // auto start = high_resolution_clock::now(); // Start measuring time
                    mySet.insert(value);
                    initOrder.push_back(value);
                    // auto stop = high_resolution_clock::now(); // Stop measuring time
                    // auto ms_int = duration_cast<milliseconds>(stop - start);
                    // /* Getting number of milliseconds as a double. */
                    // duration<double, std::milli> ms_double = stop - start;
                    // runTimes.push_back(ms_double.count());
                    break;
                }
                case 1: // Find operation
                {
                    // auto start = high_resolution_clock::now(); // Start measuring time
                    // mySet.lower_bound(value);
                    // auto stop = high_resolution_clock::now(); // Stop measuring time
                    // auto ms_int = duration_cast<milliseconds>(stop - start);
                    // /* Getting number of milliseconds as a double. */
                    // duration<double, std::milli> ms_double = stop - start;
                    // runTimes.push_back(ms_double.count());

                    findQueries.push_back(value);
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

        mySet.splay_count = 0;
        mySet.total_depth = 0;

        // assuming tree is normal

        double total = 0.0;
        for (int o : initOrder)
            mySet.find(o);

        for (int tar : findQueries) {
            auto start = high_resolution_clock::now(); // Start measuring time
            mySet.lower_bound(tar);
            auto stop = high_resolution_clock::now(); // Stop measuring time
            auto ms_int = duration_cast<milliseconds>(stop - start);
            /* Getting number of milliseconds as a double. */
            duration<double, std::milli> ms_double = stop - start;
            total += ms_double.count();
        }

        cout << mySet.SPLAY_DEPTH << ',' << mySet.splay_count << ',' << total * 1000.0 / findQueries.size() << ',' << mySet.total_depth * 1.0 / initOrder.size() << '\n';
        inputFile.close();
}

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;
    cout << "splay_depth,splay_count,avg_runtime,avg_depth" << endl;
    // bench("tests/cache_access_10_1000000.txt");
    // bench("tests/cache_access_100_1000000.txt");
    // bench("tests/cache_access_1000_1000000.txt");
    // bench("tests/cache_access_10000_1000000.txt");
    // bench("tests/cache_access_100000_1000000.txt");
    bench("tests/lb_access.txt");
    return 0;
}