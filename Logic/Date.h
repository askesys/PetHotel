//
// Created by Nikita Bekeruk on 01/12/2025.
//

#ifndef DATE_H
#define DATE_H

#include <string>

class Date {
private:
    int day;
    int month;
    int year;

    bool isValidDate(int d, int m, int y) const;
    bool isLeap(int y) const;
    int daysInMonth(int m, int y) const;
    int toDays() const;            // convert date to absolute day count
    static Date fromDays(int days); // convert absolute day count to Date

public:
    Date();
    Date(int d, int m, int y);
    Date(const std::string& str);

    // Getters
    int getDay() const;
    int getMonth() const;
    int getYear() const;

    // Operators
    Date operator+(int days) const;
    Date operator-(int days) const;
    int operator-(const Date& other) const; // difference in days

    bool operator==(const Date& other) const;
    bool operator!=(const Date& other) const;
    bool operator<(const Date& other) const;
    bool operator<=(const Date& other) const;
    bool operator>(const Date& other) const;
    bool operator>=(const Date& other) const;
};



#endif //DATE_H
