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

#include <iomanip>
#include <cstring>
#include <fstream>
#include "Product.h"
using namespace std;

namespace AMA {

    void Product::name(const char* pName) {
        if (pName != nullptr) {
            int length = strlen(pName);
            productName = new char[length + 1];
            for (int i = 0; i < length; i++) {
                productName[i] = pName[i];
            }
            productName[length] = '\0';
        }
    }

    const char* Product::name() const {
        return (productName[0] == '\0') ? nullptr : productName;
    }

    const char* Product::sku() const {
        return productSku;
    }

    const char* Product::unit() const {
        return productUnit;
    }

    bool Product::taxed() const {
        return taxable;
    }

    double Product::price() const {
        return preTaxPrice;
    }

    double Product::cost() const {
        if (taxable) {
            return preTaxPrice * (1 + tax_rate);
        }
        else {
            return preTaxPrice;
        }
    }

    void Product::message(const char* errorMsg) {
        errorState.message(errorMsg);
    }

    bool Product::isClear() const {
        return errorState.isClear();
    }

    Product::Product(char pType) {
        productType = pType;
        productSku[0] = '\0';
        productUnit[0] = '\0';
        productName = nullptr;
        quantityOnHand = -1;
        quantityNeeded = -1;
        preTaxPrice = -1;
        taxable = false;
    }

    Product::Product(const char* pSku, const char* pName, const char* pUnit, int qOnHand, bool taxStatus, double priceBeforeTax, int qNeeded) {

        strncpy(productSku, pSku, max_sku_length);
        productSku[max_sku_length] = '\0';

        strncpy(productUnit, pUnit, max_unit_length);
        productUnit[max_unit_length] = '\0';

        name(pName);
        quantityOnHand = qOnHand;
        taxable = taxStatus;
        preTaxPrice = priceBeforeTax;
        quantityNeeded = qNeeded;
    }

    Product::Product(const Product& product) {
        int length = strlen(product.productName);

        strncpy(productSku, product.productSku, max_sku_length);
        productSku[max_sku_length] = '\0';

        strncpy(productUnit, product.productUnit, max_unit_length);
        productUnit[max_unit_length] = '\0';

        productType = product.productType;
        quantityOnHand = product.quantityOnHand;
        quantityNeeded = product.quantityNeeded;
        preTaxPrice = product.preTaxPrice;
        taxable = product.taxable;

        if (product.productName != nullptr) {
            productName = new char[length + 1];

            for (int i = 0; i < length; i++) {
                productName[i] = product.productName[i];
            }
            productName[length] = '\0';
        }
        else {
            productName = nullptr;
        }
    }

    Product& Product::operator=(const Product& product) {
        if (this != &product) {
            int length = strlen(product.productName);

            strncpy(productSku, product.productSku, max_sku_length);
            productSku[max_sku_length] = '\0';

            strncpy(productUnit, product.productUnit, max_unit_length);
            productUnit[max_unit_length] = '\0';

            productType = product.productType;
            quantityOnHand = product.quantityOnHand;
            quantityNeeded = product.quantityNeeded;
            preTaxPrice = product.preTaxPrice;
            taxable = product.taxable;

            delete[] productName;
            if (product.productName != nullptr) {
                productName = new char[length + 1];
                for (int i = 0; i < length; i++) {
                    productName[i] = product.productName[i];
                }
                productName[length] = '\0';
            }
        }
        else {
            productName = nullptr;
        }
        return *this;
    }

    Product::~Product() {
        delete[] productName;
    }

    // inserts data into the fstream object delimited by commas
    std::fstream& Product::store(std::fstream& file, bool newLine) const {
        file << productType << ',' << productSku << ',' << productName << ',' << productUnit << ','
            << taxable << ',' << preTaxPrice << ',' << quantityOnHand << ',' << quantityNeeded;
        if (newLine) {
            file << endl;
        }
        return file;
    }

    // extracts fields for a single record and creates a temp object
    // to copy assign it to the current object
    std::fstream& Product::load(std::fstream& file) {
        char tempSku[max_sku_length];
        char tempName[max_name_length];
        char tempUnit[max_unit_length];
        int tempQtyOnHand;
        bool tempTaxable;
        double tempPrice;
        int tempQtyNeeded;
        char tempTax;

        if (file.is_open()) {
            file.getline(tempSku, max_sku_length, ',');
            tempSku[strlen(tempSku)] = '\0';
            file.getline(tempName, max_name_length, ',');
            tempName[strlen(tempName)] = '\0';
            file.getline(tempUnit, max_unit_length, ',');
            tempUnit[strlen(tempUnit)] = '\0';

            file >> tempTax;

            if (tempTax == '1') {
                tempTaxable = true;
            }
            else if (tempTax == '0') {
                tempTaxable = false;
            }

            file.ignore();
            file >> tempPrice;
            file.ignore();
            file >> tempQtyOnHand;
            file.ignore();
            file >> tempQtyNeeded;
            file.ignore();

            *this = Product(tempSku, tempName, tempUnit, tempQtyOnHand, tempTaxable, tempPrice, tempQtyNeeded);
        }

        return file;
    }

    // inserts the data from the current object into the ostream object
    std::ostream& Product::write(std::ostream& os, bool linear) const {
        if (!(errorState.isClear())) {
            os << errorState.message();
        }
        else if (linear) {
            os << setw(max_sku_length) << left << productSku << '|'
                << setw(20) << left << productName << '|'
                << setw(7) << right << fixed << setprecision(2) << cost() << '|'
                << setw(4) << right << quantityOnHand << '|'
                << setw(10) << left << productUnit << '|'
                << setw(4) << right << quantityNeeded << '|';
        }
        else {
            os << " Sku: " << productSku << endl
                << " Name (no spaces): " << productName << endl
                << " Price: " << preTaxPrice << endl;
            if (taxable) {
                os << " Price after tax: " << cost() << endl;
            }
            else {
                os << " Price after tax:  N/A" << endl;
            }

            os << " Quantity on Hand: " << quantityOnHand << ' ' << productUnit << endl
                << " Quantity needed: " << quantityNeeded;
        }
        return os;
    }

    // extracts data from the current object and validates them
    std::istream& Product::read(std::istream& is) {
        char taxed;
        char* pName = new char[max_name_length + 1];
        int qtyOnHand;
        int qtyNeeded;
        double price;

        if (!is.fail()) {
            cout << " Sku: ";
            is >> productSku;
            cin.ignore();

            cout << " Name (no spaces): ";
            is >> pName;
            name(pName);

            cout << " Unit: ";
            is >> productUnit;

            cout << " Taxed? (y/n): ";
            is >> taxed;

            if (!is.fail()) {
                errorState.clear();

                switch (taxed) {
                case 'y':
                    taxable = true;
                    break;
                case 'Y':
                    taxable = true;
                    break;
                case 'n':
                    taxable = false;
                    break;
                case 'N':
                    taxable = false;
                    break;
                default:
                    is.setstate(std::ios::failbit);
                    errorState.message("Only (Y)es or (N)o are acceptable");
                    return is;
                    break;
                }
            }
            else {
                is.setstate(std::ios::failbit);
                errorState.message("Only (Y)es or (N)o are acceptable");
                return is;
            }

            cout << " Price: ";
            is >> price;

            if (is.fail()) {
                errorState.clear();
                is.setstate(ios::failbit);
                errorState.message("Invalid Price Entry");
                return is;
            }
            else {
                preTaxPrice = price;
            }

            cout << " Quantity on hand: ";
            is >> qtyOnHand;

            if (is.fail()) {
                errorState.clear();
                errorState.message("Invalid Quantity Entry");
                is.setstate(ios::failbit);
                return is;
            }
            else {
                quantityOnHand = qtyOnHand;
            }

            cout << " Quantity needed: ";
            is >> qtyNeeded;
            cin.ignore();

            if (is.fail()) {
                errorState.clear();
                errorState.message("Invalid Quantity Needed Entry");
                is.setstate(ios::failbit);
                return is;
            }
            else {
                quantityNeeded = qtyNeeded;
            }

            if (!is.fail()) {
                errorState.clear();
            }
        }
        return is;
    }

    bool Product::operator==(const char* sku) const {
        return (strcmp(productSku, sku) == 0) ? true : false;
    }

    double Product::total_cost() const {
        return quantityOnHand * cost();
    }

    void Product::quantity(int qty) {
        quantityOnHand = qty;
    }

    bool Product::isEmpty() const {
        return (productName == nullptr) ? true : false;
    }

    int Product::qtyNeeded() const {
        return quantityNeeded;
    }

    int Product::quantity() const {
        return quantityOnHand;
    }

    bool Product::operator>(const char* sku) const {
        return (strcmp(productSku, sku) > 0) ? true : false;
    }

    bool Product::operator>(const iProduct& product) const {
        return (strcmp(productName, product.name()) > 0) ? true : false;
    }

    int Product::operator+=(int units) {
        if (units > 0) {
            quantityOnHand += units;
            return quantityOnHand;
        }
        else {
            return quantityOnHand;
        }
    }

    std::ostream& operator<<(std::ostream& os, const iProduct& product) {
        product.write(os, true);
        return os;
    }

    std::istream& operator>>(std::istream& is, iProduct& product) {
        product.read(is);
        return is;
    }

    double operator+=(double& dbl, const iProduct& product) {
        dbl += product.total_cost();
        return dbl;
    }
}