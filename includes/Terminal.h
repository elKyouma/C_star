#include <string>
#include <fmt/core.h>
#include <fmt/color.h>
#include <fmt/ostream.h>

using namespace std::string_literals;

enum LogLevel
{
INFO,
WARNING,
ERROR
};

class Terminal
{
public:
    static void Print(const std::string& filename, const unsigned int line, const std::string& mess, const LogLevel level);
private:
    //colors
};

#define THROW(x) {fmt::print(x); throw;}
#define ASSERT(x, y) if(!(x)) THROW(y)
