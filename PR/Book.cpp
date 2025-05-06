#include<iostream>
using namespace std;

struct Node{
    string name;
    Node *child[10];
    int ch_count;
};

class Tree{
    public:
        Node* root;
        
        Tree(){
            root = nullptr;
        }
        void createTree();
        void display(Node* r);
};

void Tree::createTree(){
    root = new Node;

    cout << "Enter name of the book: ";
    getline(cin, root->name);
    cout << "\nEnter number of chapters: ";
    cin >> root->ch_count;
    cin.ignore();

    for(int i=0; i<root->ch_count; i++){
        root->child[i] = new Node;

        cout << "\nEnter name of the chapter "<< i+1 << ": ";
        getline(cin, root->child[i]->name);

        cout << "\nEnter number of sections in the chapter " << root->child[i]->name << " :";
        cin >> root->child[i]->ch_count;
        cin.ignore();

        for(int j=0; j<root->child[i]->ch_count; j++){
            root->child[i]->child[j] = new Node;

            cout << "\nEnter name of section " << j+1 << ": ";
            getline(cin, root->child[i]->child[j]->name);
        }
    }
} 

void Tree::display(Node* r){
    if(r == nullptr){
        cout << "\nNo data present!";
        return;
    }

    cout << "\nBook name: " << r->name;

    for(int i=0; i<r->ch_count; i++){
        cout << "\n Chapter : " << i+1 << r->child[i]->name;

        for(int j=0; j<r->child[i]->ch_count; j++){
            cout << "\n     Section name: " << j+1 << r->child[i]->child[j]->name;
        }
    }
}

int main() {
    Tree gt;
    int choice;

    while (true) {
        cout << "\n----- Menu -----\n";
        cout << "1. Create tree\n";
        cout << "2. Display book hierarchy\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                gt.createTree();
                break;
            case 2:
                gt.display(gt.root);
                break;
            case 3:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice! Try again...\n";
        }
    }
}