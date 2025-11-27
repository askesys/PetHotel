//
// Created by Nikita Bekeruk on 25/11/2025.
//

#include "KennelsFH.h"
#include "../Kennel.h"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <iostream>
#include <sstream>

using namespace std;

vector<Kennel *> KennelsFH::Read(map<int, Animal *> *animalsMap) {
    vector<Kennel*> kennels;
    ifstream file{this->path, ios::in};
    string line, element;
    int delimeter, animalID;
    bool isEmpty;

    string values[6];

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
        line = values[4];
        while ((delimeter = line.find(":")) != string::npos) {
            animalID = stoi(line.substr(0, delimeter));
            animals.push_back((*animalsMap)[animalID]);
            line = line.substr(delimeter + 1, line.length());
            index++;
        }
        animalID = stoi(line);
        animals.push_back((*animalsMap)[animalID]);

        isEmpty = values[4] == "1" ? true : false;

        Kennel* kennel = new Kennel(stoi(values[0]), values[1], stoi(values[2]), values[3], isEmpty, animals);
        kennels.push_back(kennel);
    }

    return kennels;
}

void KennelsFH::Write(Kennel *kennel) {
    ofstream file{this->path, ios::app};

    if (!file) {
        cerr << this->path << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    file << kennel->GetID() << ",";
    file << kennel->GetSize() << ",";
    file << kennel->GetCapacity() << ",";
    file << kennel->GetType() << ",";
    vector<Animal*> animals = kennel->GetAnimals();
    int animalsSize = animals.size();
    for (int i = 0; i < animalsSize; i++) {
        file << animals[i]->GetID();
        if (i == animalsSize - 1) {
            file << ",";
        }
        else {
            file << ":";
        }
    }
    file << kennel->GetIsEmpty() << endl;

    file.close();
}
