#include "TextFile.h"
#include <fstream>
#include <stdexcept>

namespace io 
{

    void TextFile::loadFrom(const std::string& listFile)
    {
        std::ifstream file(listFile);
        
        if (!file.is_open())
            
            throw std::runtime_error("Cannot open file list: " + listFile);
    
        std::string line;
        while (std::getline(file, line)) 
        {
            if (!line.empty() && isCsvFilename(line))
                
                files_.push_back(line);
        }
    }
    
    
    bool TextFile::isCsvFilename(const std::string& name) noexcept 
    {
        return name.size() > 4 && name.substr(name.size() - 4) == ".csv";
    }

} // namespace io
