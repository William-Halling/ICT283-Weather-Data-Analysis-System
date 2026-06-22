#include "Statistics.h"
#include <numeric>
#include <cmath>
#include <stdexcept>

namespace weather {

float Statistics::average(const std::vector<float>& data) noexcept
{
    if (data.empty()) return 0.0f;
    const float sum = std::accumulate(data.begin(), data.end(), 0.0f);
    return sum / static_cast<float>(data.size());
}

float Statistics::stdDev(const std::vector<float>& data, float mean) noexcept
{
    if (data.size() < 2) return 0.0f;
    
    float varianceSum = 0.0f;
    
    for (const float val : data) 
    {
        const float diff = val - mean;
        varianceSum += diff * diff;
    }
    
    return std::sqrt(varianceSum / static_cast<float>(data.size() - 1));
}


float Statistics::pearsonCorrelation(const std::vector<float>& x, const std::vector<float>& y)
{
    if (x.size() != y.size() || x.empty())
    {
        throw std::invalid_argument("Vector data alignment mismatch for statistical analysis.");
    }

    const float avgX = average(x);
    const float avgY = average(y);

    float num = 0.0f;
    float denX = 0.0f;
    float denY = 0.0f;

    const size_t dataSize = x.size();
    for (size_t i = 0; i < dataSize; ++i)
    {
        const float diffX = x[i] - avgX;
        const float diffY = y[i] - avgY;
        
        num += diffX * diffY;
        denX += diffX * diffX;
        denY += diffY * diffY;
    }

    const float denominator = std::sqrt(denX * denY);
    
    return (denominator == 0.0f) ? 0.0f : (num / denominator);
}


float Statistics::roundToOneDecimal(float value) noexcept
{
    return std::round(value * 10.0f) / 10.0f;
}
