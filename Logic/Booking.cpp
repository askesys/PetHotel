//
// Created by Nikita Bekeruk on 01/12/2025.
//

#include "Booking.h"
#include <chrono>

Booking::Booking(vector<Kennel *> kennels, vector<Reservation *> reservations) {
    auto today = floor<chrono::days>(chrono::system_clock::now());
    chrono::year_month_day ymd{today};

    int year  = int(ymd.year());
    unsigned month = unsigned(ymd.month());
    unsigned day   = unsigned(ymd.day());

    beginDate = Date(day, month, year);

    const int KENNELS_COUNT = kennels.size();
    const int BOOKING_PERIOD = 90;
    int countDays = 0;

    int id = 0;
    for (Kennel *kennel : kennels) {
        mapKennelID[kennel->GetID()] = id;
    }

    vector<int> bookDays;
    for (int i = 0; i < BOOKING_PERIOD; i++) {
        bookDays.push_back(BOOKING_PERIOD - i);
    }

    for (int j = 0; j < KENNELS_COUNT; j++) {
        availableKennels.push_back(bookDays);
    }
}

void Booking::AddBooking(Animal* animal, Kennel *kennel, DatePeriod datePeriod) {
    BookingEntry be(animal->GetID(),kennel->GetID(),datePeriod.getStart(),datePeriod.getEnd());
    bookingEntries.push_back(be);
}

void Booking::BlockKennel(Kennel *kennel, DatePeriod datePeriod) {
    int id = mapKennelID[kennel->GetID()];
    for (Date date: datePeriod.toVector()) {
        availableKennels[id][date - beginDate] = 0;
    }
    int target{-1}, left_step{1};
    while (target != 0){
        Date previous = datePeriod.getStart() - left_step;
        if (previous < beginDate) break;
        int shift = previous - beginDate;
        target = availableKennels[id][shift];
        if (target != 0) {
            availableKennels[id][shift] = left_step;
            left_step++;
        }
    }
}

vector<Kennel *> Booking::FindAvailableKennels(const std::vector<Kennel*> &kennels, DatePeriod datePeriod) {
    vector<Kennel *> filteredKennels;

    for (auto kennel: kennels) {
        if (availableKennels[kennel->GetID()][datePeriod.getStart() - beginDate] == datePeriod.length()) {
            filteredKennels.push_back(kennel);
        }
    }

    return filteredKennels;
}



