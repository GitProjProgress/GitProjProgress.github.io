#include "Product.hpp"

int Product::count = 0;

void Product::setDetailsForNewProduct()
{
    ++count;
    this->Pid = count;
    cout << "\nEnter Complete Product Name : ";
    cin.ignore();
    cin.getline(this->Pname, 50, '\n');
    cout << "\nEnter Cost of The Product : ";
    cin >> this->Pcost;
    cout << "\nEnter Discount Percent on Product (if any): ";
    cin >> this->Pdiscount;
    cout << "\nEnter the Quantity of Products: ";
    cin >> this->Pcount;
}

void Product::setDetailsForExistingProduct()
{
menu3:
    int choice;
    system("cls");
    cout << "\nSelect, What you want to change from the following:\n";
    cout << "\n1. Product Cost\n";
    cout << "\n2. Product Discount\n";
    cout << "\n3. Product Quantity\n";
    cout << "\n4. Exit \n";
    cout << "\n\nEnter choice: ";
    cin >> choice;
    switch (choice)
    {
    case 1:
    {
        cout << "\nEnter new Product cost: ";
        cin >> this->Pcost;
        this->setProductShelfPrice();
        goto menu3;
    }
    case 2:
    {
        cout << "\nEnter Product New Discount: ";
        cin >> this->Pdiscount;
        this->setProductShelfPrice();
        goto menu3;
    }
    case 3:
    {
        cout << "\nEnter Product New Quantity: ";
        cin >> this->Pcount;
        this->setProductShelfPrice();
        goto menu3;
    }
    case 4:
    {
        break;
    }
    default:
    {
        cout << "\nInvalid Selection\n";
        goto menu3;
    }
    }
}

void Product::setProductShelfPrice()
{
    double disPricePerItem = (this->Pcost) - (this->Pcost * (((double)this->Pdiscount) / 100));
    this->netShelfPrice = (this->Pcount) * disPricePerItem;
}

int Product::getProdId()
{
    return this->Pid;
}

char* Product::getProdName()
{
    return this->Pname;
}

double Product::getProdCost()
{
    return this->Pcost;
}

int Product::getProdDiscount()
{
    return this->Pdiscount;
}

int Product::getProdQuantity()
{
    return this->Pcount;
}

double Product::getProdShelfPrice()
{
    return this->netShelfPrice;
}