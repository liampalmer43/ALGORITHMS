// Problem A: SpaceBalls
// Acknowledgement: This problem is from the CTU Open Contest 2014

// Juliet reads an interesting sci-fi book. In one chapter, the main character
// needs to solve a problem of maximizing the utilization of cargo spaceships.
// The ships transport valuable items that have the form of D-dimensional mesh
// with the size of 3 nodes in each dimension. The nodes are formed by balls of
// the same weight. The connections between balls are so light that their weight
// is negligible compared to the weight of balls. This means that the weight of
// any item is determined solely by the number of its nodes. On the other hand,
// the value of such an item is equal to the number of nodes plus the number of
// connections.

// zero dimension weight = 1 price = 1
//              o
// first dimension weight = 3 price = 5
//          o - o - o
// second dimension weight = 9 price = 21
//          o - o - o
//          |   |   |
//          o - o - o
//          |   |   |
//          o - o - o

// Each spaceships has a limited tonnage and we want to maximize the total value
// of items that may be stored in the ship without exceeding the tonnage. Your
// task is to decide what items of what dimension should be loaded to maximize
// their total value, providing that we have an unlimited supply of items of all
// dimensions.

// Input Specification
// The first line of the input contains the number of test cases N. Each test case
// then consists of a single line containing one positive integer number K < 10000000
// giving the ship cargo capacity.

// Output Specification
// For each test case, print one line containing space-separated non-negative
// numbers Xm Xm−1 ...X1 X0, where Xm>0 and Xi (0≤i≤m)is the number of items of the
// i-th dimension that we need to store to maximize their total value.

#include <iostream>
#include <vector>
using namespace std;

// Solution:  Despite lacking a good notion of what these items look like at
// higher dimensions (and how many nodes / connections are in each dimension),
// we can conclude the following;  A higher dimension has a higher value to weight
// ratio than any dimension lower than it.

// Thus we start by finding the heaviest dimension n that can fit on the boat
// (we need 3^n <= current weight allowance), and continue this process until
// the boat is full.  This suffices, as replacing a larger dimension with smaller
// dimensions will decrease the value to weight ratio.

// All in all, the problem boils down to outputing the ternary representation
// of a given input, as is done below.

void ternary(int value) {
    if (value < 0) {
        return;
    }
    if (value == 0) {
        cout << "0" << endl;
        return;
    }
    // We will continuously divide by 3 until the quotient is zero.
    // The reverse of the remainders stored is the desired ternary number.
    int quotient = value;
    // Holds the remainers encountered.
    vector<int> expression;
    while (quotient != 0) {
        expression.push_back(quotient % 3);
        quotient = quotient / 3;
    }
    // Output the ternary representation (remainders in reverse)
    for (int i = expression.size() - 1; i >= 0; --i) {
        cout << expression[i] << " ";
    }
    cout << endl;
}

int main() {
    int test_cases;
    cin >> test_cases;
    int test;
    for (int i = 0; i < test_cases; ++i) {
        cin >> test;
        ternary(test);
    }
    return 0;
}
