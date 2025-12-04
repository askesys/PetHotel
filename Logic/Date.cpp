//
// Created by Nikita Bekeruk on 01/12/2025.
//

#include "Date.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

Date::Date() : day(1), month(1), year(1970) {}

Date::Date(int d, int m, int y) : day(d), month(m), year(y) {
    if (m < 1 || m > 12)
        throw std::invalid_argument("Invalid month");

    if (d < 1 || d > daysInMonth(m, y))
        throw std::invalid_argument("Invalid day");
}

Date::Date(const std::string& str) {
    int d, m, y;
    char sep1, sep2;

    std::stringstream ss(str);
    ss >> d >> sep1 >> m >> sep2 >> y;

    if (ss.fail() || sep1 != '/' || sep2 != '/' || !isValidDate(d, m, y)) {
        std::cerr << "Invalid date string! Setting to default 01/01/1900.\n";
        day = 1;
        month = 1;
        year = 1900;
        return;
    }

    day = d;
    month = m;
    year = y;
}


bool Date::isLeap(int y) const {
    return (y % 400 == 0) || (y % 4 == 0 && y % 100 != 0);
}

int Date::daysInMonth(int m, int y) const {
    static const int days[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if (m == 2 && isLeap(y)) return 29;
    return days[m - 1];
}

bool Date::isValidDate(int d, int m, int y) const {
    if (y < 0 || m < 1 || m > 12 || d < 1) return false;
    return d <= daysInMonth(m, y);
}

// Convert date to number of days since 01/01/0001
int Date::toDays() const {
    int days = 0;

    for (int y = 1; y < year; ++y)
        days += 365 + isLeap(y);

    for (int m = 1; m < month; ++m)
        days += daysInMonth(m, year);

    days += day;

    return days;
}

Date Date::fromDays(int totalDays) {
    int y = 1;
    while (true) {
        int yearDays = 365 + ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0));
        if (totalDays > yearDays) {
            totalDays -= yearDays;
            y++;
        } else break;
    }

    int m = 1;
    while (true) {
        static const int baseDays[12] =
            { 31,28,31,30,31,30,31,31,30,31,30,31 };

        int dim = baseDays[m - 1];
        if (m == 2 && ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)))
            dim = 29;

        if (totalDays > dim) {
            totalDays -= dim;
            m++;
        } else break;
    }

    return Date(totalDays, m, y);
}

int Date::getDay() const { return day; }
int Date::getMonth() const { return month; }
int Date::getYear() const { return year; }

std::string Date::toString() const {
    std::ostringstream oss;
    oss << std::setw(2) << std::setfill('0') << day << "/"
        << std::setw(2) << std::setfill('0') << month << "/"
        << year;
    return oss.str();
}



// date + N days
Date Date::operator+(int days) const {
    return fromDays(toDays() + days);
}

// date - N days
Date Date::operator-(int days) const {
    return fromDays(toDays() - days);
}

// difference in days
int Date::operator-(const Date& other) const {
    return this->toDays() - other.toDays();
}

// comparisons
bool Date::operator==(const Date& other) const {
    return day == other.day && month == other.month && year == other.year;
}

bool Date::operator!=(const Date& other) const { return !(*this == other); }
bool Date::operator<(const Date& other) const { return toDays() < other.toDays(); }
bool Date::operator<=(const Date& other) const { return toDays() <= other.toDays(); }
bool Date::operator>(const Date& other) const { return toDays() > other.toDays(); }
bool Date::operator>=(const Date& other) const { return toDays() >= other.toDays(); }