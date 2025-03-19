#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;

// Node structure for Binary Search Tree (BST)
struct Node {
    string name;         // Contact name
    string phone;        // Contact phone number
    Node* left;          // Left child pointer
    Node* right;         // Right child pointer

    Node(string contactName, string contactPhone) {
        name = contactName;
        phone = contactPhone;
        left = right = nullptr;
    }
};

// Class to represent the Contact Manager
class ContactManager {
private:
    unordered_map<int, Node*> contactMap; // Hash Map for fast lookup by contact ID
    Node* root; // Root of the Binary Search Tree (BST)

    // Helper function to insert into BST
    Node* insert(Node* node, string name, string phone) {
        if (node == nullptr) {
            return new Node(name, phone);
        }
        if (name < node->name) {
            node->left = insert(node->left, name, phone);
        } else if (name > node->name) {
            node->right = insert(node->right, name, phone);
        }
        return node;
    }

    // Helper function to perform an in-order traversal (to display BST in alphabetical order)
    void inorder(Node* node) {
        if (node == nullptr) {
            return;
        }
        inorder(node->left); // Visit left subtree
        cout << "Name: " << node->name << ", Phone: " << node->phone << endl; // Visit node
        inorder(node->right); // Visit right subtree
    }

public:
    ContactManager() {
        root = nullptr;
    }

    // Function to add contact by ID (stores in HashMap and BST)
    void addContact(int id, string name, string phone) {
        Node* newContact = new Node(name, phone);
        contactMap[id] = newContact;
        root = insert(root, name, phone); // Insert contact in BST (sorted by name)
    }

    // Function to find contact by ID using Hash Map
    void findContactByID(int id) {
        if (contactMap.find(id) != contactMap.end()) {
            cout << "Contact Found: ID: " << id << ", Name: " << contactMap[id]->name << ", Phone: " << contactMap[id]->phone << endl;
        } else {
            cout << "Contact with ID " << id << " not found!" << endl;
        }
    }

    // Function to find contact by name using BST
    void findContactByName(string name) {
        Node* current = root;
        while (current != nullptr) {
            if (current->name == name) {
                cout << "Contact Found: Name: " << current->name << ", Phone: " << current->phone << endl;
                return;
            } else if (name < current->name) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        cout << "Contact with name " << name << " not found!" << endl;
    }

    // Function to delete a contact by ID
    void deleteContactByID(int id) {
        if (contactMap.find(id) != contactMap.end()) {
            contactMap.erase(id);
            cout << "Contact with ID " << id << " has been deleted." << endl;
        } else {
            cout << "Contact with ID " << id << " not found!" << endl;
        }
    }

    // Function to display all contacts in alphabetical order using BST
    void displayAllContacts() {
        cout << "Displaying all contacts in alphabetical order: " << endl;
        inorder(root);
    }
};

// Main function to demonstrate the Contact Manager system with user input
int main() {
    ContactManager cm;
    int choice, id;
    string name, phone;

    while (true) {
        // Display menu
        cout << "\nContact Manager System\n";
        cout << "1. Add Contact\n";
        cout << "2. Find Contact by ID\n";
        cout << "3. Find Contact by Name\n";
        cout << "4. Delete Contact by ID\n";
        cout << "5. Display All Contacts\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                // Add contact
                cout << "Enter Contact ID: ";
                cin >> id;
                cin.ignore();  // To ignore the newline character left by cin
                cout << "Enter Contact Name: ";
                getline(cin, name);
                cout << "Enter Contact Phone Number: ";
                getline(cin, phone);
                cm.addContact(id, name, phone);
                cout << "Contact added successfully!" << endl;
                break;

            case 2:
                // Find contact by ID
                cout << "Enter Contact ID to search: ";
                cin >> id;
                cm.findContactByID(id);
                break;

            case 3:
                // Find contact by name
                cin.ignore();  // To ignore the newline character left by cin
                cout << "Enter Contact Name to search: ";
                getline(cin, name);
                cm.findContactByName(name);
                break;

            case 4:
                // Delete contact by ID
                cout << "Enter Contact ID to delete: ";
                cin >> id;
                cm.deleteContactByID(id);
                break;

            case 5:
                // Display all contacts
                cm.displayAllContacts();
                break;

            case 6:
                // Exit
                cout << "Exiting Contact Manager system." << endl;
                return 0;

            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
