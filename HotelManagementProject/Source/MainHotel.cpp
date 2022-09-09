#include "Customer.hpp"
#include "BookingStatus.hpp"

int mainMenu()
{
    system("cls");
    int choice;
    cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\n                                WELCOME TO MUMABAI BEACH HOTEL !!!!!                                \n";
    cout << "\n@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@\n";
    cout << "\n\nTOTAL ROOMS : 1 - 25 ";
    cout << "\n\n1. Check Rooms Availability";
    cout << "\n2. Book A Room";
    cout << "\n3. Display Booked Room Details";
    cout << "\n4. Update Existing Customer Record";
    cout << "\n5. Delete Customer Record";
    cout << "\n6. Exit";
    cout << "\n\nEnter Choice : ";
    cin >> choice;
    return choice;
}

int main()
{
    string s = "BookingStatusList.txt";
    string s2 = "CustomerDetails.txt";
    char bookingFileName[50], customerDetails[50];
    strcpy_s(customerDetails, s2.c_str());
    strcpy_s(bookingFileName, s.c_str());
    char carr[1];
    Customer c;
    BookingStatus bookingStatus(bookingFileName);
    while (1)
    {
        int choice = mainMenu();
        switch (choice)
        {
        case 1:
            c.checkRoomsAvailability(bookingFileName, bookingStatus);
            break;
        case 2:
            c.bookRoomForCustomer(customerDetails, bookingFileName, bookingStatus);
            break;
        case 3:
            c.displayAllocatedRoomsDetails(customerDetails);
            break;
        case 4:
            c.modifyCustomerRecord(customerDetails, bookingFileName, bookingStatus);
            break;
        case 5:
            c.deleteCustomerRecord(customerDetails, bookingFileName, bookingStatus);
            break;
        case 6:
            exit(0);
        default:
            cout << "\n\nInvalid Booking Choice ";
            break;
        }
        cout << "\nPress Any Key To Continue...";
        cin.ignore();
        cin.getline(carr, 1);
    }

    return 0;
}