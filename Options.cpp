#include "ui/Options.h"
#include "weather/Date.h"
#include "weather/WeatherType.h"
#include "../containers/Vector.h"
#include "../weather/Statistics.h"

#include <iostream>
#include <limits>
#include <string>

namespace weather
{

/**
 * @brief Displays the main menu options
 */
void Options::displayMenu() const 
{
    std::cout << "\n=== Weather Data Analysis Menu ===\n";
    std::cout << "1. Average windspeed and sample standard deviation for a specific month and year\n";
    std::cout << "2. Average ambient air temperature and sample std dev for each month of a specified year\n";
    std::cout << "3. Total solar radiation (kWh/m²) for each month of a specified year\n";
    std::cout << "5. Quit program\n";
    std::cout << "Enter choice: ";
}

/**
 * @brief Gets and validates the user's menu choice
 * @return Valid MenuOption enum value
 */
MenuOption Options::getUserChoice() const 
{
    int input = 0;
    while (true) 
    {
        std::cin >> input;

        if (std::cin.fail()) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number: ";
            
            continue;
        }
        

        if (input == 1 || input == 2 || input == 3 || input == 5) 
        {
            return static_cast<MenuOption>(input);
        }

        std::cout << "Invalid choice. Please select 1, 2, 3, or 5: ";
    }
}


/**
 * @brief Prompts for and validates a month (1–12)
 * @return Valid month (1–12)
 */
int Options::getValidMonth() const 
{
    int month = 0;
    while (true) 
    {
        std::cout << "Enter month (1–12): ";
        std::cin >> month;

        if (std::cin.fail() || month < 1 || month > 12)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid month. Please enter a number between 1 and 12: ";
            continue;
        }
        return month;
    }
}


/**
 * @brief Prompts for and validates a year (positive integer)
 * @return Valid year
 */
int Options::getValidYear() const 
{
    int year = 0;
    while (true) 
    {
        std::cout << "Enter year: ";
        std::cin >> year;

        if (std::cin.fail() || year < 0) 
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid year. Please enter a positive number: ";
            continue;
        }
        
        return year;
    }
}



/**
 * @brief Displays windspeed statistics for a given month/year
 */
void Options::showWindspeedStats(int month, int year, const Statistics& stats) const
{
    std::string name = monthName(month);
    auto windspeeds = stats.windspeeds();

    if (windspeeds.size() == 0)
    {
        showNoData(month, year);
        
        return;
    }

    float avg = stats.average(windspeeds) * 3.6f;  // m/s → km/h
    float stdev = stats.stdDev(windspeeds, avg / 3.6f);  // back to m/s for std dev

    avg = stats.roundToOneDecimal(avg);
    stdev = stats.roundToOneDecimal(stdev);

    std::cout << name << " " << year << ":\n";
    std::cout << "  Average Speed: " << avg << " km/h\n";
    std::cout << "  Sample stdev:  " << stdev << "\n";
}


/**
 * @brief Displays temperature statistics for a single month of a year
 */
void Options::showTemperatureStats(int month, int year, const Statistics& stats) const
{
    std::string name = monthName(month);
    auto temps = stats.temperatures();

    if (temps.size() == 0)
    {
        std::cout << name << ": No Data\n";
        return;
    }
    

    float avg = stats.average(temps);
    float stdev = stats.stdDev(temps, avg);

    avg = stats.roundToOneDecimal(avg);
    stdev = stats.roundToOneDecimal(stdev);

    std::cout << name << ":\n";
    std::cout << "  Average: " << avg << " °C, stdev: " << stdev << "\n";
}

/**
 * @brief Displays total solar radiation for a single month of a year
 * (Placeholder — implement when ready)
 */
void Options::showSolarRadiationStats(int month, int year, const Statistics& stats) const
{
    std::string name = monthName(month);
    auto solar = stats.solarRadiation();

    if (solar.size() == 0) 
    {
        std::cout << name << ": No Data\n";
        
        return;
    }

    float total = stats.total(solar);
    total = stats.roundToOneDecimal(total);

    std::cout << name << ": " << total << " kWh/m²\n";
}


/**
 * @brief Displays "No Data" message for a month/year
 */
void Options::showNoData(int month, int year) const
{
    std::string name = monthName(month);
    
    std::cout << name << " " << year << ": No Data\n";
}


/**
 * @brief Converts numeric month to full name
 * @param month 1–12
 * @return Month name or "Invalid Month"
 */
std::string Options::monthName(int month) const 
{
    static const std::string names[13] = {
        "", "January", "February", "March", "April", "May", "June",
        "July", "August", "September", "October", "November", "December"
    };

    if (month >= 1 && month <= 12)
    {
        return names[month];
    }
    
    return "Invalid Month";
}

} // namespace weather
