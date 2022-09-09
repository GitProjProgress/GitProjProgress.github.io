#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include <stdlib.h>
using namespace std;

void menu()
{
    cout << "Hello! and Welcome to COSMOS Pizzas\n\n";
    cout << "Our Pizza Menu With Delicious Pizzas is here!:\n\n";
    cout << "Order no: 1) Cheese Marghareta Pizza - Price: Rs.100.00\n";
    cout << "Order no: 2) Veg Extravaganza Pizza  - Price: Rs.500.00\n";
    cout << "Order no: 3) Country Special Pizza   - Price: Rs.400.00\n";
    cout << "Order no: 4) Farmhouse Pizza         - Price: Rs.700.00\n";
    cout << "Order no: 5) Corn and Capsicum Pizza - Price: Rs.200.00\n";
    cout << "\nPRESS 0 TO EXIT\n";
    cout << "\nGST & SERVICE CHARGES on any item is Rs.25.00 only.\n";
}

int originalPrice(int choice)
{
    if (choice == 1)
        return (100);
    else if (choice == 2)
        return (500);
    else if (choice == 3)
        return (400);
    else if (choice == 4)
        return (700);
    // else if(choice==5)
    return (200);
}

int discountedPrice(int choice)
{
    int isSpecialCustom, originalprice, discountedprice;
    string password, passKey = "PASS1900";

    cout << "\n\nAre you a Special Customer at this outlet!? If YES!, You Can Avail Discount of 40%\n";
    cout << "\n1) YES";
    cout << "\n2) NO";
    cout << "\n\nEnter Your Choice ";
    cin >> isSpecialCustom;

    if (isSpecialCustom == 1)
    {
        cin.ignore();
        cout << "Enter MEMBER CODE: ";
        getline(cin, password);
        if (password == passKey)
        {
            cout << "\nCONGRATS! CODE SUCCESSFUL ";
            originalprice = originalPrice(choice);
            discountedprice = (60 * originalprice) / 100;
            return (discountedprice);
        }
        else
            return (-4);
    }

    // else if(isSpecialCustom==2)
    return (-2);
}

int toppingsPrice()
{
    int choice;
    cout << "\n\nDear Customer!,Please select your toppings-: ";
    cout << "\n\n1) Extra Cheese- Price: Rs.50";
    cout << "\n2) Mushrooms- Price: 55";
    cout << "\n3) Tomatoes and Onions- Price: Rs.50";
    cout << "\n4) Sweet Corn and Olives- Price: Rs.70";
    cout << "\n5) No Toppings\n\n";
    cout << "Enter topping No: ";
    cin >> choice;
    if (choice == 1)
        return (50);
    else if (choice == 2)
        return (55);
    else if (choice == 3)
        return (50);
    else if (choice == 4)
        return (70);
    else
        return (0);
}

void calAndDispBill(string customerName, int price, int topping, int n)
{
    float payment = 0.0f;
    cout << "\n\nORDER SUMMARY and BILL DETAILS:";
    cout << "\n\nYour Order will be ready in 30 mins";
    ofstream outstream;
    outstream.open("./customerOrderDetails.txt", ios::app);
    if (price != -2 && topping != 0)
    {
        payment = price + topping + 25;
        cout << "\nAnd your total payable amount inclusive of all taxes is: Rs." << payment << ".00 only.";
        outstream << "\nCustomerName: " << customerName << ", Payment Amount: " << payment << "\n";
    }

    else if (price == -2 && topping != 0)
    {
        payment = n + topping + 25;
        cout << "\nAnd your total payable amount inclusive of all taxes is: Rs." << payment << ".00 only.";
        outstream << "\nCustomerName: " << customerName << ", Payment Amount: " << payment << "\n";
    }

    else if (price != -2 && topping == 0)
    {
        payment = price + 25;
        cout << "\nToppings are not Available in the menu";
        cout << "\nAnd your total payable amount inclusive of all taxes is: Rs." << payment << ".00 only.";
        outstream << "\nCustomerName: " << customerName << ", Payment Amount: " << payment << "\n";
    }
    else if (price == -2 && topping == 0)
    {
        payment = n + 25;
        cout << "\nToppings are not Available in the menu";
        cout << "\nAnd your total payable amount inclusive of all taxes is: Rs." << payment << ".00 only.";
        outstream << "\nCustomerName: " << customerName << ", Payment Amount: " << payment << "\n";
    }
    cout << "\nThanks For Using Our Services!\n\n";
}

int main()
{
    int choice, topping = 0, price, n, count = 0;
    string customerName;
    while (1)
    {
        system("cls");
        menu();
        cout << "\n\nDear Customer!,Please Enter Your Name: \n";
        if (count > 0)
            cin.ignore();
        getline(cin, customerName);
        cout << "\n\nDear Customer!,Please Enter Your Order No: ";
        cin >> choice;
        try
        {
            if (choice == 0)
                exit(0);
            else if (choice < 1 || choice > 5)
            {
                cout << "\n\nENTERED INVALID ORDER NUMBER";
                throw - 100;
            }
            n = originalPrice(choice);
            price = discountedPrice(choice);
            if (price == -4)
                cout << "\nINVALID CODE\n\n";
            else
            {
                topping = toppingsPrice();
                calAndDispBill(customerName, price, topping, n);
            }
        }
        catch (int e)
        {
            char ch[1];
            cout << "\nPress any key to end invalid Order process\n";
            cin.ignore();
            cin.getline(ch, 1);
            exit(0);
        }
        system("pause");
        count++;
    }
    system("pause");
    return (0);
}
