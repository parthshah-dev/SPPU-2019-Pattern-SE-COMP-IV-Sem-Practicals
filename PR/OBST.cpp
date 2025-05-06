#include<iostream>
#include<limits.h>
using namespace std;

#define MAX 10

class OBST{
    int keys[MAX];
    int prob[MAX]; 
    int cost[MAX][MAX];
    int root[MAX][MAX];  
    int n;

    public:
        void input(){
            cout << "Enter number of keys: ";
            cin >> n;
            cout << "\nEnter sorted keys: \n";
            for(int i=1; i<=n; i++){
                cout << "\nEnter key " << i << ": ";
                cin >> keys[i];
            }

            cout << "Enter search probabilities:\n";
            for(int i=1; i<=n; i++){
                cout << "P[" << i << "] for key " << keys[i] << ": ";
                cin >> prob[i];
            }
        }

        void buildOBST(){
            //all diagonal 0
            for(int i=0; i<=n; i++){
                cost[i][i] = 0;
            }
            for(int len=1; len<=n; len++){
                for(int i=0; i<=n-len; i++){
                    int j = i+len;
                    cost[i][j] = INT_MAX;

                    float sum = 0;
                    for(int s=i+1; s<=j; s++){
                        sum += prob[s];
                    }

                    for(int r=i+1; r<=j; r++){
                        float c = cost[i][r-1] + cost[r][j];
                        if(c < cost[i][j]){
                            cost[i][j] = c;
                            root[i][j] = r;
                        }
                    }
                    cost[i][j] += sum;
                }
            }
            cout << "\nMinimum cost of OBST: " << cost[0][n] << endl;
        }

        void printTree(int i, int j, int parent, bool isLeft){
            if(i >= j){
                return;
            }
            int r = root[i][j];
            if(parent == -1){
                cout << "Root: " << keys[r] << endl;
            }
            else if(isLeft){
                cout << "Left child of " << keys[parent] << ": " << keys[r] << endl;
            }
            else{
                cout << "Right child of " << keys[parent] << ": " << keys[r] << endl;
            }
            printTree(i, r-1, r, true);
            printTree(r, j, r, false);
        }

        void display(){
            cout << "\nOptimal Binary Search Tree Structure:\n";
            printTree(0, n, -1, false);
        }
};
int main() {
    OBST tree;
    tree.input();
    tree.buildOBST();
    tree.display();
    return 0;
}