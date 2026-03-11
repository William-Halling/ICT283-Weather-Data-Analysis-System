#include "Date.h"
#include <sstream>
#include <iomanip>

namespace weather {

Date::Date(int day, int month, int year) : day_(day), month_(month), year_(year) {
    if (!isValid()) {
        throw std::invalid_argument("Invalid date");
    }
}


void Date::setDay(int d) {
    day_ = d;
 
    if (!isValid())
    {
        throw std::invalid_argument("Invalid day");
    }
}

void Date::setMonth(int m) {
    month_ = m;
    
    if (!isValid()) 
    {
        throw std::invalid_argument("Invalid month");
    }
}


void Date::setYear(int y) {
    year_ = y;
    if (!isValid()) 
    {
        throw std::invalid_argument("Invalid year");
    }
}

bool Date::operator==(const Date& other) const noexcept
{
    return day_ == other.day_ && month_ == other.month_ && year_ == other.year_;
}

bool Date::operator<(const Date& other) const noexcept 
{
    if (year_ != other.year_)
    {    
        return year_ < other.year_;
    }
    
    if (month_ != other.month_) 
    {    
        return month_ < other.month_;
    }
    
    return day_ < other.day_;
}


bool Date::isValid() const noexcept 
{
    if (year_ < 1900 || year_ > 2100) 
    {
        return false;
    }
    
    if (month_ < 1 || month_ > 12) 
    {    
        return false;
    }
    
    if (day_ < 1) 
    {    
        return false;
    }
    
    static const int daysInMonth[] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    int maxDays = daysInMonth[month_];
    
    if (month_ == 2 && isLeapYear(year_))
    {
        maxDays = 29;
    }
    
    return day_ <= maxDays;
}


bool Date::isLeapYear(int y) const noexcept 
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

std::istream& operator>>(std::istream& is, Date& date) {
    int d, m, y;
    char sep1, sep2;
    
    if (is >> d >> sep1 >> m >> sep2 >> y && sep1 == '/' && sep2 == '/') 
    {
        date = Date(d, m, y);
    } 
    else 
    {
        is.setstate(std::ios::failbit);
    }
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    os << std::setw(2) << std::setfill('0') << date.getDay() << '/'
       << std::setw(2) << std::setfill('0') << date.getMonth() << '/'
       << date.getYear();
    return os;
}

} // namespace weather
