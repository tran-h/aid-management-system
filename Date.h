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

#ifndef AMA_DATE_H
#define AMA_DATE_H
#include <iostream>

namespace AMA {

    const int NO_ERROR = 0;
    const int CIN_FAILED = 1;
    const int YEAR_ERROR = 2;
    const int MON_ERROR = 3;
    const int DAY_ERROR = 4;
    const int min_year = 2000;
    const int max_year = 2030;

  class Date {
      int year, month, day, comparator, errorState;
      int mdays(int, int)const;
      void errCode(int);
 
  public:
      Date();
      Date(int, int, int);
      bool operator==(const Date& rhs) const;
      bool operator!=(const Date& rhs) const;
      bool operator<(const Date& rhs) const;
      bool operator>(const Date& rhs) const;
      bool operator<=(const Date& rhs) const;
      bool operator>=(const Date& rhs) const;
      int errCode() const;
      bool bad() const;
      bool isEmpty() const;
      std::istream& read(std::istream& istr);
      std::ostream& write(std::ostream& ostr) const;
  };
  std::ostream& operator<<(std::ostream& ostr, const Date&);
  std::istream& operator>>(std::istream& istr, Date&);
}
#endif