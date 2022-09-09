#pragma once
#ifndef ADMIN_H
#define ADMIN_H

#include "Product.hpp"
#include <vector>

class Admin
{
private:
    vector<string> validAdmins;

public:
    Admin()
    {
        this->validAdmins = { "Ad12021", "Ad12005", "Ad12007", "Ad12009", "Ad12011" };
    }
    int adminMenu();
    void addNewProduct(char*);
    void searchProduct(char*);
    void deleteProduct(char*);
    void updateProduct(char*);
    void viewStore(char*);
    void showProductDetails(Product*);
    void adminRunner();
    bool isValidAdminId(string);
    string passGen(string);
    bool isValidPass(string);
    void removFile(char*);
};

#endif