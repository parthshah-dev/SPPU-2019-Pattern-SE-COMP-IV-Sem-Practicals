#include <iostream>
#include <cstring>
#include <cctype>

using namespace std;

struct Node {
    char data;
    Node *left, *right;
};

class ExpressionTree {
    public:
        Node* root;
        ExpressionTree() {
            root = nullptr;
        }
        void buildTreeFromPrefix(char[]);
        void postOrderTraversal(Node*);
        void deleteTree(Node*);
};

class Stack {
    Node *stackData[30];
    int top;

    public:
        Stack() {
            top = -1;
        } 
        bool isEmpty() { return top == -1; }

        void push(Node *node) {
            stackData[++top] = node;
        }

        Node* pop() {
            return isEmpty() ? nullptr : stackData[top--]; 
        }
};

void ExpressionTree::buildTreeFromPrefix(char prefixExpr[]) {
    Stack st;
    int len = strlen(prefixExpr);
    
    cout << "\nConstructing Expression Tree Step-by-Step:\n";
    
    for (int i = len - 1; i >= 0; i--) {
        Node *node = new Node;
        node->left = node->right = nullptr;
        node->data = prefixExpr[i];
        
        if (isalpha(prefixExpr[i])) { 
            st.push(node);
            cout << "Inserted operand node: " << prefixExpr[i] << endl;
        } else if (prefixExpr[i] == '+' || prefixExpr[i] == '-' || prefixExpr[i] == '*' || prefixExpr[i] == '/') { 
            if (!st.isEmpty()) node->left = st.pop();
            if (!st.isEmpty()) node->right = st.pop();
            st.push(node);
            cout << "Created operator node '" << prefixExpr[i] << "' with left child '"
                 << (node->left ? node->left->data : ' ') << "' and right child '"
                 << (node->right ? node->right->data : ' ') << "'\n";
        }
    }
    root = st.pop();
    cout << "Expression Tree Constructed Successfully\n";
}

void ExpressionTree::postOrderTraversal(Node *node) {
    if (!node) return;
    
    Stack st1, st2;
    st1.push(node);
    
    cout << "\nPostorder Traversal: ";
    
    while (!st1.isEmpty()) {
        Node *currNode = st1.pop();
        st2.push(currNode);
        
        if (currNode->left) st1.push(currNode->left);
        if (currNode->right) st1.push(currNode->right);
    }

    while (!st2.isEmpty()) {
        cout << st2.pop()->data << " "; 
    }
    cout << endl;
}

void ExpressionTree::deleteTree(Node *node) {
    if (node == nullptr) return;

    deleteTree(node->left);
    deleteTree(node->right);

    cout << "Deleting Node: " << node->data << endl;
    delete node;
}

int main() {
    char prefixExpression[20];
    int choice;
    ExpressionTree expressionTree;

    do {
        cout << "\n--- Menu ---\n";
        cout << "1. Build Expression Tree from Prefix Expression\n";
        cout << "2. Perform Post-Order Traversal\n";
        cout << "3. Delete Expression Tree\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch(choice) {
            case 1:
                cout << "Enter Prefix Expression: ";
                cin >> prefixExpression;
                expressionTree.buildTreeFromPrefix(prefixExpression);
                break;

            case 2:
                if (expressionTree.root == nullptr) {
                    cout << "Tree is empty. Build the tree first.\n";
                } else {
                    expressionTree.postOrderTraversal(expressionTree.root);
                }
                break;

            case 3:
                if (expressionTree.root == nullptr) {
                    cout << "Tree is empty. Nothing to delete.\n";
                } else {
                    expressionTree.deleteTree(expressionTree.root);
                    expressionTree.root = nullptr;
                }
                break;

            case 4:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}
