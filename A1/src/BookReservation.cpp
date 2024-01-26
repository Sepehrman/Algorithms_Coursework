//
// Created by Sepehr on 2024-01-18.
//

#include "../include/BookReservation.h"

ReservationRecord::ReservationRecord(string &patronID, string &bookISBN) {
    this->bookISBN = bookISBN;
    this->patronID = patronID;
}

ReservationRecord::ReservationRecord(const Patron &patron, const Book &book) {
    bookISBN = book.ISBN;
    patronID = patron.ID;
}


// Book Reservations System
BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations) {
    booksDB = vector<Book>();
    pendingReservations = CircularQueue<ReservationRecord>(maxPendingReservations);
    fulfilledReservations = Stack<ReservationRecord>();
    booksDB.resize(maxPendingReservations);
}

void BookReservationManagementSystem::indexBookToDB(const Book &book) {
    booksDB.push_back(book);
}

void BookReservationManagementSystem::enqueueReservation(const Patron &patron, const Book &book) {
    pendingReservations.enqueue(ReservationRecord(patron, book));
}

ReservationRecord BookReservationManagementSystem::processReservation() {
    if (pendingReservations.isEmpty()) {
        return ReservationRecord();
    }

    ReservationRecord res = pendingReservations.front();
    pendingReservations.dequeue();
    fulfilledReservations.push(res);


    return res;
}

void BookReservationManagementSystem::enqueueReservation(const ReservationRecord &reservation) {
    pendingReservations.enqueue(reservation);
}
