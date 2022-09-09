#pragma once
#ifndef BOOKINGSTATUS_H
#define BOOKINGSTATUS_H

#include <fstream>
#include <iostream>
using namespace std;

class BookingStatus
{
private:
    bool arr[25]; // No of Rooms in Hotel = 25
    bool isBookingFileAvailable(char*);
    void setBookingFileStatus(char*);
    void getBookingFileStatus(char*);

public:
    BookingStatus(char* fileName)
    {
        if (isBookingFileAvailable(fileName))
        {
            /*cout << "\nFile " << fileName << " Available for Customer Object\n";
            system("pause");*/
            this->getBookingFileStatus(fileName);
        }
        else
        {
            /*cout << "\nFile " << fileName << " NOT Available for Customer Object\n";
            system("pause");*/
            for (int i = 0; i < 25; i++)
                arr[i] = false;
            this->setBookingFileStatus(fileName);
        }
    }
    bool getRoomStatus(char*, int);
    bool* getRoomStatusList(char*);
    void setRoomStatus(char*, int, bool);
};

#endif