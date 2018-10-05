// Final Project Milestone 3
//
// Version 1.0
// Date: July 13, 2018
// Author: Henry Tran
// Student #: 
//
//
//
//
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
/////////////////////////////////////////////////////////////////

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA {

    const int max_sku_length = 7;
    const int max_unit_length = 10;
    const int max_name_length = 75;
    const double tax_rate = 0.13;

    class Product : public iProduct {

        char productType;
        char productSku[max_sku_length + 1];
        char productUnit[max_unit_length + 1];
        char* productName;
        int quantityOnHand;
        int quantityNeeded;
        double preTaxPrice;
        bool taxable;

    protected:
		ErrorState errorState;
        void name(const char*);
        const char* name() const;
        const char* sku() const;
        const char* unit() const;
        bool taxed() const;
        double price() const;
        double cost() const;
        void message(const char*);
        bool isClear() const;

    public:
        Product(char pType = 'N');
        Product(const char*, const char*, const char*, int pOnHand = 0, bool taxable = true, double priceBeforeTax = 0, int qNeeded = 0);
        Product(const Product&);
        Product& operator=(const Product&);
        ~Product();
        std::fstream& store(std::fstream& file, bool newLine = true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std::istream& read(std::istream& is);
        bool operator==(const char*) const;
        double total_cost() const;
        void quantity(int);
        bool isEmpty() const;
        int qtyNeeded() const;
        int quantity() const;
        bool operator>(const char*) const;
        bool operator>(const iProduct&) const;
        int operator+=(int);
    };

    std::ostream& operator<<(std::ostream&, const iProduct&);
    std::istream& operator>>(std::istream&, iProduct&);
    double operator+=(double&, const iProduct&);
}
#endif