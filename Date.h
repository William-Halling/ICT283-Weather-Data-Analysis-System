#pragma once
#include <iostream>

namespace weather {

class Date {
public:
    Date() = default;
    Date(int day, int month, int year);

    [[nodiscard]] int getDay()   const noexcept { return day_; }
    [[nodiscard]] int getMonth() const noexcept { return month_; }
    [[nodiscard]] int getYear()  const noexcept { return year_; }

    void setDay(int d);
    void setMonth(int m);
    void setYear(int y);

    [[nodiscard]] bool operator==(const Date& other) const noexcept;
    [[nodiscard]] bool operator<(const Date& other) const noexcept;
    [[nodiscard]] bool operator!=(const Date& other) const noexcept { return !(*this == other); }

private:
    [[nodiscard]] bool isValid() const noexcept;
    [[nodiscard]] bool isLeapYear() const noexcept;

    int day_   = 1;
    int month_ = 1;
    int year_  = 1900;
};

std::istream& operator>>(std::istream& is, Date& date);
std::ostream& operator<<(std::ostream& os, const Date& date);

} // namespace weather
