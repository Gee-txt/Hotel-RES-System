#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <vector>
#include <iostream>
#include <iomanip> 
#include <chrono>
#include <ctime>

using namespace std;

struct RUM {
    int roomno;
    int p_ebed;
    char bed[15];
    char roomtype[30];
    float roomcst;
    int avl;
    bool availability[3][7];
};



string usery;

//login and main menu
void login();
void regist();
void forget();
bool isUsernameUnique(const string& username);
void mainMenu();
//USER AND ADMIN MENUES
void displayAdminMenu();
void displayUserMenu();
//ADMIN FUNCTIONS 
void addRoom();
void displayRooms();
void displayAllBookings();
void deleteBookingByUsername(const string username);
//USER FUNCTIONS
void displayRooms();
void bookRoom(const string& username);
void displayRoomsuser();
void search();
void printCredits();
void editBooking(const string& username);
//DATE
void printCurrentDate() {
    using namespace std::chrono;

    auto now = system_clock::now();
    std::time_t now_c = system_clock::to_time_t(now);

    // Use localtime_s instead of localtime
    std::tm local_time;
    localtime_s(&local_time, &now_c);

    int year = local_time.tm_year + 1900;
    int month = local_time.tm_mon + 1;
    int day = local_time.tm_mday;

    std::cout << "Current Date: " << year << '-'
        << std::setfill('0') << std::setw(2) << month << '-'
        << std::setfill('0') << std::setw(2) << day << std::endl;
}

//********************************************************************/\******************************************************************

//LOGIN MENU IMPLMENTATION

void login() {
    printCurrentDate();
    system("cls");
    int count = 0;
    string user, pc, id, pass;

    cout << "\t\t\t\t\t\t\t\t***** Welcome To Login Page *****\t\t\t\t\t\t\t\t\n\n" << endl;
    cout << "Please Insert Username and Password" << endl;
    cout << "Username: ";
    cin >> user;
    cout << "Password: ";
    cin >> pc;

    ifstream input("data.txt");
    while (input >> id >> pass) {
        if (id == user && pass == pc) {
            count = 1;
            system("cls");
            cout << "Welcome " << user << " to your user account" << endl;
            usery = user;
            displayUserMenu(); // Pass the username
            return;
        }
    }
    input.close();

    ifstream adminInput("admin.txt");
    while (adminInput >> id >> pass) {
        if (id == user && pass == pc) {
            count = 2;
            system("cls");
            cout << "Welcome " << user << " to your admin account" << endl;
            displayAdminMenu();
            return;
        }
    }
    adminInput.close();

    system("cls");
    cout << "Error\nPlease try to enter password or username\nor try to register" << endl;
    cout << "Press 1 to go back" << endl;
    cout << "Press 2 to go to main menu" << endl;
    int num;
    cin >> num;
    cin.ignore();
    system("cls");

    if (num == 1) {
        login();
    }
    else {
        mainMenu();
    }
}

bool isUsernameUnique(const string& username) {
    ifstream dataFile("data.txt");
    ifstream adminFile("admin.txt");
    string id, pass;

    while (dataFile >> id >> pass) {
        if (id == username) {
            return false;
        }
    }
    dataFile.close();

    while (adminFile >> id >> pass) {
        if (id == username) {
            return false;
        }
    }
    adminFile.close();

    return true;
}

void regist() {
    printCurrentDate();
    int scode = 272012;
    string ruser, rpc, id, pass;
    system("cls");
    cout << "\t\t\t\t\t\t\t\t***** Welcome To Registration Page *****\t\t\t\t\t\t\t\t\n\n" << endl;
    cout << "Press 1 for Admin Registration" << endl;
    cout << "Press 2 for User Registration" << endl;
    int ch;
    cin >> ch;

    if (ch == 1) {
        cout << "Enter your Serial Code" << endl;
        int sc;
        cin >> sc;
        if (sc == scode) {
            cout << "Enter Your Username: ";
            cin >> ruser;
            cout << "Enter Your Password: ";
            cin >> rpc;

            if (!isUsernameUnique(ruser)) {
                system("cls");
                cout << "Username already exists" << endl;
                regist();
                return;
            }

            ofstream f1("admin.txt", ios::app);
            f1 << ruser << ' ' << rpc << endl;
            f1.close();
            system("cls");
            cout << "Registered Successfully" << endl;
            mainMenu();
        }
        else {
            cout << "Invalid Serial Code" << endl << "Press any key to go back" << endl;
            string st;
            cin >> st;
            regist();
        }
    }
    else if (ch == 2) {
        cout << "Enter Your Username: ";
        cin >> ruser;
        cout << "Enter Your Password: ";
        cin >> rpc;

        if (!isUsernameUnique(ruser)) {
            system("cls");
            cout << "Username already exists" << endl;
            regist();
            return;
        }

        ofstream f1("data.txt", ios::app);
        f1 << ruser << ' ' << rpc << endl;
        f1.close();
        system("cls");
        cout << "Registered Successfully" << endl;
        mainMenu();
    }
    else {
        cout << "Invalid Input" << endl << "Press any key to go back" << endl;
        string st;
        cin >> st;
        regist();
    }
}

void forget() {
    printCurrentDate();
    int option;
    system("cls");
    cout << "\t\t\t You forgot the password? No worries \n";
    cout << "Press 1 to search your id by username " << endl;
    cout << "Press 2 to go back to the main menu " << endl;
    cout << "\t\t\t Enter your choice:";
    cin >> option;

    switch (option) {
    case 1: {
        int count = 0;
        string suserId, sid, spass;
        cout << "\n\t\t\tEnter the username which you remembered :";
        cin >> suserId;
        ifstream f2("data.txt");
        while (f2 >> sid >> spass) {
            if (sid == suserId) {
                count = 1;
                break;
            }
        }
        f2.close();
        if (count == 1) {
            cout << "\n\n Your account is found! \n";
            cout << "\n\n Your password is: " << spass << endl;
        }
        else {
            cout << "\n\t Sorry! your account is not found! \n";
        }
        mainMenu();
        break;
    }
    case 2:
        mainMenu();
        break;
    default:
        cout << "\t\t\t Wrong choice! Please try again " << endl;
        forget();
    }
}

void mainMenu()
{
    printCurrentDate();
    cout << "\t\t\t\t\t\t\t\t*****Welcome To The Hotel App*****\t\t\t\t\t\t\t\t" << endl;
    cout << "\t\t\t\t\t\t\t\t\t*****Entry Menu*****\t\t\t\t\t\t\t\t\t\t\t" << endl;
    cout << "Please Choose From Options By Typing its Number" << endl;
    cout << "1. Login" << endl << "2. Register" << endl << "3. Forgot Passcode" << endl << "4. Exit" << endl;
    int choice;
    cin >> choice;
    switch (choice) {
    case 1:
         login();
        break;
    case 2:
         regist();
        break;
    case 3:
         forget();
        break;
    case 4:
        cout << "Thank You" << endl;
        break;
    default:
        system("cls");
        cout << "Please Choose From Options Given Above\n";
        mainMenu();
    }

}

//USER AND ADMIN MENUES IMPLMENTATION

void displayAdminMenu() {
    printCurrentDate();
    cout << "************************************************** [MAIN MENU] **************************************************\n";
    cout << "*Please enter your choice from menu*:\n";
    cout << "----------------------------------\n";
    cout << "Enter 1 -> Add Rooms\n";
    cout << "Enter 2 -> View Customers Records\n";
    cout << "Enter 3 -> Delete Customer Record\n";
    cout << "Enter 4 -> Edit Booking\n";
    cout << "Enter 5 -> View Rooms\n";
    cout << "Enter 6 -> Exit\n";
    cout << "----------------------------------\n";
    int ch;
    cin >> ch;
    switch (ch) {
    case 1:
        system("cls");
        addRoom();
        break;
    case 2:
        system("cls");
        displayAllBookings();
        break;
    case 3:
        system("cls");
        deleteBookingByUsername(usery);
        break;
    case 4:
        //edit
        system("cls");
        break;
    case 5:
        system("cls");
        displayRooms();
        break;
    case 6:
        system("cls");
        printCredits();
        mainMenu();
        break;
    default:
        system("cls");
        cout << "Invalid choice! Please enter again.\n";
        displayAdminMenu();
    }
}

void displayUserMenu() {
    printCurrentDate();
    cout << "************************************************** [MAIN MENU] **************************************************\n";
    cout << "*Please enter your choice from menu*:\n";
    cout << "----------------------------------\n";
    cout << "Enter 1 -> Search Rooms\n";
    cout << "Enter 2 -> Book a Room\n";
    cout << "Enter 3 -> Edit Your Booking\n";
    cout << "Enter 4 -> View Your Bookings\n";
    cout << "Enter 5 -> View All Rooms\n";
    cout << "Enter 6 -> Exit\n";
    cout << "----------------------------------\n";
    int ch;
    cin >> ch;
    switch (ch) {
    case 1:
        system("cls");
        search();
        break;
    case 2:
        system("cls");
        bookRoom(usery);
        break;
    case 3:
        system("cls");
        editBooking(usery);
        break;
    case 4:
        system("cls");
        displayAllBookingsFORUSER();
        break;
    case 5:
        system("cls");
        displayRoomsuser();
        break;
    case 6:
        system("cls");
        printCredits();
        break;
    default:
        system("cls");
        cout << "Invalid choice! Please enter again.\n";
        displayUserMenu();
    }
}

//ADMIN FUNCTIONS

void addRoom() {
    printCurrentDate();
    system("cls");
    RUM room;
    vector<RUM> rooms;
    ifstream fin("rooms.txt", ios::in | ios::binary);

    // Read all existing rooms into memory
    while (fin.read(reinterpret_cast<char*>(&room), sizeof(RUM))) {
        rooms.push_back(room);
    }
    fin.close();

    bool roomExists;
    do {
        roomExists = false;
        cout << "\n\nEnter Room Details\n";
        cout << "Room Number: ";
        cin >> room.roomno;

        // Check if room number already exists
        for (const auto& existingRoom : rooms) {
            if (existingRoom.roomno == room.roomno) {
                roomExists = true;
                cout << "Room number already exists. Please enter a different room number.\n";
                break;
            }
        }
    } while (roomExists);

    cout << "Type of Room: ";
    cin >> room.roomtype;
    cout << "Type of Bed: ";
    cin >> room.bed;
    cout << "Price of Extra Bed: ";
    cin >> room.p_ebed;
    cout << "Cost per day: ";
    cin >> room.roomcst;
    room.avl = 0;

    // Add new room to file
    ofstream fout("rooms.txt", ios::app | ios::binary);
    fout.write(reinterpret_cast<char*>(&room), sizeof(RUM));
    fout.close();

    cout << "\nRoom Added Successfully\n";
    displayAdminMenu();
}

void displayRooms() {
    printCurrentDate();
    system("cls");
    ifstream fin("rooms.txt", ios::in);
    RUM room;
    cout << "\n\t\t\t    List Of Rooms    \n";
    cout << "\n Room Number\tRoom Type\tBed Type\tCost Per Day\n";
    cout << "-------------------------------------------------------------------------------\n";
    while (fin.read(reinterpret_cast<char*>(&room), sizeof(RUM))) {
        cout << room.roomno << "\t\t" << room.roomtype << "\t\t" << room.bed << "\t\t" << room.roomcst << "\n";
    }
    fin.close();
    cout << "\n\nPress 1 to go back to menu: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        displayAdminMenu();
    }
}

void displayAllBookings() 
{
    printCurrentDate();
    ifstream bookingLog("bookings.txt");

    if (bookingLog.is_open()) {
        string line;
        cout << "All Bookings:" << endl;
        cout << "----------------------------------------" << endl;

        while (getline(bookingLog, line)) {
            cout << line << endl;
        }

        bookingLog.close();
    }
    else {
        cout << "Unable to open bookings file for reading." << endl;
    }

    cout << "Press any key to go back" << endl;
    string st;
    cin >> st;
    displayAdminMenu();
}

void displayAllBookingsFORUSER()
{
    printCurrentDate();
    ifstream bookingLog("bookings.txt");

    if (bookingLog.is_open()) {
        string line;
        cout << "All Bookings:" << endl;
        cout << "----------------------------------------" << endl;

        while (getline(bookingLog, line)) {
            cout << line << endl;
        }

        bookingLog.close();
    }
    else {
        cout << "Unable to open bookings file for reading." << endl;
    }

    cout << "Press any key to go back" << endl;
    string st;
    cin >> st;
    displayUserMenu();
}

void deleteBookingByUsername(const string username) 
{
    ifstream infile("bookings.txt");
    ofstream tempfile("temp_bookings.txt");
    string line;
    bool deleted = false;

    if (infile.is_open() && tempfile.is_open()) {
        while (std::getline(infile, line)) {
            if (line.find(username) == std::string::npos) {
                tempfile << line << "\n";
            }
            else {
                deleted = true;
            }
        }
        infile.close();
        tempfile.close();

        // Remove original file and rename temp file to original file name
        if (std::remove("bookings.txt") == 0 && std::rename("temp_bookings.txt", "bookings.txt") == 0) {
            std::cout << "Bookings for user " << username << " deleted successfully.\n";
        }
        else {
            std::cerr << "Error updating bookings file.\n";
        }
    }
    else {
        std::cerr << "Unable to open file.\n";
    }

    if (!deleted) {
        std::cout << "No bookings found for user " << username << ".\n";
    }
}


//USER FUNCTIONS

void bookRoom(const string& username) {
    printCurrentDate();
    vector<RUM> rooms;
    system("cls");
    int roomNumber;
    long long id;
    bool found = false;

    cout << "Enter Room Number to book: ";
    cin >> roomNumber;
    cout << "Enter Your National ID for reservation: ";
    cin >> id;
    string sd;
    cout << "Enter the start date" << endl;
    cin >> sd;
    string ld;
    cout << "Enter the last date" << endl;
    cin >> ld;
    ifstream infile("rooms.txt", ios::in | ios::binary);
    RUM room;

    if (infile.is_open()) {
        while (infile.read(reinterpret_cast<char*>(&room), sizeof(RUM))) {
            rooms.push_back(room);
        }
        infile.close();

        for (auto& r : rooms) {
            if (r.roomno == roomNumber) {
                found = true;
                if (r.avl == 0) {
                    r.avl = 1;
                    cout << "Room " << roomNumber << " booked successfully.\n";

                    ofstream bookingLog("bookings.txt", ios::app);
                    if (bookingLog.is_open()) {
                        bookingLog << username << " booked room: " << roomNumber << " National ID: " << id <<endl<< " Start date: " << sd << " Last date" << ld << "\n";
                        bookingLog.close();
                    }
                    else {
                        cout << "Unable to open bookings file for writing.\n";
                    }

                    ofstream outfile("rooms.txt", ios::out | ios::binary);
                    if (outfile.is_open()) {
                        for (const auto& room : rooms) {
                            outfile.write(reinterpret_cast<const char*>(&room), sizeof(RUM));
                        }
                        outfile.close();
                    }
                    else {
                        cout << "Unable to open file for writing.\n";
                    }
                    cout << "Press any key to go back" << endl;
                    cin.ignore();
                    cin.get();
                    displayUserMenu();
                }
                else {
                    cout << "Room " << roomNumber << " is already booked.\n";
                }
                break;
            }
        }

        if (!found) {
            cout << "Room " << roomNumber << " not found.\n";
            mainMenu();
        }
    }
    else {
        cout << "Unable to open file for reading.\n";
    }
    cout << "Press any key to go back" << endl;
    string st;
    cin >> st;
    displayUserMenu();
}

void editBooking(const string& username) {
    printCurrentDate();
    system("cls");

    ifstream infile("bookings.txt");
    ofstream tempfile("temp_bookings.txt");
    string line;
    bool found = false;

    if (!infile.is_open() || !tempfile.is_open()) {
        cerr << "Error opening file!" << endl;
        return;
    }

    while (getline(infile, line)) {
        if (line.find(username) != string::npos) {
            found = true;
            cout << "Current Booking Details: " << line << endl;

            // Prompt for new booking details
            int newRoomNumber;
            long long newId;
            string newStartDate, newLastDate;

            cout << "Enter new Room Number: ";
            cin >> newRoomNumber;
            cout << "Enter new National ID: ";
            cin >> newId;
            cout << "Enter new Start Date: ";
            cin >> newStartDate;
            cout << "Enter new Last Date: ";
            cin >> newLastDate;

            // Write the updated booking information
            tempfile << username << " booked room: " << newRoomNumber
                << " National ID: " << newId << endl
                << " Start date: " << newStartDate
                << " Last date: " << newLastDate << "\n";
        }
        else {
            tempfile << line << "\n";
        }
    }

    infile.close();
    tempfile.close();

    if (!found) {
        cout << "No bookings found for user " << username << ".\n";
    }
    else {
        // Replace the old bookings file with the new one
        if (remove("bookings.txt") != 0 || rename("temp_bookings.txt", "bookings.txt") != 0) {
            cerr << "Error updating bookings file." << endl;
        }
        else {
            cout << "Booking for user " << username << " updated successfully.\n";
        }
    }

    cout << "Press any key to go back" << endl;
    cin.ignore();
    cin.get();
    displayAdminMenu();
}

void search() {
    printCurrentDate();
    system("cls");

    int roomId;
    cout << "Enter the Room Number you want to check availability for: ";
    cin >> roomId;

    ifstream infile("rooms.txt", ios::in | ios::binary);
    RUM room;
    bool found = false;

    if (infile.is_open()) {
        while (infile.read(reinterpret_cast<char*>(&room), sizeof(RUM))) {
            if (room.roomno == roomId) {
                found = true;
                cout << "\nRoom Number: " << room.roomno << endl;
                cout << "Room Type: " << room.roomtype << endl;
                cout << "Bed Type: " << room.bed << endl;
                cout << "Cost per Day: " << room.roomcst << endl;
                cout << "Price of Extra Bed: " << room.p_ebed << endl;

                if (room.avl == 0) {
                    cout << "Availability: Available" << endl;
                }
                else {
                    cout << "Availability: Booked" << endl;
                }
                break;
            }
        }
        infile.close();

        if (!found) {
            cout << "Room " << roomId << " not found." << endl;
        }
    }
    else {
        cout << "Unable to open rooms file for reading." << endl;
    }

    cout << "\nPress any key to go back" << endl;
    cin.ignore();
    cin.get();
    displayUserMenu();
}

void displayRoomsuser()
{
    printCurrentDate();
    system("cls");
    ifstream fin("rooms.txt", ios::in);
    RUM room;
    cout << "\n\t\t\t    List Of Rooms    \n";
    cout << "\n Room Number\tRoom Type\tBed Type\tCost Per Day\n";
    cout << "-------------------------------------------------------------------------------\n";
    while (fin.read(reinterpret_cast<char*>(&room), sizeof(RUM))) {
        cout << room.roomno << "\t\t" << room.roomtype << "\t\t" << room.bed << "\t\t" << room.roomcst << "\n";
    }
    fin.close();
    cout << "\n\nPress 1 to go back to menu: ";
    int choice;
    cin >> choice;
    if (choice == 1) {
        displayUserMenu();
    }
    else  displayUserMenu();
   
}

void printCredits() {
    printCurrentDate();
    system("cls");
   cout << "This code is protected and maintained by Youssef Ehab.\n";
   cout << "For any issues or contributions, please contact:ehabyoussef613@gmail.com\n";

}

int main()
{
   // printCredits();
    mainMenu();
    return 0;
}