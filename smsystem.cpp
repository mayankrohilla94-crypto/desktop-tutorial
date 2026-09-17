#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>

using namespace std;

const string FILE_NAME = "students.txt";
const string CSV_FILE_NAME = "students.csv";

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
// Utility Functions
// =========================================================

void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Read integer safely
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

// Read integer within range
int readIntRange(const string &prompt, int minValue, int maxValue) {
    while (true) {
        int value = readInt(prompt);

        if (value >= minValue && value <= maxValue) {
            return value;
        }

        cout << "Please enter a value between "
             << minValue << " and " << maxValue << ".\n";
    }
}

// Read float safely
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

// Read marks between 0 and 100
float readMarks(const string &prompt) {
    while (true) {
        float marks = readFloat(prompt);

        if (marks >= 0 && marks <= 100) {
            return marks;
        }

        cout << "Marks must be between 0 and 100.\n";
    }
}

// Read non-empty text
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

// Convert string to lowercase
string toLowerCase(string text) {
    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c) {
            return tolower(c);
        }
    );

    return text;
}

// =========================================================
// Grade Calculation
// =========================================================

string getGrade(float marks) {
    if (marks >= 90)
        return "A+";
    else if (marks >= 80)
        return "A";
    else if (marks >= 70)
        return "B";
    else if (marks >= 60)
        return "C";
    else if (marks >= 50)
        return "D";
    else
        return "F";
}

// =========================================================
// File Handling
// =========================================================

vector<Student> loadStudents() {
    vector<Student> students;

    ifstream inFile(FILE_NAME);

    if (!inFile) {
        return students;
    }

    string line;

    while (getline(inFile, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);
        string token;

        Student s;

        try {
            getline(ss, token, '|');
            s.roll = stoi(token);

            getline(ss, token, '|');
            s.name = token;

            getline(ss, token, '|');
            s.age = stoi(token);

            getline(ss, token, '|');
            s.course = token;

            getline(ss, token, '|');
            s.marks = stof(token);

            students.push_back(s);
        }
        catch (...) {
            cout << "Warning: Skipping invalid record.\n";
        }
    }

    inFile.close();

    return students;
}

void saveStudents(const vector<Student> &students) {
    ofstream outFile(FILE_NAME, ios::trunc);

    if (!outFile) {
        cout << "Error: Could not save student records.\n";
        return;
    }

    for (const auto &s : students) {
        outFile
            << s.roll << '|'
            << s.name << '|'
            << s.age << '|'
            << s.course << '|'
            << s.marks
            << '\n';
    }

    outFile.close();
}

// =========================================================
// Display Functions
// =========================================================

void printTableHeader() {
    cout << left
         << setw(8)  << "Roll"
         << setw(20) << "Name"
         << setw(6)  << "Age"
         << setw(20) << "Course"
         << setw(10) << "Marks"
         << setw(8)  << "Grade"
         << '\n';

    cout << string(72, '-') << '\n';
}

void printStudentRow(const Student &s) {
    cout << left
         << setw(8)  << s.roll
         << setw(20) << s.name
         << setw(6)  << s.age
         << setw(20) << s.course
         << setw(10) << fixed << setprecision(2) << s.marks
         << setw(8)  << getGrade(s.marks)
         << '\n';
}

void displayStudentDetails(const Student &s) {
    cout << "\n-----------------------------------\n";
    cout << "Student Details\n";
    cout << "-----------------------------------\n";

    cout << "Roll Number : " << s.roll << '\n';
    cout << "Name        : " << s.name << '\n';
    cout << "Age         : " << s.age << '\n';
    cout << "Course      : " << s.course << '\n';
    cout << "Marks       : " << fixed << setprecision(2)
         << s.marks << '\n';
    cout << "Grade       : " << getGrade(s.marks) << '\n';

    cout << "-----------------------------------\n";
}

// =========================================================
// Find Student
// =========================================================

int findStudentIndex(
    const vector<Student> &students,
    int roll
) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].roll == roll) {
            return static_cast<int>(i);
        }
    }

    return -1;
}

// =========================================================
// 1. Add Student
// =========================================================

void addStudent() {
    vector<Student> students = loadStudents();

    Student s;

    s.roll = readInt("Enter Roll Number: ");

    // Check duplicate roll number
    if (findStudentIndex(students, s.roll) != -1) {
        cout << "A student with Roll Number "
             << s.roll
             << " already exists.\n";

        return;
    }

    s.name = readLine("Enter Name: ");

    s.age = readIntRange(
        "Enter Age: ",
        1,
        100
    );

    s.course = readLine("Enter Course: ");

    s.marks = readMarks(
        "Enter Marks (0-100): "
    );

    students.push_back(s);

    saveStudents(students);

    cout << "\nStudent record added successfully.\n";
}

// =========================================================
// 2. Display All Students
// =========================================================

void displayStudents() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "\nNo student records found.\n";
        return;
    }

    cout << "\n========== ALL STUDENTS ==========\n";

    printTableHeader();

    for (const auto &s : students) {
        printStudentRow(s);
    }

    cout << "\nTotal Students: "
         << students.size()
         << '\n';
}

// =========================================================
// 3. Search By Roll Number
// =========================================================

void searchByRoll() {
    vector<Student> students = loadStudents();

    int roll = readInt(
        "Enter Roll Number to search: "
    );

    int index = findStudentIndex(
        students,
        roll
    );

    if (index == -1) {
        cout << "No student found with Roll Number "
             << roll << ".\n";

        return;
    }

    displayStudentDetails(students[index]);
}

// =========================================================
// 4. Search By Name
// =========================================================

void searchByName() {
    vector<Student> students = loadStudents();

    string name = readLine(
        "Enter name to search: "
    );

    string searchName = toLowerCase(name);

    bool found = false;

    cout << "\n========== SEARCH RESULTS ==========\n";

    for (const auto &s : students) {
        if (
            toLowerCase(s.name).find(searchName)
            != string::npos
        ) {
            if (!found) {
                printTableHeader();
            }

            printStudentRow(s);
            found = true;
        }
    }

    if (!found) {
        cout << "No student found with that name.\n";
    }
}

// =========================================================
// 5. Search By Course
// =========================================================

void searchByCourse() {
    vector<Student> students = loadStudents();

    string course = readLine(
        "Enter course to search: "
    );

    string searchCourse = toLowerCase(course);

    bool found = false;

    cout << "\n========== COURSE RESULTS ==========\n";

    for (const auto &s : students) {
        if (
            toLowerCase(s.course).find(searchCourse)
            != string::npos
        ) {
            if (!found) {
                printTableHeader();
            }

            printStudentRow(s);
            found = true;
        }
    }

    if (!found) {
        cout << "No students found in that course.\n";
    }
}

// =========================================================
// 6. Update Student
// =========================================================

void updateStudent() {
    vector<Student> students = loadStudents();

    int roll = readInt(
        "Enter Roll Number of student to update: "
    );

    int index = findStudentIndex(
        students,
        roll
    );

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    Student &s = students[index];

    displayStudentDetails(s);

    cout << "\nPress Enter to keep the current value.\n";

    // Name
    cout << "New Name [" << s.name << "]: ";

    string name;
    getline(cin, name);

    if (!name.empty()) {
        s.name = name;
    }

    // Age
    cout << "New Age [" << s.age << "]: ";

    string ageInput;
    getline(cin, ageInput);

    if (!ageInput.empty()) {
        try {
            int age = stoi(ageInput);

            if (age >= 1 && age <= 100) {
                s.age = age;
            } else {
                cout << "Invalid age. Keeping old value.\n";
            }
        }
        catch (...) {
            cout << "Invalid age. Keeping old value.\n";
        }
    }

    // Course
    cout << "New Course [" << s.course << "]: ";

    string course;
    getline(cin, course);

    if (!course.empty()) {
        s.course = course;
    }

    // Marks
    cout << "New Marks [" << s.marks << "]: ";

    string marksInput;
    getline(cin, marksInput);

    if (!marksInput.empty()) {
        try {
            float marks = stof(marksInput);

            if (marks >= 0 && marks <= 100) {
                s.marks = marks;
            } else {
                cout << "Invalid marks. Keeping old value.\n";
            }
        }
        catch (...) {
            cout << "Invalid marks. Keeping old value.\n";
        }
    }

    saveStudents(students);

    cout << "\nStudent record updated successfully.\n";
}

// =========================================================
// 7. Delete Student
// =========================================================

void deleteStudent() {
    vector<Student> students = loadStudents();

    int roll = readInt(
        "Enter Roll Number of student to delete: "
    );

    int index = findStudentIndex(
        students,
        roll
    );

    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    displayStudentDetails(students[index]);

    cout << "Are you sure you want to delete this student? (y/n): ";

    char confirm;
    cin >> confirm;
    clearInput();

    if (confirm == 'y' || confirm == 'Y') {
        students.erase(
            students.begin() + index
        );

        saveStudents(students);

        cout << "Student deleted successfully.\n";
    } else {
        cout << "Deletion cancelled.\n";
    }
}

// =========================================================
// 8. Sort Students
// =========================================================

void sortStudents() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No students available.\n";
        return;
    }

    cout << "\n========== SORT STUDENTS ==========\n";
    cout << "1. Roll Number (Ascending)\n";
    cout << "2. Name (A-Z)\n";
    cout << "3. Marks (Highest to Lowest)\n";
    cout << "4. Marks (Lowest to Highest)\n";
    cout << "5. Age (Ascending)\n";

    int choice = readIntRange(
        "Choose option: ",
        1,
        5
    );

    switch (choice) {

        case 1:
            sort(
                students.begin(),
                students.end(),
                [](const Student &a, const Student &b) {
                    return a.roll < b.roll;
                }
            );
            break;

        case 2:
            sort(
                students.begin(),
                students.end(),
                [](const Student &a, const Student &b) {
                    return toLowerCase(a.name)
                         < toLowerCase(b.name);
                }
            );
            break;

        case 3:
            sort(
                students.begin(),
                students.end(),
                [](const Student &a, const Student &b) {
                    return a.marks > b.marks;
                }
            );
            break;

        case 4:
            sort(
                students.begin(),
                students.end(),
                [](const Student &a, const Student &b) {
                    return a.marks < b.marks;
                }
            );
            break;

        case 5:
            sort(
                students.begin(),
                students.end(),
                [](const Student &a, const Student &b) {
                    return a.age < b.age;
                }
            );
            break;
    }

    cout << "\n========== SORTED STUDENTS ==========\n";

    printTableHeader();

    for (const auto &s : students) {
        printStudentRow(s);
    }
}

// =========================================================
// 9. Statistics Dashboard
// =========================================================

void showStatistics() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "\nNo student data available.\n";
        return;
    }

    float totalMarks = 0;

    const Student *highest = &students[0];
    const Student *lowest = &students[0];

    int passed = 0;
    int failed = 0;

    for (const auto &s : students) {

        totalMarks += s.marks;

        if (s.marks > highest->marks) {
            highest = &s;
        }

        if (s.marks < lowest->marks) {
            lowest = &s;
        }

        if (s.marks >= 50) {
            passed++;
        } else {
            failed++;
        }
    }

    float average =
        totalMarks / students.size();

    cout << "\n========================================\n";
    cout << "          STUDENT STATISTICS\n";
    cout << "========================================\n";

    cout << "Total Students : "
         << students.size() << '\n';

    cout << "Average Marks  : "
         << fixed << setprecision(2)
         << average << '\n';

    cout << "Highest Marks  : "
         << highest->marks
         << " (" << highest->name << ")\n";

    cout << "Lowest Marks   : "
         << lowest->marks
         << " (" << lowest->name << ")\n";

    cout << "Passed         : "
         << passed << '\n';

    cout << "Failed         : "
         << failed << '\n';

    float passPercentage =
        (static_cast<float>(passed)
         / students.size()) * 100;

    cout << "Pass Percentage: "
         << passPercentage << "%\n";

    cout << "========================================\n";
}

// =========================================================
// 10. Top Students
// =========================================================

void showTopStudents() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }

    sort(
        students.begin(),
        students.end(),
        [](const Student &a, const Student &b) {
            return a.marks > b.marks;
        }
    );

    int count = min(
        3,
        static_cast<int>(students.size())
    );

    cout << "\n========== TOP "
         << count
         << " STUDENTS ==========\n";

    printTableHeader();

    for (int i = 0; i < count; i++) {
        printStudentRow(students[i]);
    }
}

// =========================================================
// 11. Filter By Grade
// =========================================================

void filterByGrade() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }

    cout << "\n========== GRADES ==========\n";
    cout << "1. A+\n";
    cout << "2. A\n";
    cout << "3. B\n";
    cout << "4. C\n";
    cout << "5. D\n";
    cout << "6. F\n";

    int choice = readIntRange(
        "Select grade: ",
        1,
        6
    );

    string selectedGrade;

    switch (choice) {
        case 1: selectedGrade = "A+"; break;
        case 2: selectedGrade = "A"; break;
        case 3: selectedGrade = "B"; break;
        case 4: selectedGrade = "C"; break;
        case 5: selectedGrade = "D"; break;
        case 6: selectedGrade = "F"; break;
    }

    bool found = false;

    for (const auto &s : students) {

        if (getGrade(s.marks) == selectedGrade) {

            if (!found) {
                cout << "\nStudents with grade "
                     << selectedGrade << ":\n";

                printTableHeader();
            }

            printStudentRow(s);
            found = true;
        }
    }

    if (!found) {
        cout << "No students found with grade "
             << selectedGrade << ".\n";
    }
}

// =========================================================
// 12. Export To CSV
// =========================================================

void exportToCSV() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No records available for export.\n";
        return;
    }

    ofstream outFile(
        CSV_FILE_NAME,
        ios::trunc
    );

    if (!outFile) {
        cout << "Error: Could not create CSV file.\n";
        return;
    }

    outFile
        << "Roll,Name,Age,Course,Marks,Grade\n";

    for (const auto &s : students) {

        outFile
            << s.roll << ','
            << '"' << s.name << '"' << ','
            << s.age << ','
            << '"' << s.course << '"' << ','
            << fixed << setprecision(2)
            << s.marks << ','
            << getGrade(s.marks)
            << '\n';
    }

    outFile.close();

    cout << "\nStudent records exported successfully to "
         << CSV_FILE_NAME << ".\n";
}

// =========================================================
// 13. Delete All Students
// =========================================================

void deleteAllStudents() {
    vector<Student> students = loadStudents();

    if (students.empty()) {
        cout << "No student records to delete.\n";
        return;
    }

    cout << "\nWARNING: This will delete ALL "
         << students.size()
         << " student records.\n";

    cout << "Type DELETE to confirm: ";

    string confirmation;
    getline(cin, confirmation);

    if (confirmation == "DELETE") {

        students.clear();

        saveStudents(students);

        cout << "All student records deleted.\n";

    } else {
        cout << "Operation cancelled.\n";
    }
}

// =========================================================
// Main Menu
// =========================================================

void showMenu() {

    cout << "\n";
    cout << "================================================\n";
    cout << "          STUDENT MANAGEMENT SYSTEM\n";
    cout << "================================================\n";

    cout << " 1. Add Student\n";
    cout << " 2. Display All Students\n";
    cout << " 3. Search by Roll Number\n";
    cout << " 4. Search by Name\n";
    cout << " 5. Search by Course\n";
    cout << " 6. Update Student\n";
    cout << " 7. Delete Student\n";
    cout << " 8. Sort Students\n";
    cout << " 9. Statistics Dashboard\n";
    cout << "10. Show Top Students\n";
    cout << "11. Filter by Grade\n";
    cout << "12. Export to CSV\n";
    cout << "13. Delete All Students\n";
    cout << "14. Exit\n";

    cout << "================================================\n";
}

// =========================================================
// Main Program
// =========================================================

int main() {

    bool running = true;

    cout << "\n";
    cout << "========================================\n";
    cout << " Welcome to Student Management System\n";
    cout << "========================================\n";

    while (running) {

        showMenu();

        int choice = readIntRange(
            "Enter your choice (1-14): ",
            1,
            14
        );

        cout << '\n';

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchByRoll();
                break;

            case 4:
                searchByName();
                break;

            case 5:
                searchByCourse();
                break;

            case 6:
                updateStudent();
                break;

            case 7:
                deleteStudent();
                break;

            case 8:
                sortStudents();
                break;

            case 9:
                showStatistics();
                break;

            case 10:
                showTopStudents();
                break;

            case 11:
                filterByGrade();
                break;

            case 12:
                exportToCSV();
                break;

            case 13:
                deleteAllStudents();
                break;

            case 14:
                cout << "Exiting program.\n";
                cout << "All data is stored in "
                     << FILE_NAME << ".\n";
                cout << "Goodbye!\n";

                running = false;
                break;
        }
    }

    return 0;
}
