#include <bits/stdc++.h>
using namespace std;

typedef vector<pair<int, int>> TestType;
/*
    {op, value}
    op = 0: insert value
    op = 1: find value
    op = 2: erase value
    op = 3: splay value
*/

vector<string> testNames;

string convertTestToString(TestType testData) {
    string result = "";
    for (auto step : testData) {
        result += to_string(step.first);
        result += " ";
        result += to_string(step.second);
        result += "\n";
    }
    return result;
}

void writeTestNames() {
    ofstream outputFile("testnames.txt", ios::out);
    for (auto testName : testNames) outputFile << testName << endl;
}

void createTestWithData(TestType testData, string testName) {
    string filePath = "tests/" + testName;
    ofstream outputFile(filePath, ios::out);

    if (!outputFile.is_open()) {
        cerr << "Error: Unable to open file " << filePath << endl;
        return;
    }

    outputFile << convertTestToString(testData);
    outputFile.close();

    testNames.push_back(testName);

    cout << "Data has been written to " << filePath << endl;
}

void buildRandomAccessTest() {
    TestType testData;

    int testSize = 1000000;
    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i);

    int numAccess = 1000000;
    while (numAccess--) {
        testData.emplace_back(1, rand() % testSize);
    }

    createTestWithData(testData, "random_access_1000000.txt");
}

void buildFullyRandomTest() {
    TestType testData;

    int testSize = 1000000;
    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, rand()% testSize);

    int numAccess = 1000000;
    while (numAccess--) {
        testData.emplace_back(1, rand() % testSize);
    }

    createTestWithData(testData, "fully_random_1000000.txt");
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    buildRandomAccessTest();
    writeTestNames();
    return 0;
}
