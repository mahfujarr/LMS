#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <sstream>
#include <windows.h>
using namespace std;

bool loggedInAsAdmin = false;
bool loggedInAsStudent = false;
string Alias = "Guest!\n";

class Book
{
public:
    string Title, Author, Genre, IssueDate, ReturnDate, Student;
    Book(string title = "NULL", string author = "NULL", string genre = "NULL", string issueDate = "NULL", string returnDate = "NULL", string username = "")
    {
        Title = title;
        Author = author;
        Genre = genre;
        IssueDate = issueDate;
        ReturnDate = returnDate;
        Student = username;
    };
    void display()
    {
        cout << "Title: " << Title << endl;
        cout << "Author: " << Author << endl;
        cout << "Genre: " << Genre << endl;
        cout << "Issue Date: " << IssueDate << endl;
        cout << "Return Date: " << ReturnDate << endl;
        cout << "Availability: " << (IssueDate != " NULL" || ReturnDate != " NULL" ? "Not Available" : "Available") << endl;
        cout << "Borrowed by: " << (IssueDate != " NULL" || ReturnDate != " NULL" ? Student : "NONE") << endl;
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
            bookList << ReturnDate << "\n";
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

void welcome();
void studentLogin();
void adminLogin();
void createAccount();
void listBooks();
void borrowBook();
void addBook();
void searchBook();
void deleteBook();
void editBook();
void logOut();
void mainMenu();

int main()
{
    system("cls");
    cout << R"( _      __      __                        __            __    __  ___ ____
| | /| / /___  / /____ ___   __ _  ___   / /_ ___      / /   /  |/  // __/
| |/ |/ // -_)/ // __// _ \ /  ' \/ -_) / __// _ \    / /__ / /|_/ /_\ \  
|__/|__/ \__//_/ \__/ \___//_/_/_/\__/  \__/ \___/   /____//_/  /_//___/  )"
         << endl
         << endl;
    welcome();
}

void welcome()
{
    if (Alias != "")
    {
        cout << "\033[1,36mHello, " << Alias << "\033[0m";
        (Alias == "Guest!\n" ? cout << "" << endl : cout << "                               00.\033[31mLogout\033[0m" << endl);
    }
    cout << "========================================" << endl;
    if (loggedInAsAdmin)
    {
        cout << "               Main Menu             (A)" << endl;
    }
    else if (loggedInAsStudent)
    {
        cout << "               Main Menu             (S)" << endl;
    }
    else
    {
        cout << "               Main Menu             (G)" << endl;
    }
    cout << "========================================" << endl;
    cout << "Press any available option to begin: " << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. \033[1;32mLogin as student\033[0m" << endl;
    cout << "2. \033[1;32mLogin as admin\033[0m" << endl;
    cout << (loggedInAsAdmin ? "3. \033[1;32mCreate student account\033[0m" : "3. Create student account") << endl;
    cout << "4. \033[1;32mList all books\033[0m" << endl;
    cout << (loggedInAsStudent ? "5. \033[1;32mBorrow Book\033[0m" : "5. Borrow Book") << endl;
    cout << (loggedInAsAdmin ? "6. \033[1;32mAdd Books\033[0m" : "6. Add Books") << endl;
    cout << "7. \033[1;32mSearch Books\033[0m" << endl;
    cout << (loggedInAsAdmin ? "8. \033[1;32mEdit Books\033[0m" : "8. Edit Books") << endl;
    cout << (loggedInAsAdmin ? "9. \033[1;31mDelete Books\033[0m" : "9. Delete Books") << endl;
    cout << "0. \033[1;31mExit the program\033[0m" << endl;
    cout << "----------------------------------------" << endl;

    bool validInput = false;

    while (!validInput)
    {
        cout << "--> ";
        string x;
        if (!(cin >> x))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            continue;
        }
        if (x == "0")
        {
            system("cls");
            cout << "Program is terminated.\nHope to see you soon," << Alias << "!" << endl;
            exit(0);
            validInput = true;
        }
        else if (x == "1")
        {
            studentLogin();
            validInput = true;
        }
        else if (x == "2")
        {
            adminLogin();
            validInput = true;
        }
        else if (x == "3")
        {
            createAccount();
            validInput = true;
        }
        else if (x == "4")
        {
            listBooks();
            validInput = true;
        }
        else if (x == "5")
        {
            borrowBook();
            validInput = true;
        }
        else if (x == "6")
        {
            addBook();
            validInput = true;
        }
        else if (x == "7")
        {
            searchBook();
            validInput = true;
        }
        else if (x == "8")
        {
            editBook();
            validInput = true;
        }
        else if (x == "9")
        {
            deleteBook();
            validInput = true;
        }
        else if (x == "00")
        {
            logOut();
            validInput = true;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 9." << endl;
        }
    }
}
void studentLogin()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "              Student Login             " << endl;
    cout << "========================================" << endl;
    loggedInAsAdmin = false;
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
                loggedInAsStudent = true;
                system("cls");
                cout << "Login successful!" << endl;
                Alias = username + "!\n";
                cout << "You'll be interacting as: '" << username << "'" << endl;
                // Sleep(2000);
                mainMenu();
            }
            else
            {
                cout << "Incorrect password." << endl;
                mainMenu();
            }
            break;
        }
    }

    if (!found)
    {
        system("cls");
        cout << "ID not found." << endl;
        mainMenu();
    }
}
void adminLogin()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "               Admin Login              " << endl;
    cout << "========================================" << endl;
    loggedInAsStudent = false;
    string pass;
    cout << "Please enter the admin password: ";
    cin >> pass;
    if (pass == "admin") // Password for admin is "admin"
    {
        system("cls");
        cout << "Login successful!" << endl;
        loggedInAsAdmin = true;
        Alias = "Admin!\n";
        cout << "You are now interacting as an Admin." << endl;
        welcome();
    }
    else
    {
        cout << "Incorrect password." << endl;
        cout << "Going to main menu in: ";
        for (int i = 3; i >= 1; i--)
        {
            cout << i << endl;
            Sleep(500);
        }
        system("cls");
        welcome();
    }
};
void createAccount()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "        Create new student account      " << endl;
    cout << "========================================" << endl;
    if (loggedInAsAdmin)
    {
        string ID, pass;

        cout << "Please enter student's ID: ";
        cin >> ID;
        ifstream fin("data/credentials.txt");
        string line;
        while (getline(fin, line))
        {
            istringstream iss(line);
            string username, password;
            iss >> username >> password;
            if (username == ID)
            {
                cout << "ID already exists." << endl;
                mainMenu();
            }
        }
        ofstream cred("data/credentials.txt", ios::app);
        if (cred.is_open())
        {
            cred << ID << " ";
            cout << "Please enter your password: ";
            cin >> pass;
            cred << pass << endl;
            system("cls");
            cred.close();
            system("cls");
            cout << "Account created Successfully." << endl;
        }
        else
        {
            cerr << "Error opening the file 'credentials.txt'" << endl;
            // mainMenu();
        }
        mainMenu();
    }
    else
    {
        // system("cls");
        cout << "You are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function." << endl;
        mainMenu();
    }
};
void listBooks()
{
    system("cls");
    ifstream fin("data/booklist.csv");
    if (!fin.is_open())
    {
        cerr << "Error opening file: booklist.csv" << endl;
    }
    string line;
    vector<Book> books;
    while (getline(fin, line))
    {
        stringstream inputString(line);
        string title, author, genre, issueDate, returnDate, isBorrowed, username;
        getline(inputString, title, ',');
        getline(inputString, author, ',');
        getline(inputString, genre, ',');
        getline(inputString, issueDate, ',');
        getline(inputString, returnDate, ',');
        getline(inputString, username, '\n');

        Book book(title, author, genre, issueDate, returnDate, username);
        books.push_back(book);
    }
    cout << "========================================" << endl;
    cout << "           Available Books (" << books.size() << ")      " << endl;
    cout << "========================================" << endl;
    for (int i = 0; i < books.size(); i++)
    {
        cout << "===============( " << i + 1 << " )===============" << endl;
        Book book = books[i];
        book.display();
        cout << endl;
        // Sleep(250);
    }
    cout << "Press any key to go to main menu." << endl;
    cout << "--> ";
    cin.get();
    cin.get();
    system("cls");
    welcome();
};
void borrowBook()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "               Borrow Book              " << endl;
    cout << "========================================" << endl;
    if (loggedInAsStudent)
    {
        ifstream fin("data/booklist.csv", ios::in);
        if (!fin.is_open())
        {
            cerr << "Error Opening CSV file" << endl;
        }

        bool bookBorrowed = false;
        string line;
        int bookNum, currentBook = 1;
        cout << "Enter the book number to borrow" << endl;
    A:
        cout << "--> ";
        cin >> bookNum;
        cin.ignore();
        system("cls");
        ofstream fout("data/TEMP.csv", ios::out);

        string username = Alias.substr(0, Alias.size() - 2);
        string title, author, genre, issueDate, returnDate;

        while (getline(fin, line))
        {
            if (currentBook == bookNum)
            {
                stringstream inputString(line);
                getline(inputString, title, ',');
                getline(inputString, author, ',');
                getline(inputString, genre, ',');
                getline(inputString, issueDate, ',');
                getline(inputString, returnDate, ',');
                // getline(inputString, username, '\n');

                cout << "---------(Book-" << currentBook << " is selected)--------" << endl;
                cout << "Title: " << title << endl;
                cout << "Author: " << author << endl;
                cout << "Genre: " << genre << endl;

                if (issueDate != " NULL" || returnDate != " NULL")
                {
                    cout << "\033[1;31mBook is not available." << endl;
                    cout << "Please select another book.\033[0m" << endl;
                    goto A;
                }

                cout << "\033[1;32mAvailable to borrow.\033[0m" << endl;
                cout << "----------------------------------------" << endl;
                cout << "Are you sure you want to borrow this book?" << endl;
                cout << "1. Yes" << endl;
                cout << "2. No" << endl;
                cout << "--> ";
                string choice;
                cin >> choice;
                cin.ignore();
                if (choice == "2")
                {
                    system("cls");
                    cout << "Book is not borrowed." << endl;
                    goto L;
                }
                else if (choice == "1")
                {
                    cout << "Borrowing book..." << endl;
                }
                else
                {
                    system("cls");
                    cout << "Invalid input." << endl;
                    goto L;
                }
                cout << "\033[1;43;30mPlease double check everything.\033[0m" << endl;
                cout << "What's the issue date?(YYYY-MM-DD)\n-->";
                getline(cin, issueDate);
                cout << "What's the return date?(YYYY-MM-DD)\n-->";
                getline(cin, returnDate);

                if (issueDate.empty() && returnDate.empty())
                {
                    cout << "You must enter the issue and return date." << endl;
                    goto L;
                    // fout << title << ", " << author << ", " << genre << ", " << i << ", " << r << ", " << username << '\n';
                }
                else
                {
                    fout << title << "," << author << "," << genre << ", " << issueDate << ", " << returnDate << ", " << username << '\n';
                    bookBorrowed = true;
                }
            }
            else
            {
                fout << line << '\n';
            }
            currentBook++;
        }
        fin.close();
        fout.close();
        if (bookBorrowed)
        {
            system("cls");
            cout << "Book borrowed successfully." << endl;
            remove("data/booklist.csv");
            rename("data/TEMP.csv", "data/booklist.csv");
        }
        else
        {
            cout << "Book not found." << endl;
        L:
            remove("data/TEMP.csv");
        }
        welcome();
    }
    else
    {
        cout << "You are not logged in as student." << endl;
        cout << "Please log in as student to use this function." << endl;
        mainMenu();
    }
};
void addBook()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "                 Add Book               " << endl;
    cout << "========================================" << endl;
    if (loggedInAsAdmin)
    {
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
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
        mainMenu();
    }
    else
    {
        cout << "You are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function." << endl;
        mainMenu();
    }
};
void searchBook()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "               Book Search              " << endl;
    cout << "========================================" << endl;
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
    bool found = false;
    while (getline(find, book))
    {
        stringstream inputString(book);
        string title, author, genre;
        getline(inputString, title, ',');
        getline(inputString, author, ',');
        getline(inputString, genre, ',');
        // getline(inputString, issueDate, ',');
        // getline(inputString, returnDate, ',');
        // getline(inputString, username, '\n');
        i++;
        if (book.find(target) != string::npos)
        {
            system("cls");
            cout << "Found entity at book " << i << ":" << endl;
            cout << "Title: " << title << endl;
            cout << "Author: " << author << endl;
            cout << "Genre: " << genre << endl;
            cout << "----------------------------------------" << endl;

            found = true;
            break;
        }
    }

    if (!found)
    {
        system("cls");
        cout << "Book not found! Perhaps a typo?" << endl;
    }
    find.close();
    welcome();
}
void deleteBook()
{
    cout << "\033[31m========================================" << endl;
    cout << "               Delete Book              " << endl;
    cout << "========================================\033[0m" << endl;
    if (loggedInAsAdmin)
    {
        ifstream fin("data/booklist.csv", ios::in);
        if (!fin.is_open())
        {
            cerr << "Error Opening CSV file" << endl;
            return;
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
        fin.close();
        fout.close();

        if (bookFound)
        {
            remove("data/booklist.csv");
            rename("data/TEMP.csv", "data/booklist.csv");
            cout << "Book deleted successfully." << endl;
            mainMenu();
        }
        else
        {
            remove("data/TEMP.csv");
            cout << "Book not found." << endl;
            mainMenu();
        }
    }
    else
    {
        cout << "You are not logged in as admin." << endl;
        mainMenu();
    }
}
void editBook()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "                Edit Book               " << endl;
    cout << "========================================" << endl;
    if (loggedInAsAdmin)
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

        string title, author, genre, issueDate, returnDate, username;

        while (getline(fin, line))
        {
            if (currentBook == bookNum)
            {
                stringstream inputString(line);
                getline(inputString, title, ',');
                getline(inputString, author, ',');
                getline(inputString, genre, ',');
                getline(inputString, issueDate, ',');
                getline(inputString, returnDate, ',');
                getline(inputString, username, '\n');
                if (username != "NULL")
                {
                    cout << "\033[1;31mBook is borrowed by #" << username << ".\nYou can't edit borrowed books.\033[0m" << endl;
                    Sleep(2000);
                    mainMenu();
                }
                cout << "\033[1;43;30mPlease double check the spellings.\033[0m" << endl;
                cout << "What's the title?\n-->";
                getline(cin, title);
                cout << "Who's the author?\n-->";
                getline(cin, author);
                cout << "What's the genre?\n-->";
                getline(cin, genre);
                cout << "What's the issue date?\n-->";
                getline(cin, issueDate);
                cout << "What's the return date?\n-->";
                getline(cin, returnDate);
                if (issueDate == "")
                {
                    issueDate = "NULL";
                    returnDate = "NULL";
                }
                fout << title << ", " << author << ", " << genre << ", " << issueDate << ", " << returnDate << '\n';
                bookFound = true;
            }
            else
            {
                fout << line << '\n';
            }
            currentBook++;
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
    }
    else
    {
        cout << "You are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function." << endl;
        mainMenu();
    }
};
void mainMenu()
{
    cout << "Going to main menu in: ";
    for (int i = 3; i >= 1; i--)
    {
        cout << i << "...";
        Sleep(1000);
    }
    cout << endl;
    system("cls");
    welcome();
};
void logOut()
{
    if (Alias == "Guest\n")
    {
        cout << "You are not logged in." << endl;
        cout << "Please log in to use this function." << endl;
        mainMenu();
    }
    else
    {
        loggedInAsAdmin = false;
        loggedInAsStudent = false;
        Alias = "Guest!\n";
        system("cls");
        cout << "Logged out successfully." << endl;
        mainMenu();
    }
};