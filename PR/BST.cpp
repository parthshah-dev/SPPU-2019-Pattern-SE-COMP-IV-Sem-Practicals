#include<iostream>
using namespace std;

struct Node{
    int data;
    Node* left;
    Node* right;

    Node(int val){
        data = val;
        left = right = nullptr;
    }
};

class BST{
    Node* root;

    public:
        BST(){
            root = nullptr;
        }

        Node* insertNode(Node* node, int val){
            if(node == NULL){
                return new Node(val);
            }
            if(val < node->data){
                node->left = insertNode(node->left, val);
            }
            else{
                node->right = insertNode(node->right, val);
            }
            return node;
        }

        void insert(int val){
            root = insertNode(root, val);
            cout << val << " inserted \n";
        }

        void search(int val){
            Node* temp = root;

            while(temp != NULL){
                if(temp->data == val){
                    cout << val << " found in tree\n";
                    return;
                }
                temp = temp->data < val ? temp->right : temp->left;
            }
            cout << val << " not found in tree\n";
        }

        int findHeight(Node* node){
            if(node == NULL) return 0;

            int left = findHeight(node->left);
            int right = findHeight(node->right);

            return max(left, right) + 1;
        }

        void dispHeight(){
            int height = findHeight(root);
            cout << "Number of nodes in longest path from root: " << height << endl;
        }

        int findMin(Node* node){
            if(node == NULL) return -1;

            while(node->left != nullptr){
                node = node->left;
            }
            return node->data;
        }

        void dispMin(){
            if(root == NULL){
                cout << "Tree is empty" << endl;
                return;
            }
            cout << "Minimum data value in the tree: " << findMin(root) << endl;
        }

        void mirror(Node* node){
            if(node == NULL) return;

            swap(node->left, node->right);
            mirror(node->left);
            mirror(node->right);
        }

        void mirrorTree(){
            mirror(root);
            cout << "Tree has been mirrored.\n";
        }
};
int main() {
    BST tree;
    int choice, val;

    while (true) {
        cout << "\n--- MENU ---\n";
        cout << "1. Insert node\n";
        cout << "2. Search value\n";
        cout << "3. Find height (longest path from root)\n";
        cout << "4. Find minimum value\n";
        cout << "5. Mirror the tree\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                tree.insert(val);
                break;
            case 2:
                cout << "Enter value to search: ";
                cin >> val;
                tree.search(val);
                break;
            case 3:
                tree.dispHeight();
                break;
            case 4:
                tree.dispMin();
                break;
            case 5:
                tree.mirrorTree();
                break;
            case 6:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice.\n";
        }
    }
}