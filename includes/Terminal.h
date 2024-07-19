#include <string>

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

#define ASSERT(x, y) if(!(x)) {fmt::print(y); throw;}
