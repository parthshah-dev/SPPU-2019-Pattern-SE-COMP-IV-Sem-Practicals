#include<iostream>
#include<cctype>
#include<cstring>
using namespace std;

struct Node{
    char data;
    Node *right;
    Node *left;
};

struct Stack{   
    Node* data[20];
    int top = -1;

    void push(Node* node){
        data[++top] = node;
    }

    Node* pop(){
        if(top == -1) return nullptr;
        return data[top--];
    }
};

Node* buildTree(char expr[]){
    Stack st;
    int len = strlen(expr);

    for(int i=len-1; i>=0; i--){
        Node* newNode = new Node{expr[i], nullptr, nullptr};

        if(isalpha(expr[i])){
            st.push(newNode);
        }
        else{
            newNode->left = st.pop();
            newNode->right = st.pop();
            st.push(newNode);
        }
    }

    return st.pop(); //root of the tree
}

void postOrder(Node* root){
    if(root == nullptr) return;

    postOrder(root->left);
    postOrder(root->right);
    cout << root->data << " ";
}

void deleteTree(Node* node){
    if(node == nullptr){
        return;
    }

    deleteTree(node->left);
    deleteTree(node->right);
    cout << "Deleting node: " << node->data << endl;
    delete node;
}

int main(){
    char expr[20];
    Node* root = nullptr;
    int ch;

    do{
        cout << "\n--- Menu ---\n";
        cout << "1. Build Expression Tree\n";
        cout << "2. Postorder Traversal\n";
        cout << "3. Delete Tree\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> ch;

        switch (ch)
        {
            case 1: cout << "Enter prefix expression: ";
                    cin >> expr;
                    root = buildTree(expr);
                    cout << "Tree built!\n";
                    break;

            case 2: 
                    if(root){
                        cout << "Postorder Traversal: ";
                        postOrder(root);
                        cout << endl;
                    }
                    else{
                        cout << "Tree is empty.\n";
                    }
                    break;

            case 3: 
                    if(root){
                        deleteTree(root);
                        root = nullptr;
                    }else{
                        cout << "Tree is already deleted.\n";
                    }
                    break;

            case 4:
                    cout << "Exiting...";
                    break;
            
            default:
                    cout << "Invalid choice.\n";
        }
    }while(ch != 4);

    return 0;
}