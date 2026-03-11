#include "Time.h"

Time::Time() : m_Hour(0), m_Minute(0), m_Second(0) {}

Time::Time(int hour, int minute, int second) : m_Hour(hour), m_Minute(minute), m_Second(second) {}

Time::Time(const Time& otherTime) 
    : m_Hour(otherTime.m_Hour), m_Minute(otherTime.m_Minute), m_Second(otherTime.m_Second) 
{}


Time::~Time() {}


const Time& Time::operator=(const Time& otherTime)
{
    if (this != &otherTime)
    {
        m_Hour   = otherTime.m_Hour;
        m_Minute = otherTime.m_Minute;
        m_Second = otherTime.m_Second;
    }
    return *this;
}


bool Time::operator==(const Time& otherTime) const
{
    return (m_Hour == otherTime.m_Hour && m_Minute == otherTime.m_Minute && m_Second == otherTime.m_Second);
}

bool Time::operator!=(const Time& otherTime) const
{
    return !(*this == otherTime);
}

int Time::getHour() const { return m_Hour; }
int Time::getMinute() const { return m_Minute; }
int Time::getSecond() const { return m_Second; }


void Time::setHour(int hour)
{
    if (validateHour(hour)) m_Hour = hour;
}


void Time::setMinute(int minute)
{
    if (validateMinute(minute)) 
    {
        m_Minute = minute;
    }
}

void Time::setSecond(int second)
{
    if (validateSecond(second))
    {
        m_Second = second;
    }
}


bool Time::validateHour(int hour) const
{
    return hour >= 0 && hour <= 23;
}


bool Time::validateMinute(int minute) const
{
    return minute >= 0 && minute <= 59;
}


bool Time::validateSecond(int second) const
{
    return second >= 0 && second <= 59;
}


std::istream& operator>>(std::istream& in, Time& t)
{
    int hour, minute, second;
    char sep1, sep2;
    
    in >> hour >> sep1 >> minute >> sep2 >> second;
    
    if (sep1 == ':' && sep2 == ':')
    {
        t.setHour(hour);
        t.setMinute(minute);
        t.setSecond(second);
    }
    
    return in;
}


std::ostream& operator<<(std::ostream& out, const Time& t)
{
    out << (t.getHour() < 10 ? "0" : "") << t.getHour() << ":"
        << (t.getMinute() < 10 ? "0" : "") << t.getMinute() << ":"
        << (t.getSecond() < 10 ? "0" : "") << t.getSecond();
    
    return out;
}
