#include <iostream>
#include <iomanip>
#include <limits>
#include <cstring>
#include <fstream> // For file handling

using namespace std;

// Constants
const int MAX_STUDENTS = 20;
const int MAX_BOOKS = 15;
const int MAX_NAME_LENGTH = 50;

// Global Variables
int student_count = 0;
int book_count = 0;
int student_roll[MAX_STUDENTS];
char student_name[MAX_STUDENTS][MAX_NAME_LENGTH];
double student_balance[MAX_STUDENTS];
char book_title[MAX_BOOKS][MAX_NAME_LENGTH];
char book_author[MAX_BOOKS][MAX_NAME_LENGTH];
int book_isbn[MAX_BOOKS];
bool book_available[MAX_BOOKS];

// Function Prototypes
void create_account();
void display_account(int roll);
void deposit_amount(int roll, double amount);
void issue_book(int roll);
void return_book(int roll);
void display_sorted_students();
int find_student(int roll);
int find_book(int isbn);
void add_book();
void edit_book();
void view_books();
void save_data();
void load_data();

// Utility Functions
void clear_input() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Main Function
int main() {
    load_data();

    while (true) {
        cout << "\nWelcome to the Library System!\n";
        cout << "1. Admin\n2. Student\n0. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (cin.fail() || choice < 0 || choice > 2) {
            clear_input();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (choice == 0) {
            save_data();
            cout << "Data saved. Exiting the system.\n";
            break;
        }

        string password;
        cout << "Enter password: ";
        cin >> password;

        if (password != "password") {
            cout << "Incorrect password. Try again.\n";
            continue;
        }

        if (choice == 1) { // Admin Menu
            cout << "\nAdmin Menu:\n";
            cout << "1. Add Book\n2. Edit Book\n3. View Books\n4. Display Sorted Students\n5. Display Student Account\n";
            cout << "Enter your choice: ";
            int admin_choice;
            cin >> admin_choice;

            if (cin.fail() || admin_choice < 1 || admin_choice > 5) {
                clear_input();
                cout << "Invalid choice. Try again.\n";
                continue;
            }

            switch (admin_choice) {
                case 1: add_book(); break;
                case 2: edit_book(); break;
                case 3: view_books(); break;
                case 4: display_sorted_students(); break;
                case 5: {
                    int roll;
                    cout << "Enter student roll number: ";
                    cin >> roll;
                    display_account(roll);
                    break;
                }
                default: cout << "Invalid option!\n"; break;
            }
        } else if (choice == 2) { // Student Menu
            int roll;
            cout << "Enter roll number: ";
            cin >> roll;

            int index = find_student(roll);
            if (index == -1) {
                cout << "Student not found. Would you like to create a new account? (1 for Yes, 0 for No): ";
                int create;
                cin >> create;
                if (create == 1) {
                    create_account();
                } else {
                    cout << "Returning to main menu.\n";
                }
                continue;
            }

            cout << "\nStudent Menu:\n";
            cout << "1. Display Account\n2. Deposit Amount\n3. Issue Book\n4. Return Book\n";
            cout << "Enter your choice: ";
            int student_choice;
            cin >> student_choice;

            if (cin.fail() || student_choice < 1 || student_choice > 4) {
                clear_input();
                cout << "Invalid choice. Try again.\n";
                continue;
            }

            switch (student_choice) {
                case 1: display_account(roll); break;
                case 2: {
                    double amount;
                    cout << "Enter amount to deposit: ";
                    cin >> amount;
                    if (amount > 0) deposit_amount(roll, amount);
                    else cout << "Invalid amount.\n";
                    break;
                }
                case 3: issue_book(roll); break;
                case 4: return_book(roll); break;
                default: cout << "Invalid option!\n"; break;
            }
        }
    }

    return 0;
}

// Function Definitions

void create_account() {
    if (student_count >= MAX_STUDENTS) {
        cout << "Maximum student limit reached.\n";
        return;
    }

    int roll;
    char name[MAX_NAME_LENGTH];
    cout << "Enter roll number: ";
    cin >> roll;
    cout << "Enter student name: ";
    cin.ignore();
    cin.getline(name, MAX_NAME_LENGTH);

    student_roll[student_count] = roll;
    strcpy(student_name[student_count], name);
    student_balance[student_count] = 0.0;
    student_count++;

    cout << "Account created successfully for " << name << " (Roll: " << roll << ").\n";
}

void display_account(int roll) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    cout << "Student Name: " << student_name[index] << endl;
    cout << "Roll Number: " << student_roll[index] << endl;
    cout << "Balance: $" << fixed << setprecision(2) << student_balance[index] << endl;
}

void deposit_amount(int roll, double amount) {
    int index = find_student(roll);
    if (index == -1) {
        cout << "Student not found.\n";
        return;
    }

    student_balance[index] += amount;
    cout << "Amount deposited successfully. New balance: $" << student_balance[index] << endl;
}

void issue_book(int roll) {
    view_books();

    int isbn;
    cout << "Enter ISBN of the book to issue: ";
    cin >> isbn;

    int book_index = find_book(isbn);
    if (book_index == -1 || !book_available[book_index]) {
        cout << "Book not available or does not exist.\n";
        return;
    }

    book_available[book_index] = false;
    cout << "Book issued successfully: " << book_title[book_index] << endl;
}

void return_book(int roll) {
    cout << "Books currently issued:\n";
    for (int i = 0; i < book_count; i++) {
        if (!book_available[i]) {
            cout << i + 1 << ". " << book_title[i] << " by " << book_author[i] << " (ISBN: " << book_isbn[i] << ")\n";
        }
    }

    int choice;
    cout << "Enter the number of the book to return (0 to cancel): ";
    cin >> choice;

    if (choice < 1 || choice > book_count || book_available[choice - 1]) {
        cout << "Invalid choice or book is already available.\n";
        return;
    }

    book_available[choice - 1] = true;
    cout << "Book successfully returned.\n";
}

void add_book() {
    if (book_count >= MAX_BOOKS) {
        cout << "Maximum book limit reached.\n";
        return;
    }

    cout << "Enter book title: ";
    cin.ignore();
    cin.getline(book_title[book_count], MAX_NAME_LENGTH);
    cout << "Enter book author: ";
    cin.getline(book_author[book_count], MAX_NAME_LENGTH);
    cout << "Enter ISBN number: ";
    cin >> book_isbn[book_count];

    book_available[book_count] = true;
    book_count++;

    cout << "Book added successfully.\n";
}

void edit_book() {
    view_books();

    int isbn;
    cout << "Enter ISBN of the book to edit: ";
    cin >> isbn;

    int book_index = find_book(isbn);
    if (book_index == -1) {
        cout << "Book not found.\n";
        return;
    }

    cout << "Enter new title: ";
    cin.ignore();
    cin.getline(book_title[book_index], MAX_NAME_LENGTH);
    cout << "Enter new author: ";
    cin.getline(book_author[book_index], MAX_NAME_LENGTH);

    cout << "Book updated successfully.\n";
}

void view_books() {
    if (book_count == 0) {
        cout << "No books available.\n";
        return;
    }

    cout << "\nBooks List:\n";
    for (int i = 0; i < book_count; i++) {
        cout << i + 1 << ". " << book_title[i] << " by " << book_author[i] 
             << " (ISBN: " << book_isbn[i] << ", Available: " 
             << (book_available[i] ? "Yes" : "No") << ")\n";
    }
}

void display_sorted_students() {
    if (student_count == 0) {
        cout << "No students available.\n";
        return;
    }

    cout << "\nStudents (Sorted by Balance):\n";
    for (int i = 0; i < student_count - 1; i++) {
        for (int j = 0; j < student_count - i - 1; j++) {
            if (student_balance[j] < student_balance[j + 1]) {
                swap(student_roll[j], student_roll[j + 1]);
                swap(student_balance[j], student_balance[j + 1]);
                swap(student_name[j], student_name[j + 1]);
            }
        }
    }

    for (int i = 0; i < student_count; i++) {
        cout << i + 1 << ". " << student_name[i] << " (Roll: " << student_roll[i]
             << ", Balance: $" << fixed << setprecision(2) << student_balance[i] << ")\n";
    }
}

int find_student(int roll) {
    for (int i = 0; i < student_count; i++) {
        if (student_roll[i] == roll) {
            return i;
        }
    }
    return -1;
}

int find_book(int isbn) {
    for (int i = 0; i < book_count; i++) {
        if (book_isbn[i] == isbn) {
            return i;
        }
    }
    return -1;
}

void save_data() {
    ofstream out("library_data.txt");

    // Save students
    out << student_count << endl;
    for (int i = 0; i < student_count; i++) {
        out << student_roll[i] << "\n" << student_name[i] << "\n" << student_balance[i] << endl;
    }

    // Save books
    out << book_count << endl;
    for (int i = 0; i < book_count; i++) {
        out << book_title[i] << "\n" << book_author[i] << "\n" 
            << book_isbn[i] << "\n" << book_available[i] << endl;
    }

    out.close();
    cout << "Data saved successfully.\n";
}

void load_data() {
    ifstream in("library_data.txt");

    if (!in) {
        cout << "No data file found. Starting with empty database.\n";
        return;
    }

    // Load students
    in >> student_count;
    in.ignore();
    for (int i = 0; i < student_count; i++) {
        in >> student_roll[i];
        in.ignore();
        in.getline(student_name[i], MAX_NAME_LENGTH);
        in >> student_balance[i];
        in.ignore();
    }

    // Load books
    in >> book_count;
    in.ignore();
    for (int i = 0; i < book_count; i++) {
        in.getline(book_title[i], MAX_NAME_LENGTH);
        in.getline(book_author[i], MAX_NAME_LENGTH);
        in >> book_isbn[i];
        in >> book_available[i];
        in.ignore();
    }

    in.close();
    cout << "Data loaded successfully.\n";
}

