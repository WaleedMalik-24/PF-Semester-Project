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
        // Stop the system
       if (command == "stop") {
           cout << "System shutting down. Thank you for using the Airline Reservation System!\n";
           break;
       }
 
       // Display seat status
       if (command == "status") {
           cout << "Current seat availability:\n";
           cout << "Economy: " << economySeats << "\n";
           cout << "Business: " << businessSeats << "\n";
           cout << "VIP: " << vipSeats << "\n";
           continue;
       }
 
       // Book a ticket
       if (command == "book") {
           string travelClass;
           int distance;
 
           cout << "Enter travel class (economy, business, vip): ";
           cin >> travelClass;
 
           if (travelClass != "economy" && travelClass != "business" && travelClass != "vip") {
               cout << "Invalid travel class. Please choose economy, business, or vip.\n";
               continue;
           }
 
           cout << "Enter travel distance (in km): ";
           cin >> distance;
 
           if (distance <= 0) {
               cout << "Invalid distance. Please enter a positive value.\n";
               continue;
           }
 
           // Booking logic
           if (travelClass == "economy") {
               if (economySeats == 0) {
                   cout << "Economy class is fully booked!\n";
                   continue;
               }
               economySeats--;
               cout << "Economy class ticket booked. Fare: $" << distance * 0.5 << "\n";
           } else if (travelClass == "business") {
               if (businessSeats == 0) {
                   cout << "Business class is fully booked!\n";
                   continue;
               }
               businessSeats--;
               cout << "Business class ticket booked. Fare: $" << distance * 1.0 << "\n";
           } else if (travelClass == "vip") {
               if (vipSeats == 0) {
                   cout << "VIP class is fully booked. Allocating economy seat instead.\n";
                   if (economySeats == 0) {
                       cout << "No economy seats available. Cannot book ticket.\n";
                       continue;
                   }
                   economySeats--;
               } else {
                   vipSeats--;
               }
               cout << "VIP class ticket booked. Fare: $" << distance * 2.0 << "\n";
           }
           continue;
       }// Cancel a ticket
       if (command == "cancel") {
           string travelClass;
 
           cout << "Enter travel class to cancel (economy, business, vip): ";
           cin >> travelClass;
 
           if (travelClass == "economy") {
               if (economySeats >= 30) {
                   cout << "No tickets booked in economy class to cancel.\n";
                   continue;
               }
               economySeats++;
               cout << "Economy class ticket canceled.\n";
           } else if (travelClass == "business") {
               if (businessSeats >= 15) {
                   cout << "No tickets booked in business class to cancel.\n";
                   continue;
               }
               businessSeats++;
               cout << "Business class ticket canceled.\n";
           } else if (travelClass == "vip") {
               if (vipSeats >= 5) {
                   cout << "No tickets booked in VIP class to cancel.\n";
                   continue;
               }
               vipSeats++;
               cout << "VIP class ticket canceled.\n";
           } else {
               cout << "Invalid travel class. Please choose economy, business, or vip.\n";
           }
           continue;
       }
 
       // Invalid command
       cout << "Invalid command. Please try again.\n";
   }
 

        
        return 0;
    }

