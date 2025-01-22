#include<iostream>
using namespace std;

struct Node {
    string ch_name;
    struct Node *child[10];
    int ch_count;
} *root;

class GT {
public:
    void create_tree();
    void display(Node *r1);
    int height(Node *r1);

    GT() {
        root = NULL;
    }
};

void GT::create_tree() {
    root = new Node;
    cout << "Enter name of the book: ";
    cin.ignore();
    getline(cin, root->ch_name);
    cout << "Enter number of chapters: ";
    cin >> root->ch_count;

    for (int i = 0; i < root->ch_count; i++) {
        root->child[i] = new Node;
        cout << "Enter name of chapter " << i + 1 << ": ";
        cin.ignore();
        getline(cin, root->child[i]->ch_name);
        cout << "Enter number of sections in chapter " << root->child[i]->ch_name << ": ";
        cin >> root->child[i]->ch_count;

        for (int j = 0; j < root->child[i]->ch_count; j++) {
            root->child[i]->child[j] = new Node;
            cout << "Enter section " << j + 1 << " name: ";
            cin.ignore();
            getline(cin, root->child[i]->child[j]->ch_name);
        }
    }
}

void GT::display(Node *r1) {
    if (r1 != NULL) {
        cout << "\n------- BOOK HIERARCHY -------";
        cout << "\nBook Title: " << r1->ch_name;
        int tchapters = r1->ch_count;

        for (int i = 0; i < tchapters; i++) {
            cout << "\nChapter " << i + 1 << ": " << r1->child[i]->ch_name;
            cout << "\nSections:";
            for (int j = 0; j < r1->child[i]->ch_count; j++) {
                cout << "\n - " << r1->child[i]->child[j]->ch_name;
            }
            cout << endl;
        }
    }
}

int GT::height(Node *r1) {
    if (r1 == NULL) return 0;
    int max_height = 0;
    for (int i = 0; i < r1->ch_count; i++) {
        int sub_tree_height = height(r1->child[i]);
        if (sub_tree_height > max_height) {
            max_height = sub_tree_height;
        }
    }
    return max_height + 1;
}

int main() {
    int choice;
    GT gt;

    while (true) {
        cout << "------------------" << endl;
        cout << "Book Tree Creation" << endl;
        cout << "------------------" << endl;
        cout << "1. Create tree" << endl;
        cout << "2. Display book hierarchy" << endl;
        cout << "3. Height of tree" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                gt.create_tree();
                break;
            case 2:
                gt.display(root);
                break;
            case 3:
                cout << "\nHeight of the tree: " << gt.height(root) << endl;
                break;
            case 4:
                cout << "Exiting program..." << endl;
                return 0;
            default:
                cout << "Invalid choice! Try again..." << endl;
        }
    }
}

