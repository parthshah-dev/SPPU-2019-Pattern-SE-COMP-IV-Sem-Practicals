#include<iostream>
#include<vector>
#include<stack>
#include<queue>
using namespace std;

void showAdjMat(vector<vector<int>>& mat, vector<string>& names){
    cout << "Adjacency Matrix \n";
    for(auto& name : names){
        cout << " " << name[0] << " ";
    }
    cout << endl;

    for(int i=0; i<mat.size(); i++){
        cout << names[i][0] << " ";
        for(int j=0; j<mat.size(); j++){
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }
}

void showAdjList(vector<vector<int>>& mat, vector<string>& names){
    cout << "Adjacency List \n";
    for(int i=0; i<mat.size(); i++){
        cout << names[i] << "-> ";
        for(int j=0; j<mat.size(); j++){
            if(mat[i][j] != 0){
                cout << names[j] << " ";
            }
        }
        cout << endl;
    }
}

void BFS(vector<vector<int>>& mat, vector<string>& names){
    int n = mat.size();

    vector<bool> visited(n, false);
    queue<int> q;

    cout << "\nBFS Traversal: ";

    q.push(0); //push the 0th node - 1st landmark
    visited[0] = true; //mark it visited

    while(!q.empty()){
        int curr = q.front();
        q.pop();
        cout << names[curr] << " ";

        for(int i=0; i<n; i++){
            if(mat[curr][i] && !visited[i]){
                q.push(i);
                visited[i] = true;
            }
        }
    }
}

void DFS(vector<vector<int>>& mat, vector<string>& names){
    int n = mat.size();

    vector<bool>visited(n, false);
    stack<int>s;

    cout << "\nDFS Traversal: ";

    s.push(0);
    visited[0] = true;

    while(!s.empty()){
        int curr = s.top();
        s.pop();
        cout << names[curr] << " ";

        for(int i=n-1; i>=0; i--){
            if(mat[curr][i] && !visited[i]){
                s.push(i);
                visited[i] = true;
            }
        }
    }
}

int main(){
    int n;
    cout << "Enter number of landmarks: ";
    cin >> n;

    vector<string> names(n);
    for(int i=0; i<n; i++){
        cout << "\nEnter name of landmark " << i+1 << " : ";
        cin >> names[i];
    }

    vector<vector<int>>mat(n, vector<int>(n, 0));
    char ch;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cout << "\nIs there a path between " << names[i] << " and " << names[j] << "? (y/n): ";
            cin >> ch;

            if(ch == 'Y' || ch == 'y'){
                mat[i][j] = 1;
            }
        }
    }

    showAdjMat(mat, names);
    showAdjList(mat, names);
    BFS(mat, names);
    DFS(mat, names);

    return 0;
}