// Exam Scheduler - starter version (Backtracking)
// Each subject is a "box". Two subjects that share students
// cannot be in the same time slot. We try slots one by one,
// and if we get stuck we go BACK and try another slot (backtracking).

#include <iostream>
#include <string>
using namespace std;

const int N = 5;           // number of subjects
const int NUM_SLOTS = 3;   // number of exam time slots available

// Names of the subjects
string courses[N] = {"Maths", "Physics", "Chemistry", "English", "Computer"};

// conflict[i][j] = 1 means subject i and subject j have the SAME students
// so they cannot be on the same slot
int conflict[N][N] = {
    {0, 1, 1, 0, 0},
    {1, 0, 0, 1, 0},
    {1, 0, 0, 1, 1},
    {0, 1, 1, 0, 0},
    {0, 0, 1, 0, 0}
};

// slotOf[i] = slot number given to subject i (-1 means not given yet)
int slotOf[N];

// Is it OK to put subject "c" in "slot"?
bool isSafe(int c, int slot) {
    for (int other = 0; other < c; other++) {
        // if they clash AND already have the same slot -> not safe
        if (conflict[c][other] == 1 && slotOf[other] == slot) {
            return false;
        }
    }
    return true;
}

// Try to give a slot to subject c, then c+1, then c+2 ...
bool solve(int c) {
    if (c == N) return true;               // all subjects done!

    for (int slot = 0; slot < NUM_SLOTS; slot++) {
        if (isSafe(c, slot)) {
            slotOf[c] = slot;              // try this slot
            if (solve(c + 1)) return true; // go to next subject
            slotOf[c] = -1;                // didn't work -> undo (backtrack)
        }
    }
    return false;                          // no slot worked
}

int main() {
    for (int i = 0; i < N; i++) slotOf[i] = -1;

    if (solve(0)) {
        cout << "Exam timetable found!\n\n";
        for (int s = 0; s < NUM_SLOTS; s++) {
            cout << "Slot " << s + 1 << ": ";
            for (int i = 0; i < N; i++) {
                if (slotOf[i] == s) cout << courses[i] << "  ";
            }
            cout << "\n";
        }
    } else {
        cout << "No timetable possible with " << NUM_SLOTS << " slots.\n";
    }
    return 0;
}
