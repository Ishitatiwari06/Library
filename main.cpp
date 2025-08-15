#include<bits/stdc++.h>
using namespace std;

class Book {
public:
    string title;
    string author;
    bool isIssued;

    Book(string t, string a, bool issued = false)
        : title(t), author(a), isIssued(issued) {}
};

class Library {
private:
    vector<Book> books;
    string filename;

public:
    Library(string file) : filename(file) {
        loadFromFile();
    }

    void addBook() {
        string title, author;
        cin.ignore();
        cout << "Enter book title: ";
        getline(cin, title);
        cout << "Enter book author: ";
        getline(cin, author);
        books.push_back(Book(title, author, false));
        saveToFile();
        cout << "Book added successfully!\n";
    }

    void issueBook() {
        string title;
        cin.ignore();
        cout << "Enter book title to issue: ";
        getline(cin, title);

        for (auto &book : books) {
            if (book.title == title) {
                if (book.isIssued) {
                    cout << "Book already issued!\n";
                } else {
                    book.isIssued = true;
                    saveToFile();
                    cout << "Book issued successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void returnBook() {
        string title;
        cin.ignore();
        cout << "Enter book title to return: ";
        getline(cin, title);

        for (auto &book : books) {
            if (book.title == title) {
                if (!book.isIssued) {
                    cout << "This book was not issued!\n";
                } else {
                    book.isIssued = false;
                    saveToFile();
                    cout << "Book returned successfully!\n";
                }
                return;
            }
        }
        cout << "Book not found!\n";
    }

    void displayBooks() {
        cout << "\nAvailable Books:\n";
        for (const auto &book : books) {
            cout << "Title: " << book.title
                 << " | Author: " << book.author
                 << " | Issued: " << (book.isIssued ? "Yes" : "No") << "\n";
        }
    }

private:
    void loadFromFile() {
        ifstream file(filename);
        if (!file) return;

        string title, author;
        bool issued;

        while (getline(file, title) && getline(file, author) && file >> issued) {
            file.ignore();
            books.push_back(Book(title, author, issued));
        }
        file.close();
    }

    void saveToFile() {
        ofstream file(filename);
        for (const auto &book : books) {
            file << book.title << "\n"
                 << book.author << "\n"
                 << book.isIssued << "\n";
        }
        file.close();
    }
};

int main() {
    Library lib("library.txt");
    int choice;

    do {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Issue Book\n";
        cout << "3. Return Book\n";
        cout << "4. Display Books\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.issueBook(); break;
            case 3: lib.returnBook(); break;
            case 4: lib.displayBooks(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice! Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
