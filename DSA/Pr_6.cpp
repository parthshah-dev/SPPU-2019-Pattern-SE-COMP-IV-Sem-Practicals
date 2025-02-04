#include<iostream>
using namespace std;

struct Node {    
    int data;
    Node* left;
    Node* right;
    
    Node(int val) : data(val), left(NULL), right(NULL) {}
};

class BST {
    private:
        Node* root;

    public:
        BST() {        
            root = NULL;
        }
        
        void createRoot() {
            if (root == NULL) {
                root = new Node(0);
                cout << "Enter value of root node: ";
                cin >> root->data;
                cout << "Root node with value " << root->data << " created!" << endl;
            }
        }
        
        void insertNode(int data) {
            Node* newNode = new Node(data);
            if (root == NULL) {
                createRoot();
                return;
            }
            Node* temp = root;
            while (temp != NULL) {
                if (data < temp->data) {
                    if (temp->left == NULL) {
                        temp->left = newNode;
                        cout << data << " inserted in left subtree." << endl;
                        return;
                    }
                    else {
                        temp = temp->left;
                    }
                }
                else {
                    if (temp->right == NULL) {
                        temp->right = newNode;
                        cout << data << " inserted in right subtree." << endl;
                        return;
                    }
                    else {
                        temp = temp->right;
                    }
                }
            }
        }
        
        void searchElement(int data) {
            if (root == NULL) {
                cout << "Binary Search Tree is empty." << endl;
                return;
            }
            Node* temp = root;
            while (temp != NULL) {
                if (temp->data == data) {
                    cout << "Element " << data << " found in the tree!" << endl;
                    return;
                }
                else if (data < temp->data) {
                    temp = temp->left;
                }
                else {
                    temp = temp->right;
                }
            }
            cout << "Element " << data << " not found in the tree!" << endl;
        }
        
        void displayTree() {
            if (root == NULL) {
                cout << "Binary Search Tree is empty." << endl;
                return;
            }
            cout << "In-order traversal: ";
            inOrderTraversal(root);
            cout << endl;
        }

        void inOrderTraversal(Node* node) {
            if (node == NULL) return;
            inOrderTraversal(node->left);
            cout << node->data << " ";
            inOrderTraversal(node->right);
        }

        int findHeight(Node* node) {
            if (node == NULL) return 0;
            int leftHeight = findHeight(node->left);
            int rightHeight = findHeight(node->right);
            return max(leftHeight, rightHeight) + 1;
        }

        void displayHeight() {
            cout << "Height of the tree: " << findHeight(root) << endl;
        }

        int findMin(Node* node) {
            if (node == NULL) return -1;
            while (node->left != NULL) {
                node = node->left;
            }
            return node->data;
        }

        void displayMinValue() {
            if (root == NULL) {
                cout << "Binary Search Tree is empty." << endl;
                return;
            }
            cout << "Minimum data value in the tree: " << findMin(root) << endl;
        }

        void mirrorTree(Node* node) {
            if (node == NULL) return;
            swap(node->left, node->right);
            mirrorTree(node->left);
            mirrorTree(node->right);
        }

        void mirror() {
            mirrorTree(root);
            cout << "Tree structure has been mirrored!" << endl;
        }
};

int main() {
    BST obj;
    int choice, data;

    while (true) {
        cout << "\n---- MENU ----\n";
        cout << "1. Create root node\n";
        cout << "2. Insert node\n";
        cout << "3. Search for an element\n";
        cout << "4. Display tree (In-order traversal)\n";
        cout << "5. Find Number of Nodes in Longest Path (Tree Height)\n";
        cout << "6. Find Minimum Data Value in the Tree\n";
        cout << "7. Mirror the Tree Structure\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                obj.createRoot();
                break;
            case 2:
                cout << "Enter data to insert: ";
                cin >> data;
                obj.insertNode(data);
                break;
            case 3:
                cout << "Enter data to search: ";
                cin >> data;
                obj.searchElement(data);
                break;
            case 4:
                obj.displayTree();
                break;
            case 5:
                obj.displayHeight();
                break;
            case 6:
                obj.displayMinValue();
                break;
            case 7:
                obj.mirror();
                break;
            case 8:
                cout << "Exiting program...\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
