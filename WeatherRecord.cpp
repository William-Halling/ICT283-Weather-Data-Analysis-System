#include "WeatherRecord.h"

namespace weather
{

bool WeatherRecord::operator<(const WeatherRecord& other) const noexcept 
{
    if (date != other.date)
        return date < other.date;
  
    return time < other.time;
}

bool WeatherRecord::operator==(const WeatherRecord& other) const noexcept 
{
    return date == other.date && time == other.time;
}

} // namespace weather
