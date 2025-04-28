#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

int main() {
    ifstream input("input.txt");
    if (!input) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    int n, m;
    input >> n >> m; // Number of processes and resources

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> available(m);

    string temp;
    input >> temp; // Read "Allocation"
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            input >> allocation[i][j];

    input >> temp; // Read "Max"
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            input >> max[i][j];

    input >> temp; // Read "Available"
    for (int j = 0; j < m; ++j)
        input >> available[j];

    vector<vector<int>> need(n, vector<int>(m));
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            need[i][j] = max[i][j] - allocation[i][j];

    vector<bool> finish(n, false);
    vector<int> safeSequence;

    for (int count = 0; count < n; ++count) {
        bool found = false;
        for (int i = 0; i < n; ++i) {
            if (!finish[i]) {
                bool canAllocate = true;
                for (int j = 0; j < m; ++j) {
                    if (need[i][j] > available[j]) {
                        canAllocate = false;
                        break;
                    }
                }
                if (canAllocate) {
                    for (int j = 0; j < m; ++j)
                        available[j] += allocation[i][j];
                    safeSequence.push_back(i);
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            cout << "The system is not in a safe state." << endl;
            return 0;
        }
    }

    cout << "The system is in a safe state.\nSafe sequence is: ";
    for (size_t i = 0; i < safeSequence.size(); ++i) {
        cout << "P" << safeSequence[i];
        if (i != safeSequence.size() - 1) cout << " -> ";
    }
    cout << endl;

    return 0;
}
