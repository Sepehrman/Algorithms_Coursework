//
// Created by Sepehr on 2024-01-18.
//

#include "../include/BookReservation.h"

ReservationRecord::ReservationRecord(string &patronID, string &bookISBN) {

}

ReservationRecord::ReservationRecord(const Patron &patron, const Book &book) {

}


//CircularQueue<ReservationRecord> pendingReservations;
//Stack<ReservationRecord> fulfilledReservations;
//std::vector<Book> booksDB;

// Book Reservations System
BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations) {
    booksDB.resize(maxPendingReservations);
}

void BookReservationManagementSystem::indexBookToDB(const Book &book) {

}

void BookReservationManagementSystem::enqueueReservation(const Patron &patron, const Book &book) {


}

ReservationRecord BookReservationManagementSystem::processReservation() {
    return ReservationRecord();
}

void BookReservationManagementSystem::enqueueReservation(const ReservationRecord &reservation) {

}
