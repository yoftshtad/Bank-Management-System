#include <iostream>
#include <string>
#include <cstring>

using namespace std;

const int acc_limit = 50;

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

    cin.ignore(); // clear newline before getline
    cout << "Name: ";
    getline(cin, name); // supports full name input

    cout << "Initial deposit: ";
    cin >> amount;

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
    for (int i = 0; i < count; i++)
    {
        cout << "\nAccount: " << accNums[i] << "\n";
        cout << "Name: " << names[i] << "\n";
        cout << "Balance: " << balances[i] << "\n";
        cout << "Note: " << note[i] << "\n";
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
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> ch;

        if (ch == 1)
            addAccount(count);
        else if (ch == 2)
            deposit();
        else if (ch == 3)
            withdraw();
        else if (ch == 4)
            show();
        else if (ch != 5)
            cout << "Wrong choice.\n";

    } while (ch != 5);

    return 0;
}
