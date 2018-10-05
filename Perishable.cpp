// Final Project Milestone 5
//
// Version 1.0
// Date: July 23, 2018
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

#include "Perishable.h"

namespace AMA {

    Perishable::Perishable() : Product('P') {
        errorState.clear();
    }

    std::fstream& Perishable::store(std::fstream& file, bool newline) const {
        Product::store(file, false);
        file << ',' << date;
        if (newline) {
            file << std::endl;
        }
        return file;
    }

    std::fstream& Perishable::load(std::fstream& file) {
        Product::load(file);
        date.read(file);
        file.ignore();
        return file;
    }

    std::ostream& Perishable::write(std::ostream& os, bool linear) const {
        Product::write(os, linear);
        if (isClear() && !isEmpty()) {
            if (linear) {
                date.write(os);
            }

            else {
                os << "\n Expiry date: ";
                date.write(os);
            }
        }
        return os;
    }

    std::istream& Perishable::read(std::istream& is) {
        Product::read(is);
        Date tempDate;

        if (errorState.isClear()) {
            std::cout << " Expiry date (YYYY/MM/DD): ";
            tempDate.read(is);
        }

        if (tempDate.errCode() == CIN_FAILED) {
            errorState.clear();
            errorState.message("Invalid Date Entry");
        }

        if (tempDate.errCode() == YEAR_ERROR) {
            errorState.clear();
            errorState.message("Invalid Year in Date Entry");
        }

        if (tempDate.errCode() == MON_ERROR) {
            errorState.clear();
            errorState.message("Invalid Month in Date Entry");
        }

        if (tempDate.errCode() == DAY_ERROR) {
            errorState.clear();
            errorState.message("Invalid Day in Date Entry");
        }

        if (tempDate.errCode()) {
            is.setstate(std::ios::failbit);
        }

        if (!is.fail()) {
            errorState.clear();
            date = tempDate;
        }

        return is;
    }

    const Date& Perishable::expiry() const {
        return date;
    }

}
