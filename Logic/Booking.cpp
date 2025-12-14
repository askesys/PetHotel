//
// Created by Nikita Bekeruk on 01/12/2025.
//

#include "Booking.h"
#include <chrono>
#include <complex>
#include "../Animals/Rodent.h"

#include "../Files/BookingFH.h"
#include "../Kennel.h"

Date Booking::beginDate;

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

void Booking::GenerateBookingCalendar(const vector<Kennel *> &kennels, map<int, Animal *> animalMap) {

    int id = 0;
    for (Kennel *kennel : kennels) {
        mapKennelID[kennel->GetID()] = id;

        int space = kennel->GetFullSpace();
        vector<int> spaces(BOOKING_PERIOD, space);
        free_spaces.push_back(spaces);

        id++;
    }

    for (BookingEntry *bookingEntry : bookingEntries) {
        int animalID = bookingEntry->GetAnimalID();
        int kennelID = bookingEntry->GetKennelID();
        Date startDate(bookingEntry->GetStartDate());
        Date endDate(bookingEntry->GetEndDate());
        if (beginDate < endDate) {
            if (startDate <= beginDate) {
                bookingEntry->SetStartDate(beginDate);
            }
            int space = animalMap[animalID]->GetSpace();
            int kid = mapKennelID[kennelID];
            DatePeriod dp(bookingEntry->GetStartDate(), bookingEntry->GetEndDate());
            for (Date date: dp.toVector()) {
                int date_s = date - beginDate;
                free_spaces[kid][date_s] -= space;
            }
        }
    }

}


map<int, vector<Animal *> > Booking::GetCurrentAnimals(map<int, Animal *> animalMap) {
    map<int,vector<Animal*>> currentKennelsAnimals;

    for (BookingEntry *bookingEntry : bookingEntries) {
        int animalID = bookingEntry->GetAnimalID();
        int kennelID = bookingEntry->GetKennelID();
        Date startDate(bookingEntry->GetStartDate());
        Date endDate(bookingEntry->GetEndDate());
        if (startDate <= beginDate && beginDate < endDate) {
            currentKennelsAnimals[kennelID].push_back(animalMap[animalID]);
        }
    }

    return currentKennelsAnimals;
}

map<int, string> Booking::GetCurrentKennelType(vector<Kennel *> kennels, map<int, Animal *> animalMap) {
    map<int, string> currentKennelTypes;

    for (Kennel* kennel : kennels) {
        int kennelID = kennel->GetID();
        for (BookingEntry* bookingEntry : bookingEntries) {
            if (kennelID == bookingEntry->GetKennelID()) {
                Animal* animal = animalMap[bookingEntry->GetAnimalID()];
                string kennelType = animal->GetType();

                if (kennelType == "Rodent") {
                    Rodent* rodent = dynamic_cast<Rodent*>(animal);
                    if (rodent)
                        kennelType = rodent->GetRodentType();
                }

                kennel->SetType(kennelType);
                currentKennelTypes[kennelID] = kennelType;
                break;
            }
        }

        if (!currentKennelTypes.contains(kennelID)) {
            kennel->SetType("NULL");
            currentKennelTypes[kennelID] = "NULL";
        }
    }


    return currentKennelTypes;
}



bool Booking::isValidStartDate(const Date &date) {
    return date >= beginDate;
}

bool Booking::isValidPeriod(const DatePeriod &datePeriod) {
    return datePeriod.length() >= MIN_DAYS_ALLOWED && datePeriod.length() <= MAX_DAYS_ALLOWED;
}




void Booking::AddBooking(int reseravationID, int animalID, int kennelID, DatePeriod datePeriod, int requiredSpace) {
    auto* be = new BookingEntry(reseravationID, animalID,kennelID,datePeriod.getStart(),datePeriod.getEnd());
    this->bookingEntries.push_back(be);

    int id = mapKennelID[kennelID];
    for (auto date: datePeriod.toVector()) {
        int date_s = date - beginDate;
        if (requiredSpace == -1) {
            free_spaces[id][date_s] = -1;
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

bool Booking::isAnyBooked(int kennelID) {
    int id = mapKennelID[kennelID];
    for (int i = 0; i < BOOKING_PERIOD; i++) {
        if (free_spaces[id][i] < 4) return true;
    }
    return false;
}


vector<BookingEntry *> Booking::GetBookings() const {
    return this->bookingEntries;
}

vector<BookingEntry *> Booking::GetBookings(int kennelID) const {
    vector<BookingEntry *> sliced;
    for (auto bookingEntry : this->bookingEntries) {
        if (bookingEntry->GetKennelID() == kennelID) sliced.push_back(bookingEntry);
    }
    return sliced;
}

vector<BookingEntry *> Booking::GetBookings(int reservationID, int animalID) {
    vector<BookingEntry *> sliced;
    for (auto bookingEntry : this->bookingEntries) {
        if (bookingEntry->GetReservationID() == reservationID && bookingEntry->GetAnimalID() == animalID) sliced.push_back(bookingEntry);
    }
    return sliced;
}


void Booking::RemoveBooking(BookingEntry *bookingEntry, map<int, Animal *> animalMap) {
    auto it = find(bookingEntries.begin(), bookingEntries.end(), bookingEntry);
    if (it != bookingEntries.end()) {
        int id = mapKennelID[bookingEntry->GetKennelID()];
        DatePeriod datePeriod(Date(bookingEntry->GetStartDate()), Date(bookingEntry->GetEndDate()));
        for (auto date: datePeriod.toVector()) {
            int date_s = date - beginDate;
            if (free_spaces[id][date_s] == -1) {
                free_spaces[id][date_s] = 4;
            }
            else {
                free_spaces[id][date_s] += animalMap[bookingEntry->GetAnimalID()]->GetSpace();
            }
        }


        bookingEntries.erase(it);
        delete bookingEntry;
    }
}


