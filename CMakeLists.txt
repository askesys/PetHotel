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
        Animals/Dog.cpp
        Animals/Dog.h
        Animals/Cat.cpp
        Animals/Cat.h
        Animals/Rodent.cpp
        Animals/Rodent.h
        Files/AnimalsFH.cpp
        Files/AnimalsFH.h
        Files/ReservationsFH.cpp
        Files/ReservationsFH.h
        Files/KennelsFH.cpp
        Files/KennelsFH.h
        Animals/AnimalFilter.cpp
        Animals/AnimalFilter.h
        Logic/Date.cpp
        Logic/Date.h
        Logic/DatePeriod.cpp
        Logic/DatePeriod.h
        Logic/Booking.cpp
        Logic/Booking.h
        Logic/BookingEntry.cpp
        Logic/BookingEntry.h
)
