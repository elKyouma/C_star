#include <iostream>

#include "Scanner.h"
#include <fmt/color.h>
#include <fmt/ostream.h>
#include <filesystem>
#include <string_view>
#include <fstream>

using namespace std::string_literals;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    if(argc < 2)
    {
        fmt::print("You didnt specify any file");
        return 1;
    }
    fs::path existingFilePath = argv[1];
    std::string filename = argv[1];
    if(!std::filesystem::exists(filename))
    {
        fmt::print("The file you specified doesn't exist");
        return 1;
    }

    std::string intermediateFileName = std::string(existingFilePath.relative_path()) + std::string(existingFilePath.stem()) + ".cstt";

    std::ofstream ofs(intermediateFileName);
    auto tokens =  ScanFile(filename);
    for(const auto& token : tokens)
        if(token.type == SEMI)
            fmt::print( ofs, "\n");
        else
            fmt::print( ofs,"{} ",tokenTypeToString[token.type]);
    ofs.close();
    return 0;
}
