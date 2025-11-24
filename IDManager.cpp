//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "IDManager.h"


int IDManager::kennelID = 0;
int IDManager::animalID = 0;
int IDManager::reservationID = 0;

int IDManager::NewID(const string& type){
    if (type == "Kennel") {
        kennelID++;
        return kennelID;
    }
    if (type == "Animal") {
        animalID++;
        return animalID;
    }
    if (type == "Reservation") {
        reservationID++;
        return reservationID;
    }
    return -1;
}