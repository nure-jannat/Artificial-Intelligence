#include <bits/stdc++.h>
using namespace std;

bool isAttacking(int row1, int col1, int row2, int col2) {
    return (row1 == row2 || col1 == col2 || abs(row1 - row2) == abs(col1 - col2));
}

int calculateFitness(const vector<int>& placement) {
    int conflicts = 0;
    int n = placement.size();

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            if (isAttacking(i, placement[i], j, placement[j])) {
                conflicts++;
            }
        }
    }

    return conflicts;
}

vector<int> crossover(const vector<int>& parent1, const vector<int>& parent2) {
    int n = parent1.size();
    int crossoverPoint = rand() % (n - 1) + 1;

    vector<int> child(n);
    for (int i = 0; i < crossoverPoint; ++i) {
        child[i] = parent1[i];
    }
    for (int i = crossoverPoint; i < n; ++i) {
        child[i] = parent2[i];
    }

    return child;
}

void mutate(vector<int>& placement) {
    int n = placement.size();
    int index = rand() % n;
    placement[index] = rand() % n;
}

vector<int> solveNQueens(int n, int populationSize, int maxGenerations) {
    srand(time(nullptr));

    vector<vector<int>> population(populationSize, vector<int>(n));
    for (int i = 0; i < populationSize; ++i) {
        for (int j = 0; j < n; ++j) {
            population[i][j] = j;
        }
        random_shuffle(population[i].begin(), population[i].end());
    }

    for (int generation = 0; generation < maxGenerations; ++generation) {
        vector<pair<int, vector<int>>> fitnessValues;
        for (const auto& placement : population) {
            int fitness = calculateFitness(placement);
            fitnessValues.push_back(make_pair(fitness, placement));
        }

        sort(fitnessValues.begin(), fitnessValues.end());

        if (fitnessValues[0].first == 0) {
            return fitnessValues[0].second; // Solution found
        }

        vector<vector<int>> parents(populationSize / 2);
        for (int i = 0; i < populationSize / 2; ++i) {
            parents[i] = fitnessValues[i].second;
        }

        vector<vector<int>> newPopulation;
        while (newPopulation.size() < populationSize) {
            int parent1Index = rand() % (populationSize / 2);
            int parent2Index = rand() % (populationSize / 2);
            vector<int> child = crossover(parents[parent1Index], parents[parent2Index]);

            if (rand() % 100 < 10) {
                mutate(child);
            }

            newPopulation.push_back(child);
        }

        population = newPopulation;
    }

    return vector<int>(); // No solution found
}

void printSolution(const vector<int>& solution) {
    int n = solution.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (j == solution[i]) {
                cout << "Q ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

int main() {
    int n = 8;
    int populationSize = 100;
    int maxGenerations = 1000;

    vector<int> solution = solveNQueens(n, populationSize, maxGenerations);
    if (!solution.empty()) {
        cout << "Solution found:" << endl;
        printSolution(solution);
    } else {
        cout << "No solution found within " << maxGenerations << " generations." << endl;
    }

    return 0;
}
