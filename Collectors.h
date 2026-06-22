#pragma once
#include "weather/WeatherRecord.h"
#include <vector>

namespace collectors {

inline void collectWindSpeed(const weather::WeatherRecord& rec, int month, int year, std::vector<float>& dest) {
    if (rec.date.getMonth() == month && rec.date.getYear() == year) {
        dest.push_back(rec.windspeed);
    }
}

inline void collectTemperature(const weather::WeatherRecord& rec, int month, int year, std::vector<float>& dest) {
    if (rec.date.getMonth() == month && rec.date.getYear() == year) {
        dest.push_back(rec.temperature);
    }
}

inline void collectAllMetrics(const weather::WeatherRecord& rec, int month, std::vector<float>& ws, std::vector<float>& temp, std::vector<float>& solar) {
    if (rec.date.getMonth() == month) {
        ws.push_back(rec.windspeed);
        temp.push_back(rec.temperature);
        solar.push_back(rec.solarRadiation);
    }
}

}
