//
// Created by Nikita Bekeruk on 02/12/2025.
//

#ifndef BOOKINGFH_H
#define BOOKINGFH_H
#include "../Logic/BookingEntry.h"

#include <string>
#include <vector>

using namespace std;

class BookingFH {
private:
    string path{"Files/BookingDB.csv"};
    string name{"Booking DB"};

public:
    vector<BookingEntry*> Read();
    void Write(BookingEntry* bookingEntry);
    void WriteAll(vector<BookingEntry*> bookingEntries);

};



#endif //BOOKINGFH_H
