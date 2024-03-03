/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/BookRecommendation.h"
using namespace std;

/**
 * This function is responsible for adding a book borrowed by a user.
 * @param userID The ID of the user borrowing the book.
 * @param book The book being borrowed.
 */
void BookRecommendation::addUserBorrowedBook(Patron &userID, Book &book) {
    // Search for the unordered set of borrowed books by the user
    UnorderedSet<Book>* borrowedBooks = userBorrowedBooks.search(userID.ID);
    if (borrowedBooks != nullptr) {
        borrowedBooks->insert(book);
    } else {
        // If the user has no borrowed books, create a new set and insert the borrowed books and associate them to the user
        borrowedBooks = new UnorderedSet<Book>();
        borrowedBooks->insert(book);
        userBorrowedBooks.insert(userID.ID, *borrowedBooks);
    }

    // Search for the set of users who borrowed this book
    UnorderedSet<Patron>* borrowedBooksByUsers = bookBorrowedByUsers.search(book.ISBN);
    if (borrowedBooksByUsers != nullptr) {
        borrowedBooksByUsers->insert(userID);
    }
    else {
        // If no users have borrowed this book, create a new set and insert the user
        borrowedBooksByUsers = new UnorderedSet<Patron>();
        borrowedBooksByUsers->insert(userID);
        bookBorrowedByUsers.insert(book.ISBN, *borrowedBooksByUsers);
    }
}

/**
 * This function is responsible for getting book recommendations for a user.
 * @param targetUserID The ID of the target user.
 * @param numRecommendations The number of recommendations to retrieve.
 * @param neighborhoodSize The size of the user neighborhood to consider.
 * @return A vector of recommended books.
 */
vector<Book> BookRecommendation::getBookRecommendations(const string &targetUserID, int numRecommendations, int neighborhoodSize) {
    // Get the neighborhood of the target user based on similarity
    UnorderedSet<string> neighbourhood = getNeighborhood(targetUserID, neighborhoodSize);
    // Get the initial recommended books based on the neighborhood
    UnorderedSet<Book> initRecommendations = getRecommendedBooks(neighbourhood, targetUserID);

    vector<Book> finalRecommendations;
    finalRecommendations.reserve(numRecommendations); // Reserve space to avoid unnecessary reallocation

    // Copy the recommended books to the final recommendations vector
    UnorderedSet<Book>::Iterator it = initRecommendations.begin();
    for (int i = 0; i < numRecommendations && it != initRecommendations.end(); ++i, ++it) {
        finalRecommendations.push_back(move(*it));
    }
    return finalRecommendations;
}

/**
 * This function is responsible for getting recommended books based on user neighborhood.
 * @param neighborhood The neighborhood of the target user.
 * @param targetUserID The ID of the target user.
 * @return A set of recommended books.
 */
UnorderedSet<Book> BookRecommendation::getRecommendedBooks(const UnorderedSet<string> &neighborhood, const string &targetUserID) {
    Stack<string> patronStack;
    unordered_map<string, int> frequencyMap;
    UnorderedSet<Book> recommendedBooks;

    // Get the set of books borrowed by the target user
    UnorderedSet<Book>* targetUserBooks = userBorrowedBooks.search(targetUserID);
    if (!targetUserBooks)
        throw runtime_error("Error: User must have borrowed books");

    // Populate stack with patron IDs
    for (const string& patronID : neighborhood) {
        patronStack.push(patronID);
    }

    // Process each patron in the neighborhood
    while (!patronStack.isEmpty()) {
        string patronID = patronStack.top();
        patronStack.pop();

        // Get the set of books borrowed by the current patron
        UnorderedSet<Book>* patronBooksBorrowed = userBorrowedBooks.search(patronID);
        if (patronBooksBorrowed) {
            // Update frequency map and recommended books
            for (const Book& bk : *patronBooksBorrowed) {
                frequencyMap[bk.ISBN]++;
                if (!targetUserBooks->search(bk)) {
                    recommendedBooks.insert(bk);
                }
            }
        }
    }

    return recommendedBooks;
}

/**
 * This function is responsible for calculating the similarity between two users based on borrowed books.
 * @param userID1 The ID of the first user.
 * @param userID2 The ID of the second user.
 * @return The Jaccard similarity coefficient between the two users.
 */
double BookRecommendation::calculateSimilarity(const string &userID1, const string &userID2) {
    double unionCardinality = 0.0;
    double intersectCardinality = 0.0;

    // Get the set of books borrowed by each given user
    UnorderedSet<Book> *user1BookSet = userBorrowedBooks.search(userID1);
    UnorderedSet<Book> *user2BookSet = userBorrowedBooks.search(userID2);

    // If any user has not borrowed any books, return 0 similarity
    if (user1BookSet->size() == 0 || user2BookSet->size() == 0)
        return unionCardinality;

    // Calculate the intersection and union of borrowed books. If there are similarities found, increment cardinality by 1
    for (const Book &bk: *user1BookSet) {
        if (user2BookSet->search(bk))
            ++intersectCardinality;
    }

    unionCardinality = user1BookSet->size() + user2BookSet->size() - intersectCardinality;

    if (unionCardinality == 0.0)
        return 1.0;

    return intersectCardinality / unionCardinality;
}

/**
 * This function is responsible for getting the neighborhood of a user based on similarity.
 * @param targetUserID The ID of the target user.
 * @param neighborhoodSize The size of the neighborhood to consider.
 * @return The neighborhood set.
 */
UnorderedSet<string> BookRecommendation::getNeighborhood(const string &targetUserID, int neighborhoodSize) {
    UnorderedSet<string> neighbourhood = UnorderedSet<string>();
    vector<pair<string, double>> similHeap;

    // Iterate over all existing users
    for (unsigned int i = 0; i < userBorrowedBooks.tableSize; ++i) {
        // If the user is not the target user
        if (userBorrowedBooks.hashTable[i].occupied && userBorrowedBooks.hashTable[i].key != targetUserID) {
            string key = userBorrowedBooks.hashTable[i].key;
            // Calculate similarity between the target user and the current user
            double similarity = calculateSimilarity(targetUserID, key);
            if (similarity == 0.0)
                continue;

            pair<string, double> tuple = make_pair(key, similarity);

            // Insert the similarity pair into the heap sorted by similarity
            bool inserted = false;
            for (vector<pair<string, double>>::iterator it = similHeap.begin(); it != similHeap.end(); ++it) {
                if (it->second < similarity || (it->second == similarity && it->first > key)) {
                    similHeap.insert(it, tuple);
                    inserted = true;
                    break;
                }
            }
            if (!inserted) {
                similHeap.push_back(tuple);
            }

            // Keep only the top neighborhoodSize similarities
            if (similHeap.size() > static_cast<unsigned>(neighborhoodSize)) {
                similHeap.pop_back();
            }
        }
    }

    // Add the top K similar users to the neighborhood set
    for (const pair<string, double> &pair : similHeap) {
        neighbourhood.insert(pair.first);
    }

    return neighbourhood;
}
