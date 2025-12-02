//
// Created by Nikita Bekeruk on 01/12/2025.
//

#ifndef BOOKING_H
#define BOOKING_H
#include <vector>
#include <map>

#include "BookingEntry.h"
#include "Date.h"
#include "DatePeriod.h"
#include "../Kennel.h"
#include "../Reservation.h"

using namespace std;

class Booking {
private:
    int BOOKING_PERIOD;
    map<int, int> mapKennelID;
    vector<BookingEntry> bookingEntries;
    vector<vector<int>> availableKennels;
    Date beginDate;

public:
    Booking() = default;
    Booking(vector<Kennel*> kennels, vector<Reservation*> reservations);
    void AddBooking(Animal* animal, Kennel* kennel, DatePeriod datePeriod);
    void BlockKennel(Kennel* kennel, DatePeriod datePeriod);
    vector<Kennel*> FindAvailableKennels(const std::vector<Kennel*> &kennels, DatePeriod datePeriod);
};



#endif //BOOKING_H
