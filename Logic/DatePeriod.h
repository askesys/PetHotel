//
// Created by Nikita Bekeruk on 01/12/2025.
//

#ifndef DATEPERIOD_H
#define DATEPERIOD_H

#include "Date.h"
#include <vector>



class DatePeriod {
private:
    Date start;
    Date end;

public:
    DatePeriod(){};
    DatePeriod(Date start, Date end);

    const Date& getStart() const;
    const Date& getEnd() const;

    bool contains(const Date& d) const;
    int length() const;  // number of days in interval
    std::vector<Date> toVector() const;

    bool overlaps(const DatePeriod& other) const;


};



#endif //DATEPERIOD_H
