#pragma once
#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <string.h>

using namespace std;

class Product
{

private:
    static int count;
    int Pid;
    char Pname[50];
    double Pcost;
    int Pdiscount;
    int Pcount;
    double netShelfPrice;

public:
    Product()
    {
        this->Pid = 0;
        char temparr[] = "No Product";
        strcpy_s(this->Pname, temparr);
        this->Pcost = 0.0;
        this->Pdiscount = 0;
        this->Pcount = 0;
        this->netShelfPrice = 0.0;
    }

    void setProductShelfPrice();
    void setDetailsForNewProduct();
    int getProdId();
    char* getProdName();
    double getProdCost();
    int getProdDiscount();
    int getProdQuantity();
    double getProdShelfPrice();
    void setDetailsForExistingProduct();
};

#endif