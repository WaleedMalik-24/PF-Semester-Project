#include <iostream>
#include <cstring>
#include <iomanip>

using namespace std;

// Constants
const int MAX_STUDENTS = 20;
const int MAX_BOOKS = 15;
const int MAX_NAME_LENGTH = 50;

// Global variables
int student_count = 0;
int book_count = 0;
double student_balance[MAX_STUDENTS];
int student_roll[MAX_STUDENTS];
char student_name[MAX_STUDENTS][MAX_NAME_LENGTH];
char book_title[MAX_BOOKS][MAX_NAME_LENGTH];
char book_author[MAX_BOOKS][MAX_NAME_LENGTH];
int book_isbn[MAX_BOOKS];
bool book_available[MAX_BOOKS];

// Function prototypes
void create_account();
void display(int roll);
void deposit_amount(int roll, double amount);
void issue_item(int roll);
void display_sorted();
int find_student(int roll);
int find_book(int isbn);
void add_book();
void edit_book();
void view_books();

int main() {
    // Initialization
    for (int i = 0; i < MAX_BOOKS; i++) {
        strcpy(book_title[i], "Title");
        strcpy(book_author[i], "Author");
        book_isbn[i] = i + 1000;
        book_available[i] = true;
    }
    book_count = MAX_BOOKS;

    int option;
    bool is_admin;
    string password;

    while (true) {
        cout << "Enter 1 for Admin or 2 for Student (0 to exit): ";
        cin >> option;

        if (option == 0) {
            break;
        }

        is_admin = (option == 1);

        cout << "Enter password: ";
        cin >> password;

        if (password == "password") {
            if (is_admin) {
                cout << "Admin Menu:\n1. Add Book\n2. Edit Book\n3. View Books\n4. Display Sorted Students\n5. Display Student\nChoose option: ";
                cin >> option;

                switch (option) {
                    case 1: add_book(); break;
                    case 2: edit_book(); break;
                    case 3: view_books(); break;
                    case 4: display_sorted(); break;
                    case 5: {
                        int roll;
                        cout << "Enter roll number: ";
                        cin >> roll;
                        display(roll);
                        break;
                    }
                    default: cout << "Invalid option!\n"; break;
                }
  } else {
                int roll;
                cout << "Enter roll number: ";
                cin >> roll;

                int index = find_student(roll);
                if (index == -1) {
                    cout << "Student not found. Create account? (1 to create): ";
                    cin >> option;
                    if (option == 1) {
                        create_account();
                    }
                } else {
                    cout << "Student Menu:\n1. Display Account\n2. Deposit Amount\n3. Issue Book\nChoose option: ";
                    cin >> option;

                    switch (option) {
                        case 1: display(roll); break;
                        case 2: {
                            double amount;
                            cout << "Enter amount to deposit: ";
                            cin >> amount;
                            deposit_amount(roll, amount);
                            break;
                        }
                        case 3: issue_item(roll); break;
                        default: cout << "Invalid option!\n"; break;
                    }
                }
            }
        } else {
            cout << "Incorrect password!\n";
        }
    }

    return 0;
}

void create_account() {
    if (student_count >= MAX_STUDENTS) {
        cout << "Student limit reached. Cannot create more accounts.\n";
        return;
    }

    int roll;
    cout << "Enter roll number: ";
    cin >> roll;

    if (find_student(roll) != -1) {
        cout << "Account already exists for this roll number.\n";
        return;
    }

    student_roll[student_count] = roll;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(student_name[student_count], MAX_NAME_LENGTH);

    double initial_deposit;
    cout << "Enter initial deposit: ";
    cin >> initial_deposit;

    if (initial_deposit < 50) {
        cout << "Initial deposit must be at least $50.\n";
        return;
    }

    student_balance[student_count] = initial_deposit - 20 - 30; // Account opening and security deposit
    student_count++;
}

void display(int roll) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }
    cout << "Roll No: " << student_roll[index] << endl;
    cout << "Name: " << student_name[index] << endl;
    cout << "Balance: $" << fixed << setprecision(2) << student_balance[index] << endl;
}
void deposit_amount(int roll, double amount) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    student_balance[index] += amount;
    cout << "New balance: $" << fixed << setprecision(2) << student_balance[index] << endl;
}

void issue_item(int roll) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Available books:\n";
    for (int i = 0; i < book_count; i++) {
        if (book_available[i]) {
            cout << i + 1 << ". " << book_title[i] << " by " << book_author[i] << " (ISBN: " << book_isbn[i] << ")\n";
        }
    }

    int choice;
    cout << "Enter book number to issue (0 to cancel): ";
    cin >> choice;

    if (cin.fail() || choice < 0 || choice > book_count) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice!\n";
        return;
    }

    if (choice == 0) {
        return;
    }

    if (book_available[choice - 1] && student_balance[index] >= 2) {
        book_available[choice - 1] = false;
        student_balance[index] -= 2;
        cout << "Book issued successfully. New balance: $" << fixed << setprecision(2) << student_balance[index] << endl;
    } else {
        cout << "Cannot issue the book. Insufficient balance or book is unavailable.\n";
    }
}

void display_sorted() {
    for (int i = 0; i < student_count; i++) {
        for (int j = i + 1; j < student_count; j++) {
            if (student_roll[i] > student_roll[j]) {
                swap(student_roll[i], student_roll[j]);
                swap(student_balance[i], student_balance[j]);
                swap(student_name[i], student_name[j]);
            }
        }
    }

    for (int i = 0; i < student_count; i++) {
        cout << student_roll[i] << " - " << student_name[i] << " - Balance: $" << fixed << setprecision(2) << student_balance[i] << endl;
    }
}
// Find a student by their roll number
int find_student(int roll) {
    for (int i = 0; i < student_count; i++) {
        if (student_roll[i] == roll) {
            return i;
        }
    }
    return -1;
}

// Find a book by its ISBN
int find_book(int isbn) {
    for (int i = 0; i < book_count; i++) {
        if (book_isbn[i] == isbn) {
            return i;
        }
    }
    return -1;
}

// Add a new book to the system
void add_book() {
    if (book_count >= MAX_BOOKS) {
        cout << "Book limit reached. Cannot add more books.\n";
        return;
    }

    cout << "Enter book title: ";
    cin.ignore();
    cin.getline(book_title[book_count], MAX_NAME_LENGTH);

    cout << "Enter book author: ";
    cin.getline(book_author[book_count], MAX_NAME_LENGTH);

    int isbn;
    cout << "Enter ISBN: ";
    cin >> isbn;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ISBN!\n";
        return;
    }

    if (find_book(isbn) != -1) {
        cout << "A book with this ISBN already exists.\n";
        return;
    }

    book_isbn[book_count] = isbn;
    book_available[book_count] = true;
    book_count++;
}

// Edit an existing book's details
void edit_book() {
    int isbn;
    cout << "Enter ISBN of the book to edit: ";
    cin >> isbn;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid ISBN!\n";
        return;
    }

    int index = find_book(isbn);
    if (index == -1) {
        cout << "Book not found.\n";
        return;
    }

    cout << "Current book title: " << book_title[index] << endl;
    cout << "Enter new book title: ";
    cin.ignore();
    cin.getline(book_title[index], MAX_NAME_LENGTH);

    cout << "Current book author: " << book_author[index] << endl;
    cout << "Enter new book author: ";
    cin.getline(book_author[index], MAX_NAME_LENGTH);

    cout << "Book details updated.\n";
}

// View all books in the system
void view_books() {
    for (int i = 0; i < book_count; i++) {
        cout << "Title: " << book_title[i] << endl;
        cout << "Author: " << book_author[i] << endl;
        cout << "ISBN: " << book_isbn[i] << endl;
        cout << "Available: " << (book_available[i] ? "Yes" : "No") << endl << endl;
    }
}

// Save student and book data to text files
void save_data() {
    ofstream student_file("students.txt");
    ofstream book_file("books.txt");

    if (!student_file.is_open() || !book_file.is_open()) {
        cout << "Error opening files for saving data!\n";
        return;
    }

    // Save student data
    student_file << student_count << endl;
    for (int i = 0; i < student_count; i++) {
        student_file << student_roll[i] << endl;
        student_file << student_name[i] << endl;
        student_file << student_balance[i] << endl;
    }

    // Save book data
    book_file << book_count << endl;
    for (int i = 0; i < book_count; i++) {
        book_file << book_title[i] << endl;
        book_file << book_author[i] << endl;
        book_file << book_isbn[i] << endl;
        book_file << book_available[i] << endl;
    }

    student_file.close();
    book_file.close();
}

// Load student and book data from text files
void load_data() {
    ifstream student_file("students.txt");
    ifstream book_file("books.txt");

    if (!student_file.is_open() || !book_file.is_open()) {
        cout << "Error opening files for loading data!\n";
        return;
    }

   




