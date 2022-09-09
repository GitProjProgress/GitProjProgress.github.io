#pragma once
#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "BookingStatus.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <string>
#include <ctime>

using namespace std;

class Customer
{

private:
    char customerName[100], customerAddress[250], date[26], todayDate[50];
    long long int phoneNo;
    int roomNo, noOfDays, stayCost;
    bool isRoomBooked(int, char*, BookingStatus&);
    bool validatePhoneNo(long long int);
    void modifyMenu(int);

public:
    void checkRoomsAvailability(char*, BookingStatus&);
    int calcStayCost(int);
    void bookRoomForCustomer(char*, char*, BookingStatus&);
    void displayAllocatedRoomsDetails(char*);
    void modifyCustomerRecord(char*, char*, BookingStatus&);
    void deleteCustomerRecord(char*, char*, BookingStatus&);

    ~Customer()
    {
        /*cout << "\nCustomer Destructor Called\n";
        system("pause");*/
    }
};

#endif