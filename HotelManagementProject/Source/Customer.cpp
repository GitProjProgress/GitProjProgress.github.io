#include "Customer.hpp"
#include <cstdio>

/*--------------------------- I S    R O O M     B O O K E D ---------------------------*/

bool Customer::isRoomBooked(int roomNo, char* bookingFileName, BookingStatus& bookingStatus)
{
    /*cout << "\nChecking if room no entered, is already booked or not in file : " << bookingFileName << "\n";
    system("pause");*/
    bool stat = bookingStatus.getRoomStatus(bookingFileName, roomNo);
    if (stat == true)
        return true; // room booked
    return false;    // room NOT booked
}

/*--------------------------- V A L I D A T E    P H O N E    N U M B E R    L E N G T H ---------------------------*/

bool Customer::validatePhoneNo(long long int phoneNo)
{
    int digitCounter = 0;

    while (digitCounter < 9)
    {
        phoneNo = phoneNo / 10;
        if (phoneNo > 0)
        {
            digitCounter++;
        }
        else
            break;
    }

    int lastRes = (int)phoneNo / 10;
    if (digitCounter == 9 && lastRes == 0)
        return true;
    return false;
}

/*--------------------------- C H E C K         R O O M S         A V A I L A B I L I T Y ---------------------------*/

void Customer::checkRoomsAvailability(char* bookingFileName, BookingStatus& bookingStatus)
{
    cout << "\n\nROOMS AVAILABILITY STATUS: \n\n";
    for (int j = 1; j <= 25; j++)
    {
        bool stat = this->isRoomBooked(j, bookingFileName, bookingStatus);
        if (stat)
            cout << "\nRoom No : " << j << "  - NOT AVAILABLE - Already Booked";
        else
            cout << "\nRoom No : " << j << " - AVAILABLE @ Rs. 750/day stay";
    }
    cout << "\n\n";
}

/*--------------------------- C A L C U L A T E      T O T A L      S T A Y      C O S T ---------------------------*/

int Customer::calcStayCost(int noOfDays)
{
    return (750 * noOfDays);
}

/*--------------------------- B O O K    A    R O O M    F O R     C U S T O M E R ---------------------------*/

void Customer::bookRoomForCustomer(char* customerDetails, char* bookingFileName, BookingStatus& bookingStatus)
{

    int choice;
    ofstream fout;
rNo:
    cout << "\nEnter Room No To Be Booked : ";
    cin >> this->roomNo;
    if (this->roomNo < 1 || this->roomNo > 25)
    {
        cout << "\nInvalid Room Number, Book A Valid Room (Room 1 - Room 25), Check Room Availability For More Details\n";
        cout << "\n1. Back To Menu For Rooms Availability";
        cout << "\n2. Proceed With Booking";
    swtch1:
        cout << "\n\nEnter Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            return;
        case 2:
            goto rNo;
        default:
            cout << "\nInvalid Selection, Press 1 or 2: ";
            goto swtch1;
        }
    }
    else
    {
        bool stat = this->isRoomBooked(this->roomNo, bookingFileName, bookingStatus);
        if (stat)
        {
            cout << "\nRoom No : " << this->roomNo << " - Already Booked, Check Room Availability For More Details\n";
            cout << "\n1. Back To Menu For Rooms Availability";
            cout << "\n2. Proceed With Booking";
        swtch2:
            cout << "\n\nEnter Choice: ";
            cin >> choice;
            switch (choice)
            {
            case 1:
                return;
            case 2:
                goto rNo;
            default:
                cout << "\nInvalid Selection, Press 1 or 2: ";
                goto swtch2;
            }
        }
    }
    cout << "\nEnter the Number of Days The Customer Wants To Stay: ";
    cin >> this->noOfDays;
    this->stayCost = calcStayCost(this->noOfDays);
    cout << "\nEnter Customer Name : ";
    cin.ignore();
    cin.getline(this->customerName, 100);
    cout << "\nEnter Customer Address : ";
    cin.getline(this->customerAddress, 250);

pNo:
    cout << "\nEnter Contact No : ";
    cin >> this->phoneNo;
    if (!(this->validatePhoneNo(this->phoneNo)))
    {
        cout << "\nNot a Valid Phone No, Please enter a valid 10 digit phone no\n";
        goto pNo;
    }

    time_t now = time(0);
    ctime_s(this->date, 26, &now);
    strcpy_s(todayDate, date);

    bookingStatus.setRoomStatus(bookingFileName, this->roomNo, true);
    fout.open(customerDetails, ios::app | ios::binary);
    fout.write((char*)this, sizeof(*this));
    fout.close();
    cout << "\nRoom " << this->roomNo << " Booked Succesfully..\n";
}

/*--------------------------- D I S P L A Y   A L L   B O O K E D   R O O M S   D E T A I L S --------------------------*/

void Customer::displayAllocatedRoomsDetails(char* customerDetails)
{
    ifstream fin;
    fin.open(customerDetails, ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nCustomer Records Do NOT Exist\n";
        fin.close();
        return;
    }
    fin.read((char*)this, sizeof(*this));
    if (fin.eof())
    {
        cout << "\nNo Records To Be Displayed\n";
        fin.close();
        return;
    }
    while (!fin.eof())
    {
        cout << "\n=====================================================================================================================================================================\n";
        cout << "\n"
            << "Room: " << this->roomNo << "         "
            << "Name: " << this->customerName << "         "
            << "Address: " << this->customerAddress << "         "
            << "Contact: " << this->phoneNo << "         "
            << "Total Stay Cost: " << this->stayCost << "         "
            << "Booking Date: " << this->todayDate << "\n";
        cout << "\n=====================================================================================================================================================================\n";
        fin.read((char*)this, sizeof(*this));
    }
    fin.close();
}

/*--------------------------- M O D I F I C A T I O N    M E N U ---------------------------*/

void Customer::modifyMenu(int room)
{
    char carr[1];
menu:
    system("cls");
    int choice;
    cout << "\nUpdating Details For Room : " << room << "\n";
    cout << "\nChoose the Customer Record you want to modify\n";
    cout << "\n1. Customer Name";
    cout << "\n2. Customer Address";
    cout << "\n3. Customer Phone No";
    cout << "\n4. Exit Menu";
    cout << "\n\nEnter your choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
        cout << "\nCurrent Name : " << this->customerName;
        cout << "\nEnter New Name: ";
        cin.ignore();
        cin.getline(this->customerName, 100);
        goto menu;

    case 2:
        cout << "\nCurrent Address : " << this->customerAddress;
        cout << "\nEnter New Address: ";
        cin.ignore();
        cin.getline(this->customerAddress, 250);
        goto menu;

    case 3:

        cout << "\nCurrent Phone No : " << this->phoneNo;
    pNo:
        cout << "\nEnter New Phone No: ";
        cin >> this->phoneNo;
        if (!(this->validatePhoneNo(this->phoneNo)))
        {
            cout << "\nNot a Valid Phone No, Please enter a valid 10 digit phone no";
            goto pNo;
        }
        goto menu;
    case 4:
        break;

    default:
        cout << "\nInvalid Modification Choice";
        cout << "\nPress any key to continue...";
        cin.getline(carr, 1);
        goto menu;
    }
}

/*--------------------------- U P D A T E     C U S T O M E R     R E C O R D ---------------------------*/

void Customer::modifyCustomerRecord(char* customerDetails, char* bookingFileName, BookingStatus& bookingStatus)
{

    int room;
    bool stat;

    ifstream fin;
    fstream file;
    fin.open(customerDetails, ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nCustomer Records Do NOT Exist\n";
        return;
    }
    else
    {
        fin.close();
    }
    file.open(customerDetails, ios::in | ios::ate | ios::out | ios::binary);
    file.seekg(0);
    file.read((char*)this, sizeof(*this));
    if (file.eof())
    {
        cout << "\nNo Existing Customer Record For Updation\n";
        file.close();
        return;
    }
    cout << "\nEnter the room number of the customer whose details are to be modified: ";
    cin >> room;

    if (room < 1 || room > 25)
    {
        cout << "\nInvalid Room Number\n";
        file.close();
        return;
    }
    stat = this->isRoomBooked(room, bookingFileName, bookingStatus);

    if (!stat)
    {
        file.close();
        cout << "\nNo Customer Found For This Room\n";
        return;
    }
    while (!file.eof())
    {
        if (this->roomNo == room)
        {
            this->modifyMenu(room);
            file.seekp((int)file.tellp() - sizeof(*this));
            file.write((char*)this, sizeof(*this));
            break;
        }
        file.read((char*)this, sizeof(*this));
    }
    file.close();
    cout << "\nRecord Modified Successfully\n";
}

/*--------------------------- D E L E T E     C U S T O M E R     R E C O R D ---------------------------*/

void Customer::deleteCustomerRecord(char* customerDetails, char* bookingFileName, BookingStatus& bookingStatus)
{
    ifstream fin;
    ofstream fout;
    int room;
    bool stat;

    fin.open(customerDetails, ios::in | ios::binary);

    if (!fin)
    {
        cout << "\nCustomer Records Do NOT Exist\n";
        fin.close();
        return;
    }

    fin.read((char*)this, sizeof(*this));

    if (fin.eof())
    {
        cout << "\nNo Records Available For Deletion\n";
        fin.close();
        return;
    }

    cout << "\nEnter the room number of the customer whose details are to be deleted: ";
    cin >> room;

    if (room < 1 || room > 25)
    {
        cout << "\nInvalid Room Number\n";
        fin.close();
        return;
    }

    stat = this->isRoomBooked(room, bookingFileName, bookingStatus);

    if (!stat)
    {
        fin.close();
        cout << "\nNo Customer Record Found For This Room\n";
        return;
    }

    fout.open("tempfile.txt", ios::app | ios::binary);

    while (!fin.eof())
    {
        if (!(this->roomNo == room))
        {
            fout.write((char*)this, sizeof(*this));
        }
        fin.read((char*)this, sizeof(*this));
    }

    fin.close();
    fout.close();

    remove(customerDetails);
    rename("tempfile.txt", "CustomerDetails.txt");

    bookingStatus.setRoomStatus(bookingFileName, room, false);
    cout << "\nRecord Deleted Successfully\n";
}