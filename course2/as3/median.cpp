using namespace std;
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>

const int ARRAY_SIZE = 10000;

void findMedians(int arr[]) {
    priority_queue<int> low;
    priority_queue<int, vector<int>, greater<int>> high;

    low.push(arr[0]);
    long long int median = arr[0];
    unsigned long long int medianSum = arr[0];
    cout << "M1: " << median << ", SUM: " << medianSum << endl;
    // low.push(0);
    for (int i = 1; i < ARRAY_SIZE; i++) {
        if (arr[i] < low.top()) {
            low.push(arr[i]);
        } else {
            high.push(arr[i]);
        }

        if (low.size() > high.size()) {
            high.push(low.top());
            low.pop();
        } else if (low.size() < high.size()) {
            low.push(high.top());
            high.pop();
        }

        if (high.size() > low.size()) {
            median = high.top();
        } else {
            median = low.top();
        }
        medianSum += median;
        cout << "M" << i + 1 << ": " << median << ", SUM: " << medianSum << endl;
    }

    cout << "last four of median: " << (medianSum % 10000) << endl;
}
int main() {
    int arr[ARRAY_SIZE];
    int index = 0;
    int number;
    ifstream inFile;

    inFile.open("median.txt");

    if (!inFile) {
        cerr << "Unable to open file" << endl;
        exit(1);
    }

    while (inFile >> number && index < ARRAY_SIZE) {
        arr[index] = number;
        index++;
    }

    inFile.close();

    findMedians(arr);
    return 0;
}
