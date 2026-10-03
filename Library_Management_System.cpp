#include <iostream>
#include <string>
using namespace std;

class Book
{
private:
    int id;
    string name;
    string author;
    string student;
    float price;
    int pages;

public:

    void input()
    {
        cout << "Enter Book Id" << endl;
        cin >> id;

        cin.ignore();

        cout << "Enter Book Name" << endl;
        getline(cin, name);

        cout << "Enter Book Author" << endl;
        getline(cin, author);

        cout << "Enter Student Name" << endl;
        getline(cin, student);

        cout << "Enter Book Price" << endl;
        cin >> price;

        cout << "Enter Number of Pages" << endl;
        cin >> pages;
    }

    void display()
    {
        cout << "\n========== BOOK DETAILS ==========" << endl;

        cout << "Book Id       : " << id << endl;
        cout << "Book Name     : " << name << endl;
        cout << "Book Author   : " << author << endl;
        cout << "Student Name  : " << student << endl;
        cout << "Book Price    : Rs. " << price << endl;
        cout << "Pages         : " << pages << endl;

        cout << "==================================" << endl;
    }
};

int main()
{
    Book books[100];

    int choice;
    int count = 0;

    do
    {
        cout << "\nEnter 1 to input details like id, name, author, student, price, pages" << endl;
        cout << "Enter 2 to display details" << endl;
        cout << "Enter 3 to quit" << endl;

        cin >> choice;

        switch (choice)
        {
        case 1:

            if (count < 100)
            {
                books[count].input();
                count++;

                cout << "\nBook details added successfully!" << endl;
            }
            else
            {
                cout << "Library is full." << endl;
            }

            break;

        case 2:

            if (count == 0)
            {
                cout << "\nNo book details available." << endl;
            }
            else
            {
                for (int i = 0; i < count; i++)
                {
                    books[i].display();
                }
            }

            break;

        case 3:

            cout << "\nProgram ended. Thank you!" << endl;
            break;

        default:

            cout << "\nInvalid choice. Please try again." << endl;
        }

    } while (choice != 3);

    return 0;
}