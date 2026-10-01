#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class BankAccount
{
private:
    string name;
    double balance;

public:

    // Constructor
    BankAccount(string accountName, double initialBalance)
    {
        name = accountName;
        balance = initialBalance;
    }

    // Deposit money
    void deposit(double amount)
    {
        if (amount > 0)
        {
            balance += amount;
            cout << "Amount deposited successfully." << endl;
        }
        else
        {
            cout << "Invalid deposit amount." << endl;
        }
    }

    // Withdraw money
    void withdraw(double amount)
    {
        if (amount <= 0)
        {
            cout << "Invalid withdrawal amount." << endl;
        }
        else if (amount <= balance)
        {
            balance -= amount;
            cout << "Amount withdrawn successfully." << endl;
        }
        else
        {
            cout << "Insufficient Funds." << endl;
        }
    }

    // Display balance
    void displayBalance()
    {
        cout << "\nAccount Holder: " << name << endl;
        cout << "Current Balance: Rs. " << balance << endl;
    }

    // Save account data
    void saveToFile()
    {
        ofstream file("account.txt");

        if (file.is_open())
        {
            file << name << endl;
            file << balance << endl;
            file.close();

            cout << "Account data saved successfully." << endl;
        }
        else
        {
            cout << "Error: Unable to save account data." << endl;
        }
    }
};

int main()
{
    string name;
    double initialDeposit;

    cout << "====================================" << endl;
    cout << "      BANK MANAGEMENT SYSTEM" << endl;
    cout << "====================================" << endl;

    // Get customer name
    cout << "Enter your name: ";
    getline(cin, name);

    // Get initial deposit
    cout << "Enter initial deposit: Rs. ";
    cin >> initialDeposit;

    // Validate initial deposit
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');

        cout << "Invalid input. Please enter a number." << endl;
        return 0;
    }

    if (initialDeposit < 0)
    {
        cout << "Initial deposit cannot be negative." << endl;
        return 0;
    }

    // Create object
    BankAccount account(name, initialDeposit);

    int choice;
    double amount;

    do
    {
        cout << "\n====================================" << endl;
        cout << "              MENU" << endl;
        cout << "====================================" << endl;
        cout << "1. Deposit" << endl;
        cout << "2. Withdraw" << endl;
        cout << "3. Check Balance" << endl;
        cout << "4. Save Account" << endl;
        cout << "5. Exit" << endl;
        cout << "====================================" << endl;

        cout << "Enter your choice: ";

        // Prevent infinite loop on invalid input
        if (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(10000, '\n');

            cout << "Please enter a number from 1 to 5." << endl;
            continue;
        }

        switch (choice)
        {
            case 1:
                cout << "Enter deposit amount: Rs. ";
                cin >> amount;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid amount." << endl;
                }
                else
                {
                    account.deposit(amount);
                }
                break;

            case 2:
                cout << "Enter withdrawal amount: Rs. ";
                cin >> amount;

                if (cin.fail())
                {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "Invalid amount." << endl;
                }
                else
                {
                    account.withdraw(amount);
                }
                break;

            case 3:
                account.displayBalance();
                break;

            case 4:
                account.saveToFile();
                break;

            case 5:
                account.saveToFile();
                cout << "Thank you for using Bank Management System!" << endl;
                break;

            default:
                cout << "Invalid choice. Please enter 1 to 5." << endl;
        }

    } while (choice != 5);

    return 0;
}