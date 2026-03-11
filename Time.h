#ifndef TIME_H
#define TIME_H

#include <iostream>

/**
 * @class Time
 * @brief This class is used to store and manipulate time information (hour, minute, second).
 *
 * @author William Halling
 * @version 0.3
 * @date April 2024
 */
class Time
{
public:
    /// Default constructor: initializes time to 00:00:00
    Time();

    /// Parameterized constructor
    Time(int hour, int minute, int second);

    /// Copy constructor
    Time(const Time& otherTime);

    /// Destructor
    ~Time();

    /// Assignment operator
    const Time& operator=(const Time& otherTime);

    /// Equality operator
    bool operator==(const Time& otherTime) const;

    /// Inequality operator
    bool operator!=(const Time& otherTime) const;

    /// Getters
    int getHour() const;
    int getMinute() const;
    int getSecond() const;

    /// Setters
    void setHour(int hour);
    void setMinute(int minute);
    void setSecond(int second);

    /// Validation functions
    bool validateHour(int hour) const;
    bool validateMinute(int minute) const;
    bool validateSecond(int second) const;

private:
    int m_Hour;   /// Hour of the day (0-23)
    int m_Minute; /// Minute of the hour (0-59)
    int m_Second; /// Second of the minute (0-59)
};

// Stream operators
std::istream& operator>>(std::istream& in, Time& t);
std::ostream& operator<<(std::ostream& out, const Time& t);

#endif // TIME_H
