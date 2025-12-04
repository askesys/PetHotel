//
// Created by Nikita Bekeruk on 25/11/2025.
//

#include "ReservationsFH.h"
#include "../Reservation.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

vector<Reservation*> ReservationsFH::Read(map<int,Animal*> *animalsMap) {
    vector<Reservation*> reservations;
    ifstream file{this->path, ios::in};
    string line, element;
    int delimeter, animalID;
    bool putTogether;

    string values[5];

    if (!file) {
        cerr << this->name << " cannot be opened for reading" << endl;
        exit(EXIT_FAILURE);
    }

    getline(file, line);
    while (getline(file, line)) {
        vector<Animal*> animals;
        int index = 0;
        while ((delimeter = line.find(",")) != string::npos) {
            values[index] = line.substr(0, delimeter);
            line = line.substr(delimeter + 1, line.length());
            index++;
        }
        values[index] = line;

        index = 0;
        line = values[3];
        if (line != "") {
            while ((delimeter = line.find(":")) != string::npos) {
                animalID = stoi(line.substr(0, delimeter));
                animals.push_back((*animalsMap)[animalID]);
                line = line.substr(delimeter + 1, line.length());
                index++;
            }
            animalID = stoi(line);
            animals.push_back((*animalsMap)[animalID]);
        }
        putTogether = values[4] == "1" ? true : false;

        Reservation* reservation = new Reservation(stoi(values[0]), values[1], values[2], animals, putTogether);
        reservations.push_back(reservation);
    }

    return reservations;
}

void ReservationsFH::Write(Reservation *reservation) {
    ofstream file{this->path, ios::app};

    if (!file) {
        cerr << this->path << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    file << reservation->GetID() << ",";
    file << reservation->GetStartDate() << ",";
    file << reservation->GetEndDate() << ",";
    vector<Animal*> animals = reservation->GetAnimals();
    int animalsSize = animals.size();
    for (int i = 0; i < animalsSize; i++) {
        file << animals[i]->GetID();
        if (i != animalsSize - 1) {
            file << ":";
        }
    }
    file << ",";
    file << reservation->GetPutTogether() << endl;

    file.close();
}

void ReservationsFH::WriteAll(vector<Reservation *> reservations) {
    ofstream file{this->path, ios::out};

    if (!file) {
        cerr << this->name << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    file << "ID" << ",";
    file << "StartDate" << ",";
    file << "EndDate" << ",";
    file << "Animals" << ",";
    file << "PutTogether" << endl;

    for (auto reservation : reservations) {
        file << reservation->GetID() << ",";
        file << reservation->GetStartDate() << ",";
        file << reservation->GetEndDate() << ",";
        vector<Animal*> animals = reservation->GetAnimals();
        int animalsSize = animals.size();
        for (int i = 0; i < animalsSize; i++) {
            file << animals[i]->GetID();
            if (i != animalsSize - 1) {
                file << ":";
            }
        }
        file << ",";
        file << reservation->GetPutTogether() << endl;
    }

    file.close();
}


void ReservationsFH::Delete(Reservation *reservation) {
    int reservationID{reservation->GetID()};
    ifstream rfile{this->path, ios::binary};

    if (!rfile) {
        cerr << this->name << " cannot be opened for reading" << endl;
        exit(EXIT_FAILURE);
    }

    string data((istreambuf_iterator<char>(rfile)),istreambuf_iterator<char>());

    rfile.close();

    istringstream iss(data);
    ofstream wfile{this->path, ios::app};
    string line;

    if (!wfile) {
        cerr << this->name << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    while (getline(iss, line)) {
        int id = stoi(line.substr(0, line.find(",")));
        if (id != reservationID) {
            wfile << line << endl;
        }
    }

    wfile.close();
}
