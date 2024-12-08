#include <iostream>
using namespace std;

void welcome();

int main()
{
    welcome();
}

void welcome()
{
    cout << "Welcome to Library Management System." << endl;
    cout << "Press any option below to begin: " << endl;
    cout << "1. Login as student\n2. Login as admin\n3. Create student account\n4. List all books" << endl;
}