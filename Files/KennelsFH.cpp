//
// Created by Nikita Bekeruk on 25/11/2025.
//

#include "KennelsFH.h"
#include "../Kennel.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>

using namespace std;

vector<Kennel *> KennelsFH::Read(map<int, Animal *> *animalsMap) {
    vector<Kennel*> kennels;
    ifstream file{this->path, ios::in};
    string line, element;
    int delimeter, animalID;
    bool isEmpty;

    string values[3];

    if (!file) {
        cerr << this->name << " cannot be opened for reading" << endl;
        exit(EXIT_FAILURE);
    }

    getline(file, line);
    while (getline(file, line)) {
        //vector<Animal*> animals;
        int index = 0;
        while ((delimeter = line.find(",")) != string::npos) {
            values[index] = line.substr(0, delimeter);
            line = line.substr(delimeter + 1, line.length());
            index++;
        }
        values[index] = line;


        Kennel* kennel = new Kennel(stoi(values[0]), values[1], stoi(values[2]));
        kennels.push_back(kennel);
    }

    return kennels;
}

void KennelsFH::Write(Kennel *kennel) {
    ofstream file{this->path, ios::app};

    if (!file) {
        cerr << this->name << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    file << kennel->GetID() << ",";
    file << kennel->GetSize() << ",";
    file << kennel->GetCapacity() << endl;

    file.close();
}

void KennelsFH::WriteAll(vector<Kennel *> kennels) {
    ofstream file{this->path, ios::out};

    if (!file) {
        cerr << this->name << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    file << "ID" << ",";
    file << "Size" << ",";
    file << "Capacity" << endl;

    for (auto kennel : kennels) {
        file << kennel->GetID() << ",";
        file << kennel->GetSize() << ",";
        file << kennel->GetCapacity() << endl;
    }

    file.close();
}