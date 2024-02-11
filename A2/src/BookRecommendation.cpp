/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */


#include "../include/BookRecommendation.h"

UnorderedSet<Book>
BookRecommendation::getRecommendedBooks(const UnorderedSet<std::string> &neighborhood, const string &targetUserID) {
    return UnorderedSet<Book>();
}

UnorderedSet<std::string> BookRecommendation::getNeighborhood(const string &targetUserID, int neighborhoodSize) {
    return UnorderedSet<std::string>();
}

double BookRecommendation::calculateSimilarity(const string &userID1, const string &userID2) {
    return 0;
}

std::vector<Book>
BookRecommendation::getBookRecommendations(const string &targetUserID, int numRecommendations, int neighborhoodSize) {
    return std::vector<Book>();
}

void BookRecommendation::addUserBorrowedBook(Patron &userID, Book &book) {

}
