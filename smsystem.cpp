#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>

using namespace std;

const string FILE_NAME = "students.txt";

// =========================================================
// Student record structure
// =========================================================
struct Student {
    int roll;
    string name;
    int age;
    string course;
    float marks;
};

// =========================================================
// Utility: clear bad input from cin
// =========================================================
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// =========================================================
// Utility: safely read an integer
// =========================================================
int readInt(const string &prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a number.\n";
        } else {
            clearInput();
            return value;
        }
    }
}

// =========================================================
// Utility: safely read a float
// =========================================================
float readFloat(const string &prompt) {
    float value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail()) {
            clearInput();
            cout << "Invalid input. Please enter a valid number.\n";
        } else {
            clearInput();
            return value;
        }
    }
}

// =========================================================
// Utility: safely read a line of text (non-empty)
// =========================================================
string readLine(const string &prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin, value);
        if (value.empty()) {
            cout << "Input cannot be empty. Try again.\n";
        } else {
            return value;
        }
    }
}

// =========================================================
// Load all students from the file into a vector
// =========================================================
vector<Student> loadStudents() {
    vector<Student> students;
    ifstream inFile(FILE_NAME);

    if (!inFile) {
        return students; 
    }

    string line;
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string token;
        Student s;

        getline(ss, token, '|'); s.roll = stoi(token);
        getline(ss, token, '|'); s.name = token;
        getline(ss, token, '|'); s.age = stoi(token);
        getline(ss, token, '|'); s.course = token;
        getline(ss, token, '|'); s.marks = stof(token);

        students.push_back(s);
    }

    inFile.close();
    return students;
}

// =========================================================
// Save the entire vector of students back to the file
// =========================================================
void saveStudents(const vector<Student> &students) {
    ofstream outFile(FILE_NAME, ios::trunc);

    for (const auto &s : students) {
        outFile << s.roll << '|' << s.name << '|' << s.age << '|'
                << s.course << '|' << s.marks << '\n';
    }

    outFile.close();
}

// =========================================================
// Print a single student row (formatted)
// =========================================================
void printStudentRow(const Student &s) {
    cout << left
         << setw(8)  << s.roll
         << setw(20) << s.name
         << setw(6)  << s.age
         << setw(15) << s.course
         << setw(8)  << fixed << setprecision(2) << s.marks
         << '\n';
}

void printTableHeader() {
    cout << left
         << setw(8)  << "Roll"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(15) << "Course"
         << setw(8)  << "Marks" << '\n';
    cout << string(57, '-') << '\n';
}

// =========================================================
// 1. Add a new student
// =========================================================
void addStudent() {
    vector<Student> students = loadStudents();
    Student s;

    s.roll = readInt("Enter Roll Number: ");

    // Check for duplicate roll number
    for (const auto &existing : students) {
        if (existing.roll == s.roll) {
            cout << "A student with Roll Number " << s.roll
                 << " already exists.\n";
            return;
        }
    }

    s.name   = readLine("Enter Name: ");
    s.age    = readInt("Enter Age: ");
    s.course = readLine("Enter Course: ");
    s.marks  = readFloat("Enter Marks: ");

    students.push_back(s);
    saveStudents(students);

    cout << "Student record added successfully.\n";
}

// =========================================================
// 2. Display all students
// =========================================================
void displayStudents() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }

    cout << "\n--- All Student Records (" << students.size() << ") ---\n";
    printTableHeader();
    for (const auto &s : students) {
        printStudentRow(s);
    }
}

// =========================================================
// Helper: find index of a student by roll number, -1 if none
// =========================================================
int findStudentIndex(const vector<Student> &students, int roll) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].roll == roll) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

// =========================================================
// 3. Search for a student by roll number
// =========================================================
void searchStudent() {
    vector<Student> students = loadStudents();
    int roll = readInt("Enter Roll Number to search: ");

    int idx = findStudentIndex(students, roll);
    if (idx == -1) {
        cout << "No student found with Roll Number " << roll << ".\n";
        return;
    }

    cout << "\n--- Student Found ---\n";
    printTableHeader();
    printStudentRow(students[idx]);
}

// =========================================================
// 4. Update an existing student's details
// =========================================================
void updateStudent() {
    vector<Student> students = loadStudents();
    int roll = readInt("Enter Roll Number of student to update: ");

    int idx = findStudentIndex(students, roll);
    if (idx == -1) {
        cout << "No student found with Roll Number " << roll << ".\n";
        return;
    }

    cout << "Current details:\n";
    printTableHeader();
    printStudentRow(students[idx]);

    cout << "\nEnter new details (leave blank to keep current value):\n";

    cout << "New Name [" << students[idx].name << "]: ";
    string name;
    getline(cin, name);
    if (!name.empty()) students[idx].name = name;

    cout << "New Age [" << students[idx].age << "] (enter 0 to keep): ";
    string ageInput;
    getline(cin, ageInput);
    if (!ageInput.empty()) {
        try {
            int age = stoi(ageInput);
            if (age != 0) students[idx].age = age;
        } catch (...) {
            cout << "Invalid age, keeping previous value.\n";
        }
    }

    cout << "New Course [" << students[idx].course << "]: ";
    string course;
    getline(cin, course);
    if (!course.empty()) students[idx].course = course;

    cout << "New Marks [" << students[idx].marks << "] (enter -1 to keep): ";
    string marksInput;
    getline(cin, marksInput);
    if (!marksInput.empty()) {
        try {
            float marks = stof(marksInput);
            if (marks != -1) students[idx].marks = marks;
        } catch (...) {
            cout << "Invalid marks, keeping previous value.\n";
        }
    }

    saveStudents(students);
    cout << "Student record updated successfully.\n";
}

// =========================================================
// 5. Delete a student record
// =========================================================
void deleteStudent() {
    vector<Student> students = loadStudents();
    int roll = readInt("Enter Roll Number of student to delete: ");

    int idx = findStudentIndex(students, roll);
    if (idx == -1) {
        cout << "No student found with Roll Number " << roll << ".\n";
        return;
    }

    cout << "Are you sure you want to delete this record? (y/n): ";
    char confirm;
    cin >> confirm;
    clearInput();

    if (confirm == 'y' || confirm == 'Y') {
        students.erase(students.begin() + idx);
        saveStudents(students);
        cout << "Student record deleted successfully.\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

// =========================================================
// Display the main menu
// =========================================================
void showMenu() {
    cout << "\n=========================================\n";
    cout << "       STUDENT MANAGEMENT SYSTEM\n";
    cout << "=========================================\n";
    cout << "1. Add Student\n";
    cout << "2. Display All Students\n";
    cout << "3. Search Student by Roll Number\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "=========================================\n";
}

// =========================================================
// Main program loop
// =========================================================
int main() {
    int choice;
    bool running = true;

    cout << "Welcome to the Student Management System\n";

    while (running) {
        showMenu();
        choice = readInt("Enter your choice (1-6): ");

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayStudents();
                break;
            case 3:
                searchStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                cout << "Exiting program. All data has been saved to '"
                     << FILE_NAME << "'. Goodbye!\n";
                running = false;
                break;
            default:
                cout << "Invalid choice. Please select an option between 1 and 6.\n";
        }
    }

    return 0;
}
