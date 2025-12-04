//
// Created by Nikita Bekeruk on 06/11/2025.
//

#include "Animal.h"

#include "PetHotel.h"

Animal::Animal(const string &name, const string &birthDate, const string &breed):
    name(name), birthDate(birthDate), breed(breed) {}


Animal::~Animal() {}


string Animal::GetName() const {
    return this->name;
}

void Animal::SetName(const string& name) {
    this->name = name;
}

string Animal::GetBirthDate() const {
    return this->birthDate;
}

void Animal::SetBirthDate(const string& date) {
    this->birthDate = date;
}

string Animal::GetBreed() const {
    return this->breed;
}

void Animal::SetBreed(const string& breed) {
    this->breed = breed;
}

int Animal::GetID() const {
    return this->ID;
}

void Animal::SetID(int ID) {
    this->ID = ID;
}

string Animal::GetCareSchedule() const {
    return this->careSchedule;
}


void Animal::SetCareSchedule(const string& careSchedule) {
    this->careSchedule = careSchedule;
}


string Animal::CarvinoresWeightToSize(int weight) {
    if (weight < 0) {
        invalid_argument("passed weight is negative");
        return "";
    }

    if (weight >= 25) return "Large";
    if (weight >= 10 && weight < 25) return "Medium";
    if (weight < 10) return "Small";

    return "Invalid string";
}

string Animal::RecommendCareSchedule(const string &type, int weight) {
    if (type == "Dog") {
        return "Should be walked several times a day";
    }
    else if (type == "Cat") {
        if (weight >= 15) {
            return "Should be fed 4 times per day";
        }
        else if (weight > 0 && weight < 15) {
            return "Should be fed 3 times per day";
        }
        else {
            throw invalid_argument("RecommendCareSchedule: passed wrong weight");
        }
    }
    else {
        throw invalid_argument("RecommendCareSchedule: passed wrong type");
    }
}

string Animal::RecommendCareSchedule(const string &type, const string &rodentType) {
    if (type == "Rodent") {
        if (rodentType == "Rabbit") {
            return "Should be cleaned each 2 days";
        }
        else if (rodentType == "GuineaPig") {
            return "Should be cleaned each 3 days";
        }
        else if (rodentType == "Mouse") {
            return "Should be cleaned each 4 days";
        }
        else {
            throw invalid_argument("RecommendCareSchedule: passed wrong rodentType");
        }
    }
    else {
        throw invalid_argument("RecommendCareSchedule: passed wrong type");
    }
}

int Animal::AnimalSizeToSpace(const string &size) {
    if (size == "Large") {
        return 4;
    }
    else if (size == "Medium") {
        return 2;
    }
    else if (size == "Small") {
        return 1;
    }
    else if (size == "Mini" || size == "NULL") {
        return 0;
    }
    else {
        throw runtime_error("Kennel::AnimalSizeToSpace(): Unknown size");
    }
}

int Animal::WeightToSpace(int weight) {
    string size = Animal::CarvinoresWeightToSize(weight);
    return AnimalSizeToSpace(size);
}



