#include <iostream>
#include <string>
using namespace std;

class Book {
public:
    int ISBN;
    string title;
    string author;

    Book() : ISBN(0), title(""), author("") {}

    Book(int isbn, string t, string a) {
        ISBN = isbn;
        title = t;
        author = a; 
    }

};


class Node {
    public:
        Book book;
        Node* left;
        Node* right;
        int height;

        Node(Book b){
            book = b;
            left = nullptr;
            right = nullptr;
            height = 1;
        }
    };
    


class AVLTree {
private:
    Node* root;

    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    Node* createNode(int ISBN, string title, string author) {
        Book book(ISBN, title, author);
        Node* node = new Node(book);
        return node;
    }

    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;
        x->right = y;
        y->left = T2;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        return x;
    }

    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;
        y->left = x;
        x->right = T2;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        return y;
    }

    Node* balance(Node* node) {
        node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
        int balance = getBalanceFactor(node);
        
        if (balance > 1 && getBalanceFactor(node->left) >= 0)
            return rightRotate(node);
        if (balance > 1 && getBalanceFactor(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }
        if (balance < -1 && getBalanceFactor(node->right) <= 0)
            return leftRotate(node);
        if (balance < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }
        return node;
    }

    Node* insert(Node* node, int ISBN, string title, string author) {
        if (!node) return createNode(ISBN, title, author);
        if (ISBN < node->book.ISBN)
            node->left = insert(node->left, ISBN, title, author);
        else if (ISBN > node->book.ISBN)
            node->right = insert(node->right, ISBN, title, author);
        else
            return node;
        return balance(node);
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    Node* remove(Node* node, int ISBN) {
        if (!node) return nullptr;
        if (ISBN < node->book.ISBN)
            node->left = remove(node->left, ISBN);
        else if (ISBN > node->book.ISBN)
            node->right = remove(node->right, ISBN);
        else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            Node* temp = findMin(node->right);
            node->book = temp->book;
            node->right = remove(node->right, temp->book.ISBN);
        }
        return balance(node);
    }

    Node* search(Node* node, int ISBN) {
        if (!node || node->book.ISBN == ISBN)
            return node;
        if (ISBN < node->book.ISBN)
            return search(node->left, ISBN);
        return search(node->right, ISBN);
    }

    void inOrder(Node* node) {
        if (!node) return;
        inOrder(node->left);
        cout << "ISBN: " << node->book.ISBN << " | Title: " << node->book.title << " | Author: " << node->book.author << endl;
        inOrder(node->right);
    }

    void rangeSearch(Node* node, int low, int high) {
        if (!node) return;
        if (low < node->book.ISBN)
            rangeSearch(node->left, low, high);
        if (low <= node->book.ISBN && node->book.ISBN <= high)
            cout << "ISBN: " << node->book.ISBN << " | Title: " << node->book.title << " | Author: " << node->book.author << endl;
        if (high > node->book.ISBN)
            rangeSearch(node->right, low, high);
    }

public:
    AVLTree() : root(nullptr) {}

    void addBook(int ISBN, string title, string author) {
        root = insert(root, ISBN, title, author);
    }

    void removeBook(int ISBN) {
        root = remove(root, ISBN);
    }

    void searchBook(int ISBN) {
        Node* res = search(root, ISBN);
        if (res)
            cout << "Found: ISBN: " << res->book.ISBN << " | Title: " << res->book.title << " | Author: " << res->book.author << endl;
        else
            cout << "Book not found." << endl;
    }

    void displayBooks() {
        inOrder(root);
    }

    void displayBooksInRange(int low, int high) {
        rangeSearch(root, low, high);
    }
};

int main() {
    AVLTree bookstore;
    bookstore.addBook(1001, "The Great Gatsby", "F. Scott Fitzgerald");
    bookstore.addBook(2002, "To Kill a Mockingbird", "Harper Lee");
    bookstore.addBook(1503, "1984", "George Orwell");
    bookstore.addBook(1204, "Pride and Prejudice", "Jane Austen");
    bookstore.addBook(3005, "The Catcher in the Rye", "J.D. Salinger");
    
    cout << "\nAll Books in Sorted Order:\n";
    bookstore.displayBooks();
    
    cout << "\nSearch for ISBN 1503:\n";
    bookstore.searchBook(1503);
    
    cout << "\nRemoving book with ISBN 1204:\n";
    bookstore.removeBook(1204);
    bookstore.displayBooks();
    
    cout << "\nDisplaying books between ISBN 1000 and 2500:\n";
    bookstore.displayBooksInRange(1000, 2500);
    
    return 0;
}
