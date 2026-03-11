#include "Time.h"
#include <stdexcept>

namespace weather {

Time::Time(int h, int m) {
    setHour(h);
    setMinute(m);
}

void Time::setHour(int h) {
    if (h < 0 || h > 23) throw std::invalid_argument("Invalid hour");
    hour_ = h;
}

void Time::setMinute(int m) 
{
    if (m < 0 || m > 59) throw std::invalid_argument("Invalid minute");
    minute_ = m;
}

bool Time::operator==(const Time& other) const noexcept 
{
    return hour_ == other.hour_ && minute_ == other.minute_;
}

bool Time::operator<(const Time& other) const noexcept 
{
    if (hour_ != other.hour_) return hour_ < other.hour_;
    return minute_ < other.minute_;
}

std::istream& operator>>(std::istream& is, Time& time) 
{
    int h, m;
    char colon;
    if (is >> h >> colon >> m && colon == ':')
        time = Time(h, m);
    else
        is.setstate(std::ios::failbit);
    
    return is;
}

std::ostream& operator<<(std::ostream& os, const Time& time) 
{
    os << time.getHour() << ':' << time.getMinute();
    return os;
}

} // namespace weather
