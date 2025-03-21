#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int main() {
    int n;
    cout << "Enter number of cities: ";
    cin >> n;

    vector<vector<int>> cities(n, vector<int>(n, -1));
    vector<string> cname(n);

    for (int i = 0; i < n; i++) {
        cout << "Enter name of city " << i + 1 << ": ";
        cin >> cname[i];
    }

    cout << "\nEnter the cost of roads between cities (-1 for no connection):\n";
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            cout << "Cost between " << cname[i] << " and " << cname[j] << ": ";
            cin >> cities[i][j];
            cities[j][i] = cities[i][j];
        }
    }

    vector<bool> visited(n, false);
    visited[0] = true;
    int minCost = 0;

    cout << "\nSelected edges in MST:\n";

    for (int k = 0; k < n - 1; k++) {
        int minEdge = INT_MAX, row = -1, col = -1;

        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                for (int j = 0; j < n; j++) {
                    if (!visited[j] && cities[i][j] != -1 && cities[i][j] < minEdge) {
                        minEdge = cities[i][j];
                        row = i;
                        col = j;
                    }
                }
            }
        }

        if (row != -1 && col != -1) {
            cout << cname[row] << " -> " << cname[col] << " (Cost: " << minEdge << ")\n";
            minCost += minEdge;
            visited[col] = true;
        }
    }

    cout << "\nTotal Minimum Cost: " << minCost << endl;
    return 0;
}
