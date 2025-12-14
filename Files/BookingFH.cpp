//
// Created by Nikita Bekeruk on 02/12/2025.
//

#include "BookingFH.h"
#include<fstream>
#include<cstdlib>
#include <iostream>
#include<vector>

using namespace std;

vector<BookingEntry *> BookingFH::Read() {
    vector<BookingEntry *> bookingEntries;

    ifstream file{this->path, ios::in};
    string line, element;
    int delimeter;

    string values[6];

    if (!file) {
        cerr << this->path << " cannot be opened for reading" << endl;
        exit(EXIT_FAILURE);
    }

    getline(file, line);
    while (getline(file, line)) {
        int index = 0;
        while ((delimeter = line.find(",")) != string::npos) {
            values[index] = line.substr(0, delimeter);
            line = line.substr(delimeter + 1, line.length());
            index++;
        }
        values[index] = line;

        BookingEntry* be = new BookingEntry(stoi(values[0]),stoi(values[1]), stoi(values[2]), stoi(values[3]),Date(values[4]), Date(values[5]));
        bookingEntries.push_back(be);
    }

    file.close();

    return bookingEntries;
}

void BookingFH::Write(BookingEntry* bookingEntry) {
    ofstream file{this->path, ios::app};

    if (!file) {
        cerr << this->path << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    file << bookingEntry->GetID() << ",";
    file << bookingEntry->GetReservationID() << ",";
    file << bookingEntry->GetAnimalID() << ",";
    file << bookingEntry->GetKennelID() << ",";
    file << bookingEntry->GetStartDate() << ",";
    file << bookingEntry->GetEndDate() << endl;

    file.close();
}

void BookingFH::WriteAll(vector<BookingEntry *> bookingEntries) {
    ofstream file{this->path, ios::out};

    if (!file) {
        cerr << this->name << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    file << "ID" << ",";
    file << "ReservationID" << ",";
    file << "AnimalID" << ",";
    file << "KennelID" << ",";
    file << "StartDate" << ",";
    file << "EndDate" << endl;

    for (auto bookingEntry : bookingEntries) {
        file << bookingEntry->GetID() << ",";
        file << bookingEntry->GetReservationID() << ",";
        file << bookingEntry->GetAnimalID() << ",";
        file << bookingEntry->GetKennelID() << ",";
        file << bookingEntry->GetStartDate() << ",";
        file << bookingEntry->GetEndDate() << endl;
    }

    file.close();
}

