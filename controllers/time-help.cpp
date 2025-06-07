#include <iostream>
#include <ctime>

// Function to get the current date and time
std::tm getCurrentTime() {
    std::time_t now = std::time(nullptr);
    return *std::localtime(&now);
}

// Function to check if a date is before the current date and time
bool isBeforeNow(const std::tm& date) {
    std::time_t now = std::time(nullptr);
    std::time_t inputTime = std::mktime(const_cast<std::tm*>(&date));
    return inputTime < now;
}

// Function to calculate a date that is a certain number of years into the future
std::tm calculateFutureDate(int years) {
    std::tm currentDate = getCurrentTime();
    currentDate.tm_year += years;
    std::mktime(&currentDate); // Normalize the date
    return currentDate;
}

// Function to calculate a date that is a certain number of years into the past
std::tm calculatePastDate(int years) {
    return calculateFutureDate(-years);
}

// Utility functions to extract components of a date
int getYear(const std::tm& date) {
    return date.tm_year + 1900; // tm_year represents years since 1900
}

int getMonth(const std::tm& date) {
    return date.tm_mon + 1; // tm_mon is 0-based, so add 1
}

int getDay(const std::tm& date) {
    return date.tm_mday;
}

int getHour(const std::tm& date) {
    return date.tm_hour;
}

int getMinute(const std::tm& date) {
    return date.tm_min;
}

int getSecond(const std::tm& date) {
    return date.tm_sec;
}

int main() {
    std::tm now = getCurrentTime();
    std::cout << "Current date and time: "
              << getYear(now) << "-" << getMonth(now) << "-" << getDay(now) << " "
              << getHour(now) << ":" << getMinute(now) << ":" << getSecond(now) << std::endl;

    std::tm futureDate = calculateFutureDate(5);
    std::cout << "Date 5 years from now: "
              << getYear(futureDate) << "-" << getMonth(futureDate) << "-" << getDay(futureDate) << std::endl;

    std::cout << "Is a date in the past? " << (isBeforeNow(futureDate) ? "Yes" : "No") << std::endl;

    return 0;
}
