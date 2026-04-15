#include <iostream>
#include <fstream>
using namespace std;

class BankAccount {
private:
    int accNo;
    string name;
    float balance;

public:
    void createAccount() {
        cout << "\nEnter Account Number: ";
        cin >> accNo;
        cout << "Enter Name: ";
        cin >> name;
        cout << "Enter Balance: ";
        cin >> balance;
    }

    void showAccount() {
        cout << "\nAccount No: " << accNo;
        cout << "\nName: " << name;
        cout << "\nBalance: " << balance << endl;
    }

    int getAccNo() {
        return accNo;
    }

    void deposit() {
        float amt;
        cout << "Enter amount to deposit: ";
        cin >> amt;
        balance += amt;
    }

    void withdraw() {
        float amt;
        cout << "Enter amount to withdraw: ";
        cin >> amt;
        if (amt > balance)
            cout << "Insufficient balance!\n";
        else
            balance -= amt;
    }
};

// 🔹 Function to add account
void addAccount() {
    BankAccount acc;
    ofstream file("bank.dat", ios::binary | ios::app);

    acc.createAccount();
    file.write((char*)&acc, sizeof(acc));

    file.close();
    cout << "\nAccount Created Successfully!\n";
}

// 🔹 Function to display all accounts
void displayAll() {
    BankAccount acc;
    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&acc, sizeof(acc))) {
        acc.showAccount();
        cout << "\n------------------";
    }

    file.close();
}

// 🔹 Search account
void searchAccount() {
    int num;
    bool found = false;

    cout << "Enter Account Number to search: ";
    cin >> num;

    BankAccount acc;
    ifstream file("bank.dat", ios::binary);

    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccNo() == num) {
            acc.showAccount();
            found = true;
        }
    }

    if (!found)
        cout << "Account not found!\n";

    file.close();
}

// 🔹 Deposit / Withdraw
void modifyAccount(bool isDeposit) {
    int num;
    cout << "Enter Account Number: ";
    cin >> num;

    BankAccount acc;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);

    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.getAccNo() == num) {

            if (isDeposit)
                acc.deposit();
            else
                acc.withdraw();

            int pos = (-1) * sizeof(acc);
            file.seekp(pos, ios::cur);
            file.write((char*)&acc, sizeof(acc));

            cout << "Transaction Successful!\n";
            return;
        }
    }

    cout << "Account not found!\n";
    file.close();
}

// 🔹 Main Function
int main() {
    int choice;

    do {
        cout << "\n\n==== BANK MANAGEMENT SYSTEM ====";
        cout << "\n1. Create Account";
        cout << "\n2. Display All Accounts";
        cout << "\n3. Search Account";
        cout << "\n4. Deposit";
        cout << "\n5. Withdraw";
        cout << "\n6. Exit";
        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addAccount(); break;
            case 2: displayAll(); break;
            case 3: searchAccount(); break;
            case 4: modifyAccount(true); break;
            case 5: modifyAccount(false); break;
            case 6: cout << "Thank You!\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 6);

    return 0;
}
