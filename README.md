# PROJECT : Library management system
# Library Management System

## Table of Contents

1. [Introduction](#introduction)
2. [Key Features](#key-features)
3. [System Design](#system-design)
4. [Data Structures Used](#data-structures-used)
5. [Code Organization](#code-organization)
6. [How to Use](#how-to-use)
7. [File Overview](#file-overview)
8. [Example Workflow](#example-workflow)
9. [Planned Enhancements](#planned-enhancements)
10. [Contributing Guidelines](#contributing-guidelines)

---

## Introduction

This project is a comprehensive Library Management System built in C. It simplifies the management of books and users with features such as adding, updating, removing, and searching. It also facilitates borrowing and returning books while keeping track of recent activities and managing user requests. The system ensures data persistence through file storage and enhances search efficiency using a Binary Search Tree (BST).

---

## Key Features

- **Manage Books**: Add, update, delete, search, and display books.
- **User Management**: Add, update, delete, search, and display users.
- **Borrowing and Returning**: Record borrow and return transactions and update book availability.
- **Activity Logs**: Track recent actions using a stack.
- **Request Queue**: Process requests in a first-in, first-out (FIFO) manner using a queue.
- **Efficient Searches**: Utilize a BST for fast book lookups by title.
- **Persistent Data**: Save and load books and users from text files.
- <p align="center">
  <img src="https://github.com/user-attachments/assets/27569a83-34d5-4966-84da-e43d11d62c38" alt="Library Management System Architecture" style="width: 600px; height: auto;">
</p>

---

## System Design

The system is divided into key components:

1. **Book Management**:  
   - Uses a linked list for book data storage and operations.  
   - Implements a BST for efficient book searches by title.  
   - Saves and loads books from a persistent file (`books.txt`).  

2. **User Management**:  
   - Maintains user data in a linked list.  
   - Supports operations like adding, updating, searching, and deleting users.  
   - Saves and loads user data from a file (`users.txt`).  

3. **Borrowing and Returning System**:  
   - Tracks book availability and manages user transactions.  

4. **Activity Tracking**:  
   - Uses a stack to log recent borrow or return activities.  

5. **Request Handling**:  
   - Manages user requests with a queue to ensure FIFO processing.  

6. **Persistent Data Storage**:  
   - Text files store book and user data, ensuring no data is lost between sessions.  

7. **User Interface**:  
   - Provides a menu-driven interface for easy system interaction.  

---

## Data Structures Used

### Book Structure
Stores book details in a linked list:
```c
typedef struct Book {
    int id;
    char title[100];
    char author[50];
    char genre[30];
    int available; // 1 = available, 0 = borrowed
    struct Book *next;
} Book;
```


### User Structure
Maintains user data in a linked list:
```c
typedef struct User {
    int id;
    char name[50];
    char contact[50];
    struct User *next;
} User;
```
### Stack for Recent Activities
Tracks recent actions like book borrow and return:
```c
typedef struct StackNode {
    int bookId;
    struct StackNode *next;
} StackNode;
```
### Queue for Requests
Processes user requests in FIFO order:

```c
typedef struct QueueNode {
    int userId;
    int bookId;
    struct QueueNode *next;
} QueueNode;
```
### Binary Search Tree (BST)
Organizes books for efficient searches:

```c
typedef struct TreeNode {
    Book *book;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode; 
```
# Code Organization

## Main Function
The main function initializes the program, displays a menu for user interaction, and executes functions based on user input.

## Book Functions
- **Add Book**: Adds a new book to the system.  
- **Remove Book**: Deletes a book by ID.  
- **Update Book**: Updates book details.  
- **Search Book**: Searches for a book by ID or title.  
- **Display Books**: Displays all books.  

## User Functions
- **Add User**: Adds a new user to the system.  
- **Remove User**: Deletes a user by ID.  
- **Update User**: Updates user details.  
- **Search User**: Searches for a user by name or ID.  
- **Display Users**: Displays all users.  

## Stack Functions
- **Push**: Adds an activity to the stack.  
- **Pop**: Removes the most recent activity.  
- **Display Stack**: Shows recent activities.  

## Queue Functions
- **Enqueue**: Adds a user request to the queue.  
- **Dequeue**: Processes the next request in the queue.  
- **Display Queue**: Shows all pending requests.  

## BST (Binary Search Tree) Functions
- **Insert Book**: Adds a book to the BST for efficient searching.  
- **Search Book**: Searches for a book by title in the BST.  
- **Display BST**: Displays all books in sorted order.  

---

## File Overview

- **books.txt**: Stores book information persistently.  
- **users.txt**: Stores user information persistently.








