# Student Management System

A simple **console-based Student Management System** built using **C++**.
The application allows users to manage student records through a menu-driven interface and stores the data permanently in a text file.

## Features

* Add a new student
* Display all student records
* Search for a student by roll number
* Update student details
* Delete a student record
* Prevent duplicate roll numbers
* Input validation for numbers and text
* Persistent data storage using `students.txt`

## Student Information

Each student record contains:

| Field       | Description               |
| ----------- | ------------------------- |
| Roll Number | Unique student identifier |
| Name        | Student's name            |
| Age         | Student's age             |
| Course      | Student's course          |
| Marks       | Student's marks           |

The student structure is defined with these five fields in the program.

## Technologies Used

* **C++**
* File Handling (`fstream`)
* STL `vector`
* `stringstream`
* Input validation
* Console-based UI

## Data Storage

Student records are stored in:

```text
students.txt
```

Each record is stored in the following format:

```text
roll|name|age|course|marks
```

Example:

```text
101|Rahul|20|Computer Science|85.5
102|Ankit|21|Information Technology|91
```

The program loads records from the file when required and saves the complete student list back to the file after modifications.

## Menu

When the application starts, it provides the following options:

```text
=========================================
       STUDENT MANAGEMENT SYSTEM
=========================================
1. Add Student
2. Display All Students
3. Search Student by Roll Number
4. Update Student
5. Delete Student
6. Exit
=========================================
```

The main program continuously displays this menu until the user selects **Exit**.

## How It Works

### 1. Add Student

The program asks for:

* Roll number
* Name
* Age
* Course
* Marks

Before adding the student, it checks whether the roll number already exists. Duplicate roll numbers are rejected.

### 2. Display Students

Displays all stored student records in a formatted table.

```text
Roll    Name                Age   Course         Marks
---------------------------------------------------------
101     Rahul               20    CSE            85.50
102     Ankit               21    IT             91.00
```

### 3. Search Student

Users can search for a student using their **roll number**.

### 4. Update Student

Existing student information can be updated.

Pressing Enter without entering a new value keeps the existing value for text fields. For age, entering `0` keeps the current value, while entering `-1` keeps the current marks.

### 5. Delete Student

Users can delete a student by roll number. The program asks for confirmation before deleting the record.

### 6. Exit

The program exits while keeping all saved student records in `students.txt`.

## Project Structure

```text
desktop-tutorial/
│
├── main.cpp
├── students.txt
└── README.md
```

> `students.txt` is automatically used by the application for storing student records.

## Requirements

You need a C++ compiler such as:

* GCC / MinGW
* Clang
* Microsoft Visual C++

A compiler supporting **C++11 or later** is recommended.

## Compilation

### Using GCC

```bash
g++ main.cpp -o student-management
```

### Run

**Windows:**

```bash
student-management.exe
```

**Linux/macOS:**

```bash
./student-management
```

## Input Validation

The program includes validation for:

* Invalid integer input
* Invalid floating-point input
* Empty text input
* Duplicate roll numbers
* Non-existent students during search, update, and deletion

The input helper functions continuously request valid values when invalid input is provided.

## Concepts Demonstrated

This project demonstrates several fundamental C++ concepts:

* Structures
* Functions
* Vectors
* Loops
* Conditional statements
* Switch statements
* File handling
* Exception handling
* String parsing
* Input validation
* CRUD operations

## CRUD Operations

| Operation | Function                                |
| --------- | --------------------------------------- |
| Create    | `addStudent()`                          |
| Read      | `displayStudents()` / `searchStudent()` |
| Update    | `updateStudent()`                       |
| Delete    | `deleteStudent()`                       |

## Future Improvements

Possible improvements include:

* GUI interface
* Database integration using MySQL/PostgreSQL
* Student sorting
* Search by name or course
* Marks/grade calculation
* Authentication
* Export to CSV
* Better input validation and error handling
* Separate header and implementation files
* CMake build system

## License

This project is created for educational and learning purposes.
