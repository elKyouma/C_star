#include "Terminal.h"

void Terminal::Print(const std::string& filename, const unsigned int line, const std::string& mess, const LogLevel level)
{
    fmt::print("[{}] Line: {} \t {}\n", filename, line, mess);
}
