cmake_minimum_required(VERSION 3.31)
project(PetHotel)

set(CMAKE_CXX_STANDARD 26)

add_executable(PetHotel main.cpp
        PetHotel.h
        Animal.cpp
        Animal.h
        Reservation.cpp
        Reservation.h
        Kennel.cpp
        Kennel.h
        PetHotel.cpp
        IDManager.cpp
        IDManager.h
        Dog.cpp
        Dog.h
)
