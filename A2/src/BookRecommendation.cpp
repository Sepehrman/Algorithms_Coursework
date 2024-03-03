/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/BookRecommendation.h"

void BookRecommendation::addUserBorrowedBook(Patron &userID, Book &book) {
    UnorderedSet<Book>* borrowedBooks = userBorrowedBooks.search(userID.ID);
    if (borrowedBooks) {
        borrowedBooks->insert(book);
    } else {
        borrowedBooks = new UnorderedSet<Book>();
        borrowedBooks->insert(book);
        userBorrowedBooks.insert(userID.ID, *borrowedBooks);
    }

    UnorderedSet<Patron>* borrowedBooksByUsers = bookBorrowedByUsers.search(book.ISBN);
    if (borrowedBooksByUsers)
        borrowedBooksByUsers->insert(userID);
    else {
        borrowedBooksByUsers = new UnorderedSet<Patron>();
        borrowedBooksByUsers->insert(userID);
        bookBorrowedByUsers.insert(book.ISBN, *borrowedBooksByUsers);
    }
}


std::vector<Book> BookRecommendation::getBookRecommendations(const std::string &targetUserID,
                                                             int numRecommendations, int neighborhoodSize) {
    UnorderedSet<std::string> neighbourhood = getNeighborhood(targetUserID, neighborhoodSize);
    UnorderedSet<Book> initRecommendations = getRecommendedBooks(neighbourhood, targetUserID);

    std::vector<Book> finalRecommendations;
    finalRecommendations.reserve(numRecommendations); // Reserve space to avoid unnecessary reallocation

    UnorderedSet<Book>::Iterator it = initRecommendations.begin();
    for (int i = 0; i < numRecommendations && it != initRecommendations.end(); ++i, ++it) {
        finalRecommendations.push_back(std::move(*it));
    }
    return finalRecommendations;
}

UnorderedSet<Book> BookRecommendation::getRecommendedBooks(const UnorderedSet<std::string> &neighborhood,
                                                           const std::string &targetUserID) {
    Stack<std::string> patronStack;
    std::unordered_map<std::string, int> frequencyMap;
    UnorderedSet<Book> recommendedBooks;

    UnorderedSet<Book>* targetUserBooks = userBorrowedBooks.search(targetUserID);
    if (!targetUserBooks)
        throw std::runtime_error("Error: User must have borrowed books");

    // Populate stack with patron IDs
    for (const std::string& patronID : neighborhood) {
        patronStack.push(patronID);
    }

    // Process each patron
    while (!patronStack.isEmpty()) {
        std::string patronID = patronStack.top();
        patronStack.pop();

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

double BookRecommendation::calculateSimilarity(const std::string &userID1, const std::string &userID2) {
    double unionCardinality = 0.0;
    double intersectCardinality = 0.0;

    UnorderedSet<Book> *user1BookSet = userBorrowedBooks.search(userID1);
    UnorderedSet<Book> *user2BookSet = userBorrowedBooks.search(userID2);

    if (user1BookSet == nullptr || user1BookSet->size() == 0 || user2BookSet == nullptr || user2BookSet->size() == 0)
        return unionCardinality;



    for (const Book &bk: *user1BookSet) {
        if (user2BookSet->search(bk))
            ++intersectCardinality;
    }

    unionCardinality = user1BookSet->size() + user2BookSet->size() - intersectCardinality;

    if (unionCardinality == 0.0)
        return 1.0;

    return intersectCardinality / unionCardinality;
}

UnorderedSet<std::string> BookRecommendation::getNeighborhood(const std::string &targetUserID, int neighborhoodSize) {
    UnorderedSet<std::string> neighbourhood = UnorderedSet<std::string>();
    std::vector<std::pair<std::string, double>> similHeap(0);
    Stack<std::string> topKStack = Stack<std::string>();

    std::make_heap(similHeap.begin(), similHeap.end(),
                   [](std::pair<std::string, double> a, std::pair<std::string, double> b) -> bool {
                       if (a.second == b.second)
                           return a.first > b.first;
                       return a.second < b.second;
                   });

    for (unsigned int i = 0; i < userBorrowedBooks.tableSize; ++i) {
        if (userBorrowedBooks.hashTable[i].occupied && userBorrowedBooks.hashTable[i].key != targetUserID) {
            std::string key = userBorrowedBooks.hashTable[i].key;
            double similarity = calculateSimilarity(targetUserID, key);
            if (similarity == 0.0)
                continue; // no similarity, we don't give a FUCK. PLEASE say this in the assignment readme next timeFUCK.

            std::pair<std::string, double> tuple = make_pair(key, similarity);

            similHeap.emplace_back(tuple);
            std::push_heap(similHeap.begin(), similHeap.end(), // belongs to "algorithms" lib therefore allowed
                           [](std::pair<std::string, double> a, std::pair<std::string, double> b) -> bool {
                               if (a.second == b.second)
                                   return a.first > b.first;// lexographic sorting if same similarity.
                               return a.second < b.second;
                           });
        }
    }

    for (int i = 0; i < neighborhoodSize && similHeap.size() != 0; i++) {
        // we HAVE to use a stack according to ass md or we lose marks
        // we can just as easily directly insert to the unordered set instead and save additional + K, though.
        topKStack.push(similHeap[0].first);
        std::pop_heap(similHeap.begin(), similHeap.end(), [](std::pair<std::string, double> a, std::pair<std::string, double> b) -> bool {
            if (a.second == b.second)
                return a.first > b.first;
            return a.second < b.second;
        });
        similHeap.pop_back();
    }

    while (topKStack.size() > 0) {
        neighbourhood.insert(topKStack.top());
        topKStack.pop();
    }

    return neighbourhood;
}

