#pragma once

#include <iosfwd>
#include <vector>
#include <string>

namespace ui
{

    enum class MenuOption 
    {
        WindStats = 1,
        TempStats,
        SolarCorrelation,
        Quit = 5
    };

    class Options 
    {
    public:
        void displayMenu() const;
        MenuOption getUserChoice() const;
    
        int  getValidMonth() const;
        int  getValidYear()  const;
    
        void showWindspeedStats(int month, int year, const std::vector<float>& windspeeds) const;
        void showTemperatureStats(int month, int year, const std::vector<float>& temperatures) const;
        void showSolarCorrelation(int month, const std::vector<float>& windspeeds, const std::vector<float>& temperatures, const std::vector<float>& solar) const;
        void showNoData(int month, int year) const;
    
    private:
        std::string monthName(int month) const;
    };

} // namespace ui
