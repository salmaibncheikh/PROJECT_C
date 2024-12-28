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



