#include "../include/BookReservation.h"
#include "../include/LExceptions.h"

/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

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
 * @param maxPendingReservations Max number of pending reservations the Circular Queue can accept
 */
BookReservationManagementSystem::BookReservationManagementSystem(int maxPendingReservations) {
    booksDB = vector<Book>();
    pendingReservations = CircularQueue<ReservationRecord>(maxPendingReservations);
    fulfilledReservations = Stack<ReservationRecord>();
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


ReservationRecord BookReservationManagementSystem::processReservation() {

    for (int i = 0; i < pendingReservations.size(); i++)
    {
        ReservationRecord frontInLine = pendingReservations.front();
        pendingReservations.dequeue();
        for (int j = 0; j < booksDB.size(); j++)
        {
            if (booksDB[j].copies > 0 && booksDB[j].ISBN == frontInLine.bookISBN)
            {
                booksDB[j].copies--;
                fulfilledReservations.push(frontInLine);
                return frontInLine;
            }
        }
        pendingReservations.enqueue(frontInLine);
    }

    throw LEXCEPTIONS_H::ReservationRecordUnavailable();
}

/**
 * Enqueues and adds a reservation (object) to the pending reservations given the reservation
 * @param reservation an Object representing a reservation
 */
void BookReservationManagementSystem::enqueueReservation(const ReservationRecord &reservation) {
    pendingReservations.enqueue(reservation);
}