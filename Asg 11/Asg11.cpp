/*
Department maintains a student information. The file contains roll number, name, division and address Allow user to add, delete information of student. Display information of particular employee. If record of student does not exist an appropriate message is displayed. If it is, then the system displays the student details. Use sequential file to main the data.
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student {
public:
    int rollNumber;
    string name;
    string division;
    string address;

    // Function to input student details
    void inputDetails() {
        cout << "Enter roll number: ";
        cin >> rollNumber;
        cin.ignore(); // Ignore newline character

        cout << "Enter name: ";
        getline(cin, name);

        cout << "Enter division: ";
        getline(cin, division);

        cout << "Enter address: ";
        getline(cin, address);
    }

    // Function to display student details
    void displayDetails() {
        cout << "Roll number: " << rollNumber << endl;
        cout << "Name: " << name << endl;
        cout << "Division: " << division << endl;
        cout << "Address: " << address << endl;
    }
};

// Function to add a new student record
void addStudent() {
    Student student;
    student.inputDetails();

    ofstream file("students.dat", ios::binary | ios::app);
    if (file.is_open()) {
        file.write(reinterpret_cast<const char*>(&student), sizeof(Student));
        file.close();
        cout << "Student record added successfully." << endl;
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

// Function to delete a student record based on roll number
void deleteStudent(int rollNumber) {
    ifstream inputFile("students.dat", ios::binary);
    ofstream outputFile("temp.dat", ios::binary);

    if (inputFile.is_open() && outputFile.is_open()) {
        Student student;
        bool found = false;

        while (inputFile.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            if (student.rollNumber != rollNumber) {
                outputFile.write(reinterpret_cast<const char*>(&student), sizeof(Student));
            } else {
                found = true;
            }
        }

        inputFile.close();
        outputFile.close();

        if (found) {
            remove("students.dat");
            rename("temp.dat", "students.dat");
            cout << "Student record deleted successfully." << endl;
        } else {
            remove("temp.dat");
            cout << "Error: Student record not found." << endl;
        }
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

// Function to display student details based on roll number
void displayStudent(int rollNumber) {
    ifstream file("students.dat", ios::binary);

    if (file.is_open()) {
        Student student;
        bool found = false;

        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            if (student.rollNumber == rollNumber) {
                found = true;
                student.displayDetails();
                break;
            }
        }

        file.close();

        if (!found) {
            cout << "Error: Student record not found." << endl;
        }
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

// Function to display all student data
void displayAllStudents() {
    ifstream file("students.dat", ios::binary);

    if (file.is_open()) {
        Student student;

        while (file.read(reinterpret_cast<char*>(&student), sizeof(Student))) {
            student.displayDetails();
            cout << endl;
        }

        file.close();
    } else {
        cout << "Error: Unable to open file." << endl;
    }
}

int main() {
    int choice;
    int rollNumber;

    do {
        cout << "----- Student Information Management System -----";
        cout << "\n1. Add Student";
        cout << "\n2. Delete Student";
        cout << "\n3. Display Student";
        cout << "\n4. Display All Students";
        cout << "\n5. Exit";
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                cout << "Enter roll number of the student to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            case 3:
                cout << "Enter roll number of the student to display: ";
                cin >> rollNumber;
                displayStudent(rollNumber);
                break;
            case 4:
                displayAllStudents();
                break;
            case 5:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
        }
    } while (choice != 5);

    return 0;
}
