#include "Options.h"
#include "../weather/Statistics.h"
#include <iostream>
#include <limits>

namespace ui {

void Options::displayMenu() const 
{
    std::cout << "\n--- Weather Statistics Processing Framework ---\n"
              << "1. Average wind speed and standard deviation for a targeted month/year\n"
              << "2. Average temperature and standard deviation for every month of a year\n"
              << "3. Pearson correlation coefficients evaluations for a targeted month\n"
              << "5. Quit and shut down operational context loop\n";
}


MenuOption Options::getUserChoice() const 
{
    int choice;
    while (true) 
    {
        std::cout << "Selection choice entry interface context string target: ";
        
        if (std::cin >> choice && ((choice >= 1 && choice <= 3) || choice == 5))
        {
            return static_cast<MenuOption>(choice);
        }
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid entry selection runtime exception interface parsing failure.\n";
    }
}


int Options::getValidMonth() const 
{
    int month;
    while (true) 
    {
        std::cout << "Enter targeted month (1-12): ";
        
        if (std::cin >> month && month >= 1 && month <= 12) 
           
            return month;
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


int Options::getValidYear() const 
{
    int year;
    while (true) 
    {
        std::cout << "Enter targeted evaluation context year: ";
        
        if (std::cin >> year && year >= 1900) 
            return year;
        
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}


void Options::showWindspeedStats(int month, int year, const std::vector<float>& windspeeds) const
{
    if (windspeeds.empty()) 
    {
        std::cout << monthName(month) << " " << year << ": Specified log set empty.\n";
        
        return;
    }
    float avg = weather::average(windspeeds) * 3.6f; // conversion logic
    float sd = weather::stdDev(windspeeds, avg / 3.6f) * 3.6f;
    std::cout << monthName(month) << " " << year << " execution results output:\n"
              << "  Average speed metrics: " << weather::roundToOneDecimal(avg) << " km/h\n"
              << "  Deviation value trace: " << weather::roundToOneDecimal(sd) << " km/h\n";
}


void Options::showTemperatureStats(int month, int year, const std::vector<float>& temperatures) const 
{
    if (temperatures.empty())
        
        return;
    
    float avg = weather::average(temperatures);
    float sd = weather::stdDev(temperatures, avg);
    std::cout << monthName(month) << ": avg " << weather::roundToOneDecimal(avg) << "°C, stdev " << weather::roundToOneDecimal(sd) << "°C\n";
}


void Options::showSolarCorrelation(int month, const std::vector<float>& ws, const std::vector<float>& temp, const std::vector<float>& solar) const 
{
    if (ws.empty() || temp.empty() || solar.empty()) 
    {
        std::cout << monthName(month) << ": Insufficient element metrics found.\n";
        
        return;
    }
    std::cout << "Pearson Evaluation matrix logs for " << monthName(month) << ":\n"
              << "  Wind-Temp trace : " << weather::roundToOneDecimal(weather::pearsonCorrelation(ws, temp)) << "\n"
              << "  Wind-Solar trace: " << weather::roundToOneDecimal(weather::pearsonCorrelation(ws, solar)) << "\n"
              << "  Temp-Solar trace: " << weather::roundToOneDecimal(weather::pearsonCorrelation(temp, solar)) << "\n";
}


std::string Options::monthName(int month) const 
{
    static const char* names[] = { "January", "February", "March", "April", "May", "June",  "July", "August", "September", "October", "November", "December" };
    
    return (month >= 1 && month <= 12) ? names[month - 1] : "Invalid";
}

} // namespace ui
