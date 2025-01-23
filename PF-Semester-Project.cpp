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

