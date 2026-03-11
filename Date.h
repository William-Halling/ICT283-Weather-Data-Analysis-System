#pragma once

#include <iosfwd>

namespace weather {

class Date {
public:
    Date() = default;
    Date(int day, int month, int year);

    int getDay()   const noexcept { return day_; }
    int getMonth() const noexcept { return month_; }
    int getYear()  const noexcept { return year_; }

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    bool operator==(const Date& other) const noexcept;
    bool operator!=(const Date& other) const noexcept { return !(*this == other); }
    bool operator< (const Date& other) const noexcept;

private:
    bool isValid() const noexcept;
    bool isLeapYear() const noexcept;

    int day_   = 1;
    int month_ = 1;
    int year_  = 1900;
};

std::istream& operator>>(std::istream& is, Date& date);
std::ostream& operator<<(std::ostream& os, const Date& date);

} // namespace weather
