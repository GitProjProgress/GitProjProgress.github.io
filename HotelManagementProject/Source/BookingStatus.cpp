#include "BookingStatus.hpp"

bool BookingStatus::getRoomStatus(char* fileName, int room)
{
    getBookingFileStatus(fileName);
    /*cout << "\nSetting Room Status from file into Object\n";
    system("pause");*/
    bool stat = (this->arr)[room - 1];
    return stat;
}

bool* BookingStatus::getRoomStatusList(char* fileName)
{
    getBookingFileStatus(fileName);
    /*cout << "\nReturning Status List, that was Received From File Into Object\n";
    system("pause");*/
    return this->arr;
}

void BookingStatus::setRoomStatus(char* fileName, int room, bool stat)
{
    (this->arr)[room - 1] = stat;
    /*cout << "\nRoom Status Set In Object\n";
    system("pause");*/
    setBookingFileStatus(fileName);
}

bool BookingStatus::isBookingFileAvailable(char* fileName)
{

    ifstream fin;
    fin.open(fileName, ios::in | ios::binary); // error
    if (!fin)
    {
        /*cout << "\nFile Available - False\n";
        system("pause");*/
        return false;
    }
    else
    {
        /*cout << "\nFile Available - True\n";
        system("pause");*/
        fin.close();
    }
    return true;
}

void BookingStatus::setBookingFileStatus(char* fileName)
{

    ofstream fout;
    /*cout << "\nCreating New BookingStatusList.txt file OR Writing status in Existing File\n";
    system("pause");*/
    fout.open(fileName, ios::out | ios::binary);
    fout.write((char*)this, sizeof(*this));
    fout.close();
    /*cout << "\nRoom Status Set In Object, also Set In File\n";
    system("pause");*/
}

void BookingStatus::getBookingFileStatus(char* fileName)
{
    /*cout << "\nFileName to get status from is " << fileName << "\n";
    system("pause");*/
    ifstream fin;
    fin.open(fileName, ios::in | ios::binary);
    if (!fin)
    {
        /*cout << "\nBooking File Note Found in getBookingFileStatus\n";
        system("pause");*/
        return;
    }
    fin.read((char*)this, sizeof(*this));
    fin.close();
    /*cout << "\nGot Booking Status From File Into Object\n";
    system("pause");*/
}