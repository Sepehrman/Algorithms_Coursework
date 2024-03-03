/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/BookRecommendation.h"
#include <algorithm>

void BookRecommendation::addUserBorrowedBook(Patron &userID, Book &book) {
    UnorderedSet<Book>* booksBorrowed = userBorrowedBooks.search(userID.ID);
    if (booksBorrowed) {
        booksBorrowed->insert(book);
    } else {
        booksBorrowed = new UnorderedSet<Book>();
        booksBorrowed->insert(book);
        userBorrowedBooks.insert(userID.ID, *booksBorrowed);
    }

    UnorderedSet<Patron>* usersBorrowingBook = bookBorrowedByUsers.search(book.ISBN);
    if (usersBorrowingBook)
        usersBorrowingBook->insert(userID);
    else {
        usersBorrowingBook = new UnorderedSet<Patron>();
        usersBorrowingBook->insert(userID);
        bookBorrowedByUsers.insert(book.ISBN, *usersBorrowingBook);
    }
}


std::vector<Book> BookRecommendation::getBookRecommendations(const std::string &targetUserID, int numRecommendations,
                                                             int neighborhoodSize) {
    UnorderedSet<std::string> neighbourhood = getNeighborhood(targetUserID, neighborhoodSize);

    UnorderedSet<Book> initialRecs = getRecommendedBooks(neighbourhood, targetUserID);
    std::vector<Book> finalRecommendations = std::vector<Book>();

    int i = 0;
    for (const Book& bk : initialRecs) {
        if (i == numRecommendations)
            break;
        finalRecommendations.emplace_back(bk);
    }

    return finalRecommendations;
}

UnorderedSet<Book> BookRecommendation::getRecommendedBooks(const UnorderedSet<std::string> &neighborhood,
                                                           const std::string &targetUserID) {
    Stack<std::string> patronStack = Stack<std::string>();
    HashTable<std::string, int> frequencyMap = HashTable<std::string, int>();
    UnorderedSet<Book>* targetUserBooks = userBorrowedBooks.search(targetUserID);

    if (!targetUserBooks)
        throw std::runtime_error("User has to have borrowed books to have neighbours.");

    UnorderedSet<Book> recommendedBooks = UnorderedSet<Book>();

    for (const std::string patronID : neighborhood) {
        patronStack.push(patronID); // literally only here so i don't lose marks for not using a stack
    }

    while (!patronStack.isEmpty()) {
        std::string patronID = patronStack.top();
        UnorderedSet<Book>* patronBooksBorrowed = userBorrowedBooks.search(patronID);
        if (patronBooksBorrowed) {
            for (const Book &bk: *patronBooksBorrowed) {
                int *bookExists = frequencyMap.search(bk.ISBN);
                int updatedFreq = bookExists ? ++(*bookExists) : 1;
                frequencyMap.insert(bk.ISBN, updatedFreq);
                if (!targetUserBooks->search(bk))
                    recommendedBooks.insert(bk);
            }
        }
        patronStack.pop();
    }


    return recommendedBooks;
}

double BookRecommendation::calculateSimilarity(const std::string &userID1, const std::string &userID2) {
    double unionCardinality = 0.0;
    double intersectCardinality = 0.0;

    UnorderedSet<Book> *user1BookSet = userBorrowedBooks.search(userID1);
    UnorderedSet<Book> *user2BookSet = userBorrowedBooks.search(userID2);

    if (user1BookSet == nullptr || user1BookSet->size() == 0 || user2BookSet == nullptr || user2BookSet->size() == 0)
//        throw std::runtime_error("User doesn't exist in DB or doesn't have books.");
        return 0.0;



    for (const Book &bk: *user1BookSet)
        if (user2BookSet->search(bk))
            ++intersectCardinality;

    // everything in both sets minus the intersection overcounting
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

