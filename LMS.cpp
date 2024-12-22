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
        cout << "Availability: " << (IssueDate != " NULL" || ReturnDate != " NULL" ? "Not Available" : "Available") << endl;
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
            bookList << ReturnDate << ", ";
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
void navigate();

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

int main()
{
    system("cls");
    cout << R"(
 __        __   _                          
 \ \      / /__| | ___ ___  _ __ ___   ___ 
  \ \ /\ / / _ \ |/ __/ _ \| '_ ` _ \ / _ \
   \ V  V /  __/ | (_| (_) | | | | | |  __/
    \_/\_/ \___|_|\___\___/|_| |_| |_|\___|
                                           
)" << endl;

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
    if (Alias != "")
    {
        cout << "\033[1,36mHello, " << Alias << "\033[0m";
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
    cout << "Press available option below to begin: " << endl;
    cout << "----------------------------------------" << endl;
    cout << "1. \033[1;32mLogin as student\033[0m" << endl;
    cout << "2. \033[1;32mLogin as admin\033[0m" << endl;
    cout << (loggedInAsAdmin ? "3. \033[1;32mCreate student account\033[0m" : "3. Create student account") << endl;
    cout << "4. \033[1;32mList all books\033[0m" << endl;
    cout << (loggedInAsAdmin ? "5. \033[1;32mAdd Books\033[0m" : "5. Add Books") << endl;
    cout << "6. \033[1;32mSearch Books\033[0m" << endl;
    cout << (loggedInAsAdmin ? "7. \033[1;32mEdit Books\033[0m" : "7. Edit Books") << endl;
    cout << (loggedInAsAdmin ? "8. \033[1;31mDelete Books\033[0m" : "8. Delete Books") << endl;
    cout << "0. \033[1;31mExit the program\033[0m" << endl;
    cout << "----------------------------------------" << endl;

    bool validInput = false;

    while (!validInput)
    {
        cout << "--> ";
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
            cout << "Program is terminated.\nHope to see you soon," << Alias << "!" << endl;
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
                Sleep(2000);
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
    cout << "========================================" << endl;
    cout << "             Available Books            " << endl;
    cout << "========================================" << endl;
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
        string title, author, genre, issueDate, returnDate, isBorrowed;
        getline(inputString, title, ',');
        getline(inputString, author, ',');
        getline(inputString, genre, ',');
        getline(inputString, issueDate, ',');
        getline(inputString, returnDate, '\n');
        // getline(inputString, isBorrowed, '\n');

        Book book(title, author, genre, issueDate, returnDate);
        books.push_back(book);
    }
    system("cls");
    cout << "Listing all " << books.size() << " books." << endl;
    for (int i = 0; i < books.size(); i++)
    {
        cout << "===============( " << i + 1 << " )===============" << endl;
        Book book = books[i];
        book.display();
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
        }
        else
        {
            remove("data/TEMP.csv");
            cout << "Book not found." << endl;
        }
    }
    else
    {
        cout << "You are not logged in as admin." << endl;
    }
}

void editBook()
{
    system("cls");
    cout << "========================================" << endl;
    cout << "                Edit Book               " << endl;
    cout << "========================================" << endl;
    if (loggedInAsAdmin == true)
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
                cout << "\033[1;43;30mPlease double check the spellings.\033[0m" << endl;
                stringstream inputString(line);
                getline(inputString, title, ',');
                getline(inputString, author, ',');
                getline(inputString, genre, ',');
                getline(inputString, issueDate, ',');
                getline(inputString, returnDate, '\n');
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
void navigate() {

};