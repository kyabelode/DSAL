#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct Employee {
    int id;
    char name[50];
    char designation[50];
    float salary;
};

struct IndexEntry {
    int id;
    long position;
};

void createIndex() {
    ifstream fin("employee_data.dat", ios::binary);
    ofstream fout("employee_index.dat", ios::binary);
    Employee e;
    IndexEntry idx;

    while (fin.read((char*)&e, sizeof(e))) {
        idx.id = e.id;
        idx.position = fin.tellg() - sizeof(e);
        fout.write((char*)&idx, sizeof(idx));
    }

    fin.close();
    fout.close();
}

void addEmployee() {
    ofstream fout("employee_data.dat", ios::app | ios::binary);
    Employee e;

    cout << "Enter ID: ";
    cin >> e.id;
    cin.ignore();
    cout << "Enter Name: ";
    cin.getline(e.name, 50);
    cout << "Enter Designation: ";
    cin.getline(e.designation, 50);
    cout << "Enter Salary: ";
    cin >> e.salary;

    fout.write((char*)&e, sizeof(e));
    fout.close();

    createIndex();  // rebuild index
    cout << "Employee added.\n";
}

void displayEmployee(int empID) {
    ifstream indexFile("employee_index.dat", ios::binary);
    IndexEntry idx;
    bool found = false;
    long pos = -1;

    // Search for ID in index
    while (indexFile.read((char*)&idx, sizeof(idx))) {
        if (idx.id == empID) {
            found = true;
            pos = idx.position;
            break;
        }
    }
    indexFile.close();

    if (found) {
        ifstream dataFile("employee_data.dat", ios::binary);
        Employee e;
        dataFile.seekg(pos);
        dataFile.read((char*)&e, sizeof(e));
        cout << "\nEmployee Found:\n";
        cout << "ID: " << e.id << "\n";
        cout << "Name: " << e.name << "\n";
        cout << "Designation: " << e.designation << "\n";
        cout << "Salary: " << e.salary << "\n";
        dataFile.close();
    } else {
        cout << "Employee not found.\n";
    }
}

void deleteEmployee(int empID) {
    ifstream fin("employee_data.dat", ios::binary);
    ofstream fout("temp.dat", ios::binary);
    Employee e;
    bool found = false;

    while (fin.read((char*)&e, sizeof(e))) {
        if (e.id == empID) {
            found = true;
            cout << "Deleting employee with ID: " << empID << "\n";
            continue;
        }
        fout.write((char*)&e, sizeof(e));
    }

    fin.close();
    fout.close();

    remove("employee_data.dat");
    rename("temp.dat", "employee_data.dat");

    createIndex();  // Rebuild index

    if (!found)
        cout << "Employee not found.\n";
    else
        cout << "Employee deleted successfully.\n";
}

void displayAll() {
    ifstream fin("employee_data.dat", ios::binary);
    Employee e;
    cout << "\n--- All Employees ---\n";
    while (fin.read((char*)&e, sizeof(e))) {
        cout << "\nID: " << e.id
             << "\nName: " << e.name
             << "\nDesignation: " << e.designation
             << "\nSalary: " << e.salary << "\n";
    }
    fin.close();
}

int main() {
    int choice, id;
    do {
        cout << "\n--- Employee Management System (Index Sequential File) ---\n";
        cout << "1. Add Employee\n";
        cout << "2. Display Employee by ID\n";
        cout << "3. Delete Employee\n";
        cout << "4. Display All Employees\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                cout << "Enter Employee ID to search: ";
                cin >> id;
                displayEmployee(id);
                break;
            case 3:
                cout << "Enter Employee ID to delete: ";
                cin >> id;
                deleteEmployee(id);
                break;
            case 4:
                displayAll();
                break;
            case 5:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
