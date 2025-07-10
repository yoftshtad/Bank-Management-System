#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int acc_limit = 50;

// Global variables remain the same
int accNums[acc_limit];
float balances[acc_limit];
string names[acc_limit];
string note[acc_limit];
int count = 0;

int find(int num)
{
    for (int i = 0; i < count; i++)
    {
        if (accNums[i] == num)
            return i;
    }
    return -1;
}

void addAccount(int &c)
{
    if (c >= acc_limit)
    {
        cout << "Limit reached.\n";
        return;
    }

    int num;
    string name;
    float amount;

    cout << "Account number: ";
    cin >> num;

    if (find(num) != -1)
    {
        cout << "Already exists.\n";
        return;
    }

    cin.ignore(); 
    cout << "Name: ";
    getline(cin, name);

    cout << "Initial deposit: ";
    cin >> amount;
    
    // Added a check for negative deposit based on our previous discussion
    if (amount < 0) {
        cout << "Initial deposit cannot be negative. Account not created.\n";
        return;
    }

    accNums[c] = num;
    names[c] = name;
    balances[c] = amount;
    note[c] = "Account created.";

    c++;
    cout << "Account added!\n";
}

void deposit()
{
    int num;
    float amount;
    cout << "Account number: ";
    cin >> num;

    int i = find(num);
    if (i == -1)
    {
        cout << "Not found.\n";
        return;
    }

    float *p = &balances[i];

    cout << "Amount: ";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "Deposit must be a positive amount.\n";
        return;
    }

    *p += amount;
    note[i] = "Deposit made.";
    cout << "Done. New balance: " << *p << "\n";
}

void withdraw()
{
    int num;
    float amount;
    cout << "Account number: ";
    cin >> num;

    int i = find(num);
    if (i == -1)
    {
        cout << "Not found.\n";
        return;
    }

    cout << "Amount: ";
    cin >> amount;
    
    if (amount <= 0) {
        cout << "Withdrawal must be a positive amount.\n";
        return;
    }

    if (amount > balances[i])
    {
        cout << "Not enough money.\n";
        return;
    }

    balances[i] -= amount;
    note[i] = "Withdrawal done.";
    cout << "Done. New balance: " << balances[i] << "\n";
}

void show()
{
    if (count == 0) {
        cout << "\nNo accounts to show.\n";
        return;
    }
    for (int i = 0; i < count; i++)
    {
        cout << "\nAccount: " << accNums[i] << "\n";
        cout << "Name: " << names[i] << "\n";
        cout << "Balance: " << balances[i] << "\n";
        cout << "Note: " << note[i] << "\n";
    }
}

// ======================================================
// ==               NEW FEATURE 1                      ==
// ======================================================
/**
 * @brief Displays only accounts with a balance greater than 1000.
 */
void showHighValueAccounts()
{
    cout << "\n--- Accounts with Balance > $1000 ---\n";
    int foundCount = 0; // To track if we find any matching accounts

    for (int i = 0; i < count; i++)
    {
        if (balances[i] > 1000)
        {
            cout << "\nAccount: " << accNums[i] << "\n";
            cout << "Name: " << names[i] << "\n";
            cout << "Balance: " << balances[i] << "\n";
            cout << "Note: " << note[i] << "\n";
            foundCount++;
        }
    }

    if (foundCount == 0)
    {
        cout << "No accounts found with a balance over $1000.\n";
    }
    cout << "--------------------------------------\n";
}

// ======================================================
// ==               NEW FEATURE 2                      ==
// ======================================================
/**
 * @brief Recursively counts how many accounts have a balance > 1000.
 * @param index The current position in the array to check.
 * @return The total count of high-value accounts from this index onwards.
 */
int countHighValueRecursive(int index)
{
    // Base Case: If we are past the end of the list of accounts, there are 0.
    if (index >= count)
    {
        return 0;
    }

    // Recursive Step:
    // 1. Ask for the count from the REST of the list (from the next index onwards).
    int countFromRestOfTheList = countHighValueRecursive(index + 1);

    // 2. Check the CURRENT account. If it's a high-value one, add 1 to the count.
    if (balances[index] > 1000)
    {
        return 1 + countFromRestOfTheList;
    }
    else
    {
        // Otherwise, the count is just whatever the rest of the list had.
        return countFromRestOfTheList;
    }
}


int main()
{
    int ch;

    do
    {
        cout << "\n1. Add Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. Show All Accounts\n";
        cout << "5. Show High-Value Accounts (> $1000)\n";
        cout << "6. Count High-Value Accounts\n";
        cout << "7. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        switch (ch)
        {
        case 1:
            addAccount(count);
            break;
        case 2:
            deposit();
            break;
        case 3:
            withdraw();
            break;
        case 4:
            show();
            break;
        case 5:
            showHighValueAccounts();
            break;
        case 6:
            {
                int highValueCount = countHighValueRecursive(0);
                cout << "\nTotal number of accounts with balance > $1000: " << highValueCount << "\n";
            }
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Wrong choice.\n";
        }

    } while (ch != 7);

    return 0;
}
