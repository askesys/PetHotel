//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "IDManager.h"
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

map<string, int> IDManager::idMap = {
    {"Reservation", 0},
        {"Kennel", 0},
    {"Dog", 0},
    {"Cat", 0},
    {"Rodent", 0},
    {"Booking", 0}
};

int IDManager::NewID(const string& type){
    idMap[type]++;
    return idMap[type];
}

void IDManager::Read() {
    ifstream file{"Files/MetadataID.txt", ios::in};
    string title;

    if (!file) {
        cerr << "IDs metadata cannot be opened for reading" << endl;
        exit(EXIT_FAILURE);
    }

    file >> title >> idMap["Reservation"];
    file >> title >> idMap["Kennel"];
    file >> title >> idMap["Dog"];
    file >> title >> idMap["Cat"];
    file >> title >> idMap["Rodent"];
    file >> title >> idMap["Booking"];

    file.close();

}

void IDManager::Write() {
    ofstream file{"Files/MetadataID.txt", ios::out};

    if (!file) {
        cerr << "IDs metadata cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    file << "Reservation " << idMap["Reservation"] << endl;
    file << "Kennel " << idMap["Kennel"] << endl;
    file << "Dog " << idMap["Dog"] << endl;
    file << "Cat " << idMap["Cat"] << endl;
    file << "Rodent " << idMap["Rodent"] << endl;
    file << "Booking " << idMap["Booking"] << endl;

    file.close();
}