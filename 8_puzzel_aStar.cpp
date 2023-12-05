#include <bits/stdc++.h>
using namespace std;

// Structure to represent the puzzle state
struct PuzzleState {
    vector<vector<int>> state; // Current state of the puzzle
    int moves; // Number of moves taken to reach this state
    int heuristic; // Heuristic value (here, Manhattan distance)

    PuzzleState(const vector<vector<int>>& s, int m, int h) : state(s), moves(m), heuristic(h) {}

    bool operator<(const PuzzleState& other) const {
        return (moves + heuristic) > (other.moves + other.heuristic); // A* search comparison based on f(n) = g(n) + h(n)
    }
};

// Function to calculate the Manhattan distance heuristic
int calculateHeuristic(const vector<vector<int>>& state) {
    int distance = 0;
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (state[i][j] != 0) {
                int targetX = (state[i][j] - 1) / 3; // Expected row
                int targetY = (state[i][j] - 1) % 3; // Expected column
                distance += abs(i - targetX) + abs(j - targetY); // Manhattan distance calculation
            }
        }
    }
    return distance;
}

// Function to print the puzzle state
void printPuzzleState(const vector<vector<int>>& state) {
    for (const auto& row : state) {
        for (int val : row) {
            cout << val << " ";
        }
        cout << endl;
    }
}

// Function to get the possible next states from the current state
vector<vector<vector<int>>> getNextStates(const vector<vector<int>>& currentState) {
    vector<vector<vector<int>>> nextStates;
    int zeroRow = -1, zeroCol = -1;

    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (currentState[i][j] == 0) {
                zeroRow = i;
                zeroCol = j;
                break;
            }
        }
    }

    // Define the four possible moves: up, down, left, right
    const int dr[] = {-1, 1, 0, 0};
    const int dc[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i) {
        int newRow = zeroRow + dr[i];
        int newCol = zeroCol + dc[i];

        if (newRow >= 0 && newRow < 3 && newCol >= 0 && newCol < 3) {
            vector<vector<int>> nextState = currentState;
            swap(nextState[zeroRow][zeroCol], nextState[newRow][newCol]);
            nextStates.push_back(nextState);
        }
    }
    return nextStates;
}

// Function to solve the puzzle using A* search
bool solvePuzzle(vector<vector<int>>& initialState) {
    int heuristic = calculateHeuristic(initialState);
    priority_queue<PuzzleState> pq;
    map<vector<vector<int>>, int> cost;
    pq.push(PuzzleState(initialState, 0, heuristic));

    while (!pq.empty()) {
        PuzzleState current = pq.top();
        pq.pop();

        if (current.heuristic == 0) { // If the heuristic is 0, it means the goal state is reached
            cout << "Solution found in " << current.moves << " moves:" << endl;
            printPuzzleState(current.state);
            return true;
        }

        if (cost.find(current.state) != cost.end() && cost[current.state] < current.moves) {
            continue; // If the state is already visited with a lower cost, skip it
        }

        cost[current.state] = current.moves;
        vector<vector<vector<int>>> nextStates = getNextStates(current.state);

        for (const auto& nextState : nextStates) {
            int h = calculateHeuristic(nextState);
            pq.push(PuzzleState(nextState, current.moves + 1, h));
        }
    }
    cout << "No solution found!" << endl;
    return false;
}

int main() {
    vector<vector<int>> initialState = {{1, 2, 3},{5, 6, 0},{7, 8, 4}};
    cout << "Initial state:" << endl;
    printPuzzleState(initialState);
    solvePuzzle(initialState);

    return 0;
}
