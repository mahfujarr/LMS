#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void welcome();
void studentLogin();
void adminLogin();
void createAccount();
void listBooks();

int main()
{
    welcome();
    ofstream out("data.txt");
    out << "This is a sample line.";
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
    ofstream cred("credentials.txt");
    cout << "Please enter your username: " << endl;
    cout << "Please enter your password: " << endl;
}
void adminLogin() {

};
void createAccount()
{
    string name, pass;
    cout << "ONLY ONE RULE FOR USERNAME!!\nDON'T use ':' character in your username.\n";
    cout << "Please enter your username: ";
    cin >> name;
    ofstream cred("data/credentials.txt", ios::app);
    if (cred.is_open())
    {
        cred << name << ":";
        cout << "Please enter your password: ";
        cin >> pass;
        cred << pass << endl;
        cout << "Account created Successfully.";
        cred.close();
    }
    else
    {
        cout << "Error opening the file 'credentials.txt'" << endl;
    }
};
void listBooks() {

};