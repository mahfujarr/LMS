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
    Book(string title = "NULL", string author = "NULL", string genre = "NULL", string issueDate = "NULL", string returnDate = "NULL")
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
    void add()
    {
        ofstream bookList("data/booklist.csv", ios::app);
        if (bookList.is_open())
        {
            bookList << Title << ", ";
            bookList << Author << ", ";
            bookList << Genre << ", ";
            bookList << IssueDate << ", ";
            bookList << ReturnDate << endl;
            cout << "Book Added Successfully." << endl;
            bookList.close();
        }
        else
        {
            cout << "Error opening the file 'booklist.txt'" << endl;
        }
    }
    ~Book() {

    };
};
class Student
{
public:
    string Name;
    int ID;
    string borrowedBook;
    Student(string name, int id)
    {
        Name = name;
        ID = id;
    }
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
void addBook();
void searchBook();
void deleteBook();
void editBook();
void navigate();

int main()
{
    system("cls");
    welcome();
    // studentLogin();
    // adminLogin();
    // createAccount();
    // listBooks();
    // addBook();
    // deleteBook();
    // editBook();
    // searchBook();
    // navigate();
}

void welcome()
{
    cout << "Welcome to Library Management System." << endl;
    cout << "Press any option below to begin: " << endl;
    cout << "1. Login as student" << endl;
    cout << "2. Login as admin" << endl;
    cout << "3. Create student account" << endl;
    cout << "4. List all books" << endl;
    cout << "5.Add Books." << endl;
    cout << "6.Search Books." << endl;
    cout << "7.Edit Books." << endl;
    cout << "8.Delete Books." << endl;
    cout << "0.Exit the program." << endl;

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
        if (x == 0)
        {
            system("cls");
            cout << "Program is terminated.\nHope to see you soon!";
            exit(0);
            validInput = true;
        }
        else if (x == 1)
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
            addBook();
            validInput = true;
        }
        else if (x == 6)
        {
            searchBook();
            validInput = true;
        }
        else if (x == 7)
        {
            editBook();
            validInput = true;
        }
        else if (x == 8)
        {
            deleteBook();
            validInput = true;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 8." << endl;
        }
    }
}
void studentLogin()
{
    string ID, pass, line;
    ifstream cred("data/credentials.txt");

    if (!cred)
    {
        cout << "Unable to open 'credentials.txt'" << endl;
        return;
    }

    cout << "Please enter your ID: ";
    cin >> ID;

    bool found = false;
    while (getline(cred, line))
    {
        istringstream iss(line);
        string username, password;
        iss >> username >> password;

        if (username == ID)
        {
            found = true;
            cout << "Please enter your password: ";
            cin >> pass;

            if (pass == password)
            {
                system("cls");
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
                system("cls");
                welcome();
            }
            break;
        }
    }

    if (!found)
    {
        cout << "ID not found." << endl;
    }
}
void adminLogin() {

};
void createAccount()
{
    string ID, pass;
    system("cls");
    // cout << "ONLY ONE RULE FOR USERNAME!!\nDON'T use ':' character in your username.\n";
    cout << "Please enter your ID: ";
    cin >> ID;
    ofstream cred("data/credentials.txt", ios::app);
    if (cred.is_open())
    {
        cred << ID << " ";
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
    for (int i = 3; i >= 1; i--)
    {
        cout << i << endl;
        Sleep(1000);
    }
    system("cls");
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
    cout << "Listing all " << books.size() << " books." << endl;
    for (int i = 0; i < books.size(); ++i)
    {
        cout << "===============( " << i + 1 << " )===============" << endl;
        Book book = books[i];
        book.display();
        // Sleep(250);
    }
    cout << "Press any key to go to main menu." << endl;
    cin.get();
    cin.get();
    cout << "Going to main menu in: ";
    for (int i = 3; i >= 1; i--)
    {
        cout << i << endl;
        Sleep(1000);
    }
    welcome();
};
void addBook()
{
    string title, author, genre;
    cout << "Welcome to the book adding section.\nPlease double check the spellings." << endl;
    cout << "What's the title?\n-->";
    getline(cin, title);
    cout << "Who's the author?\n-->";
    getline(cin, author);
    cout << "What's the genre?\n-->";
    getline(cin, genre);

    Book b1(title, author, genre);
    b1.add();
};
void searchBook()
{
    ifstream find("data/booklist.csv");
    if (!find.is_open())
    {
        cerr << "Error opening file: booklist.csv" << endl;
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string target;
    cout << "Enter the book title, author, or genre to search: ";
    getline(cin, target);

    int i = 0;
    string book;
    while (getline(find, book))
    {
        i++;
        if (book.find(target) != string::npos)
        {
            cout << "Found entity at book " << i << ": " << book << endl;
            // cout << "The 2 dates after #genre are subsequently the #issue & #return date." << endl;
            break;
        }
    }

    if (i == 0)
    {
        cout << "Target string not found." << endl;
    }
    find.close();
}
void deleteBook()
{
    ifstream fin("data/booklist.csv", ios::in);
    if (!fin.is_open())
    {
        cerr << "Error Opening CSV file" << endl;
    }

    bool bookFound = false;
    string line;
    int bookNum, currentBook = 1;
    cout << "Enter the book number to delete: ";
    cin >> bookNum;
    ofstream fout("data/TEMP.csv", ios::out);
    while (getline(fin, line))
    {
        if (currentBook != bookNum)
        {
            fout << line << '\n';
        }
        else
        {
            bookFound = true;
        }
        currentBook++;
    }
    if (bookFound)
    {
        cout << "Book deleted successfully." << endl;
    }
    else
    {
        cout << "Book not found" << endl;
    }
    fin.close();
    fout.close();
    remove("data/booklist.csv");
    rename("data/TEMP.csv", "data/booklist.csv");
};
void editBook()
{
    ifstream fin("data/booklist.csv", ios::in);
    if (!fin.is_open())
    {
        cerr << "Error Opening CSV file" << endl;
    }

    bool bookFound = false;
    string line;
    int bookNum, currentBook = 1;
    cout << "Enter the book number to edit: ";
    cin >> bookNum;
    cin.ignore();
    ofstream fout("data/TEMP.csv", ios::out);

    string title, author, genre, issueDate, returnDate;

    while (getline(fin, line))
    {
        if (currentBook == bookNum)
        {
            cout << "Welcome to the book editing section.\nPlease double check the spellings." << endl;
            stringstream inputString(line);
            getline(inputString, title, ',');
            getline(inputString, author, ',');
            getline(inputString, genre, ',');
            getline(inputString, issueDate, ',');
            getline(inputString, returnDate, '\n');
            if (issueDate == "" || returnDate == "")
            {
                issueDate = "NULL";
                returnDate = "NULL";
            }
            cout << "What's the title?\n-->";
            getline(cin, title);
            cout << "Who's the author?\n-->";
            getline(cin, author);
            cout << "What's the genre?\n-->";
            getline(cin, genre);
            fout << title << ", " << author << ", " << genre << ", " << issueDate << ", " << returnDate << '\n';
            bookFound = true;
        }
        else
        {
            fout << line << '\n';
        }
        currentBook++;
    }
    if (bookFound)
    {
        cout << "Book edited successfully." << endl;
    }
    else
    {
        cout << "Book not found" << endl;
    }
    fin.close();
    fout.close();
    if (bookFound)
    {
        cout << "Book edited successfully." << endl;
        remove("data/booklist.csv");
        rename("data/TEMP.csv", "data/booklist.csv");
    }
    else
    {
        cout << "Book not found." << endl;
        remove("data/TEMP.csv");
    }
    welcome();
};
void navigate() {

};