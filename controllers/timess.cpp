#include "timess.h"

timess::timess()
{

}
int timess::get_year(const std::tm& date)
{
return date.tm_year+1900;
}
int timess::getMonth(const std::tm& date) {
    return date.tm_mon + 1;
}

int timess::getDay(const std::tm& date) {
    return date.tm_mday;
}
int timess::get_hour(const std::tm& date)
{
    return date.tm_hour;
}
int timess::get_minute(const std::tm& date)
{
    return date.tm_min;
}
int timess::get_second(const std::tm& date)
{
    return date.tm_sec;
}
std::tm timess::getCurrentTime()
{
    std::time_t now= std::time(nullptr);
    return *std::localtime(&now);
}
std::string timess::timepassed()
{
    int seconds =time(0);
    return  std::to_string(seconds);
}
