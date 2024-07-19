#include <iostream>

#include "Scanner.h"
#include <fmt/color.h>
#include <fmt/ostream.h>
#include <filesystem>
#include <stdexcept>
#include <string_view>
#include <fstream>
#include "Terminal.h"
using namespace std::string_literals;
namespace fs = std::filesystem;

int main(int argc, char* argv[])
{
    ASSERT(argc >= 2, "You didnt specify any file\n");

    fs::path existingFilePath = argv[1];
    std::string filename = argv[1];

    ASSERT(std::filesystem::exists(filename), "The file you specified doesn't exist\n")
    ASSERT(existingFilePath == ".cst", "The file has wrong extension\n")

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
