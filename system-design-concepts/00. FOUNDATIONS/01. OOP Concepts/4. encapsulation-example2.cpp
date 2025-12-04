#include <bits/stdc++.h>
using namespace std;

/*
--------------------------------------------------------------
👉 Problem: Demonstrate Encapsulation in C++
--------------------------------------------------------------
You are required to design a simple Bank Account System using the Encapsulation principle of OOP.
The system must:

- Keep sensitive account details (accountHolder, accountNumber, balance) private.
- Allow safe updates (deposit, withdrawal, name change) through public methods only.
- Perform data validation to avoid invalid or inconsistent states.
- Provide read-only access to account details through getters.

👉 Concept

| Core Idea                            | Explanation                                                                        |
| ------------------------------------ | ---------------------------------------------------------------------------------- |
| **Encapsulation**                    | Wrapping data + logic together while hiding internal details.                      |
| **Private Members**                  | Prevent direct external access to sensitive information.                           |
| **Public Methods (Setters/Getters)** | Provide safe, validated, and controlled access.                                    |
| **Data Validation**                  | Ensures system integrity and prevents invalid operations (e.g., negative deposit). |

👉 Real-World Analogy

Just like a bank system:

- You can’t directly change your account’s balance from the database.
- You interact via secure APIs (deposit/withdraw), which validate your requests before applying changes.
That’s encapsulation — safe and controlled modification.
--------------------------------------------------------------
*/

// --------------------------------------------------------------
// CLASS: BankAccount
// Demonstrates Encapsulation with data hiding, validation, and
// controlled access to account details.
// --------------------------------------------------------------
class BankAccount {
private:
    // Private Data Members (Hidden from outside access)
    string accountHolder;   // Name of the account holder
    int accountNumber;      // Unique account number
    double balance;         // Current balance (kept private for security)

public:
    // ----------------------------------------------------------
    // Constructor
    // Purpose: Initializes account with holder name, account number, and initial balance.
    // Adds validation to ensure no negative balance at creation.
    // ----------------------------------------------------------
    BankAccount(string name, int accNum, double initialBalance) {
        accountHolder = name;
        accountNumber = accNum;
        
        // Validation: initial balance cannot be negative
        if (initialBalance < 0) {
            cout << "Invalid initial balance. Setting to 0.\n";
            balance = 0;
        } else {
            balance = initialBalance;
        }
    }

    // ----------------------------------------------------------
    // Setter for Account Holder Name (with validation)
    // Ensures the name is meaningful before updating.
    // ----------------------------------------------------------
    void setAccountHolder(string name) {
        if (name.length() > 1) {
            accountHolder = name;
        } else {
            cout << "Invalid name. Update failed.\n";
        }
    }

    // ----------------------------------------------------------
    // Deposit Function
    // Adds amount to balance safely (validated for positivity).
    // ----------------------------------------------------------
    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Deposit amount must be positive.\n";
            return;
        }
        balance += amount;
        cout << "Deposited: " << amount << " | New Balance: " << balance << endl;
    }

    // ----------------------------------------------------------
    // Withdraw Function
    // Deducts amount from balance with safety checks for:
    // - Positive input
    // - Sufficient balance
    // ----------------------------------------------------------
    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Withdrawal amount must be positive.\n";
            return;
        }
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return;
        }
        balance -= amount;
        cout << "Withdrawn: " << amount << " | Remaining Balance: " << balance << endl;
    }

    // ----------------------------------------------------------
    // Getter Functions (Read-Only Access)
    // Allow reading private data without modification.
    // ----------------------------------------------------------
    string getAccountHolder() { return accountHolder; }
    int getAccountNumber() { return accountNumber; }
    double getBalance() { return balance; }

    // ----------------------------------------------------------
    // Display Function
    // Presents all account details neatly.
    // ----------------------------------------------------------
    void displayDetails() {
        cout << "\n----- Account Details -----\n";
        cout << "Holder: " << accountHolder << endl;
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: " << balance << endl;
    }
};

// --------------------------------------------------------------
// MAIN FUNCTION
// Demonstrates Encapsulation in action through various operations.
// --------------------------------------------------------------
int main() {
    // Step 1: Create an account object with valid initial data
    BankAccount acc("Alice", 101, 5000.0);

    // Step 2: Display initial details
    acc.displayDetails();

    // Step 3: Deposit some money (valid)
    acc.deposit(2000);

    // Step 4: Attempt invalid deposit (negative value)
    acc.deposit(-500);

    // Step 5: Withdraw money (valid)
    acc.withdraw(1000);

    // Step 6: Attempt invalid withdrawal (insufficient balance)
    acc.withdraw(10000);

    // Step 7: Change account holder name (valid)
    acc.setAccountHolder("Alice Johnson");

    // Step 8: Attempt invalid name change
    acc.setAccountHolder("A");

    // Step 9: Display final state of the account
    acc.displayDetails();

    return 0;
}
