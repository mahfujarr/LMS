#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <windows.h>
#include <sstream>

using namespace std;

class Book
{
public:
    string Title, Author, Genre, IssueDate, ReturnDate;
    Book(string title, string author, string genre, string issueDate, string returnDate)
    {
        Title = title;
        Author = author;
        Genre = genre;
        IssueDate = issueDate;
        ReturnDate = returnDate;
    };
    void display()
    {
        cout << "Title: " << Title << endl;
        cout << "Author: " << Author << endl;
        cout << "Genre: " << Genre << endl;
        cout << "Issue Date: " << IssueDate << endl;
        cout << "Return Date: " << ReturnDate << endl;
    }
    ~Book() {

    };
};

class Student : public Book
{
private:
    string Name;
    int ID;
    string borrowedBook;

public:
    Student(string name, int id)
    {
        ID = id;
        Name = name;
    };
    void borrowBook(string title)
    {
        borrowedBook = title;
    };
    ~Student() {

    };
};

void welcome();
void studentLogin();
void adminLogin();
void createAccount();
void listBooks();
void search();
void navigate();

int main()
{
    welcome();
}

void welcome()
{
    system("cls");
    cout << "Welcome to Library Management System." << endl;
    cout << "Press any option below to begin: " << endl;
    cout << "1. Login as student\n2. Login as admin\n3. Create student account\n4. List all books\n5.Search Books." << endl;
    bool validInput = false;

    while (!validInput)
    {
        cout << "---> ";
        int x;
        if (!(cin >> x))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            continue;
        }
        if (x == 1)
        {
            studentLogin();
            validInput = true;
        }
        else if (x == 2)
        {
            adminLogin();
            validInput = true;
        }
        else if (x == 3)
        {
            createAccount();
            validInput = true;
        }
        else if (x == 4)
        {
            listBooks();
            validInput = true;
        }
        else if (x == 5)
        {
            search();
            validInput = true;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 1 and 4." << endl;
        }
    }
}
void studentLogin()
{
    string name, pass, line;
    ifstream cred("data/credentials.txt");

    if (!cred)
    {
        cout << "Unable to open 'credentials.txt'" << endl;
        return;
    }

    cout << "Please enter your username: " << endl;
    cin >> name;

    bool found = false;
    while (getline(cred, line))
    {
        istringstream iss(line);
        string username, password;
        iss >> username >> password;

        if (username == name)
        {
            found = true;
            cout << "Please enter your password: " << endl;
            cin >> pass;

            if (pass == password)
            {
                cout << "Login successful!" << endl;
            }
            else
            {
                cout << "Incorrect password." << endl;
                cout << "Going to main menu in: ";
                for (int i = 3; i >= 1; i--)
                {
                    cout << i << endl;
                    Sleep(1000);
                }
                welcome();
            }
            break;
        }
    }

    if (!found)
    {
        cout << "Username not found." << endl;
    }
}
void adminLogin() {

};

void createAccount()
{
    string name, pass;
    system("cls");
    cout << "ONLY ONE RULE FOR USERNAME!!\nDON'T use ':' character in your username.\n";
    cout << "Please enter your username: ";
    cin >> name;
    ofstream cred("data/credentials.txt", ios::app);
    if (cred.is_open())
    {
        cred << name << " ";
        cout << "Please enter your password: ";
        cin >> pass;
        cred << pass << endl;
        system("cls");
        cout << "Account created Successfully." << endl;
        cred.close();
    }
    else
    {
        cout << "Error opening the file 'credentials.txt'" << endl;
    }
    // cout << "press any button to go to the main menu." << endl;
    cout << "Going to main menu in: ";
    for (int i = 5; i >= 1; i--)
    {
        cout << i << endl;
        Sleep(1000);
    }
    welcome();
};

void listBooks()
{
    ifstream list("data/booklist.csv");
    // list.open("booklist.csv");
    if (!list.is_open())
    {
        cerr << "Error opening file: booklist.csv" << endl;
    }
    string line;
    vector<Book> books;
    while (getline(list, line))
    {
        stringstream inputString(line);
        string title, author, genre, issueDate, returnDate;
        getline(inputString, title, ',');
        getline(inputString, author, ',');
        getline(inputString, genre, ',');
        getline(inputString, issueDate, ',');
        getline(inputString, returnDate, '\n');

        Book book(title, author, genre, issueDate, returnDate);
        books.push_back(book);
    }
    system("cls");
    for (auto book : books)
    {
        book.display();
        cout << "====================================" << endl;
    }
};

// void navigate()
// {
//     cout << "What do you want to do now?" << endl;
//     cout <<
// }