#include<iostream>
#include<vector>
using namespace std;

class MarksHeap{
    void maxHeapify(vector<int>& arr, int n, int i){
        int largest = i;
        int left = 2*i+1;
        int right = 2*i+2;

        if(left < n && arr[left] > arr[largest]){
            largest = left;
        }
        if(right < n && arr[right] > arr[largest]){
            largest = right;
        }

        if(largest != i){
            swap(arr[i], arr[largest]);
            maxHeapify(arr, n, largest);
        }
    }

    void minHeapify(vector<int>& arr, int n, int i){
        int smallest = i;
        int left = 2*i+1;
        int right = 2*i+2;

        if(left < n && arr[left] < smallest){
            smallest = left;
        }
        if(right < n && arr[right] < arr[smallest]){
            smallest = right;
        }

        if(smallest != i){
            swap(arr[i], arr[smallest]);
            minHeapify(arr, n, smallest);
        }
    }

    public:
        void acceptMarks(){
            int n;
            cout << "\nEnter number of students: ";
            cin >> n;

            vector<int> marks(n);

            for(int i=0; i<n; i++){
                cout << "\nEnter marks of student " << i+1 << ": ";
                cin >> marks[i];
            }
            
            vector<int> minHeap(marks);
            vector<int> maxHeap(marks);

            //build max heap
            for(int i=n/2-1; i>=0; i--){
                maxHeapify(maxHeap, n, i);
            }

            //build min heap
            for(int i=n/2-1; i>=0; i--){
                minHeapify(minHeap, n, i);
            }

            cout << "Minimum Marks: " << minHeap[0] << endl;
            cout << "Maximum Marks: " << maxHeap[0] << endl;
        }
};
int main(){
    MarksHeap mh;
    mh.acceptMarks();
    return 0;
}