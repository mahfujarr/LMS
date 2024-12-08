#include <iostream>
using namespace std;

void welcome();
void studentLogin();
void adminLogin();
void createAccount();
void listBooks();

int main()
{
    welcome();
}

void welcome()
{
    cout << "Welcome to Library Management System." << endl;
    cout << "Press any option below to begin: " << endl;
    cout << "1. Login as student\n2. Login as admin\n3. Create student account\n4. List all books" << endl;
    cout << "---> ";
    int x;
    bool validInput = false;

    while (!validInput)
    {
        cin >> x;
        switch (x)
        {
        case 1:
            studentLogin();
            validInput = true;
            break;
        case 2:
            adminLogin();
            validInput = true;
            break;
        case 3:
            createAccount();
            validInput = true;
            break;
        case 4:
            listBooks();
            validInput = true;
            break;
        default:
            cout << "Invalid input." << endl;
            cout << "Please input from 1 to 4." << endl;
            cout << "---> ";
            break;
        }
    }
}
void studentLogin()
{
    cout << "Please enter your username: " << endl;
    cout << "Please enter your password: " << endl;
}
void adminLogin() {

};
void createAccount() {

};
void listBooks() {

};