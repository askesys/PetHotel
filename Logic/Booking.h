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
#include "../Files/BookingFH.h"

using namespace std;

struct BookingData {
    int kennelID;
    Date startDate;
    Date endDate;
};

class Booking {
private:
    const int BOOKING_PERIOD{90};
    map<int, int> mapKennelID;
    vector<BookingEntry*> bookingEntries;
    vector<vector<int>> free_spaces;
    Date beginDate;
    BookingFH bookingFH;

public:
    Booking();
    ~Booking();

    void GenerateBookingCalendar(vector<Kennel *> kennels, map<int, Animal*> animalMap);
    void AddBooking(int animalID, int kennelID, DatePeriod datePeriod, int requiredSpace);
    void FindPossibleBookings(const vector<Kennel *> &kennels, DatePeriod datePeriod, int requiredSpace,
    vector<BookingData>& bookingData);
    bool isBookingExists(const vector<Kennel *> &kennels, DatePeriod datePeriod, int requiredSpace);
};



#endif //BOOKING_H
