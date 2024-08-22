#include "trial.h"

void mainMenu()
{
    
        cout << "\t\t\t\t\t\t\t\t*****Welcome To The Hotel Site*****\t\t\t\t\t\t\t\t" << endl;
        cout << "\t\t\t\t\t\t\t\t\t*****Entry Menu*****\t\t\t\t\t\t\t\t\t\t\t" << endl;
        cout << "Please Choose From Options By Typing its Number" << endl;
        cout << "1. Login" << endl << "2. Register" << endl << "3. Forgot Passcode" << endl << "4. Exit" << endl;
        int choice;
        cin >> choice;
        switch (choice) {
        case 1:
          //  login();
            break;
        case 2:
           // regist();
            break;
        case 3:
           // forget();
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
