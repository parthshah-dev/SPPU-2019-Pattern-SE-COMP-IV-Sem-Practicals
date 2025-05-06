#include<iostream>
using namespace std;

struct Node{
    string key, meaning;
    Node* left;
    Node* right;
    int height;
};

class AVLTree{
    Node* root;

    int height(Node* n){
        return n ? n->height : 0;
    }

    int balanceFactor(Node* n){
        return n ? height(n->left) - height(n->right) : 0;
    }

    int max(int a, int b){
        return a > b ? a : b;
    }

    Node* rightRotate(Node* y){
        Node* x = y -> left;
        Node* T2 = x -> right;
        x->right = y;
        y->left = T2;
        y->height = 1 + max(height(y->left), height(y->right));
        x->height = 1 + max(height(x->left), height(x->right));
        return x;
    }

    Node* leftRotate(Node* x){
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = 1 + max(height(x->left), height(x->right));
        y->height = 1 + max(height(y->left), height(y->right));
        return y;
    }

    Node* insert(Node* node, string& key, string& meaning){
        if(node == nullptr){
            Node* newNode = new Node{key, meaning, NULL, NULL, 1};
            return newNode;
        }

        if(key < node->key){
            node->left = insert(node->left, key, meaning);
        }
        else if(key > node->key){
            node->right = insert(node->right, key, meaning);
        }
        else{
            cout << "Keyword already exists. Use update option.\n";
            return node;
        }

        node->height = 1 + max(height(node->left), height(node->right));
        int bf = balanceFactor(node);

        if(bf > 1 && key < node->left->key){
            return rightRotate(node);
        }
        if(bf < -1 && key > node->right->key){
            return leftRotate(node);
        }
        if(bf > 1 && key > node->left->key){
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if(bf < -1 && key < node->right->key){
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    void inorder(Node* root){
        if(root == nullptr){
            return;
        }
        inorder(root->left);
        cout << root->key << " : " << root->meaning << endl;
        inorder(root->right);
    }

    void revInorder(Node* root){
        if(root == nullptr){
            return;
        }
        revInorder(root->right);
        cout << root->key << " : " << root->meaning << endl;
        revInorder(root->left);
    }

    Node* minVal(Node* n){
        Node* cur = n;
        while(cur -> left){
            cur = cur -> left;
        }
        return cur;
    }

    Node* delNode(Node* root, string& key){
        if(root == nullptr){
            return root;
        }
        if(key < root -> key){
            root -> left = delNode(root->left, key);
        }
        else if(key > root -> key){
            root -> right = delNode(root->right, key);
        }
        else{
            //node has 0 or 1 child
            if(!root->left || !root->right){
                Node *temp = root->left ? root->left : root->right;
                delete root;
                return temp;
            }
            //node has 2 children
            Node* temp = minVal(root->right);
            root -> key = temp -> key;
            root -> meaning = temp -> meaning;
            root -> right = delNode(root->right, temp->key);

            root -> height = 1 + max(height(root->left), height(root->right));
            int bf = balanceFactor(root);

            if(bf > 1 && balanceFactor(root->left) >= 0){
                return rightRotate(root);
            }
            if(bf < -1 && balanceFactor(root -> right) <= 0){
                return leftRotate(root);
            }
            if(bf > 1 && balanceFactor(root->left) < 0){
                root->left = leftRotate(root->left);
                return rightRotate(root);
            }
            if(bf < -1 && balanceFactor(root->right) > 0){
                root -> right = rightRotate(root->right);
                return leftRotate(root);
            }
        }
        return root;
    }

    bool search(Node* root, string& key, int& comparisons){
        if(root == nullptr){
            return false;
        }
        comparisons++;
        if(key == root->key){
            return true;
        }
        else if(key < root->key){
            return search(root->left, key, comparisons);
        }
        else{
            return search(root->right, key, comparisons);
        }
    }

    void update(Node* root, string& key){
        if(root == nullptr){
            return;
        }
        if(key == root->key){
            cout << "Enter new meaning: ";
            cin >> root->meaning;
            cout << "Updated successfully.\n";
        }
        else if(key < root->key){
            update(root->left, key);
        }
        else{
            update(root->right, key);
        }
    }

    public:
        AVLTree(){
            root = NULL;
        }

        void insertKey(){
            string k, m;
            cout << "\nEnter keyword: ";
            cin >> k; 
            cout << "\nEnter meaning: ";
            cin >> m;
            
            root = insert(root, k, m);
        }

        void deleteKey(){
            string k;
            cout << "\nEnter keyword to delete: ";
            cin >> k;

            root = delNode(root, k);
        }

        void updateKey(){
            string k;
            cout << "\nEnter keyword to update: ";
            cin >> k;
            update(root, k);
        }

        void searchKey(){
            string k;
            cout << "\nEnter keyword to search: ";
            cin >> k;
            int comparison = 0;
            if(search(root, k, comparison)){
                cout << "Found in " << comparison << " comparisons.\n";
            }
            else{
                cout << "Not found. Comparisons done: " << comparison << endl;
            } 
        }

        void dispAscending(){
            cout << "\n--- Ascending Order ---\n";
            inorder(root);
        }

        void dispDescending(){
            cout << "\n--- Descending Order ---\n";
            revInorder(root);
        }
};


int main() {
    AVLTree dict;
    int choice;
    char ch;
    do {
        cout << "\n---- Dictionary Menu ----\n";
        cout << "1. Add Keyword\n2. Delete Keyword\n3. Update Meaning\n4. Search Keyword\n5. Display Ascending\n6. Display Descending\n7. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: dict.insertKey(); break;
            case 2: dict.deleteKey(); break;
            case 3: dict.updateKey(); break;
            case 4: dict.searchKey(); break;
            case 5: dict.dispAscending(); break;
            case 6: dict.dispDescending(); break;
            case 7: cout << "\nExiting..."; break;
            default: cout << "Invalid choice\n";
        }
    } while (ch != 7);

    return 0;
}