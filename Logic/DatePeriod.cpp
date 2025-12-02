//
// Created by Nikita Bekeruk on 01/12/2025.
//

#include "DatePeriod.h"
#include <stdexcept>
#include "Date.h"
#include <vector>

DatePeriod::DatePeriod(Date s, Date e) : start(s), end(e) {
    if (e < s)
        throw std::invalid_argument("End date must be >= start date");
}

const Date& DatePeriod::getStart() const { return start; }
const Date& DatePeriod::getEnd() const { return end; }

bool DatePeriod::contains(const Date& d) const {
    return (d >= start && d <= end);
}

int DatePeriod::length() const {
    return end - start + 1; // inclusive
}

std::vector<Date> DatePeriod::toVector() const {
    std::vector<Date> result;
    result.reserve(length());

    for (Date d = start; d <= end; d = d + 1)
        result.push_back(d);

    return result;
}

bool DatePeriod::overlaps(const DatePeriod& other) const {
    return !(other.end < start || other.start > end);
}