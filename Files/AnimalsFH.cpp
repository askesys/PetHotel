//
// Created by Nikita Bekeruk on 25/11/2025.
//

#include "AnimalsFH.h"
#include<fstream>
#include<cstdlib>
#include <iostream>
#include "../Animals/Dog.h"
#include "../Animals/Cat.h"
#include "../Animals/Rodent.h"

vector<Animal *> AnimalsFH::Read() {
    vector<Animal *> animals;
    ifstream file{this->path, ios::in};
    string line, element;
    int delimeter;

    string values[8];

    if (!file) {
        cerr << this->path << " cannot be opened for reading" << endl;
        exit(EXIT_FAILURE);
    }

    file >> line;

    while (getline(file, line)) {
        int index = 0;
       while ((delimeter = line.find(",")) != string::npos) {
           values[index] = line.substr(0, delimeter);
           line = line.substr(delimeter + 1, line.length());
           index++;
       }
        values[index] = line;

        if (values[1] == "Dog") {
            Dog* dog = new Dog(stoi(values[0]), values[2], values[3], values[4], values[5], stoi(values[6]));
            animals.push_back(dog);
        }
        else if (values[1] == "Cat") {
            Cat* cat = new Cat(stoi(values[0]), values[2], values[3], values[4], values[5], stoi(values[6]));
            animals.push_back(cat);
        }
        else if (values[1] == "Rodent") {
            Rodent* rodent = new Rodent(stoi(values[0]), values[2], values[3], values[4], values[5], values[7]);
            animals.push_back(rodent);
        }
    }

    file.close();

    return animals;
}

void AnimalsFH::Write(Animal* animal) {
    ofstream file{this->path, ios::app};

    if (!file) {
        cerr << this->path << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    string animal_type = animal->GetType();

    file << animal->GetID() << ",";
    file << animal_type << ",";
    file << animal->GetName() << ",";
    file << animal->GetBirthDate() << ",";
    file << animal->GetBreed() << ",";
    file << animal->GetCareSchedule() << ",";

    if (animal_type == "Dog") {
        file << static_cast<Dog*>(animal)->GetWeight() << ",";
        file << "NULL" << endl;
    }
    else if (animal_type == "Cat") {
        file << static_cast<Cat*>(animal)->GetWeight() << ",";
        file << "NULL" << endl;
    }
    else if (animal_type == "Rodent") {
        file << "NULL" << ",";
        file << static_cast<Rodent*>(animal)->GetRodentType() << endl;
    }

    file.close();

}

void AnimalsFH::WriteAll(vector<Animal *> animals) {
    ofstream file{this->path, ios::out};

    if (!file) {
        cerr << this->name << " cannot be opened for writing" << endl;
        exit(EXIT_FAILURE);
    }

    for (auto animal : animals) {
        string animal_type = animal->GetType();

        file << animal->GetID() << ",";
        file << animal_type << ",";
        file << animal->GetName() << ",";
        file << animal->GetBirthDate() << ",";
        file << animal->GetBreed() << ",";
        file << animal->GetCareSchedule() << ",";

        if (animal_type == "Dog") {
            file << static_cast<Dog*>(animal)->GetWeight() << ",";
            file << "NULL" << endl;
        }
        else if (animal_type == "Cat") {
            file << static_cast<Cat*>(animal)->GetWeight() << ",";
            file << "NULL" << endl;
        }
        else if (animal_type == "Rodent") {
            file << "NULL" << ",";
            file << static_cast<Rodent*>(animal)->GetRodentType() << endl;
        }
    }

    file.close();
}


