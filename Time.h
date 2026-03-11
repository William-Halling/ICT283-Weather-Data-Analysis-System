#pragma once

#include <iosfwd>

namespace weather 
{

class Time 
{
public:
    Time() noexcept = default;
    Time(int hour, int minute);

    int getHour() const;
    int getMinute() const;

    void setHour(int h);
    void setMinute(int m);

    bool operator==(const Time& other) const noexcept;
    bool operator<(const Time& other) const noexcept;
    bool operator>(const Time& other) const noexcept { return other < *this; }

private:
    int hour_ = 0;
    int minute_ = 0;
};

std::istream& operator>>(std::istream& is, Time& time);
std::ostream& operator<<(std::ostream& os, const Time& time);

} // namespace weather
