#include <iostream>
#include <vector>
#include <utility>
#include <map>
using namespace std;

// Determines if the pair (left_state, right_state) exists in the states array
bool existsIn(const vector<pair<int, int> >& states, const int& left_state, const int& right_state){
    for (int iter = 0; iter < states.size(); ++iter) {
        if (states[iter].first == left_state && states[iter].second == right_state) {
            return true;
        }
    }
    return false;
}

// Takes two positive integers and returns their greatest common divisor (by Euclidean algorithm)
int gcd(const int& n, const int& m) {
    if (n == 1 || m == 1) {
        return 1;
    }
    if (n == m) {
        return n;
    }
    if (n > m) {
        return gcd(n - m, m);
    }
    else {
        return gcd(n, m - n);
    }
}    

// Consumes an array of already formed states.  Each entry in the states array is a pair of
// integers representing the volume of liquid in the left and right cup respectively.  The
// left_state and right_state parameters is the new state being considered at this step of
// the recursion, while n and m are the total volumes of the initial left and right cups.
void apply(vector<pair<int, int> >& states, const int& left_state, const int& right_state, const int& n, const int& m){
    // If we have encountered this state before, we have executed the recursion from there
    // and have thus considered all possibilities stemming from this state.  This is the
    // bottoming out of the recursion that allows it to stop at some point.
    if (existsIn(states, left_state, right_state)) {
        return;
    }
    // If the state is new, push it onto the existing states array
    pair<int, int> p(left_state, right_state);
    states.push_back(p);
    // Now we consider the finite number of single operations that one can perform with a given state
    // One can fill up the left cup
    apply(states, n, right_state, n, m);
    // One can Fill up the right cup
    apply(states, left_state, m, n, m);
    // One can empty the left cup
    apply(states, 0, right_state, n, m);
    // One can empty the right cup
    apply(states, left_state, 0, n, m);
    // One can pour the left cup's liquid to the right cup
    if (left_state <= m - right_state) {
        apply(states, 0, right_state + left_state, n , m);
    }
    else {
        apply(states, left_state - (m - right_state), m, n, m);
    }
    // One can pour the right cup's liquid to the left cup
    if (right_state <= n - left_state) {
        apply(states, left_state + right_state, 0, n, m);
    }
    else {
        apply(states, n, right_state - (n - left_state), n, m);
    }
}

// This is a brute force method for solving the problem.  We start with the two cups empty and recursively
// apply all possible actions (outlined in the apply(...) method above).
vector<int> brute_force_method(const int& n, const int& m) {
    // No possible states observed yet
    vector<pair<int, int> > possible_states;
    // Start with an initial state of two empty cups, and let the recursion do all the work
    apply(possible_states, 0, 0, n, m);
    // Iterate through all possible states and extract the individual volumes obtained.
    map<int, int> values;
    vector<int> result;
    for (int iter = 0; iter < possible_states.size(); ++iter) {
        if (values.count(possible_states[iter].first) == 0) {
            result.push_back(possible_states[iter].first);
            values[possible_states[iter].first] = 1;
        }
        if (values.count(possible_states[iter].second) == 0) {
            result.push_back(possible_states[iter].second);
            values[possible_states[iter].second] = 1;
        }
    }
    // Sort the list of volumes (here we use bubble sort just to be easy)
    for (int a = 0; a < result.size(); ++a) {
        for (int b = 0; b < result.size() - a - 1; ++b) {
            if (result[b] > result[b+1]) {
                int temp = result[b];
                result[b] = result[b+1];
                result[b+1] = temp;
            }
        }
    }
    // result is an array of possible volumes
    return result;
}

// This is a method for solving the problem that exploits the following property:
// If gcd(n,m) is 1, possible volumes include every integer from 0 to max(n,m)
// If gcd(n,m) = c, possible volumes include 0, c, 2c, 3c, 4c, ... , max(n, m)
// A sketch of the proof is outlined below:
vector<int> number_properties_method(const int& n, const int& m) {
    vector<int> result;
    if (n == 0) {
        if (m != 0) {
            result.push_back(0);
        }
        result.push_back(m);
        return result;
    }
    if (m == 0) {
        result.push_back(0);
        result.push_back(n);
        return result;
    }
    int GCD = gcd(n, m);
    int max = m > n ? m : n;
    if (GCD == 1) {
        for (int a = 0; a <= max; ++a) {
            result.push_back(a);
        }
        return result;
    }
    else {
        for (int a = 0; a <= max; a += GCD) {
            result.push_back(a);
        }
        return result;
    }
}

int main(){
    int n, m;
    while (cin >> n >> m) {
        if (n < 0 || m < 0) {
            cout << "Not valid integers" << endl;
        }
        else {
            break;
        }
    }
    // Brute force method
    vector<int> result = brute_force_method(n, m);
    for (int iter = 0; iter < result.size(); ++iter) {
        cout << result[iter] << " ";
    }
    cout << endl;
    // Number properties method
    result = number_properties_method(n, m);
    for (int iter = 0; iter < result.size(); ++iter) {
        cout << result[iter] << " ";
    }
    cout << endl;
    return 1;
}
