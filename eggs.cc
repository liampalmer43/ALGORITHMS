// Problem C: Power Eggs
// From the University of Waterloo ACM Local Contest, September 27th, 2015

// Benedict bought K identical power eggs from Dropeggs.com, and now he wants to
// test them by dropping them from different floors of his building. His building
// has N floors numbered 1 to N. F is an unknown number in the range from 0 to N,
// inclusive. Each egg will break if dropped from floor F+1 or above, but will not
// break if dropped from floor F or below. Benedict can drop each egg as many times
// as he wants from any floor until it breaks. He wants to know the minimum number
// of egg drops necessary to ensure that he can determine F.

// For example, if there are three floors and Benedict has only one egg, then he has
// to first throw the egg from the first floor, then from the second floor (if the
// egg survived), and then from the third floor (if the egg survived). Therefore,
// three drops are required in the worst case.

// Input Specification
// The first line contains one number T (1 ≤ T ≤ 10000) which is the number of test
// cases, followed by T lines. Each of the next T lines contains two numbers: N,
// the number of floors (1 ≤ N ≤ 2000000007) and K, the number of eggs (1 ≤ K ≤ 32).

// Output Specification
// For each of the T lines, print the minimal number of drops required, or if it's
// greater than 32, print the word Impossible. After that many drops, Benedict gets
// too tired and cannot continue.

#include <iostream>
#include <vector>
using namespace std;

// A simple maximum function
int max(int a, int b) {
    return a > b ? a : b;
}

// Returns the minimal number of drops required for a given number of floors and a given
// number of eggs.  The parameter found_solutions keeps track of already found solutions
// to the problem for given "floor" and "egg" values (stored at found_solutions[floor][egg].
// This cuts off the recursion earlier instead of resolving many of the cases, and greatly
// increased the efficiency of this given solution.
int worstCaseDrops(const int& floors, const int& eggs, int (&found_solutions)[101][101]) {
    // If we have already found the solutions to this (floor, egg) solutions, simply return
    if (found_solutions[floors][eggs] != -1) {
        return found_solutions[floors][eggs];
    }
    // This variable will keep track of the minimum drops required as we conside different
    // first steps.
    int best_choice_drops = -1;
    // Here we consider the possible first steps; that is, dropping the first egg from the first
    // floor, the second floor, ... , or the last floor.  If a certain case proves to be more
    // optimal than any previous encounterd case, we update best_choice_drops appropriately.
    for (int drop_floor = 1; drop_floor <= floors; ++drop_floor) {
        // worstCaseDrops(drop_floor - 1, eggs - 1) corresponds to dropping the egg from floor
        // "drop_floor" and having it break.  Then you are reduced to testing the drop_floor-1
        // floors below this one with one less egg than you previously had.

        // worstCaseDrops(floors - drop_floor, eggs) corresponds to dropping the egg from floor
        // "drop_floor and having it not break.  Then you are reduced to testing the floors-drop_floor
        // floors above this one with the same number of eggs.

        // The egg could either break or not break in practice, so we must take the maximum of these
        // two computed values (and add 1 for the drop we are considering from floor drop_floor).

        int min_egg_drops = 1 + max(worstCaseDrops(drop_floor - 1, eggs - 1, found_solutions),
				    worstCaseDrops(floors - drop_floor, eggs, found_solutions));
        if (best_choice_drops == -1 || min_egg_drops < best_choice_drops) {
            best_choice_drops = min_egg_drops;
        }       
    }
    // Update the found solutions for future reference.
    found_solutions[floors][eggs] = best_choice_drops;
    return best_choice_drops;
}

int main() {
    int tests, eggs, floors;
    cin >> tests;
    for (int t = 0; t < tests; ++t) {
        cin >> floors >> eggs;
        // A slight modification from the above specifications...
        if (floors > 100 || eggs > 100 || floors < 1 || eggs < 1) {
            cout << "Out of Range" << endl;
            break;
        }
        int found_solutions[101][101];
        for (int a = 0; a <= 100; ++a) {
            for (int b = 0; b <= 100; ++b) {
                // Here we update some base case values for the recursion.  Without this, the solution
                // would never finish!  If there is 1 floor we need 1 drop, if there are 0 floors we
                // need 0 drops, and if there is one egg and "a" floors we need a drops.
                if (a == 1 || a == 0 || b == 1) {
                    found_solutions[a][b] = a;
                }
                else {
                    found_solutions[a][b] = -1;
                }
            }
        }
        cout << worstCaseDrops(floors, eggs, found_solutions) << endl;
    } 
}
