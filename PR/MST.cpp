#include<iostream>
#include<vector>
#include<limits.h>
using namespace std;

int main(){
    int n;
    cout << "Enter number of cities (offices): ";
    cin >> n;

    vector<string>names(n);
    vector<vector<int>>cost(n, vector<int>(n, -1));
    
    for(int i=0; i<n; i++){
        cout << "\nEnter city " << i+1 << " name: ";
        cin >> names[i];
    }

    cout << "\nEnter connection if not then -1";
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i==j){
                cost[i][j] = 0;
                cost[j][i] = 0;
            }
            else if(cost[i][j] == -1 && cost[j][i] == -1){
                cout << "\nEnter connection cost between " << names[i] << " and " << names[j] << ": ";
                cin >> cost[i][j];
                cost[j][i] = cost[i][j];
            }
        }
    }

    vector<bool>selected(n, false);
    selected[0] = true;
    int totalCost = 0;

    cout << "\nSelected connections (MST):\n";
    
    for(int edgeCount = 0; edgeCount < n-1; edgeCount++){
        int minCost = INT_MAX;
        int from = -1, to = -1;

        for(int i=0; i<n; i++){
            if(selected[i]){
                for(int j=0; j<n; j++){
                    if(!selected[j] && cost[i][j] != -1 && cost[i][j] < minCost){
                        minCost = cost[i][j];
                        from = i;
                        to = j;
                    }
                }
            }
        }

        if(from != -1 && to != -1){
            cout << names[from] << " ---- " << names[to] << "  (Cost: " << minCost << ")\n";
            totalCost += minCost;
            selected[to] = true;
        }
    }

    cout << "\nTotal Minimum Cost to Connect All Cities: " << totalCost << endl;
    
    return 0;
}
