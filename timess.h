#ifndef TIMESS_H
#define TIMESS_H
#include <ctime>
#include<iostream>
class timess
{
public:
    timess();
    static int get_year(const std::tm& date);
    static int get_hour(const std::tm& date);
    static int get_minute(const std::tm& date);
    static int get_second(const std::tm& date);
    static int getMonth(const std::tm& date);
    static int getDay(const std::tm& date);
    static std::tm getCurrentTime();
    static std::string timepassed();
};

#endif // TIMESS_H
