//
// Created by Nikita Bekeruk on 27/11/2025.
//

#include "AnimalFilter.h"

#include <ranges>

AnimalFilter::AnimalFilter(map<AnimalKey, string> keyMap):keyMap(keyMap){}

void AnimalFilter::Filter(vector<Animal *>& animals) {
    std::vector<Animal*> result;

    for (Animal* animal : animals) {
        bool keep = true;
        for (const auto& [key, value] : this->keyMap) {
            if (key == AnimalKey::ID && animal->GetID() != std::stoi(value))
                keep = false;
            else if (key == AnimalKey::Name && animal->GetName() != value)
                keep = false;
            else if (key == AnimalKey::Type && animal->GetType() != value)
                keep = false;
            else if (key == AnimalKey::BirthDate && animal->GetBirthDate() != value)
                keep = false;
            else if (key == AnimalKey::Breed && animal->GetBreed() != value)
                keep = false;
            else if (key == AnimalKey::CareSchedule && animal->GetCareSchedule() != value)
                keep = false;
        }
        if (keep)
            result.push_back(animal);
    }

    animals = result;
}


