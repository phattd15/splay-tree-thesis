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
    result += to_string(testData.size());
    result += "\n";

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

void buildRandomSmallAccessTest() {
    TestType testData;

    int testSize = 1000000;
    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i);

    int numAccess = 10000;
    while (numAccess--) {
        testData.emplace_back(1, rand() % testSize);
    }

    createTestWithData(testData, "random_access_10000.txt");
}

void buildMidRandomSmallAccessTest() {
    TestType testData;

    int testSize = 100000;
    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i);

    int numAccess = 10000;
    while (numAccess--) {
        testData.emplace_back(1, rand() % testSize);
    }

    createTestWithData(testData, "mid_random_access_10000.txt");
}

void buildSmallRandomSmallAccessTest() {
    TestType testData;

    int testSize = 10000;
    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i);

    int numAccess = 10000;
    while (numAccess--) {
        testData.emplace_back(1, rand() % testSize);
    }

    createTestWithData(testData, "small_random_access_10000.txt");
}

void buildRandomAccessTest(int testSize, int numAccess) {
    TestType testData;

    int ts = testSize;
    int na = numAccess;

    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i);
    random_shuffle(testData.begin(), testData.end());
    while (numAccess--) {
        testData.emplace_back(1, rand() % testSize);
    }
    string tname;
    
    if (ts == 10) createTestWithData(testData, "random_access_10_1000000.txt");
    if (ts == 100) createTestWithData(testData, "random_access_100_1000000.txt");
    if (ts == 1000) createTestWithData(testData, "random_access_1000_1000000.txt");
    if (ts == 10000) createTestWithData(testData, "random_access_10000_1000000.txt");
    if (ts == 100000) createTestWithData(testData, "random_access_100000_1000000.txt");
    if (ts == 1000000) createTestWithData(testData, "random_access_1000000_1000000.txt");
    // createTestWithData(testData, tname);
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

void buildGradualAccessTest() {
    TestType testData;

    int testSize = 100000;
    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i); // insert

    for (int i = 0; i < 10; i++) {
        
        for (int j = 0; j < testSize; j++) {
            testData.emplace_back(1, j); // find
        }
    }

    createTestWithData(testData, "gradual_access_100000.txt");
}

void buildCacheAccess(int ts) {
    TestType testData;

    int testSize = 1000000;
    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i);
    
    int numCount = ts;
    const int range = 1000000;
    unordered_set<int> uniqueNumbers;
    random_device rd;  // Random number generator
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<> dis(0, range-1); // Distribution in range [0, range-1]

    while (uniqueNumbers.size() < numCount) {
        int num = dis(gen);
        uniqueNumbers.insert(num);
    }

    // Transfer the unique numbers to a vector
    std::vector<int> uniqueVector(uniqueNumbers.begin(), uniqueNumbers.end());

    int queries = 1000000;
    for (int i = 0; i < queries; i++) {
        testData.emplace_back(1, uniqueVector[rand() % numCount]);
    }

    // createTestWithData(testData, "cache_access.txt");

    if (ts == 10) createTestWithData(testData, "cache_access_10_1000000.txt");
    if (ts == 100) createTestWithData(testData, "cache_access_100_1000000.txt");
    if (ts == 1000) createTestWithData(testData, "cache_access_1000_1000000.txt");
    if (ts == 10000) createTestWithData(testData, "cache_access_10000_1000000.txt");
    if (ts == 100000) createTestWithData(testData, "cache_access_100000_1000000.txt");
    if (ts == 1000000) createTestWithData(testData, "cache_access_1000000_1000000.txt");
}

void buildStrictCacheAccess() {
    TestType testData;

    int testSize = 1000000;
    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i);
    
    const int numCount = 500;
    const int range = 1000000;
    unordered_set<int> uniqueNumbers;
    random_device rd;  // Random number generator
    mt19937 gen(rd()); // Mersenne Twister engine
    uniform_int_distribution<> dis(0, range-1); // Distribution in range [0, range-1]

    while (uniqueNumbers.size() < numCount) {
        int num = dis(gen);
        uniqueNumbers.insert(num);
    }

    // Transfer the unique numbers to a vector
    std::vector<int> uniqueVector(uniqueNumbers.begin(), uniqueNumbers.end());

    int queries = 1000000;
    for (int i = 0; i < queries; i++) {
        testData.emplace_back(1, uniqueVector[rand() % numCount]);
    }

    createTestWithData(testData, "strict_cache_access.txt");
}

void buildLowerBoundTest(int testSize, int gap, int numAccess) {
    TestType testData;

    for (int i = 0; i < testSize; i++)
        testData.emplace_back(0, i * gap);

    random_shuffle(testData.begin(), testData.end());

    while (numAccess--) {
        testData.emplace_back(1, rand() % (testSize * gap));
    }
    createTestWithData(testData, "lb_access_2.txt");
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    // buildRandomAccessTest();
    // buildFullyRandomTest();
    // buildRandomSmallAccessTest();
    // buildSmallRandomSmallAccessTest();
    // buildMidRandomSmallAccessTest();
    // buildGradualAccessTest();
    // buildCacheAccess();

    // buildStrictCacheAccess();

    // buildRandomAccessTest(10, 1000000);
    // buildRandomAccessTest(100, 1000000);
    // buildRandomAccessTest(1000, 1000000);
    // buildRandomAccessTest(10000, 1000000);
    // buildRandomAccessTest(100000, 1000000);
    // buildRandomAccessTest(1000000, 1000000);

    // buildCacheAccess(10);
    // buildCacheAccess(100);
    // buildCacheAccess(1000);
    // buildCacheAccess(10000);
    // buildCacheAccess(100000);
    // buildCacheAccess(1000000);

    buildLowerBoundTest(1000000, 10, 100000);

    writeTestNames();
    return 0;
}
