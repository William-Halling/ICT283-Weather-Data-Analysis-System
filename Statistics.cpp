#include "Statistics.h"
#include <numeric>
#include <cmath>
#include <stdexcept>

namespace weather {

float average(const std::vector<float>& data) noexcept {
    if (data.empty()) return 0.0f;
    float sum = std::accumulate(data.begin(), data.end(), 0.0f);
    return sum / static_cast<float>(data.size());
}

float stdDev(const std::vector<float>& data, float mean) noexcept {
    if (data.size() < 2) return 0.0f;
    float varSum = 0.0f;
    for (float val : data) {
        float diff = val - mean;
        varSum += diff * diff;
    }
    return std::sqrt(varSum / static_cast<float>(data.size() - 1));
}

float pearsonCorrelation(const std::vector<float>& x, const std::vector<float>& y) {
    if (x.size() != y.size() || x.empty()) {
        throw std::invalid_argument("Vector dataset lengths misaligned for evaluation calculations.");
    }

    float avgX = average(x);
    float avgY = average(y);
    float num = 0.0f, denX = 0.0f, denY = 0.0f;

    for (size_t i = 0; i < x.size(); ++i) {
        float diffX = x[i] - avgX;
        float diffY = y[i] - avgY;
        num += diffX * diffY;
        denX += diffX * diffX;
        denY += diffY * diffY;
    }

    float denominator = std::sqrt(denX * denY);
    return (denominator == 0.0f) ? 0.0f : (num / denominator);
}

float roundToOneDecimal(float value) noexcept {
    return std::round(value * 10.0f) / 10.0f;
}

} // namespace weather
