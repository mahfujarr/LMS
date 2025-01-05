# LMS
### Library Management System

<br>

I have been tasked to build a library management system as followed in question number 1 in ```project questions.pdf```

## Report

### Overview
The Library Management System (LMS) is a console-based application written in C++ that allows users to manage a library's book inventory. The system supports functionalities for both students and administrators, including logging in, searching for books, borrowing and returning books, and generating reports.

### Features
1. **Login System**:
   - Students and administrators can log in using their credentials.
   - Administrators have a default password of "admin".

2. **Book Management**:
   - **Add Book**: Administrators can add new books to the inventory.
   - **Edit Book**: Administrators can edit the details of existing books.
   - **Delete Book**: Administrators can delete books from the inventory.
   - **List Books**: All users can list all available books in the library.
   - **Search Book**: Users can search for books by title, author, or genre.

3. **Borrow and Return Books**:
   - Students can borrow available books and specify the issue and return dates.
   - Administrators can return books on behalf of students and calculate fines for late returns.

4. **Reports**:
   - Administrators can generate reports showing the total number of books, borrowed books, available books, and the most borrowed book.

### Classes and Functions
- **Class `Book`**:
  - Attributes: `Title`, `Author`, `Genre`, `IssueDate`, `ReturnDate`, `Student`.
  - Methods: `display()`, `add()`.

- **Functions**:
  - `welcome()`: Displays the welcome screen and main menu.
  - `studentLogin()`: Handles student login.
  - `adminLogin()`: Handles admin login.
  - `createAccount()`: Allows admin to create new student accounts.
  - `listBooks()`: Lists all books in the inventory.
  - `borrowBook()`: Allows students to borrow books.
  - `returnBook()`: Allows admin to return books.
  - `addBook()`: Allows admin to add new books.
  - `searchBook()`: Allows users to search for books.
  - `deleteBook()`: Allows admin to delete books.
  - `editBook()`: Allows admin to edit book details.
  - `report()`: Generates a report of the library's inventory.
  - `mainMenu()`: Navigates back to the main menu.
  - `logOut()`: Logs out the current user.

### File Structure
- **`LMS.cpp`**: Main source code file containing the implementation of the Library Management System.
- **`data/booklist.csv`**: CSV file storing the list of books.
- **`data/credentials.txt`**: Text file storing user credentials.
- **`data/TEMP.csv`**: Temporary file used during book borrowing and returning operations.

### Usage
1. Compile the `LMS.cpp` file using a C++ compiler.
2. Run the compiled executable to start the Library Management System.
3. Follow the on-screen instructions to log in, manage books, and generate reports.

### Conclusion
The Library Management System provides a comprehensive solution for managing a library's book inventory, supporting both student and administrator roles. The system ensures efficient book management and easy access to library resources.