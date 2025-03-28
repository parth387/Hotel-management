#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <fstream>

using namespace std;

// Room class to represent a hotel room
class Room {
public:
    int roomNumber;          // Room number
    bool isBooked;           // Booking status
    string guestName;       // Name of the guest

    // Constructor to initialize room
    Room(int number) : roomNumber(number), isBooked(false), guestName("") {}
};

// Hotel class to manage rooms and bookings
class Hotel {
private:
    vector<Room> rooms;      // Vector to store rooms

public:
    // Constructor to initialize hotel with a given number of rooms
    Hotel(int numRooms) {
        for (int i = 1; i <= numRooms; i++) {
            rooms.push_back(Room(i)); // Add rooms to the hotel
        }
        loadBookings();
    }

    // Function to check if a string is valid (only alphabets)
    bool isValidName(const string& name) {
        for (char ch : name) {
            if (!isalpha(ch) && ch != ' ') {
                return false;
            }
        }
        return true;
    }

    // Function to book a room
    void bookRoom() {
        int roomNumber;
        string guestName;

        cout << "Enter room number to book: ";
        cin >> roomNumber;

        // Check if the room number is valid
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number!" << endl;
            return;
        }

        // Check if the room is already booked
        if (rooms[roomNumber - 1].isBooked) {
            cout << "Room " << roomNumber << " is already booked!" << endl;
            return;
        }

        cout << "Enter guest name (alphabets only): ";
        cin >> ws;  // To consume any leading whitespace
        getline(cin, guestName);

        // Validate guest name
        if (!isValidName(guestName)) {
            cout << "Invalid name! Please use only alphabets and spaces." << endl;
            return;
        }

        // Book the room
        rooms[roomNumber - 1].isBooked = true;
        rooms[roomNumber - 1].guestName = guestName;
        cout << "Room " << roomNumber << " booked successfully for " << guestName << "." << endl;
    }

    // Function to view all rooms with their booking status
    void viewAllRooms() {
        cout << "Room Status:" << endl;
        for (const auto& room : rooms) {
            cout << "Room " << room.roomNumber << (room.isBooked ? " (Booked by " + room.guestName + ")" : " (Available)") << endl;
        }
    }

    // Function to view available rooms
    void viewAvailableRooms() {
        cout << "Available Rooms:" << endl;
        bool foundAvailable = false;
        for (const auto& room : rooms) {
            if (!room.isBooked) {
                cout << "Room " << room.roomNumber << endl;
                foundAvailable = true;
            }
        }
        if (!foundAvailable) {
            cout << "No rooms available." << endl;
        }
    }

    // Function to check out of a room
    void checkOut() {
        int roomNumber;

        cout << "Enter room number to check out: ";
        cin >> roomNumber;

        // Check if the room number is valid
        if (roomNumber < 1 || roomNumber > rooms.size()) {
            cout << "Invalid room number!" << endl;
            return;
        }

        // Check if the room is booked
        if (!rooms[roomNumber - 1].isBooked) {
            cout << "Room " << roomNumber << " is not booked!" << endl;
            return;
        }

        // Check out of the room
        rooms[roomNumber - 1].isBooked = false;
        rooms[roomNumber - 1].guestName = "";
        cout << "Checked out from room " << roomNumber << " successfully." << endl;
    }

    // Save bookings to a file
    void saveBookings() {
        ofstream outFile("bookings.txt");
        for (const auto& room : rooms) {
            if (room.isBooked) {
                outFile << room.roomNumber << " " << room.guestName << endl;
            }
        }
        outFile.close();
    }

    // Load bookings from a file
    void loadBookings() {
        ifstream inFile("bookings.txt");
        if (inFile) {
            int roomNumber;
            string guestName;
            while (inFile >> roomNumber) {
                inFile.ignore(); // Ignore the space before the guest name
                getline(inFile, guestName);
                rooms[roomNumber - 1].isBooked = true;
                rooms[roomNumber - 1].guestName = guestName;
            }
            inFile.close();
        }
    }

    // Function to display the menu
    void displayMenu() {
        cout << "\nHotel Booking System" << endl;
        cout << "1. Book Room" << endl;
        cout << "2. View All Rooms" << endl;
        cout << "3. View Available Rooms" << endl;
        cout << "4. Check Out" << endl;
        cout << "5. Exit" << endl;
        cout << "Choose an option: ";
    }
};

int main() {
    int choice;
    Hotel hotel(10); // Create a hotel with 10 rooms

    while (true) {
        hotel.displayMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                hotel.bookRoom();
                hotel.saveBookings(); // Save bookings after a room is booked
                break;
            case 2:
                hotel.viewAllRooms();
                break;
            case 3:
                hotel.viewAvailableRooms();
                break;
            case 4:
                hotel.checkOut();
                hotel.saveBookings(); // Save bookings after checkout
                break;
            case 5:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}