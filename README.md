# DSA Theory Assignment

**Course:** Data Structures and Algorithms (DSA)  
**Section:** A9  
**Instructor:** Muhammad Adeel

## Team Members

| Name                      | Student ID     |
|---------------------------|----------------|
| Huzaif ur Rehman Aamir    | F2023376207    |
| Moad Ahmad Chishti        | F2023376222    |

## Project Overview

This repository contains solutions to the DSA Theory Assignment, focusing on the following problems:

1. **Parking Lot Management System:**  
   Design and implement a system to manage parking in a multi-story car park, adhering to specific rules and constraints.

2. **Online Bookstore Management System:**  
   Develop a system to manage an online bookstore where each book is uniquely identified by its ISBN, utilizing an AVL tree to ensure efficient operations.

## Problem 1: Parking Lot Management System

**Objective:**  
Create a system to manage parking in a multi-story car park with the following features:

- **Entry and Exit Management:**  
  - Each floor can hold a maximum of N cars.
  - Cars are assigned to floors sequentially.
  - Cars entering the parking lot are tracked using a queue.

- **Floor Management:**  
  - Each floor uses a stack to represent parked cars.
  - The system adjusts when a car leaves to maintain proper structure.

- **Waitlist for Overflow:**  
  - If all floors are full, cars waiting to park are added to a linked list representing an overflow waitlist.

- **System Maintenance:**  
  - A dynamic array maintains details of currently parked cars, including floor number and position.

**Implementation:**  
The solution is implemented in C++. The `ParkingLot` class manages the parking system, handling operations such as adding and removing cars, displaying the parking lot status, and expanding the parking lot.

*For detailed code, refer to [`carParking.cpp`](carParking.cpp).*

## Problem 2: Online Bookstore Management System

**Objective:**  
Develop a system to manage an online bookstore with the following requirements:

- **Bookshelf Management:**  
  - Books are stored in a Binary Search Tree (BST), where the ISBN is the key.
  - The BST remains balanced using AVL tree properties.

- **Operations:**  
  - Add a book using its ISBN.
  - Remove a book by its ISBN.
  - Find and display a book's details using its ISBN.
  - Display all books sorted in ascending order of their ISBN.
  - Display all books within a given range of ISBNs.

- **Book Details:**  
  - ISBN (unique key)
  - Title
  - Author

**Implementation:**  
The solution is implemented in C++. The `Bookstore` class manages the AVL tree, ensuring it remains balanced after every insertion and deletion. It supports operations such as adding, removing, searching, and displaying books.

*For detailed code, refer to [`bookstore.cpp`](bookstore.cpp).*

## Compilation and Execution

To compile and run the programs:

1. **Parking Lot Management System:**
   - Compile: `g++ carParking.cpp -o carParking`
   - Run: `./carParking`

2. **Online Bookstore Management System:**
   - Compile: `g++ bookstore.cpp -o bookstore`
   - Run: `./bookstore`

Ensure that you have a C++ compiler installed and properly configured in your development environment.

