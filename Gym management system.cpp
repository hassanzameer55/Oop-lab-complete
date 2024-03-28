#include<iostream>
#include<list>
#include<map>
#include<vector>

using namespace std;

class Member {
public:
    string name;

    Member(string name) : name(name) {}
};

class Booking {
public:
    Member* member;
    int slot;

    Booking(Member* member, int slot) : member(member), slot(slot) {}
};

class FitnessClass {
public:
    string className;
    int totalSlots;
    list<Booking*> bookings;

    FitnessClass(string className, int totalSlots) : className(className), totalSlots(totalSlots) {}

    bool bookSlot(Member* member, int slot) {
        if (slot > totalSlots) {
            cout << "Invalid slot number.\n";
            return false;
        }

        for (Booking* booking : bookings) {
            if (booking->slot == slot) {
                cout << "Slot already booked.\n";
                return false;
            }
            if (booking->member->name == member->name) {
                cout << "Member has already booked a slot in this class.\n";
                return false;
            }
        }

        bookings.push_back(new Booking(member, slot));
        cout << "Booking successful.\n";
        return true;
    }

    void displayAvailableSlots() {
        vector<int> availableSlots(totalSlots, 1);

        for (Booking* booking : bookings) {
            availableSlots[booking->slot - 1] = 0;
        }

        cout << "Available slots for " << className << ":\n";
        for (int i = 0; i < totalSlots; i++) {
            if (availableSlots[i] == 1) {
                cout << i + 1 << "\n";
            }
        }
    }

    void displayBookingsForMember(string memberName) {
        cout << "Bookings for " << memberName << ":\n";
        for (Booking* booking : bookings) {
            if (booking->member->name == memberName) {
                cout << "Slot: " << booking->slot << "\n";
            }
        }
    }
};

class FitnessCenter {
public:
    map<string, FitnessClass*> classes;

    void addClass(string className, int totalSlots) {
        classes[className] = new FitnessClass(className, totalSlots);
        cout << "Class " << className << " added successfully.\n";
    }

    void bookSlot(string className, Member* member, int slot) {
        if (classes.find(className) != classes.end()) {
            cout << "Are you sure you want to book slot " << slot << " for member " << member->name << " in class " << className << "? (yes/no): ";
            string confirmation;
            cin >> confirmation;
            if (confirmation == "yes") {
                if (!classes[className]->bookSlot(member, slot)) {
                    delete member;  // Delete the member object if the booking was not successful
                }
                else {
                    cout << "Booking successful for member " << member->name << " in class " << className << ".\n";
                }
            }
            else {
                cout << "Booking cancelled.\n";
                delete member;  // Delete the member object if the booking was cancelled
            }
        }
        else {
            cout << "Class not found.\n";
            delete member;  // Delete the member object if the class was not found
        }
    }

    void displayAvailableSlots(string className) {
        if (classes.find(className) != classes.end()) {
            classes[className]->displayAvailableSlots();
        }
        else {
            cout << "Class not found.\n";
        }
    }

    void displayBookingsForMember(string className, string memberName) {
        if (classes.find(className) != classes.end()) {
            classes[className]->displayBookingsForMember(memberName);
        }
        else {
            cout << "Class not found.\n";
        }
    }
};

int main() {
    FitnessCenter center;
    string command, className, memberName;
    int totalSlots, slot;

    while (true)
    {
        cout << "\n**** Fitness Center Management System ****\n";
        cout << "1. Add Class\n";
        cout << "2. Book Slot\n";
        cout << "3. Display Available Slots\n";
        cout << "4. Display Bookings for Member\n";
        cout << "5. Quit\n";
        cout << "Enter your choice: ";
        cin >> command;

        if (command == "1")
        {
            cout << "Enter class name: ";
            cin >> className;
            cout << "Enter total slots: ";
            cin >> totalSlots;
            center.addClass(className, totalSlots);
        }
        else if (command == "2")
        {
            cout << "Enter class name: ";
            cin >> className;
            cout << "Enter member name: ";
            cin >> memberName;
            cout << "Enter slot: ";
            cin >> slot;
            center.bookSlot(className, new Member(memberName), slot);
        }
        else if (command == "3")
        {
            cout << "Enter class name: ";
            cin >> className;
            center.displayAvailableSlots(className);
        }
        else if (command == "4")
        {
            cout << "Enter class name: ";
            cin >> className;
            cout << "Enter member name: ";
            cin >> memberName;
            center.displayBookingsForMember(className, memberName);
        }
        else if (command == "5")
        {
            break;
        }
        else
        {
            cout << "Invalid command.\n";
        }
    }

    return 0;
}
