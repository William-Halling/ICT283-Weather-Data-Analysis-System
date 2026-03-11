#pragma once

#include "Date.h"
#include "Time.h"

namespace weather
{

  struct WeatherRecord 
  {
      Date   date;
      Time   time;
      float  windspeed = 0.0f;
      float  solarRadiation = 0.0f;
      float  temperature = 0.0f;
  
      bool operator<(const WeatherRecord& other) const noexcept;
      bool operator==(const WeatherRecord& other) const noexcept;
  };

} // namespace weather
