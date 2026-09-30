#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <cstring>
#include <limits>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    char name[50];
    double balance;

public:
    BankAccount() {
        accountNumber = 0;
        strcpy(name, "");
        balance = 0.0;
    }

    BankAccount(int accNo, const char* customerName, double initialBalance) {
        accountNumber = accNo;
        strncpy(name, customerName, sizeof(name) - 1);
        name[sizeof(name) - 1] = '\0';
        balance = initialBalance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    const char* getName() const {
        return name;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount > 0) {
            balance += amount;
        }
    }

    bool withdraw(double amount) {
        if (amount <= 0 || amount > balance) {
            return false;
        }

        balance -= amount;
        return true;
    }

    void display() const {
        cout << "\n----------------------------------------\n";
        cout << "Account Number : " << accountNumber << '\n';
        cout << "Customer Name  : " << name << '\n';
        cout << fixed << setprecision(2);
        cout << "Balance        : Rs. " << balance << '\n';
        cout << "----------------------------------------\n";
    }
};

// Read all accounts from file
vector<BankAccount> loadAccounts() {
    vector<BankAccount> accounts;
    ifstream file("accounts.dat", ios::binary);

    if (!file) {
        return accounts;
    }

    BankAccount account;
    while (file.read(reinterpret_cast<char*>(&account), sizeof(BankAccount))) {
        accounts.push_back(account);
    }

    file.close();
    return accounts;
}

// Save all accounts to file
void saveAccounts(const vector<BankAccount>& accounts) {
    ofstream file("accounts.dat", ios::binary | ios::trunc);

    for (const BankAccount& account : accounts) {
        file.write(reinterpret_cast<const char*>(&account), sizeof(BankAccount));
    }

    file.close();
}

// Find account index
int findAccount(const vector<BankAccount>& accounts, int accountNumber) {
    for (int i = 0; i < static_cast<int>(accounts.size()); i++) {
        if (accounts[i].getAccountNumber() == accountNumber) {
            return i;
        }
    }

    return -1;
}

// Create a new account
void createAccount() {
    vector<BankAccount> accounts = loadAccounts();

    int accountNumber;
    char name[50];
    double initialDeposit;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    if (findAccount(accounts, accountNumber) != -1) {
        cout << "Account number already exists.\n";
        return;
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Customer Name: ";
    cin.getline(name, 50);

    cout << "Enter Initial Deposit: Rs. ";
    cin >> initialDeposit;

    if (initialDeposit < 0) {
        cout << "Initial deposit cannot be negative.\n";
        return;
    }

    accounts.emplace_back(accountNumber, name, initialDeposit);
    saveAccounts(accounts);

    cout << "\nAccount created successfully!\n";
}

// Deposit money
void depositMoney() {
    vector<BankAccount> accounts = loadAccounts();

    int accountNumber;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    int index = findAccount(accounts, accountNumber);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter Deposit Amount: Rs. ";
    cin >> amount;

    if (amount <= 0) {
        cout << "Invalid amount.\n";
        return;
    }

    accounts[index].deposit(amount);
    saveAccounts(accounts);

    cout << "Amount deposited successfully.\n";
    cout << "New Balance: Rs. "
         << fixed << setprecision(2)
         << accounts[index].getBalance() << '\n';
}

// Withdraw money
void withdrawMoney() {
    vector<BankAccount> accounts = loadAccounts();

    int accountNumber;
    double amount;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    int index = findAccount(accounts, accountNumber);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    cout << "Enter Withdrawal Amount: Rs. ";
    cin >> amount;

    if (accounts[index].withdraw(amount)) {
        saveAccounts(accounts);

        cout << "Amount withdrawn successfully.\n";
        cout << "Remaining Balance: Rs. "
             << fixed << setprecision(2)
             << accounts[index].getBalance() << '\n';
    } else {
        cout << "Withdrawal failed. Check amount or available balance.\n";
    }
}

// Check balance
void checkBalance() {
    vector<BankAccount> accounts = loadAccounts();

    int accountNumber;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    int index = findAccount(accounts, accountNumber);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    cout << "\nCurrent Balance: Rs. "
         << fixed << setprecision(2)
         << accounts[index].getBalance() << '\n';
}

// Display account details
void displayAccount() {
    vector<BankAccount> accounts = loadAccounts();

    int accountNumber;

    cout << "\nEnter Account Number: ";
    cin >> accountNumber;

    int index = findAccount(accounts, accountNumber);

    if (index == -1) {
        cout << "Account not found.\n";
        return;
    }

    accounts[index].display();
}

// Display all accounts
void displayAllAccounts() {
    vector<BankAccount> accounts = loadAccounts();

    if (accounts.empty()) {
        cout << "\nNo accounts found.\n";
        return;
    }

    cout << "\n========== ALL ACCOUNTS ==========\n";

    for (const BankAccount& account : accounts) {
        account.display();
    }
}

int main() {
    int choice;

    do {
        cout << "\n\n========================================\n";
        cout << "       BANK MANAGEMENT SYSTEM\n";
        cout << "========================================\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Check Balance\n";
        cout << "5. Display Account Details\n";
        cout << "6. Display All Accounts\n";
        cout << "7. Exit\n";
        cout << "----------------------------------------\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                createAccount();
                break;

            case 2:
                depositMoney();
                break;

            case 3:
                withdrawMoney();
                break;

            case 4:
                checkBalance();
                break;

            case 5:
                displayAccount();
                break;

            case 6:
                displayAllAccounts();
                break;

            case 7:
                cout << "\nThank you for using Bank Management System!\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 7);

    return 0;
}