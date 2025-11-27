//
// Created by Nikita Bekeruk on 06/11/2025.
//

#ifndef IDMANAGER_H
#define IDMANAGER_H
#include <map>
#include <string>

using namespace std;


class IDManager {
    static int kennelID;
    static int animalID;
    static int reservationID;
    static int dogID;
    static int catID;
    static int rodentID;

    static map<string, int> idMap;

public:
    static int NewID(const string& type);
    static void Read();
    static void Write();
};


#endif //IDMANAGER_H
