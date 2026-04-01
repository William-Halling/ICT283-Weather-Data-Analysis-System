#pragma once

#include "TextFile.h"
#include "../weather/WeatherRecord.h"
#include "../container/BinarySearchTree.h"
#include <string>
#include <string_view>
#include <map>

namespace io {

class CsvFile {
public:
    explicit CsvFile(TextFile source) : sourceFiles_(std::move(source)) {}

    void loadAllInto(container::BinarySearchTree<weather::WeatherRecord>& tree);

private:
    void parseFile(const std::string& filename, container::BinarySearchTree<weather::WeatherRecord>& tree);
    void parseHeader(std::string_view header);
    // Passing by reference for efficiency
    void parseRow(std::string_view row, weather::WeatherRecord& rec) const;

    std::map<std::string, int> columnIndices_;
    TextFile sourceFiles_;
};

} // namespace io
