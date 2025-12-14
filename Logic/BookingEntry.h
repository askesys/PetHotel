//
// Created by Nikita Bekeruk on 01/12/2025.
//

#ifndef BOOKINGENTRY_H
#define BOOKINGENTRY_H
#include "Date.h"
#include <string>

using namespace std;


class BookingEntry {
private:
    int ID;
    int ReservationID;
    int AnimalID;
    int KennelID;
    Date StartDate;
    Date EndDate;

public:
    BookingEntry(int ID, int ReservationID, int AnimalID, int KennelID, Date StartDate, Date EndDate);
    BookingEntry(int ReservationID, int AnimalID, int KennelID, Date StartDate, Date EndDate);
    void SetID(int id);
    int GetID() const;
    int GetReservationID() const;
    int GetAnimalID() const;
    int GetKennelID() const;
    string GetStartDate() const;
    void SetStartDate(Date startDate);
    string GetEndDate() const;
};



#endif //BOOKINGENTRY_H
