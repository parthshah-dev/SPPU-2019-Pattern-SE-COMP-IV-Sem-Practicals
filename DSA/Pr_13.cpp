#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

void displayAdjList(vector<vector<int>>& matrix, vector<char>& vname) {
    cout << "\nAdjacency List representation:\n";
    for (int i = 0; i < vname.size(); i++) {
        cout << vname[i] << " -> ";
        for (int j = 0; j < matrix[i].size(); j++) {
            if (matrix[i][j] != 0) {
                cout << vname[j] << " (weight: " << matrix[i][j] << ") ";
            }
        }
        cout << endl;
    }
}

void DFSTraversal(vector<vector<int>>& matrix, vector<char>& vname) {
    int n = matrix.size();
    vector<bool> visited(n, false);
    stack<int> s;
    cout << "\nDFS Traversal: ";
    s.push(0);
    visited[0] = true;
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << vname[current] << " ";
        for (int i = 0; i < n; i++) {
            if (matrix[current][i] != 0 && !visited[i]) {
                s.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

void BFSTraversal(vector<vector<int>>& matrix, vector<char>& vname) {
    int n = matrix.size();
    vector<bool> visited(n, false);
    queue<int> q;
    cout << "\nBFS Traversal: ";
    q.push(0);
    visited[0] = true;
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << vname[current] << " ";
        for (int i = 0; i < n; i++) {
            if (matrix[current][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter number of vertices: ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n, 0));
    vector<char> vname;
    char vn;

    for (int i = 0; i < n; i++) {
        cout << "\nEnter name of vertex " << i + 1 << ": ";
        cin >> vn;
        vname.push_back(vn);
    }

    int weight;

    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[i].size(); j++) {
            char inp;
            cout << "\nIs there edge between " << vname[i] << " to " << vname[j] << " (y/n):  ";
            cin >> inp;
            if (inp == 'y') {
                cout << "\nEnter weight of the edge: ";
                cin >> weight;
                matrix[i][j] = weight;
            }
        }
    }

    cout << "Adjacency matrix representation: " << endl;
    cout << "   ";
    for (int i = 0; i < vname.size(); i++) {
        cout << vname[i] << "  ";
    }
    cout << endl;
    for (int i = 0; i < matrix.size(); i++) {
        cout << vname[i] << "  ";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j] << "  ";
        }
        cout << endl;
    }

    displayAdjList(matrix, vname);
    BFSTraversal(matrix, vname);
    DFSTraversal(matrix, vname);

    return 0;
}
