#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <windows.h>
using namespace std;

const string credFile = "data/credentials.txt";
const string bookFile = "data/booklist.csv";
const string tempFile = "data/TEMP.csv";

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
        ofstream bookList(bookFile, ios::app);
        if (bookList.is_open())
        {
            bookList << Title << ", ";
            bookList << Author << ", ";
            bookList << Genre << ", ";
            bookList << IssueDate << ", ";
            bookList << ReturnDate << ",";
            bookList << " " << ",";
            bookList << "0" << "\n";
            cout << "Book Added Successfully." << endl;
            bookList.close();
        }
        else
        {
            cout << "Error opening the file 'booklist.csv'" << endl;
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
void returnBook();
void addBook();
void searchBook();
void deleteBook();
void editBook();
void report();
void logOut();
void mainMenu();

int main()
{
    system("cls");
    cout << "\033[1m";
    cout << R"(____    __    ____  _______  __        ______   ______   .___  ___.  _______    .___________.  ______  
\   \  /  \  /   / |   ____||  |      /      | /  __  \  |   \/   | |   ____|   |           | /  __  \ 
 \   \/    \/   /  |  |__   |  |     |  ,----'|  |  |  | |  \  /  | |  |__      `---|  |----`|  |  |  |
  \            /   |   __|  |  |     |  |     |  |  |  | |  |\/|  | |   __|         |  |     |  |  |  |
   \    /\    /    |  |____ |  `----.|  `----.|  `--'  | |  |  |  | |  |____        |  |     |  `--'  |
    \__/  \__/     |_______||_______| \______| \______/  |__|  |__| |_______|       |__|      \______/ )"
         << endl
         << endl;
    Sleep(1000);
    // system("cls");
    cout << R"( __       __  .______   .______          ___      .______     ____    ____
|  |     |  | |   _  \  |   _  \        /   \     |   _  \    \   \  /   /
|  |     |  | |  |_)  | |  |_)  |      /  ^  \    |  |_)  |    \   \/   / 
|  |     |  | |   _  <  |      /      /  /_\  \   |      /      \_    _/  
|  `----.|  | |  |_)  | |  |\  \----./  _____  \  |  |\  \----.   |  |    
|_______||__| |______/  | _| `._____/__/     \__\ | _| `._____|   |__|    )"
         << endl
         << endl;
    Sleep(1000);
    // system("cls");
    cout << R"(.___  ___.      ___      .__   __.      ___       _______  _______ .___  ___.  _______ .__   __. .___________.
|   \/   |     /   \     |  \ |  |     /   \     /  _____||   ____||   \/   | |   ____||  \ |  | |           |
|  \  /  |    /  ^  \    |   \|  |    /  ^  \   |  |  __  |  |__   |  \  /  | |  |__   |   \|  | `---|  |----`
|  |\/|  |   /  /_\  \   |  . `  |   /  /_\  \  |  | |_ | |   __|  |  |\/|  | |   __|  |  . `  |     |  |     
|  |  |  |  /  _____  \  |  |\   |  /  _____  \ |  |__| | |  |____ |  |  |  | |  |____ |  |\   |     |  |     
|__|  |__| /__/     \__\ |__| \__| /__/     \__\ \______| |_______||__|  |__| |_______||__| \__|     |__|     )"
         << endl
         << endl;
    Sleep(1000);
    // system("cls");
    cout << R"(     _______.____    ____  _______.___________. _______ .___  ___.
    /       |\   \  /   / /       |           ||   ____||   \/   |
   |   (----` \   \/   / |   (----`---|  |----`|  |__   |  \  /  |
    \   \      \_    _/   \   \       |  |     |   __|  |  |\/|  |
.----)   |       |  | .----)   |      |  |     |  |____ |  |  |  |
|_______/        |__| |_______/       |__|     |_______||__|  |__|)"
         << endl
         << endl;
    Sleep(1000);
    cout << "\033[32mPress any key to start the program." << endl;
    cout << "--> \033[0m";
    cin.get();
    system("cls");

    welcome();
}

void welcome()
{
    if (Alias != "")
    {
        cout << "\033[1,36mHello, " << Alias << "\033[0m";
        (Alias == "Guest!\n" ? cout << "" << endl : cout << "                               00.\033[31mLogout\033[0m" << endl);
    }
    cout << "\033[1;36m========================================\033[0m" << endl;
    if (loggedInAsAdmin)
    {
        cout << "\033[1;36m               Main Menu             (A)\033[0m" << endl;
    }
    else if (loggedInAsStudent)
    {
        cout << "\033[1;36m               Main Menu             (S)\033[0m" << endl;
    }
    else
    {
        cout << "\033[1;36m               Main Menu             (G)\033[0m" << endl;
    }
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[2mPress any available option to begin: " << endl;
    cout << "----------------------------------------\033[0m" << endl;
    cout << "1. \033[1;32mLogin as student\033[0m" << endl;
    cout << "2. \033[1;32mLogin as admin\033[0m" << endl;
    cout << "3. \033[1;32mSearch Books\033[0m" << endl;
    cout << "4. \033[1;32mList all books\033[0m" << endl;
    if (loggedInAsStudent || loggedInAsAdmin)
    {
        cout << "5. " << (loggedInAsAdmin ? "\033[2mBorrow Book\033[0m" : "\033[1;32mBorrow Book\033[0m") << endl;
    }
    if (loggedInAsAdmin)
    {
        cout << "6. \033[1;32mReturn Book\033[0m" << endl;
        cout << "7. \033[1;32mCreate student account\033[0m" << endl;
        cout << "8. \033[1;32mAdd Books\033[0m" << endl;
        cout << "9. \033[1;32mEdit Books\033[0m" << endl;
        cout << "10. \033[1;31mDelete Books\033[0m" << endl;
    }
    cout << (loggedInAsAdmin ? "\033[34mType 'report' to generate a report.\033[0m" : "") << endl;
    cout << "0. \033[1;31mExit the program\033[0m" << endl;
    cout << "----------------------------------------" << endl;

    bool validInput = false;

    while (!validInput)
    {
        cout << "--> ";
        string x;
        if (!(cin >> x))
        {
            cin.ignore();
            cin.ignore();
            cout << "Invalid input. Please enter a number between 1 and 5." << endl;
            continue;
        }
        if (x == "0")
        {
            system("cls");
            cout << "Program is terminated.\nHope to see you soon," << Alias << endl;
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
            searchBook();
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
            returnBook();
            validInput = true;
        }
        else if (x == "7")
        {
            createAccount();
            validInput = true;
        }
        else if (x == "8")
        {
            addBook();
            validInput = true;
        }
        else if (x == "9")
        {
            editBook();
            validInput = true;
        }
        else if (x == "10")
        {
            deleteBook();
            validInput = true;
        }
        else if (x == "00")
        {
            logOut();
            validInput = true;
        }
        else if (x == "report")
        {
            report(); // Only available for admin
            validInput = true;
        }
        else
        {
            cout << "Invalid input. Please enter a number between 0 and 10." << endl;
        }
    }
}
void studentLogin()
{
    system("cls");
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m              Student Login             \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
    loggedInAsAdmin = false;
    string ID, pass, line;
    ifstream cred(credFile);

    if (!cred)
    {
        cout << "Unable to open 'credentials.txt'" << endl;
        cout << "Maybe the file is missing?" << endl;
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
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m               Admin Login              \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
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
        mainMenu();
    }
};
void createAccount()
{
    system("cls");
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m        Create new student account      \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
    if (loggedInAsAdmin)
    {
        string ID, pass;

        cout << "Please enter student's ID: ";
        cin >> ID;
        ifstream fin(credFile);
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
        ofstream cred(credFile, ios::app);
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
        }
        mainMenu();
    }
    else
    {
        // system("cls");
        cout << "\033[1;31mYou are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function.\033[0m" << endl;
        mainMenu();
    }
};
void listBooks()
{
    system("cls");
    ifstream fin(bookFile);
    if (!fin.is_open())
    {
        cerr << "Error opening file: booklist.csv" << endl;
    }
    string line;
    vector<Book> books;
    while (getline(fin, line))
    {

        string title, author, genre, issueDate, returnDate, isBorrowed, username, borrowTimes;
        stringstream inputString(line);
        getline(inputString, title, ',');
        getline(inputString, author, ',');
        getline(inputString, genre, ',');
        getline(inputString, issueDate, ',');
        getline(inputString, returnDate, ',');
        getline(inputString, username, ',');
        getline(inputString, borrowTimes, '\n');

        Book book(title, author, genre, issueDate, returnDate, username);
        books.push_back(book);
    }
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m           Available Books (" << books.size() << ")      \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
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
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m               Borrow Book              \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
    if (loggedInAsStudent)
    {
        ifstream fin(bookFile, ios::in);
        if (!fin.is_open())
        {
            cerr << "Error Opening CSV file" << endl;
        }

        bool bookBorrowed = false;
        bool coutNotAvailable = false;
        string line;
        int bookNum, currentBook = 1;
        cout << "Enter the book number to borrow" << endl;
        cout << "--> ";
        cin >> bookNum;
        cin.ignore();
        system("cls");
        ofstream fout(tempFile, ios::out);

        string username = Alias.substr(0, Alias.size() - 2);
        string title, author, genre, issueDate, returnDate, borrowTimes, name;

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
                getline(inputString, name, ',');
                getline(inputString, borrowTimes, '\n');

                cout << "---------(Book-" << currentBook << " is selected)--------" << endl;
                cout << "Title: " << title << endl;
                cout << "Author: " << author << endl;
                cout << "Genre: " << genre << endl;
                cout << "Borrowed " << borrowTimes << " times." << endl;

                if (issueDate != " NULL" || returnDate != " NULL")
                {
                    cout << "\033[1;31mBook is not available." << endl;
                    cout << "Please select another book.\033[0m" << endl;
                    // bool coutNotAvailable = true;
                    cout << "Press any key to go to main menu." << endl;
                    cout << "--> ";
                    cin.get();
                    system("cls");
                    welcome();
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
                    cout << "\033[1;31mBook is not borrowed.\033[0m" << endl;
                    coutNotAvailable = true;
                    break;
                }
                else if (choice == "1")
                {
                    cout << "Borrowing book..." << endl;
                }
                else
                {
                    system("cls");
                    cout << "Invalid input." << endl;
                }
                cout << "\033[1;33mPlease double check the dates to avoid fines.\033[0m" << endl;
                cout << "What's the issue date?(DD-MM-YYYY)\n-->";
                getline(cin, issueDate);
                cout << "What's the return date?(DD-MM-YYYY)\n-->";
                getline(cin, returnDate);

                if (issueDate.empty() || returnDate.empty())
                {
                    system("cls");
                    cout << "\033[1;31mYou must enter the issue and return date." << endl;
                    cout << "Book is not borrowed.\033[0m" << endl;
                    coutNotAvailable = true;
                }
                else
                {
                    borrowTimes = to_string(stoi(borrowTimes) + 1);
                    fout << title << "," << author << "," << genre << ", " << issueDate << ", " << returnDate << ", " << username << "," << borrowTimes << '\n';
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
        if (bookBorrowed == true)
        {
            if (remove(bookFile.c_str()) != 0)
            {
                cerr << "Error deleting file: booklist.csv" << endl;
            }
            if (rename(tempFile.c_str(), bookFile.c_str()) != 0)
            {
                cerr << "Error renaming file: TEMP.csv" << endl;
            }
            system("cls");
            cout << "\033[1;32mBook borrowed successfully.\033[0m" << endl;
        }
        else
        {
            cout << ((coutNotAvailable) ? "" : "\033[1;31mBook not found.\033[0m") << endl;
            if (remove(tempFile.c_str()) != 0)
            {
                cerr << "Error deleting file: TEMP.csv" << endl;
            }
        }
        mainMenu();
    }
    else
    {
        cout << "\033[1;31mYou are not logged in as student." << endl;
        cout << "Please log in as student to use this function.\033[0m" << endl;
        mainMenu();
    }
};
void returnBook()
{
    if (loggedInAsAdmin)
    {
        system("cls");
        cout << "\033[1;36m========================================\033[0m" << endl;
        cout << "\033[1;36m               Return Book              \033[0m" << endl;
        cout << "\033[1;36m========================================\033[0m" << endl;
        ifstream fin(bookFile, ios::in);
        if (!fin.is_open())
        {
            cerr << "Error Opening CSV file" << endl;
        }

        bool bookReturned = false;
        string line;
        int bookNum, currentBook = 1;
        cout << "Enter the book number to return" << endl;

        cout << "--> ";
        cin >> bookNum;
        cin.ignore();
        system("cls");
        ofstream fout(tempFile, ios::out);

        string title, author, genre, issueDate, returnDate, username, borrowTimes;

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
                getline(inputString, username, ',');
                getline(inputString, borrowTimes, '\n');

                cout << "---------(Book-" << currentBook << " is selected)--------" << endl;
                cout << "Title: " << title << endl;
                cout << "Author: " << author << endl;
                cout << "Genre: " << genre << endl;
                cout << "Issue Date: " << issueDate << endl;
                cout << "Return Date: " << returnDate << endl;
                cout << "Borrowed by: " << username << endl;
                cout << "----------------------------------------" << endl;
                cout << "How many days are the student late?" << endl;
                int daysLate;
                cout << "--> ";
                cin >> daysLate;
                if (daysLate > 0)
                {
                    system("cls");
                    cout << "The student is " << daysLate << " days late." << endl;
                    cout << "The fine is: " << daysLate * 10 << " BDT" << endl;
                }
                else
                {
                    system("cls");
                    cout << "Clear!! No fine for this student." << endl;
                }
                fout << title << "," << author << "," << genre << "," << " NULL" << "," << " NULL" << ',' << " " << ',' << borrowTimes << '\n';
                bookReturned = true;
            }
            else
            {
                fout << line << '\n';
            }
            currentBook++;
        }
        fin.close();
        fout.close();
        if (bookReturned == true)
        {
            cout << "Book returned successfully." << endl;
            if (remove(bookFile.c_str()) != 0)
            {
                cerr << "Error deleting file: booklist.csv" << endl;
            }
            if (rename(tempFile.c_str(), bookFile.c_str()) != 0)
            {
                cerr << "Error renaming file: TEMP.csv" << endl;
            }
        }
        else
        {
            cout << "Book not found." << endl;
            if (remove(tempFile.c_str()) != 0)
            {
                cerr << "Error deleting file: TEMP.csv" << endl;
            }
        }
        mainMenu();
    }
    else
    {
        cout << "\033[1;31mYou are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function.\033[0m" << endl;
        mainMenu();
    }
};
void addBook()
{
    system("cls");
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m                 Add Book               \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
    if (loggedInAsAdmin)
    {
        cin.ignore();
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
        cout << "\033[1;31mYou are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function.\033[0m" << endl;
        mainMenu();
    }
};
void searchBook()
{
    system("cls");
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m               Book Search              \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
    ifstream find(bookFile);
    if (!find.is_open())
    {
        cerr << "Error opening file: booklist.csv" << endl;
        return;
    }
    cin.ignore();
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
        cout << "\033[1;31mBook not found!\n\033[1;33mPerhaps a typo?\033[0m" << endl;
    }
    find.close();
    welcome();
}
void deleteBook()
{
    system("cls");
    cout << "\033[31m========================================" << endl;
    cout << "               Delete Book              " << endl;
    cout << "========================================\033[0m" << endl;
    if (loggedInAsAdmin)
    {
        ifstream fin(bookFile, ios::in);
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
        ofstream fout(tempFile, ios::out);
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

        if (bookFound == true)
        {
            cout << "Book deleted successfully." << endl;
            if (remove(bookFile.c_str()) != 0)
            {
                cerr << "Error deleting file: booklist.csv" << endl;
            }
            if (rename(tempFile.c_str(), bookFile.c_str()) != 0)
            {
                cerr << "Error renaming file: TEMP.csv" << endl;
            }
        }
        else
        {
            if (remove(tempFile.c_str()) != 0)
            {
                cerr << "Error deleting file: TEMP.csv" << endl;
            }
            cout << "Book not found." << endl;
        }
        mainMenu();
    }
    else
    {
        cout << "\033[1;31mYou are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function.\033[0m" << endl;
        mainMenu();
    }
}
void editBook()
{
    system("cls");
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m                Edit Book               \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
    if (loggedInAsAdmin)
    {
        ifstream fin(bookFile, ios::in);
        ofstream fout(tempFile, ios::out);
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

        string title, author, genre, issueDate, returnDate, username, borrowTimes;

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
                getline(inputString, username, ',');
                getline(inputString, borrowTimes, '\n');
                if (username != " ")
                {
                    cout << "\033[1;31mBook is borrowed by #" << username << ".\nYou can't edit borrowed books.\033[0m" << endl;
                    Sleep(2000);
                    mainMenu();
                }
                cout << "---------(Book-" << currentBook << " is selected)--------" << endl;
                cout << "Title: " << title << endl;
                cout << "Author: " << author << endl;
                cout << "Genre: " << genre << endl;
                cout << "Issue Date: " << issueDate << endl;
                cout << "Return Date: " << returnDate << endl;
                cout << "----------------------------------------" << endl;
                cout << "\033[1;33mPlease double check the spellings.\033[0m" << endl;
                cout << "What's the title?\n-->";
                getline(cin, title);
                cout << "Who's the author?\n-->";
                getline(cin, author);
                cout << "What's the genre?\n-->";
                getline(cin, genre);

                fout << title << ", " << author << ", " << genre << "," << issueDate << "," << returnDate << ", " << "" << "," << borrowTimes << '\n';
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

        if (bookFound == true)
        {
            system("cls");
            cout << "Book edited successfully." << endl;
            if (remove(bookFile.c_str()) != 0)
            {
                cerr << "Error deleting file: booklist.csv" << endl;
            }
            if (rename(tempFile.c_str(), bookFile.c_str()) != 0)
            {
                cerr << "Error renaming file: TEMP.csv" << endl;
            }
        }
        else
        {
            cout << "Book not found." << endl;
            if (remove(tempFile.c_str()) != 0)
            {
                cerr << "Error deleting file: TEMP.csv" << endl;
            }
        }
        mainMenu();
    }
    else
    {
        cout << "\033[1;31mYou are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function.\033[0m" << endl;
        mainMenu();
    }
};
void report()
{
    system("cls");
    cout << "\033[1;36m========================================\033[0m" << endl;
    cout << "\033[1;36m                 Report                 \033[0m" << endl;
    cout << "\033[1;36m========================================\033[0m" << endl;
    if (loggedInAsAdmin)
    {
        ifstream fin(bookFile, ios::in);
        if (!fin.is_open())
        {
            cerr << "Error Opening CSV file" << endl;
        }
        string line, Title, Author, Genre;
        int totalBooks = 0, borrowedBooks = 0, mostBorrowed = 0;
        while (getline(fin, line))
        {
            totalBooks++;
            string title, author, genre, issueDate, returnDate, username, borrowTimes;
            stringstream inputString(line);
            getline(inputString, title, ',');
            getline(inputString, author, ',');
            getline(inputString, genre, ',');
            getline(inputString, issueDate, ',');
            getline(inputString, returnDate, ',');
            getline(inputString, username, ',');
            getline(inputString, borrowTimes, '\n');

            if (issueDate != " NULL" || returnDate != " NULL")
            {
                borrowedBooks++;
            }
            if (mostBorrowed < stoi(borrowTimes))
            {
                mostBorrowed = stoi(borrowTimes);
                Title = title;
                Author = author;
                Genre = genre;
            }
        }
        cout << "Total books: " << totalBooks << endl;
        cout << "Borrowed books: " << borrowedBooks << endl;
        cout << "Available books: " << totalBooks - borrowedBooks << endl;
        cout << endl;
        cout << "==========Most borrowed book==========" << endl;
        cout << "Title: " << Title << endl;
        cout << "Author: " << Author << endl;
        cout << "Genre: " << Genre << endl;
        cout << "Borrowed " << mostBorrowed << " times." << endl;
        cout << "----------------------------------------" << endl;
        cout << "Press any key to go to main menu." << endl;
        cout << "--> ";
        cin.get();
        cin.get();
        system("cls");
        welcome();
    }
    else
    {
        cout << "\033[31mYou are not logged in as admin." << endl;
        cout << "Please log in as admin to use this function.\033[0m" << endl;
        mainMenu();
    }
};
void mainMenu()
{
    cout << "\033[2mGoing to main menu in: ";
    for (int i = 3; i >= 1; i--)
    {
        cout << i << "...";
        Sleep(1000);
    }
    cout << "\033[0m";
    cout << endl;
    system("cls");
    welcome();
};
void logOut()
{
    if (Alias == "Guest!\n")
    {
        system("cls");
        cout << "\033[31mYou are not logged in." << endl;
        cout << "Please log in to use this function.\033[0m" << endl;
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