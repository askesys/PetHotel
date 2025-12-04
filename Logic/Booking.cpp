//
// Created by Nikita Bekeruk on 01/12/2025.
//

#include "Booking.h"
#include <chrono>
#include <complex>

#include "../Files/BookingFH.h"
#include "../Kennel.h"

Booking::Booking() {
    auto today = floor<chrono::days>(chrono::system_clock::now());
    chrono::year_month_day ymd{today};

    int year  = int(ymd.year());
    unsigned month = unsigned(ymd.month());
    unsigned day   = unsigned(ymd.day());

    beginDate = Date(day, month, year);

    this->bookingEntries = bookingFH.Read();
}

Booking::~Booking() {
    bookingFH.WriteAll(bookingEntries);
    for (auto bookingEntry : bookingEntries) {
        delete bookingEntry;
    }
}

void Booking::GenerateBookingCalendar(vector<Kennel *> kennels, map<int, Animal *> animalMap) {
    int id = 0;
    for (Kennel *kennel : kennels) {
        mapKennelID[kennel->GetID()] = id;

        int space = kennel->GetFullSpace();
        vector<int> spaces(BOOKING_PERIOD, space);
        free_spaces.push_back(spaces);

        id++;
    }

    for (BookingEntry *bookingEntry : bookingEntries) {
        Date endDate(bookingEntry->GetEndDate());
        if (beginDate < endDate) {
            Date startDate(bookingEntry->GetStartDate());
            if (startDate < beginDate) bookingEntry->SetStartDate(beginDate);
            int animalID = bookingEntry->GetAnimalID();
            int space = animalMap[animalID]->GetSpace();
            int kennelID = bookingEntry->GetKennelID();
            int kid = mapKennelID[kennelID];
            DatePeriod dp(bookingEntry->GetStartDate(), bookingEntry->GetEndDate());
            for (Date date: dp.toVector()) {
                int date_s = date - beginDate;
                free_spaces[kid][date_s] -= space;
            }
        }
    }
}



void Booking::AddBooking(int animalID, int kennelID, DatePeriod datePeriod, int requiredSpace) {
    BookingEntry* be = new BookingEntry(animalID,kennelID,datePeriod.getStart(),datePeriod.getEnd());
    bookingEntries.push_back(be);

    int id = mapKennelID[kennelID];
    for (auto date: datePeriod.toVector()) {
        int date_s = date - beginDate;
        if (requiredSpace == -1) {
            free_spaces[id][date_s] == -1;
        }
        else {
            free_spaces[id][date_s] -= requiredSpace;
        }
    }
}

void Booking::FindPossibleBookings(const vector<Kennel *> &kennels, DatePeriod datePeriod, int requiredSpace,
    vector<BookingData>& bookingData) {

    if (!isBookingExists(kennels, datePeriod, requiredSpace)) return;

    int prefixLength = 0;
    int suitable_kennel = -1;
    for (Kennel *kennel : kennels) {
        int current_prefix = 0;
        int kennel_id = mapKennelID[kennel->GetID()];
        for (Date date: datePeriod.toVector()) {
            int date_s = date - beginDate;

            if (requiredSpace <= free_spaces[kennel_id][date_s]) {
                current_prefix++;
            }
            else break;

            if (current_prefix > prefixLength ) {
                prefixLength = current_prefix;
                suitable_kennel = kennel->GetID();
            }
        }
    }

    if (suitable_kennel != -1) {
        if (prefixLength == datePeriod.length()) {
            bookingData.push_back(BookingData(suitable_kennel, datePeriod.getStart(), datePeriod.getEnd()));
        }
        else {
            bookingData.push_back(BookingData(suitable_kennel, datePeriod.getStart(),datePeriod.getStart()+prefixLength));
            DatePeriod dp(datePeriod.getStart()+prefixLength, datePeriod.getEnd());
            FindPossibleBookings(kennels, dp, requiredSpace, bookingData);
        }
    }
}

bool Booking::isBookingExists(const vector<Kennel *> &kennels, DatePeriod datePeriod, int requiredSpace) {
    int begin_mask = 0;
    int end_mask = pow(2, datePeriod.length()) - 1;

    for (Kennel *kennel : kennels) {
        int current_mask = 0;
        int kennel_id = mapKennelID[kennel->GetID()];
        for (Date date: datePeriod.toVector()) {
            int date_s = date - beginDate;

            int value = requiredSpace <= free_spaces[kennel_id][date_s] ? 1 : 0;
            current_mask = (current_mask << 1) | value;
        }

        begin_mask |= current_mask;

        if (begin_mask == end_mask) return true;
    }

    return false;
}



