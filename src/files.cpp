#include "files.h"
#include <filesystem>

bool isEmptyFile(std::string filePath)
{
    return std::filesystem::is_empty(filePath);
}