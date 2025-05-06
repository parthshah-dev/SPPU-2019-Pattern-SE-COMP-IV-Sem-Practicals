#include<iostream>
#include<vector>
using namespace std;

struct Patient{
    string name;
    int priority;
};

class Hospital{
    vector<Patient> heap;

    void maxHeapify(int i){
        int largest = i;
        int left = 2*i+1;
        int right = 2*i+2;
        int n = heap.size();

        if(left < n && heap[left].priority > heap[largest].priority){
            largest = left;
        }   
        if(right < n && heap[right].priority > heap[largest].priority){
            largest = right;
        }

        if(largest != i){
            swap(heap[i], heap[largest]);
            maxHeapify(largest);
        }
    }

    void buildMaxHeap(){
        for(int i=heap.size()/2 - 1; i>=0; i--){
            maxHeapify(i);
        }
    }

    public:
        void insert(string& name, int& priority){
            Patient p;
            p.name = name;
            p.priority = priority;
            heap.push_back(p);
            buildMaxHeap();
            cout << "\nPatient added into queue...";
        }

        void serve(){
            if(heap.empty()){
                cout << "No patients to serve.\n";
                return;
            }
            cout << "\nServing patient: " << heap[0].name;

            heap[0] = heap.back();
            heap.pop_back();
            maxHeapify(0);
        }

        void displayQueue(){
            if(heap.empty()){
                cout << "\nQueue is empty!";
                return;
            }
            cout << "\nPatients in the queue:\n";
            for(auto& p : heap){
                cout << "Name: " << p.name << ", Priority: ";
                if(p.priority == 10){
                    cout << "Serious";
                }
                else if(p.priority == 5){
                    cout << "Non-Serious";
                }
                else{
                    cout << "General Checkup";
                }
                cout << endl;
            }
        }
};

int main(){
    Hospital hp;
    string name;
    int priority, ch;

    do{
        cout << "\n--- HOSPITAL PRIORITY QUEUE ---\n" << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. Serve Patient" << endl;
        cout << "3. Display Queue" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter ur choice: ";
        cin >> ch;

        switch(ch)
        {
            case 1: 
                cout << "\nEnter name: ";
                cin >> name;
                cout << "\nEnter Priority: ";
                cin >> priority;
                hp.insert(name, priority);
                break;
            
            case 2: 
                hp.serve();
                break;
    
            case 3:
                hp.displayQueue();
                break;

            case 4:
                cout << "Exiting..";
                break;

            default:
                cout << "Invalid choice!";
        }
    }while(ch != 4);
    
    return 0;
}