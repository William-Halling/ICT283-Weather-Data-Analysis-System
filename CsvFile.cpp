#include "CsvFile.h"
#include <fstream>
#include <sstream>
#include <stdexcept>

namespace io {

void CsvFile::loadAllInto(container::BinarySearchTree<weather::WeatherRecord>& tree)
{
    for (const auto& fname : sourceFiles_.getFiles())
        parseFile(fname, tree);
}

void CsvFile::parseFile(const std::string& filename, container::BinarySearchTree<weather::WeatherRecord>& tree)
{
    std::ifstream file(filename);
    
    if (!file.is_open())
        
        throw std::runtime_error("Cannot open CSV: " + filename);

    std::string header;
    
    if (!std::getline(file, header))
        
        return; // empty file

    parseHeader(header);

    std::string line;
    while (std::getline(file, line)) 
    {
        if (line.empty()) 
            
            continue;
        
        weather::WeatherRecord rec;
        parseRow(line, rec);
        tree.insert(rec);
    }
}

void CsvFile::parseHeader(const std::string& header) 
{
    columnIndices_.clear();
    std::stringstream ss(header);
    std::string col;
    int idx = 0;
    while (std::getline(ss, col, ',')) 
    {
        columnIndices_[col] = idx++;
    }
}

void CsvFile::parseRow(const std::string& row, weather::WeatherRecord& rec) const 
{
    std::stringstream ss(row);
    std::string field;
    int idx = 0;

    auto getIndex = [&](const std::string& name)
    {
        auto it = columnIndices_.find(name);
        
        return (it != columnIndices_.end()) ? it->second : -1;
    };

    int posWAST = getIndex("WAST");
    int posSR   = getIndex("SR");
    int posT    = getIndex("T");
    int posS    = getIndex("S");

    while (std::getline(ss, field, ',')) 
    {
        if (idx == posWAST) 
        {
            std::stringstream fs(field);
            fs >> rec.date >> rec.time;
        }
            
        else if (idx == posSR) 
        {
            float val;
            std::stringstream(field) >> val;
            rec.solarRadiation = val * (1.0f/6.0f) / 100.0f;
        }
            
        else if (idx == posT) 
        {
            std::stringstream(field) >> rec.temperature;
        }
        else if (idx == posS)
        {
            std::stringstream(field) >> rec.windspeed;
        }
        ++idx;
    }
}

} // namespace io
