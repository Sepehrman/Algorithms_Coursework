/**
 * @author          Sepehr Mansouri
 * @StudentNumber   A01067581
 */

#include "../include/LibraryRestructuring.h"
using namespace std;

/**
 * Constructs the LibraryRestructuring object and creates a graph of books based on borrowing records.
 * @param records The collection of borrowing records.
 * @param bookCollection The collection of all books.
 */
LibraryRestructuring::LibraryRestructuring(const UnorderedSet<BorrowRecord>& records, const UnorderedSet<Book>& bookCollection) {
    //Initialize the 'allBooks' hash table with available books
    for (const Book& book : bookCollection) {
        allBooks.insert(book.ISBN, book);
    }

    HashTable<string, UnorderedSet<string>> patronToBooks;
    for (const BorrowRecord& record : records) {
        string isbn = record.bookISBN;
        string patronId = record.patronId;

        // Update the mapping of patron to books
        if (!patronToBooks.search(patronId)) {
            UnorderedSet<string> set;
            set.insert(isbn);
            patronToBooks.insert(patronId, set);
        } else {
            patronToBooks[patronId].insert(isbn);
        }

        int borrowTime = Date::diffDuration(record.checkoutDate, record.returnDate);
        if (bookBorrowingTime.search(isbn)) {
            bookBorrowingTime[isbn] += borrowTime;
        } else {
            bookBorrowingTime.insert(isbn, borrowTime);
        }
    }

    // Create relationships in the graph
    for (const auto& entry : patronToBooks) {
        const UnorderedSet<string>& books = entry->value;
        for (const string& book1 : books) {
            for (const string& book2 : books) {
                if (book1 != book2) {
                    graph[book1].insert(book2);
                }
            }
        }
    }
}

/**
 * Depth-first search (DFS) function used for creating clusters.
 * @param current The current ISBN being explored.
 * @param cluster The vector to store the cluster's ISBNs.
 * @param visited Hash table to track visited nodes.
 */
void LibraryRestructuring::dfs(const string &current, vector<string> &cluster, HashTable<string, bool> &visited) {
    visited[current] = true;
    cluster.push_back(current);
    UnorderedSet<string>* adjacentBooks = graph.search(current);
    if (adjacentBooks) {
        for (const string& adjacentISBN : *adjacentBooks) {
            if (!visited.search(adjacentISBN) || !(visited[adjacentISBN])) {
                dfs(adjacentISBN, cluster, visited);
            }
        }
    }
}

/**
 * Calculates the average borrowing time for a cluster of books.
 * @param cluster The vector containing ISBNs of books in the cluster.
 * @return The average borrowing time for the books in the cluster.
 */
double LibraryRestructuring::getAverageBorrowingTime(const vector<string>& cluster) {
    if (cluster.empty()) {
        return 0.0;
    }
    size_t validEntries = 0;
    double totalBorrowingTime = 0.0;

    for (const string& isbn : cluster) {
        if (bookBorrowingTime.search(isbn)) {
            totalBorrowingTime += bookBorrowingTime[isbn];
            ++validEntries;
        }
    }

    if (validEntries == 0) return 0.0;
    return totalBorrowingTime / validEntries;
}



/**
 * Clusters and sorts the books using the provided sorting method.
 * @param sortBy The method by which to sort the clusters.
 * @return A vector of clusters, each containing a vector of ISBNs.
 */
vector<vector<string>> LibraryRestructuring::clusterAndSort(const string& sortBy) {
    vector<vector<string>> clusters;
    HashTable<string, bool> visited;

    for (const auto& entry : graph) {
        const string& currentISBN = entry->key;

        // If the current node is not visited, perform DFS to create a cluster
        if (!visited[currentISBN]) {
            vector<string> cluster;
            dfs(currentISBN, cluster, visited);
            clusters.push_back(cluster);
        }
    }

    // Sorting using MergeSort
    MergeSort<vector<string>> mergeSort([this](const vector<string>& a, const vector<string>& b) {
        return getAverageBorrowingTime(a) < getAverageBorrowingTime(b);
    });
    mergeSort.sort(clusters);
    return clusters;
}