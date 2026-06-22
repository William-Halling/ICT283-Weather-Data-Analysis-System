#include "CsvFile.h"
#include <fstream>
#include <charconv>
#include <string_view>
#include <stdexcept>

namespace io {

void CsvFile::loadAllInto(container::BinarySearchTree<weather::WeatherRecord>& tree)
{
    for (const auto& fname : sourceFiles_.getFiles())
       
        parseFile(fname, tree);
}

void CsvFile::parseFile(const std::string& filename, container::BinarySearchTree<weather::WeatherRecord>& tree)
{
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open())
        throw std::runtime_error("Cannot open CSV: " + filename);

    std::string header;
    if (!std::getline(file, header))
        
        return; 

    parseHeader(header);

    
    std::string line;
    while (std::getline(file, line)) 
    {
        if (line.empty()) 
        {    
            continue;
        }
        weather::WeatherRecord rec;
        parseRow(line, rec);
        tree.insert(std::move(rec));
    }
}

void CsvFile::parseHeader(const std::string& header) 
{
    columnIndices_.clear();
    std::string_view view(header);
    size_t start = 0;
    int idx = 0;

    while (start < view.size()) 
    {
        size_t end = view.find(',', start);
        
        if (end == std::string_view::npos) 
        {
            end = view.size();
        }
        
        std::string col(view.substr(start, end - start));
        columnIndices_[std::move(col)] = idx++;
        start = end + 1;
    }
}


void CsvFile::parseRow(const std::string& row, weather::WeatherRecord& rec) const 
{
    std::string_view view(row);
    int idx = 0;

    auto getIndex = [&](const std::string& name) noexcept -> int 
    {
        auto it = columnIndices_.find(name);
        
        return (it != columnIndices_.end()) ? it->second : -1;
    };
    

    const int posWAST = getIndex("WAST");
    const int posSR   = getIndex("SR");
    const int posT    = getIndex("T");
    const int posS    = getIndex("S");

    size_t start = 0;
    while (start < view.size()) 
    {
        size_t end = view.find(',', start);
        
        if (end == std::string_view::npos)
            end = view.size();
        
        std::string_view field = view.substr(start, end - start);

        if (idx == posWAST) 
        {
            
            size_t spacePos = field.find(' ');
            if (spacePos != std::string_view::npos) 
            {
                std::string_view dateField = field.substr(0, spacePos);
                std::string_view timeField = field.substr(spacePos + 1);
                
                
                int d = 0, m = 0, y = 0, hr = 0, mn = 0;
                size_t p1 = dateField.find('/');
                size_t p2 = dateField.find('/', p1 + 1);
                
                std::from_chars(dateField.data(), dateField.data() + p1, d);
                std::from_chars(dateField.data() + p1 + 1, dateField.data() + p2, m);
                std::from_chars(dateField.data() + p2 + 1, dateField.data() + dateField.size(), y);
                
                size_t colonPos = timeField.find(':');
                std::from_chars(timeField.data(), timeField.data() + colonPos, hr);
                std::from_chars(timeField.data() + colonPos + 1, timeField.data() + timeField.size(), mn);
                
                rec.date = weather::Date(d, m, y);
                rec.time = weather::Time(hr, mn);
            }
        }
            
        else if (idx == posSR) 
        {
            float val = 0.0f;
            std::from_chars(field.data(), field.data() + field.size(), val);
            rec.solarRadiation = val * (1.0f / 6.0f) / 100.0f;
        }
            
        else if (idx == posT) 
        {
            std::from_chars(field.data(), field.data() + field.size(), rec.temperature);
        }
            
        else if (idx == posS)
        {
            std::from_chars(field.data(), field.data() + field.size(), rec.windspeed);
        }

        start = end + 1;
        ++idx;
    }
}
}
