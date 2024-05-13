//
//  main.cpp
//  Laba5_4sem
//
//  Created by Роман Перепонов on 14.05.2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <filesystem>

struct Book {
    std::string id;
    std::string author;
    std::string title;
    int pages;
};

std::vector<std::string> split(const std::string& s, char delimiter) {
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(s);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

void addBook(const std::string& PathToFile) {
    std::ofstream file(PathToFile, std::ios::app);
    if (file.is_open()) {
        std::string id, author, title;
        int pages;

        std::cout << "ID: ";
        std::cin >> id;
        std::cout << "Author: ";
        std::cin.ignore();
        std::getline(std::cin, author);
        std::cout << "Title: ";
        std::getline(std::cin, title);
        std::cout << "Pages: ";
        std::cin >> pages;

        file << id << " " << author << " " << title << " " << pages << std::endl;

        file.close();
        std::cout << "Book added successfully." << std::endl;
    }
    else {
        std::cerr << "Unable open file." << std::endl;
    }
}

void viewBooks(const std::string& PathToFile) {
    std::ifstream file(PathToFile);
    if (file.is_open()) {
        std::string line;

        std::cout << "ID\tAuthor\tTitle\tPages" << std::endl;
        while (std::getline(file, line)) {
            std::vector<std::string> bookData = split(line, ' ');
            std::cout << bookData[0] << "\t" << bookData[1] << "\t" << bookData[2] << "\t" << bookData[3] << std::endl;
        }

        file.close();
    }
    else {
        std::cerr << "Unable open file." << std::endl;
    }
}

void deleteBook(const std::string& PathToFile) {
    std::string id;
    std::cout << "Enter ID of book to delete: ";
    std::cin >> id;

    std::ifstream fileIn(PathToFile);
    std::ofstream fileOut(PathToFile + ".tmp");
    if (fileIn.is_open() && fileOut.is_open()) {
        std::string line;
        bool found = false;

        while (std::getline(fileIn, line)) {
            std::vector<std::string> bookData = split(line, ' ');
            if (bookData[0] != id) {
                fileOut << line << std::endl;
            }
            else {
                found = true;
            }
        }

        fileIn.close();
        fileOut.close();

        std::remove(PathToFile.c_str());
        std::rename((PathToFile + ".tmp").c_str(), PathToFile.c_str());

        if (found) {
            std::cout << "Book deleted successfully." << std::endl;
        }
        else {
            std::cout << "Not found." << std::endl;
        }
    }
    else {
        std::cerr << "Unable open file." << std::endl;
    }
}

void searchByAuthor(const std::string& PathToFile) {
    std::string author;
    std::cout << "Enter author to search for: ";
    std::cin.ignore();
    std::getline(std::cin, author);

    std::ifstream file(PathToFile);
    if (file.is_open()) {
        std::string line;

        std::cout << "ID\tAuthor\tTitle\tPages" << std::endl;
        while (std::getline(file, line)) {
            std::vector<std::string> bookData = split(line, ' ');
            if (bookData[1] == author) {
                std::cout << bookData[0] << "\t" << bookData[1] << "\t" << bookData[2] << "\t" << bookData[3] << std::endl;
            }
        }

        file.close();
    }
    else {
        std::cerr << "Unable to open file." << std::endl;
    }
}

void editBook(const std::string& PathToFile) {
    std::string id;
    std::cout << "Enter ID of book: ";
    std::cin >> id;

    std::ifstream fileIn(PathToFile);
    std::ofstream fileOut(PathToFile + ".tmp");
    if (fileIn.is_open() && fileOut.is_open()) {
        std::string line;
        bool found = false;
        int pages;

        while (std::getline(fileIn, line)) {
            std::vector<std::string> bookData = split(line, ' ');
            if (bookData[0] != id) {
                fileOut << line << std::endl;
            }
            else {
                found = true;

                std::string author, title;

                std::cout << "New author: ";
                std::cin.ignore();
                std::getline(std::cin, author);
                std::cout << "New title: ";
                std::getline(std::cin, title);
                std::cout << "New pages: ";
                std::cin >> pages;

                fileOut << bookData[0] << " " << author << " " << title << " " << pages << std::endl;
            }
        }

        fileIn.close();
        fileOut.close();

        std::remove(PathToFile.c_str());
        std::rename((PathToFile + ".tmp").c_str(), PathToFile.c_str());

        if (found) {
            std::cout << "Book edited successfully." << std::endl;
        }
        else {
            std::cout << "Not found." << std::endl;
        }
    }
    else {
        std::cerr << "Unable open file." << std::endl;
    }
}

int main() {
    std::string PathToFile = "/Users/romanpereponov/Documents/untitled folder/Laba5_4sem/Laba5_4sem/book.txt";

//    std::cout << "Current working directory: " << std::filesystem::current_path() << std::endl;

    int choice;
    do {
        std::cout << "1. Add book" << std::endl;
        std::cout << "2. View books" << std::endl;
        std::cout << "3. Delete book" << std::endl;
        std::cout << "4. Search books by author" << std::endl;
        std::cout << "5. Edit book" << std::endl;
        std::cout << "0. Exit" << std::endl;
        std::cout << "Your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            addBook(PathToFile);
            break;
        }
        case 2: {
            viewBooks(PathToFile);
            break;
        }
        case 3: {
            deleteBook(PathToFile);
            break;
        }
        case 4: {
            searchByAuthor(PathToFile);
            break;
        }
        case 5: {
            editBook(PathToFile);
            break;
        }
        case 0: {
            break;
        }
        default: {
            std::cout << "Invalid choice.Try again." << std::endl;
            break;
        }
        }

        std::cout << std::endl;

    } while (choice != 0);

    return 0;
}
