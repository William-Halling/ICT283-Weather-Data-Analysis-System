#pragma once

#include <string>
#include <vector>

namespace io 
{

    class TextFile 
    {
    public:
        TextFile() = default;
        explicit TextFile(std::vector<std::string> files) : files_(std::move(files)) {}
    
        const std::vector<std::string>& getFiles() const noexcept { return files_; }
    
        void loadFrom(const std::string& listFile);
    
    private:
        static bool isCsvFilename(const std::string& name) noexcept;
    
        std::vector<std::string> files_;
    };

} // namespace io
