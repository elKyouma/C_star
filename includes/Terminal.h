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

#define LOG(x) Terminal::Print(__FILE__, __LINE__, x, LogLevel::INFO)
#define WRN(x) Terminal::Print(__FILE__, __LINE__, x, LogLevel::WARNING)
#define ERR(x) Terminal::Print(__FILE__, __LINE__, x, LogLevel::ERROR)
