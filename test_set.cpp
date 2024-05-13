#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <chrono>

using namespace std;
using namespace std::chrono;

int main() {
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    ifstream inputFile("tests/gradual_access_100000.txt"); // Assuming input file name is input.txt
    ofstream outputFile("output_set.csv"); // Output CSV file

    int N;
    inputFile >> N; // Read the number of operations

    set<int> mySet;
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
                auto start = high_resolution_clock::now(); // Start measuring time
                mySet.erase(value);
                auto stop = high_resolution_clock::now(); // Stop measuring time
                auto ms_int = duration_cast<milliseconds>(stop - start);
                /* Getting number of milliseconds as a double. */
                duration<double, std::milli> ms_double = stop - start;
                runTimes.push_back(ms_double.count());
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
