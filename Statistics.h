#pragma once
#include <vector>

namespace weather {

float average(const std::vector<float>& data) noexcept;
float stdDev(const std::vector<float>& data, float mean) noexcept;
float pearsonCorrelation(const std::vector<float>& x, const std::vector<float>& y);
float roundToOneDecimal(float value) noexcept;

} // namespace weather
