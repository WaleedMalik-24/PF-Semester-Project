#include <iostream>
#include <string>
using namespace std;

int main() {
    //capacity of Seats
    int economySeats = 30;
    int businessSeats = 15;
    int vipSeats = 5;

    // Command input
    string command;

    cout << "Welcome to the Airline Reservation System!\n";
    cout << "Total seats available: Economy (30), Business (15), VIP (5)\n";

    while (true) {
        // Display options
        cout << "\nOptions:\n";
        cout << "1. Enter 'book' to book a ticket.\n";
        cout << "2. Enter 'cancel' to cancel a ticket.\n";
        cout << "3. Enter 'status' to check seat availability.\n";
        cout << "4. Enter 'stop' to stop the system.\n";
        cout << "Your choice: ";
        cin >> command;
        
        return 0;
    }
}
