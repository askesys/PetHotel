//
// Created by Nikita Bekeruk on 06/11/2025.
//

#ifndef IDMANAGER_H
#define IDMANAGER_H
#include <string>

using namespace std;


class IDManager {
    static int kennelID;
    static int animalID;
    static int reservationID;

public:
    static int NewID(const string& type);
};


#endif //IDMANAGER_H
