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
        cerr << this->name << " cannot be opened for writing" << endl;
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
        if (i != animalsSize - 1) {
            file << ":";
        }
    }
    file << ",";
    file << kennel->GetIsEmpty() << endl;

    file.close();
}

void KennelsFH::WriteAll(vector<Kennel *> kennels) {
    ofstream file{this->path, ios::out};

    if (!file) {
        cerr << this->name << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    for (auto kennel : kennels) {
        file << kennel->GetID() << ",";
        file << kennel->GetSize() << ",";
        file << kennel->GetCapacity() << ",";
        file << kennel->GetType() << ",";
        vector<Animal*> animals = kennel->GetAnimals();
        int animalsSize = animals.size();
        for (int i = 0; i < animalsSize; i++) {
            file << animals[i]->GetID();
            if (i != animalsSize - 1) {
                file << ":";
            }
        }
        file << ",";
        file << kennel->GetIsEmpty() << endl;
    }

    file.close();
}


void KennelsFH::Delete(Kennel *kennel) {
    int kennelID{kennel->GetID()};
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
        if (id != kennelID) {
            wfile << line << endl;
        }
    }

    wfile.close();
}

void KennelsFH::Update(Kennel *kennel) {
    int kennelID{kennel->GetID()};
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
        if (id != kennelID) {
            wfile << line << endl;
        }else {
            wfile << kennel->GetID() << ",";
            wfile << kennel->GetSize() << ",";
            wfile << kennel->GetCapacity() << ",";
            wfile << kennel->GetType() << ",";
            vector<Animal*> animals = kennel->GetAnimals();
            int animalsSize = animals.size();
            for (int i = 0; i < animalsSize; i++) {
                wfile << animals[i]->GetID();
                if (i != animalsSize - 1) {
                    wfile << ":";
                }
            }
            wfile << ",";
            wfile << kennel->GetIsEmpty() << endl;
        }
    }

    wfile.close();
}

