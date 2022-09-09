#include "Admin.hpp"
#include <fstream>
#include <string>
#include <cstdlib>
#include <stdio.h>
/*
 *---------------------------------------- A D M I N    M E N U -------------------------------------
 */
int Admin::adminMenu()
{
    int choice;
    system("cls");
    cout << "\n\n                           *******************************************************************************";
    cout << "\n\n                           !!!!!!..................WELCOME TO METRO MEGA SUPER MARKET..............!!!!!!!";
    cout << "\n\n                           *******************************************************************************\n\n";
    cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    cout << "\nHi Admin, Select from the below options: \n";
    cout << "\n\nADMIN OPTIONS : \n\n";
    cout << "\n1. Add New Product In Store";
    cout << "\n2. Search For Existing Product In Store";
    cout << "\n3. Remove Product from Store";
    cout << "\n4. Update Existing Product in Store";
    cout << "\n5. View Store";
    cout << "\n6. Remove Store File";
    cout << "\n7. Exit";
    cout << "\n\nNOTE : \n"
        << "1) If you don't remember the products you have added, do - View Store (option 5)\n"
        << "2) Option 6 can only be performed using Master admin Id\n"
        << "3) Each product will have unique product Id, if the product is removed and re added, the re added product will have a new product id\n"
        << "4) REMEMBER to exit after updating product in (option 4)";
    cout << "\n\nEnter Choice: ";
    cin >> choice;
    return choice;
}
/*
 *---------------------------------------- A D D   N E W   P R O D U C T -------------------------------------
 */
void Admin::addNewProduct(char* fileName)
{
    Product p;
    p.setDetailsForNewProduct();
    p.setProductShelfPrice();
    cout << "\nProduct Added Successfully\n";
    ofstream fout;
    fout.open(fileName, ios::app | ios::binary);
    fout.write((char*)&p, sizeof(p));
    fout.close();
}
/*
 *---------------------------------------- D I S P L A Y    P R O D U C T    D E T A I L S ------------------------
 */
void Admin::showProductDetails(Product* prod)
{
    cout << "\n------------------------------------------------------------------------------\n";
    cout << "\nProduct ID: "
        << prod->getProdId();
    cout << "\nProduct Name: "
        << prod->getProdName();
    cout << "\nProduct Cost: "
        << prod->getProdCost();
    cout << "\nProduct Discount%: "
        << prod->getProdDiscount();
    cout << "\nProduct Quantity: "
        << prod->getProdQuantity();
    cout << "\nNet Shelf Price for Product: "
        << prod->getProdShelfPrice();
    cout << "\n------------------------------------------------------------------------------\n";
}
/*
 *---------------------------------------- D I S P L A Y    A L L   S T O R E    I T E M S ------------------------
 */
void Admin::viewStore(char* fileName)
{
    ifstream fin;
    fin.open(fileName, ios::in | ios::binary);
    Product tempProd;
    if (!fin)
    {
        cout << "\nFILE DOES NOT EXIST\n";
        return;
    }
    fin.read((char*)&tempProd, sizeof(tempProd));
    if (fin.eof())
    {
        cout << "\nNo Items are currently available in the store\n";
        return;
    }
    while (!fin.eof())
    {
        showProductDetails(&tempProd);
        fin.read((char*)&tempProd, sizeof(tempProd));
    }
    fin.close();
}
/*
 *---------------------------------------- S E A R C H    F O R    P R O D U C T   I N    S T O R E-------------------
 */
void Admin::searchProduct(char* fileName)
{
    ifstream fin;
    bool flag = false;
    Product tempProd;
    char prodName[50];
    fin.open(fileName, ios::in | ios::binary);
    if (!fin)
    {
        cout << "\nFILE DOES NOT EXIST\n";
        return;
    }
    fin.read((char*)&tempProd, sizeof(tempProd));
    if (fin.eof())
    {
        cout << "\nNo Items are currently available in the store\n";
        return;
    }

    cout << "\nEnter product name you want to search: ";
    cin.ignore();
    cin.getline(prodName, 50, '\n');
    while (!fin.eof())
    {
        if (strcmp(tempProd.getProdName(), prodName) == 0)
        {
            flag = true;
            cout << "\nProduct Found\n";
            this->showProductDetails(&tempProd);
            break;
        }
        fin.read((char*)&tempProd, sizeof(tempProd));
    }
    if (flag == false)
        cout << "\nProduct Searched, Could Not be Found in Store\n";
    fin.close();
}
/*
 *---------------------------------------- D E L E T E   P R O D U C T   F R O M    S T O R E ------------------------
 */
void Admin::deleteProduct(char* fileName)
{

    ifstream fin;
    ofstream fout;
    Product tempProd;
    bool flag = false;
    char prodName[50];
    {
        fin.open(fileName, ios::in | ios::binary);
        if (!fin)
        {
            cout << "\nFILE DOES NOT EXIST\n";
            return;
        }
        else
        {
            fin.read((char*)&tempProd, sizeof(tempProd));
            if (fin.eof())
            {
                cout << "\nNo Items are currently available in the store\n";
                return;
            }
            fout.open("tempfile.txt", ios::out | ios::binary);
            cout << "\nEnter product name you want to delete: ";
            cin.ignore();
            cin.getline(prodName, 50, '\n');
            while (!fin.eof())
            {
                if (strcmp(tempProd.getProdName(), prodName) != 0)
                    fout.write((char*)&tempProd, sizeof(tempProd));
                else
                    flag = true;
                fin.read((char*)&tempProd, sizeof(tempProd));
            }
            if (flag == false)
                cout << "\nProduct to be Deleted Could Not be Found in Store\n";
            else
                cout << "\nProduct Deleted Successfully\n";
            fin.close();
            fout.close();
        }
    }

    remove(fileName);
    rename("tempfile.txt", "ProductMarket.txt");
}
/*
 *---------------------------- U P D A T E   P R O D U C T   D E T A I L S   I N    S T O R E ---------------
 */
void Admin::updateProduct(char* fileName)
{
    fstream file;
    file.open(fileName, ios::in | ios::ate | ios::out | ios::binary);
    Product tempProd;
    char prodName[50];
    bool flag = false;
    if (!file)
    {
        cout << "\nFILE DOES NOT EXIST\n";
        return;
    }
    file.seekg(0);
    file.read((char*)&tempProd, sizeof(tempProd));
    if (file.eof())
    {
        cout << "\nNo Items are currently available in the store\n";
        return;
    }

    cout << "\nEnter product name you want to update: ";
    cin.ignore();
    cin.getline(prodName, 50, '\n');
    while (!file.eof())
    {
        if (strcmp(tempProd.getProdName(), prodName) == 0)
        {
            flag = true;
            tempProd.setDetailsForExistingProduct();
            file.seekp((int)file.tellp() - sizeof(tempProd));
            file.write((char*)&tempProd, sizeof(tempProd));
            break;
        }
        file.read((char*)&tempProd, sizeof(tempProd));
    }
    if (flag == false)
        cout << "\nProduct to be Updated Could Not be Found in Store\n";
    else
        cout << "\nProduct Updated Successfully\n";
}
/*
 *---------------------------------------- V A L I D A T E     A D M I N     I D ------------------------
 */
bool Admin::isValidAdminId(string adminId)
{
    bool res = false;
    vector<string>::iterator it = (this->validAdmins).begin();
    while (it != (this->validAdmins).end())
    {
        if ((*it) == adminId)
        {
            res = true;
            break;
        }
        it++;
    }
    return res;
}
/*
 *---------------------------------------- O T P    G E N E R A T O R ------------------------
 */
string Admin::passGen(string adminId)
{

    srand(time(nullptr));
    int num = rand() % 100;
    string s = "O";
    string newnum = to_string(num);
    string tempOtp = s.append(adminId);
    string otp = tempOtp.append(newnum);
    return otp;
}
/*
 *------------------------V A L I D A T E      O T P      E N T E R E D     B Y     A D M I N -----------------
 */
bool Admin::isValidPass(string adminId)
{
    bool res = false;
    string enteredOtp, otp = passGen(adminId);
    cout << "\nOTP is : " << otp << "\n";
    cout << "\nEnter the OTP received: ";
    getline(cin, enteredOtp, '\n');
    if (enteredOtp == otp)
    {
        res = true;
    }
    return res;
}
/*
 *---------------------------------------- R E M O V E    S T O R E    F I L E ------------------------
 */
void Admin::removFile(char* fileName)
{
    char c;
    string enteredMasterId;
    string masterId = (this->validAdmins).at(0);
    string exitotp;
    string adminOtp;
    ifstream filecheck;
    filecheck.open(fileName, ios::in | ios::binary);
    if (!filecheck)
    {
        cout << "\nFILE DOES NOT EXIST\n";
        return;
    }
    filecheck.close();
    cout << "\nAre you sure you wish to remove the file:\n";
    cout << "\nPress Y or N: ";
    cin >> c;
    if (c == 'y' || c == 'Y')
    {
        cout << "\nEnter Only Master Admin Id: ";
        cin.ignore();
        getline(cin, enteredMasterId, '\n');
        if (enteredMasterId != masterId)
        {
            cout << "\nInvalid Master Id, File could Not be deleted\n";
            return;
        }

        exitotp = passGen(masterId);
        cout << "\nOTP is: " << exitotp << "\n";
        cout << "\nEnter the OTP: ";
        cin >> adminOtp;
        if (adminOtp != exitotp)
        {
            cout << "\nInvalid OTP, File could Not be deleted\n";
            return;
        }
        remove(fileName);
        cout << "\nFile Removed Successfully\n";
    }
}
/*
 *---------------------------------------- A D M I N     R U N N E R ------------------------
 */
void Admin::adminRunner()
{

    string adminId;
    char fileName[50] = "./ProductMarket.txt";
    char pauseProg[1];
    int adminChoice;

re:
    cout << "\n\n                           *******************************************************************************";
    cout << "\n\n                           !!!!!!..................WELCOME TO METRO MEGA SUPER MARKET..............!!!!!!!";
    cout << "\n\n                           *******************************************************************************\n\n";
    cout << "\n\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n\n";
    cout << "\nEnter your Admin Id for validation: ";
    getline(cin, adminId, '\n');
    if (!isValidAdminId(adminId))
    {
        cout << "\nInvalid Admin Id\n";
        cout << "\n\nPress Any Key To Continue....";
        cin.getline(pauseProg, 1);
        cin.getline(pauseProg, 1);
        system("cls");
        goto re;
    }
    else if (!isValidPass(adminId))
    {
        cout << "\nInvalid OTP\n";
        cout << "\n\nPress Any Key To Continue....";
        cin.getline(pauseProg, 1);
        cin.getline(pauseProg, 1);
        system("cls");
        goto re;
    }

    while (1)
    {
        adminChoice = this->adminMenu();
        switch (adminChoice)
        {
        case 1:
        {
            this->addNewProduct(fileName);
            break;
        }

        case 2:
        {
            this->searchProduct(fileName);
            break;
        }

        case 3:
        {
            this->deleteProduct(fileName);
            break;
        }

        case 4:
        {
            this->updateProduct(fileName);
            break;
        }

        case 5:
        {
            this->viewStore(fileName);
            break;
        }

        case 6:
        {
            this->removFile(fileName);
            break;
        }

        case 7:
        {
            exit(0);
        }

        default:
        {
            cout << "\nInvalid Admin Choice\n";
        }
        }
        cout << "\n\nPress Any Key To Continue....";
        cin.getline(pauseProg, 1);
        cin.getline(pauseProg, 1);
    }
    delete this;
}