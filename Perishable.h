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

#ifndef AMA_PERISHABLE_H
#define AMA_PERISHABLE_H

#include "Product.h"
#include "Date.h"

namespace AMA {

    class Perishable : public Product {

        Date date;

    public:
        Perishable();
        std::fstream& store(std::fstream& file, bool newline = true) const;
        std::fstream& load(std::fstream& file);
        std::ostream& write(std::ostream& os, bool linear) const;
        std::istream& read(std::istream& is);
        const Date& expiry() const;
    };
}

#endif 
