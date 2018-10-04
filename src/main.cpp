#include <iostream>
#include <omp.h>
#include <vector>
#include <unordered_set>

using std::vector;
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ratio;
using std::unordered_set;
using std::chrono::time_point;
using std::chrono::duration;
using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::nanoseconds;

const int size = 200'000;

bool isProperDivisor(int divisor, int dividend) {
    return divisor % dividend == 0;
}

vector<int> calculateFactors(int max) {
    vector<int> v;
    v.resize(static_cast<unsigned long>(max));

#pragma omp parallel for schedule(dynamic, 100)
    for (int i = 1; i < max; i++) {
        int factorSum = 0;
        unordered_set<int> factors;

        for (int x = 1; x < (i / 2) + 1; x++) {
            if (isProperDivisor(i, x)) {
                if (factors.find(x) == factors.end()) {
                    factors.insert(x);
                    factorSum += x;
                }
            }
        }

        v[i - 1] = factorSum;
    }

    return v;
}

void printAmicablePairs(vector<int> v) {
    for (int i = 1; i < size; i++) {
        int iFactorSum = v[i - 1];
        if (v[iFactorSum - 1] == i) {
            cout << i << " " << v[i - 1] << endl;
        }
    }
}

int main() {
    time_point startTime = high_resolution_clock::now();
    vector<int> v = calculateFactors(size);
    time_point endTime = high_resolution_clock::now();

    duration timeTaken = duration_cast<nanoseconds>(endTime - startTime);

//    printAmicablePairs(v);
    cout << "Calculating factors took " << timeTaken.count() << "ns" << endl;
}