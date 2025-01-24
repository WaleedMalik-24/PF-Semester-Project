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



