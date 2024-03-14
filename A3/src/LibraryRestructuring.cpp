//
// Created by Winston on 11/10/2023.
//
#include "../include/MergeSort.h"
#include "../include/RadixSort.h"
#include "../include/LibraryRestructuring.h"
#include <string>
#include <sstream>

//The LibraryRestructuring constructor and create graph of books.
LibraryRestructuring::LibraryRestructuring(const UnorderedSet<BorrowRecord>& records, const UnorderedSet<Book>& bookCollection) {
    //Initialize the 'allBooks' hash table with book information
    for (const Book& book : bookCollection) {
        allBooks.insert(book.ISBN, book);
    }

    HashTable<std::string, UnorderedSet<std::string>> patronToBooks;
    for (const BorrowRecord& record : records) {
        std::string isbn = record.bookISBN;
        std::string patronId = record.patronId;

        int borrowingTime = Date::diffDuration(record.checkoutDate, record.returnDate);
        if (bookBorrowingTime.search(isbn)) {
            bookBorrowingTime[isbn] += borrowingTime;
        } else {
            bookBorrowingTime.insert(isbn, borrowingTime);
        }

        // Update the mapping of patron to books
        if (!patronToBooks.search(patronId)) {
            UnorderedSet<std::string> tempSet;
            tempSet.insert(isbn);
            patronToBooks.insert(patronId, tempSet);
        } else {
            patronToBooks[patronId].insert(isbn);
        }
    }

    // Create relationships in the graph
    for (const auto& entry : patronToBooks) {
        const UnorderedSet<std::string>& books = entry->value;
        for (const std::string& book1 : books) {
            for (const std::string& book2 : books) {
                if (book1 != book2) {
                    graph[book1].insert(book2);
                }
            }
        }
    }
}

//Create Cluster and uses Radixsort and Mergesort.
std::vector<std::vector<std::string>> LibraryRestructuring::clusterAndSort(const std::string& sortBy) {
    std::vector<std::vector<std::string>> clusters;
    HashTable<std::string, bool> visited;

    for (const auto& entry : graph) {
        const std::string& currentISBN = entry->key;

        // If the current node is not visited, perform DFS to create a cluster
        if (!visited[currentISBN]) {
            std::vector<std::string> cluster;
            dfs(currentISBN, cluster, visited);
            clusters.push_back(cluster);
        }
    }

    // Sorting using MergeSort
    MergeSort<std::vector<std::string>> mergeSort([this](const std::vector<std::string>& a, const std::vector<std::string>& b) {
        return getAverageBorrowingTime(a) < getAverageBorrowingTime(b);
    });
    mergeSort.sort(clusters);

    // Sorting using RadixSort
    //The alternative sorting way.
//    for (auto& cluster : clusters) {
//        RadixSort<std::string> radixSort(cluster, [this, &sortBy](const std::string& isbn) {
//            const Book& book = allBooks[isbn];
//            if (sortBy == "title") {
//                return book.title.length() > 0 ? book.title[0] : 0;
//            } else if (sortBy == "author") {
//                return book.author.length() > 0 ? book.author[0] : 0;
//            } else if (sortBy == "yearPublished") {
//                return book.yearPublished.length() > 0 ? book.yearPublished[0] : 0;
//            }
//            return 0;
//        });
//        radixSort.sort();
//    }

    return clusters;
}

//The DFS Function.
void LibraryRestructuring::dfs(const std::string &current, std::vector<std::string> &cluster, HashTable<std::string, bool> &visited) {
    visited[current] = true;
    cluster.push_back(current);
    UnorderedSet<std::string>* adjacentBooks = graph.search(current);
    if (adjacentBooks) {
        for (const std::string& adjacentISBN : *adjacentBooks) {
            if (!visited.search(adjacentISBN) || !(visited[adjacentISBN])) {
                dfs(adjacentISBN, cluster, visited);
            }
        }
    }
}

//Get cluster's average borrowing time.
double LibraryRestructuring::getAverageBorrowingTime(const std::vector<std::string>& cluster) {
    if (cluster.empty()) {
        return 0.0;
    }

    double totalBorrowingTime = 0.0;
    size_t validEntries = 0;
    for (const std::string& isbn : cluster) {
        if (bookBorrowingTime.search(isbn)) {
            totalBorrowingTime += bookBorrowingTime[isbn];
            ++validEntries;
        }
    }

    if (validEntries == 0) return 0.0;
    return totalBorrowingTime / validEntries;
}

