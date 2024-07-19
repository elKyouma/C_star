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

//using namespace std::literals;
//#define LOG(x) Terminal::Print(__FILE__, __LINE__, "[Internal] "s + x, LogLevel::INFO)
//#define WRN(x) Terminal::Print(__FILE__, __LINE__, "[Internal] "s + x, LogLevel::WARNING)
//#define ERR(x) Terminal::Print(__FILE__, __LINE__, "[Internal] "s + x, LogLevel::ERROR)
