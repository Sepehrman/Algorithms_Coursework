//
// Created by Sepehr on 2024-01-18.
//

#include "../include/BookReservation.h"



/**
 * The following constructor initializes a book reservation record given its patronID & Book's ISBN
 * @param patronID a String representing patron ID
 * @param bookISBN a String representing a book's ISBN
 */
ReservationRecord::ReservationRecord(string &patronID, string &bookISBN) {
    this->bookISBN = bookISBN;
    this->patronID = patronID;
}

/**
 * The following constructor initializes a book reservation record given book & patron objects
 * @param patronID an Object representing a patron
 * @param bookISBN an Object representing a book
 */
ReservationRecord::ReservationRecord(const Patron &patron, const Book &book) {
    bookISBN = book.ISBN;
    patronID = patron.ID;
}


/**
 * The following constructor initializes the book reservation system and initializes all of the pending & fulfilled
 * reservations
 * @param maxPendingReservations
 */
BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations) {
    booksDB = vector<Book>();
    pendingReservations = CircularQueue<ReservationRecord>(maxPendingReservations);
    fulfilledReservations = Stack<ReservationRecord>();
//    booksDB.resize(maxPendingReservations);
}

/**
 * Indexes/pushes a book onto the books Database
 * @param book an Object representing a book
 */
void BookReservationManagementSystem::indexBookToDB(const Book &book) {
    booksDB.push_back(book);
}

/**
 * Enqueues and adds a reservation (object) to the pending reservations provided the patron & book objects
 * @param patronID an Object representing a patron
 * @param bookISBN an Object representing a book
 */
void BookReservationManagementSystem::enqueueReservation(const Patron &patron, const Book &book) {
    pendingReservations.enqueue(ReservationRecord(patron, book));
}


/**
 * Processes a reservation. This would mean that the front-most reservation would be picked, pushed to the fulfilled
 * reservations and once the reservation is complete, the current reservation is dequeued for the next reservation set
 * @return a Reservation object
 */
ReservationRecord BookReservationManagementSystem::processReservation() {
    if (pendingReservations.isEmpty()) {
        return ReservationRecord();
    }

    ReservationRecord res = pendingReservations.front();
    fulfilledReservations.push(res);
    pendingReservations.dequeue();


    return res;
}

void BookReservationManagementSystem::enqueueReservation(const ReservationRecord &reservation) {
    pendingReservations.enqueue(reservation);
}
