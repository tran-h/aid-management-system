// Final Project Milestone 2
//
// Version 1.0
// Date: July 2, 2018
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

#include <cstring>
#include "ErrorState.h"

namespace AMA {

    ErrorState::ErrorState(const char * errorMessage) {
        if (errorMessage == nullptr) {
            msgAddress = nullptr;
        }
        else {
            msgAddress = new char[strlen(errorMessage) + 1];
            strcpy(msgAddress, errorMessage);
        }
    }

    ErrorState::~ErrorState() {
        delete[] msgAddress;
        msgAddress = nullptr;
    }

    void ErrorState::clear() {
        delete[] msgAddress;
        msgAddress = nullptr;
    }

    bool ErrorState::isClear() const {
        return (msgAddress == nullptr) ? true : false;
    }

    void ErrorState::message(const char* str) {
        delete[] msgAddress;
        msgAddress = new char[strlen(str) + 1];
        strcpy(msgAddress, str);
    }

    const char * ErrorState::message() const {
        return msgAddress;
    }

    std::ostream& operator<<(std::ostream& ostr, const ErrorState& em) {
        if (!em.isClear()) {
            ostr << em.message();
        }
        return ostr;
    }

}
