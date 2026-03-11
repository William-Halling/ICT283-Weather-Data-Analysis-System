#pragma once

#include <iosfwd>

namespace weather
{

class Time
{
public:
    Time() = default;
    Time(int hour, int minute);

    int getHour()   const noexcept { return hour_; }
    int getMinute() const noexcept { return minute_; }

    void setHour(int h);
    void setMinute(int m);

    bool operator==(const Time& other) const noexcept;
    bool operator!=(const Time& other) const noexcept { return !(*this == other); }
    bool operator< (const Time& other) const noexcept;

private:
    int hour_   = 0;
    int minute_ = 0;
};

std::istream& operator>>(std::istream& is, Time& time);
std::ostream& operator<<(std::ostream& os, const Time& time);

} // namespace weather
