#include "Options.h"
#include "../weather/Statistics.h"
#include <iostream>
#include <limits>

namespace ui {

    void Options::displayMenu() const
    {
        std::cout << "\n--- Weather Statistics Menu ---\n"
                  << "1. Average wind speed and std dev for a given month/year\n"
                  << "2. Average temperature and std dev for each month of a year\n"
                  << "3. Pearson correlation (wind‑temp, wind‑solar, temp‑solar) for a month\n"
                  << "5. Quit\n";
    }


    MenuOption Options::getUserChoice() const     
    {
        int choice;
        while (true) 
        {
            std::cout << "Enter option: ";
           
            if (std::cin >> choice && choice >= 1 && choice <= 5 && choice != 4) 
            {
                return static_cast<MenuOption>(choice);
            }
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid choice. Please enter 1,2,3 or 5.\n";
        }
    }
    
    int Options::getValidMonth() const 
    {
        int month;
        while (true) 
        {
            std::cout << "Enter month (1‑12): ";
           
            if (std::cin >> month && month >= 1 && month <= 12)
                
                return month;
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid month.\n";
        }
    }
    
    int Options::getValidYear() const 
    {
        int year;
        while (true) 
        {
            std::cout << "Enter year (e.g., 2023): ";
            
            if (std::cin >> year && year >= 0)
                
                return year;
            
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid year.\n";
        }
    }
    
    void Options::showWindspeedStats(int month, int year, const std::vector<float>& windspeeds) const 
    {
        std::string mname = monthName(month);
        
        if (windspeeds.empty())
        {
            showNoData(month, year);
            
            return;
        }
        
        float avg = weather::average(windspeeds) * 3.6f;       // m/s → km/h
        float sd  = weather::stdDev(windspeeds, avg / 3.6f);
        std::cout << mname << " " << year << ":\n"
                  << "  Average wind speed: " << weather::roundToOneDecimal(avg) << " km/h\n"
                  << "  Sample std dev:     " << weather::roundToOneDecimal(sd)  << " km/h\n";
    }


    void Options::showTemperatureStats(int month, int year, const std::vector<float>& temperatures) const
    {
        std::string mname = monthName(month);
        
        if (temperatures.empty()) 
        {
            showNoData(month, year);
          
            return;
        }
        
        float avg = weather::average(temperatures);
        float sd  = weather::stdDev(temperatures, avg);
        std::cout << mname << ": "
                  << "avg " << weather::roundToOneDecimal(avg) << "°C, "
                  << "stdev " << weather::roundToOneDecimal(sd) << "°C\n";
    }
    
    void Options::showSolarCorrelation(int month, const std::vector<float>& windspeeds, const std::vector<float>& temperatures, const std::vector<float>& solar) const
    {
        std::string mname = monthName(month);
        
        if (windspeeds.empty() || temperatures.empty() || solar.empty()) 
        {
            std::cout << mname << ": insufficient data for correlation.\n";
            
            return;
        }
        
        float r_st = weather::pearsonCorrelation(windspeeds, temperatures);
        float r_sr = weather::pearsonCorrelation(windspeeds, solar);
    
        
        float r_tr = weather::pearsonCorrelation(temperatures, solar);
        std::cout << "Pearson correlations for " << mname << ":\n"
                  << "  Wind‑Temp : " << weather::roundToOneDecimal(r_st) << "\n"
                  << "  Wind‑Solar: " << weather::roundToOneDecimal(r_sr) << "\n"
                  << "  Temp‑Solar: " << weather::roundToOneDecimal(r_tr) << "\n";
    }
    
    void Options::showNoData(int month, int year) const 
    {
        std::cout << monthName(month) << " " << year << ": No Data\n";
    }
    
    
    std::string Options::monthName(int month) const 
    {
        static const char* names[] = {
            "January", "February", "March", "April", "May", "June",
            "July", "August", "September", "October", "November", "December"
        };
        
        if (month >= 1 && month <= 12) 
            
            return names[month-1];
        
        return "Invalid";
    }

} // namespace ui
