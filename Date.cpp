// Final Project Milestone 1
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

#include "Date.h"

namespace AMA {

    // number of days in month mon_ and year year_
    //
    int Date::mdays(int mon, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int month = mon >= 1 && mon <= 12 ? mon : 13;
        month--;
        return days[month] + int((month == 1)*((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }

    bool Date::isEmpty() const {
        return (year == 0 && month == 0 && day == 0) ? true : false;
    }

    // reads the date from the console
    std::istream& Date::read(std::istream& istr) {
        char delimiter;
        istr.clear();
        istr >> year >> delimiter >> month >> delimiter >> day;

        if (istr.fail()) {
            errCode(CIN_FAILED);
        }
        else if (year < min_year || year > max_year) {
            Date A;
            A.errCode(YEAR_ERROR);
            *this = A;
        }
        else if (month < 1 || month > 12) {
            Date A;
            A.errCode(MON_ERROR);
            *this = A;
        }
        else if (day < 1 || day > mdays(month, year)) {
            Date A;
            A.errCode(DAY_ERROR);
            *this = A;
        }

        return istr;
    }

    // writes the date to an ostream object in the format: YYYY/MM/DD
    std::ostream& Date::write(std::ostream& ostr) const {
        ostr << year << '/';

        if (month < 10) {
            ostr << 0;
        }

        ostr << month << '/';

        if (day < 10) {
            ostr << 0;
        }

        ostr << day;

        return ostr;
    }

    void Date::errCode(int errorCode) {
        errorState = errorCode;
    }

    Date::Date() {
        errorState = NO_ERROR;
        comparator = 0;
        year = 0;
        month = 0;
        day = 0;
    }

    Date::Date(int year, int month, int day) {
        bool validYear = (year >= min_year && year <= max_year) ? true : false;
        bool validMonth = (month >= 1 && month <= 12) ? true : false;
        int daysInMonth = mdays(month, year);
        bool validDay = (day >= 1 && day <= daysInMonth) ? true : false;

        if (validYear && validMonth && validDay) {
            this->year = year;
            this->month = month;
            this->day = day;
            comparator = year * 372 + month * 13 + day;
            errorState = NO_ERROR;
        }
        else {
            this->year = 0;
            this->month = 0;
            this->day = 0;
            comparator = 0;
        }
    }

    bool Date::operator==(const Date& rhs) const {
        if (!isEmpty() && !rhs.isEmpty()) {
            if (year == rhs.year && month == rhs.month && day == rhs.day) {
                return true;
            }
        }
        return false;
    }

    bool Date::operator!=(const Date& rhs) const {
        if (!isEmpty() && !rhs.isEmpty()) {
            return !(*this == rhs);
        }
        else {
            return false;
        }
    }

    bool Date::operator<(const Date& rhs) const {
        if (!isEmpty() && !rhs.isEmpty()) {
            if (year < rhs.year) {
                return true;
            }
            else if (year == rhs.year) {
                if (month < rhs.month) {
                    return true;
                }
                else if (month == rhs.month) {
                    if (day < rhs.day) {
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else {
                    return false;
                }
            }
            else {
                return false;
            }
        }
        else {
            return false;
        }
    }

    bool Date::operator>(const Date& rhs) const {
        return !(*this < rhs);
    }

    bool Date::operator<=(const Date& rhs) const {
        return (*this < rhs || *this == rhs);
    }

    bool Date::operator>=(const Date& rhs) const {
        return (*this > rhs || *this == rhs);
    }

    int Date::errCode() const {
        return errorState;
    }

    bool Date::bad() const {
        return errorState != NO_ERROR;
    }

    std::ostream& operator<<(std::ostream& ostr, const Date& d) {
        d.write(ostr);
        return ostr;
    }

    std::istream& operator>>(std::istream& istr, Date& d) {
        d.read(istr);
        return istr;
    }

}
