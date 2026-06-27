#include "weather/WeatherRecord.h"
#include "container/BinarySearchTree.h"
#include "io/TextFile.h"
#include "io/CsvFile.h"
#include "ui/Options.h"
#include "collectors.h"
#include <iostream>
#include <vector>

int main() 
{
    try {
        io::TextFile fileList;
        fileList.loadFrom("data/data_source.txt");

        io::CsvFile parser(std::move(fileList));
        container::BinarySearchTree<weather::WeatherRecord> records;
        parser.loadAllInto(records);

        ui::Options ui;

        std::vector<float> windspeeds;
        std::vector<float> temperatures;
        std::vector<float> solar;

        while (true) {
            ui.displayMenu();
            auto choice = ui.getUserChoice();

            if (choice == ui::MenuOption::Quit) 
            {
                std::cout << "System shutting down safely.\n";
                
                break;
            }

            int month = 0, year = 0;
            windspeeds.clear();
            temperatures.clear();
            solar.clear();

            switch (choice) 
            {
                case ui::MenuOption::WindStats:
                    month = ui.getValidMonth();
                    year  = ui.getValidYear();
                    records.inOrderTraverse(collectors::collectWindSpeed, month, year, windspeeds);
                    ui.showWindspeedStats(month, year, windspeeds);
                break;

                case ui::MenuOption::TempStats:
                    year = ui.getValidYear();
                    for (int m = 1; m <= 12; ++m) 
                    {
                        temperatures.clear();
                        records.inOrderTraverse(collectors::collectTemperature, m, year, temperatures);
                        ui.showTemperatureStats(m, year, temperatures);
                    }
                break;

                case ui::MenuOption::SolarCorrelation:
                    month = ui.getValidMonth();
                    records.inOrderTraverse(collectors::collectAllMetrics, month, windspeeds, temperatures, solar);
                    ui.showSolarCorrelation(month, windspeeds, temperatures, solar);
                break;

                
                case ui::MenuOption::DiagnosticExport:
                    std::cout << "Exporting Pre-Order (Tree Structure):\n";
                    records.preOrderTraverse([](const auto& record) 
                    { 
                        std::cout << record.date << " "; 
                    });
                    
                    std::cout << "\nCleaning/Deleting nodes via Post-Order logic...\n";
                    records.postOrderTraverse([](const auto& record) 
                    {
                        
                    });
                break;

                default:
                    break;
            }
        }
    }
        
    catch (const std::exception& e)
    {
        std::cerr << "Fatal Exec Failure Routine Caught: " << e.what() << '\n';
        
        return 1;
    }
    return 0;
}
