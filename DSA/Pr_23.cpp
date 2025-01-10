//Program to implement file handling functions

#include<iostream>
#include<fstream>
#include<string>
using namespace std;

struct Student {
    string name;
    int rollno;
    char div;
    string address;
};

// Function to add student data
void addData(int rollno, string name, string address, char div) {
    fstream writeobj;
    writeobj.open("student.txt", ios::out | ios::app);

    if (writeobj.is_open()) {
        writeobj << rollno << "\n" << name << "\n" << div << "\n" << address << "\n";
        cout << "Student data added successfully!\n";
        writeobj.close();
    } else {
        cout << "Error in opening the file!\n";
    }
}

// Function to read student data
void readData(int rollno) {
    fstream readobj;
    readobj.open("student.txt", ios::in);

    if (readobj.is_open()) {
        bool found = false;
        Student s;

        while (readobj >> s.rollno) {
            readobj.ignore(); 
            getline(readobj, s.name); 
            readobj >> s.div;
            readobj.ignore();  
            getline(readobj, s.address); 

            if (s.rollno == rollno) {
                found = true;
                cout << "\nDetails of Roll No " << rollno << " are:\n";
                cout << "Roll No: " << s.rollno << "\nName: " << s.name 
                     << "\nDivision: " << s.div << "\nAddress: " << s.address << endl;
                break;
            }
        }

        if (!found) {
            cout << "No record found for Roll No " << rollno << endl;
        }

        readobj.close();
    } else {
        cout << "Error in opening the file!" << endl;
    }
}

// Function to delete student data
void deleteData(int rollno) {
    fstream readobj, writeobj;
    readobj.open("student.txt", ios::in);

    if (readobj.is_open()) {
        writeobj.open("temp.txt", ios::out | ios::app);

        bool found = false;
        Student s;

        while (readobj >> s.rollno) {
            readobj.ignore(); 
            getline(readobj, s.name); 
            readobj >> s.div;
            readobj.ignore();  
            getline(readobj, s.address);  
            if (s.rollno == rollno) {
                found = true;
                continue; 
            } else {
                writeobj << s.rollno << "\n" << s.name << "\n" << s.div << "\n" << s.address << "\n";
            }
        }

        if (found) {
            cout << "Record with Roll No " << rollno << " has been deleted!" << endl;
        } else {
            cout << "No record found for Roll No " << rollno << endl;
        }

        readobj.close();
        writeobj.close();

        remove("student.txt");  
        rename("temp.txt", "student.txt");  
    } else {
        cout << "Error in opening the file!" << endl;
    }
}

int main() {
    string name, address;
    int rollno;
    char div;
    int choice;

    while (true) {
        cout << "\n\n****** MENU ******";
        cout << "\n1. Add Student Data\n2. Read Student Data\n3. Delete Student Data\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();  
        switch (choice) {
            case 1:
                cout << "Enter Name: ";
                getline(cin, name);

                cout << "Enter Roll No: ";
                cin >> rollno;

                cout << "Enter Division: ";
                cin >> div;

                cout << "Enter Address: ";
                cin.ignore();  
                getline(cin, address);

                addData(rollno, name, address, div);
                break;

            case 2:
                cout << "Enter Roll No to search: ";
                cin >> rollno;

                readData(rollno);
                break;

            case 3:
                cout << "Enter Roll No to delete: ";
                cin >> rollno;

                deleteData(rollno);
                break;

            case 4:
                cout << "Thank you for using the program!\n";
                return 0;

            default:
                cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}

