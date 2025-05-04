#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Student {
    int roll;
    char name[50];
    char division;
    char address[100];
};

void addStudent() {
    ofstream fout("students.txt", ios::app | ios::binary);
    Student s;

    cout << "Enter Roll No: ";
    cin >> s.roll;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(s.name, 50);
    cout << "Enter Division: ";
    cin >> s.division;
    cin.ignore();
    cout << "Enter Address: ";
    cin.getline(s.address, 100);

    fout.write((char*)&s, sizeof(s));
    fout.close();
    cout << "Student record added.\n";
}

void displayStudent(int rollNo) {
    ifstream fin("students.txt", ios::in | ios::binary);
    Student s;
    bool found = false;

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.roll == rollNo) {
            cout << "\nRecord Found:\n";
            cout << "Roll No: " << s.roll << "\n";
            cout << "Name: " << s.name << "\n";
            cout << "Division: " << s.division << "\n";
            cout << "Address: " << s.address << "\n";
            found = true;
            break;
        }
    }

    fin.close();
    if (!found)
        cout << "Student record not found.\n";
}

void deleteStudent(int rollNo) {
    ifstream fin("students.txt", ios::in | ios::binary);
    ofstream fout("temp.txt", ios::out | ios::binary);
    Student s;
    bool found = false;

    while (fin.read((char*)&s, sizeof(s))) {
        if (s.roll == rollNo) {
            found = true;
            cout << "Deleting record of roll number " << s.roll << "\n";
            continue; // skip writing this record
        }
        fout.write((char*)&s, sizeof(s));
    }

    fin.close();
    fout.close();

    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (!found)
        cout << "Record not found.\n";
    else
        cout << "Record deleted successfully.\n";
}

int main() {
    int choice, roll;

    do {
        cout << "\n--- Student Information System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display Student by Roll No\n";
        cout << "3. Delete Student\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter Roll No to search: ";
                cin >> roll;
                displayStudent(roll);
                break;
            case 3:
                cout << "Enter Roll No to delete: ";
                cin >> roll;
                deleteStudent(roll);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }
    } while (choice != 4);

    return 0;
}
