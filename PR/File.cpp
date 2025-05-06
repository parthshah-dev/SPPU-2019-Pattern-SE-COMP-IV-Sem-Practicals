#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student{
    int roll;
    string name, address;

    public:

        Student(){
            roll = 0;
            name = address = "";
        }

        void addData(int r, string n, string add){
            fstream wobj;
            wobj.open("student.txt", ios::out | ios::app);

            if(wobj.is_open()){
                wobj << r << "\n" << n << "\n" << add << "\n";
                cout << "Data added successfully" << endl;
            }
            else{
                cout << "Error occured! Try again" << endl;
            }
            wobj.close();
        }

        void readData(int roll){
            fstream robj;
            robj.open("student.txt", ios::in);

            if(!robj.is_open()){
                cout << "Error in opening file!" << endl;
                return;
            }

            int r;
            string n, a;
            bool found = false;

            while(robj >> r){
                robj.ignore();
                getline(robj, n);
                getline(robj, a);

                if(r == roll){
                    found = true;
                    cout << "Student Found: " << endl;
                    cout << "Roll No: " << r << endl;
                    cout << "Name: " << n << endl;
                    cout << "Address: " << a << endl;
                    break;
                }
            }
            if(!found){
                cout << "Student with roll no " << roll << " not found" << endl;
            }
            robj.close();
        }
        
        void deleteData(int roll){
            fstream fin;
            fstream fout;
            
            fin.open("student.txt", ios::in);
            fout.open("temp.txt", ios::out);

            if(!fin.is_open() || !fout.is_open()){
                cout << "Error occured! Try again" << endl;
                return;
            }

            int r; 
            string n, a;
            bool found = false;

            while(fin >> r){
                fin.ignore();
                getline(fin, n);
                getline(fin, a);

                if(r == roll){
                    found = true;
                    continue;
                }

                fout << r << "\n" << n << "\n" << a << "\n";
            }

            if(!found){
                cout << "Student with roll no " << roll << " not found" << endl;
            }
            else{
                cout << "Student data deleted!" << endl;
            }
            fin.close();
            fout.close();

            remove("student.txt");
            rename("temp.txt", "student.txt");
        }
};

int main() {
    Student s;
    int choice;

    while (true) {
        cout << "\n---- STUDENT MANAGEMENT ----\n";
        cout << "1. Add Student\n";
        cout << "2. Read Student by Roll No\n";
        cout << "3. Delete Student by Roll No\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int roll;
            string name, address;
            cout << "Enter Roll No: ";
            cin >> roll;
            cin.ignore();
            cout << "Enter Name: ";
            getline(cin, name);
            cout << "Enter Address: ";
            getline(cin, address);
            s.addData(roll, name, address);
        }
        else if (choice == 2) {
            int roll;
            cout << "Enter Roll No to search: ";
            cin >> roll;
            s.readData(roll);
        }
        else if (choice == 3) {
            int roll;
            cout << "Enter Roll No to delete: ";
            cin >> roll;
            s.deleteData(roll);
        }
        else if (choice == 4) {
            cout << "Exiting program...\n";
            break;
        }
        else {
            cout << "Invalid choice! Try again.\n";
        }
    }

    return 0;
}