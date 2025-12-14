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
    static const int BOOKING_PERIOD{90};
    static const int MIN_DAYS_ALLOWED{2};
    static const int MAX_DAYS_ALLOWED{14};
    static Date beginDate;

    map<int, int> mapKennelID;
    vector<BookingEntry*> bookingEntries;
    vector<vector<int>> free_spaces;
    BookingFH bookingFH;

public:
    Booking();
    ~Booking();

    static bool isValidStartDate(const Date &date);
    static bool isValidPeriod(const DatePeriod &datePeriod);

    void GenerateBookingCalendar(const vector<Kennel *> &kennels, map<int, Animal*> animalMap);
    map<int,vector<Animal*>> GetCurrentAnimals(map<int, Animal*> animalMap);
    void AddBooking(int reseravationID, int animalID, int kennelID, DatePeriod datePeriod, int requiredSpace);
    void FindPossibleBookings(const vector<Kennel *> &kennels, DatePeriod datePeriod, int requiredSpace,
    vector<BookingData>& bookingData);
    bool isBookingExists(const vector<Kennel *> &kennels, DatePeriod datePeriod, int requiredSpace);
    bool isAnyBooked(int kennelID);

    vector<BookingEntry*> GetBookings() const;
    vector<BookingEntry*> GetBookings(int kennelID) const;
    vector<BookingEntry*> GetBookings(int reservationID, int animalID);

    void RemoveBooking(BookingEntry* bookingEntry, map<int, Animal *> animalMap);
};



#endif //BOOKING_H
