#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define the Book structure
typedef struct Book{
    int id;
    char title[100];
    char author[50];
    char genre[30];
    int available; // 1 if available, 0 if borrowed
    struct Book *next;
} Book;

// Define the User structure
typedef struct User{
    int id;
    char name[50];
    char contact[50];
    struct User *next;
} User;

// Define the Stack Node structure
typedef struct StackNode{
    int bookId;
    struct StackNode *next;
} StackNode;

// Define the Queue Node structure
typedef struct QueueNode{
    int userId;
    int bookId;
    struct QueueNode *next;
} QueueNode;

// Define the Tree Node structure for BST
typedef struct TreeNode{
    Book *book;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

// Function to display the menu and get user choice
int displayMenu(){
    int choice;
    printf("\nLibrary Management System\n");
    printf("1. Add Book\n");
    printf("2. Remove Book\n");
    printf("3. Update Book\n");
    printf("4. Borrow Book\n");
    printf("5. Return Book\n");
    printf("6. Search Book by Title\n");
    printf("7. Display All Books\n");
    printf("8. Add User\n");
    printf("9. Remove User\n");
    printf("10. Update User\n");
    printf("11. Search User by Name\n");
    printf("12. Display All Users\n");
    printf("13. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    return choice;
}

// Functions for Linked List (Books)
void addBook(Book **head, int id, const char *title, const char *author, const char *genre);
void removeBook(Book **head, int id);//remove with title of book
void updateBook(Book *head, int id, const char *newTitle, const char *newAuthor, const char *newGenre);
Book *searchBook(Book *head, int id);
void displayBooks(Book *head);
void saveBooksToFile(Book *head);

// Functions for Linked List (Users)
void addUser(User **head, int id, const char *name, const char *contact);
void removeUser(User **head, int id);
void updateUser(User *head, int id, const char *newName, const char *newContact);
User *searchUserByName(User *head, const char *name);
void displayUsers(User *head);
void saveUsersToFile(User *head);

// Functions for Stack
void push(StackNode **top, int bookId);
int pop(StackNode **top);
void displayStack(StackNode *top);

// Functions for Queue
void enqueue(QueueNode **front, QueueNode **rear, int userId, int bookId);
void dequeue(QueueNode **front, QueueNode **rear);
void displayQueue(QueueNode *front);

// Functions for Binary Search Tree (BST)
void insertBookToBST(TreeNode **root, Book *book);
Book *searchBookInBST(TreeNode *root, const char *title);
void displayBST(TreeNode *root);
Book* loadBooks(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening books file");
        return NULL;
    }

    Book *head = NULL, *tail = NULL;
    while (!feof(file)) {
        Book *newBook = (Book *)malloc(sizeof(Book));
        if (fscanf(file, "%d,%99[^,],%49[^,],%29[^,],%d\n",
                   &newBook->id,
                   newBook->title,
                   newBook->author,
                   newBook->genre,
                   &newBook->available) == 5) {
            newBook->next = NULL;
            if (head == NULL) {
                head = tail = newBook;
            } else {
                tail->next = newBook;
                tail = newBook;
            }
        } else {
            free(newBook); // Lib�rer la m�moire si la lecture �choue
        }
    }
    fclose(file);
    return head;
}
User* loadUsersFromFile(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erreur d'ouverture du fichier %s\n", filename);
        return NULL;
    }

    User *userList = NULL;
    User *currentUser = NULL;

    while (!feof(file)) {
        User *newUser = (User *)malloc(sizeof(User));
        if (newUser == NULL) {
            printf("Erreur d'allocation m�moire pour un utilisateur.\n");
            fclose(file);
            return userList;
        }

        // Lire les informations de l'utilisateur depuis le fichier
        int res = fscanf(file, "%d,%49[^,],%49[^\n]", &newUser->id, newUser->name, newUser->contact);
        if (res == 3) { // Si 3 valeurs sont lues
            newUser->next = NULL;

            if (userList == NULL) {
                // Premier utilisateur, initialise la liste
                userList = newUser;
            } else {
                // Ajoute � la fin de la liste
                currentUser->next = newUser;
            }
            currentUser = newUser; // Met � jour le pointeur de l'utilisateur courant
        }
    }

    fclose(file);
    return userList;
}
StackNode* initializeStackWithBooks(Book *bookList) {
    StackNode *stackTop = NULL;  // La pile est vide au d�but
    Book *currentBook = bookList;

    // On ajoute chaque livre de bookList � la pile
    while (currentBook != NULL) {
        push(&stackTop, currentBook->id);  // Utilisation de la fonction push
        currentBook = currentBook->next;   // Passer au livre suivant
    }

    return stackTop;  // Retourner la pile initialis�e
}
TreeNode* initializeBSTWithBooks(Book *bookList) {
    TreeNode *bookTree = NULL;  // Initialisation de l'arbre comme NULL
    Book *currentBook = bookList;

    while (currentBook != NULL) {
        insertBookToBST(&bookTree, currentBook);  // Insertion de chaque livre dans l'arbre
        currentBook = currentBook->next;  // Passer au livre suivant
    }

    return bookTree;  // Retourner l'arbre binaire de recherche initialis�
}
int isBookIdUnique(Book *head, int id){
    Book *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return 0; // ID not unique
        }
        current = current->next;
    }
    return 1; // ID unique
}
int isUserIdUnique(User *head, int id){
    User *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return 0; // ID not unique
        }
        current = current->next;
    }
    return 1; // ID unique
}
int main()
{
    Book *bookList = loadBooks("books.txt");
    User *userList = loadUsersFromFile("users.txt");
    //StackNode *recentActivities = NULL;
    StackNode *recentActivities = initializeStackWithBooks(bookList);
    QueueNode *requestQueueFront = NULL,
    *requestQueueRear = NULL;
    TreeNode *bookTree = initializeBSTWithBooks(bookList);


    //remplissage par les fichiers
    int choice, id,uid;
    char title[100], author[50], genre[30], name[50], contact[50];

    while ((choice = displayMenu()) != 13)
    {
        switch (choice)
        {
        case 1:
            printf("Enter Book ID: ");
            scanf("%d", &id);
            printf("Enter Book Title: ");
            getchar(); // to consume the newline character left by scanf
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0'; // Remove trailing newline
            printf("Enter Book Author: ");
            fgets(author, sizeof(author), stdin);
            author[strcspn(author, "\n")] = '\0'; // Remove trailing newline
            printf("Enter Book Genre: ");
            fgets(genre, sizeof(genre), stdin);
            genre[strcspn(genre, "\n")] = '\0'; // Remove trailing newline
            addBook(&bookList, id, title, author, genre);
            push(&recentActivities, id);
            Book *newBook = searchBook(bookList, id);
            insertBookToBST(&bookTree, newBook);
            break;
        case 2:
            printf("Enter Book ID to Remove: ");
            scanf("%d", &id);
            removeBook(&bookList, id);
            break;
        case 3:
            printf("Enter Book ID to Update: ");
            scanf("%d", &id);
            printf("Enter New Book Title: ");
            getchar(); // to consume the newline character left by scanf
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0'; // Remove trailing newline
            printf("Enter New Book Author: ");
            fgets(author, sizeof(author), stdin);
            author[strcspn(author, "\n")] = '\0'; // Remove trailing newline
            printf("Enter New Book Genre: ");
            fgets(genre, sizeof(genre), stdin);
            genre[strcspn(genre, "\n")] = '\0'; // Remove trailing newline
            updateBook(bookList, id, title, author, genre);
            break;
        case 4:
            printf("Enter Book ID to Borrow: ");
            scanf("%d", &id);
            Book *bookToBorrow = searchBook(bookList, id);
            if (bookToBorrow && bookToBorrow->available == 1)
            {
                bookToBorrow->available = 0;
                printf("Book with ID %d borrowed successfully.\n", id);
            }
             else
            {
                printf("Book with ID %d is already borrowed.\n", id);
            }
            saveBooksToFile(bookList); // Update the file after borrowing
            break;
        case 5:
            printf("Enter Book ID to Return: ");
            scanf("%d", &id);
            Book *bookToReturn = searchBook(bookList, id);
            if (bookToReturn && bookToReturn->available == 0)
            {
                bookToReturn->available = 1;
                printf("Book with ID %d returned successfully.\n", id);
            }
            else
            {
                printf("Book with ID %d is not borrowed.\n", id);
            }
            saveBooksToFile(bookList); // Update the file after returning
            break;
        case 6:
            printf("Enter Book Title to Search: ");
            getchar(); // to consume the newline character left by scanf
            fgets(title, sizeof(title), stdin);
            title[strcspn(title, "\n")] = '\0'; // Remove trailing newline
            Book *foundBook = searchBookInBST(bookTree, title);
            if (foundBook)
            {
                printf("ID: %d, Title: %s, Author: %s, Genre: %s, Available: %d\n",
                       foundBook->id, foundBook->title, foundBook->author, foundBook->genre, foundBook->available);
            }
            else
            {
                printf("No books found with title: %s\n", title);
            }
            break;
        case 7:
            displayBooks(bookList);
            break;
        case 8:
            printf("Enter User ID: ");
            scanf("%d", &id);
            printf("Enter User Name: ");
            getchar(); // to consume the newline character left by scanf
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
            printf("Enter User Contact: ");
            fgets(contact, sizeof(contact), stdin);
            contact[strcspn(contact, "\n")] = '\0'; // Remove trailing newline
            addUser(&userList, id, name, contact);
            break;
        case 9:
            printf("Enter User ID to Remove: ");
            scanf("%d", &id);
            removeUser(&userList, id);
            break;
        case 10:
            printf("Enter User ID to Update: ");
            scanf("%d", &id);
            printf("Enter New User Name: ");
            getchar(); // to consume the newline character left by scanf
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
            printf("Enter New User Contact: ");
            fgets(contact, sizeof(contact), stdin);
            contact[strcspn(contact, "\n")] = '\0'; // Remove trailing newline
            updateUser(userList, id, name, contact);
            break;
        case 11:
            printf("Enter User Name to Search: ");
            getchar(); // to consume the newline character left by scanf
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = '\0'; // Remove trailing newline
            User *foundUser = searchUserByName(userList, name);
            if (foundUser)
            {
                printf("ID: %d, Name: %s, Contact: %s\n", foundUser->id, foundUser->name, foundUser->contact);
            }
            else
            {
                printf("No users found with name: %s\n", name);
            }
            break;
        case 12:
            displayUsers(userList);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    // Save all data to files before exiting
    saveBooksToFile(bookList);
    saveUsersToFile(userList);

    return 0;
}

// Functions for Linked List (Books)

void addBook(Book **head, int id, const char *title, const char *author, const char *genre)
{
    if (!isBookIdUnique(*head, id))
    {
        printf("\nError: Book ID %d already exists. Please use a unique ID.\n", id);
        return;
    }

    Book *newBook = (Book *)malloc(sizeof(Book));
    newBook->id = id;
    strcpy(newBook->title, title);
    strcpy(newBook->author, author);
    strcpy(newBook->genre, genre);
    newBook->available = 1;
    newBook->next = *head;
    *head = newBook;

    printf("Book with ID %d added successfully.\n", id);

    // Save to file
    FILE *file = fopen("books.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%d,%s,%s,%s,%d\n", id, title, author, genre, 1);
        fclose(file);
    }
    else
    {
        printf("Error opening file!\n");
    }
}
void removeBook(Book **head, int id)
{
    Book *temp = *head, *prev = NULL;
    if (temp != NULL && temp->id == id)
    {
        *head = temp->next;
        free(temp);
        saveBooksToFile(*head); // Update the file after removal
        return;
    }

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("Book with ID %d not found.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    saveBooksToFile(*head); // Update the file after removal
}

void updateBook(Book *head, int id, const char *newTitle, const char *newAuthor, const char *newGenre)
{
    Book *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            strcpy(current->title, newTitle);
            strcpy(current->author, newAuthor);
            strcpy(current->genre, newGenre);
            saveBooksToFile(head); // Update the file after updating
            break;
        }
        current = current->next;
    }
}

Book *searchBook(Book *head, int id)
{
    Book *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayBooks(Book *head)
{
    Book *current = head;
    printf("Books in library:\n");
    while (current != NULL)
    {
        printf("ID: %d, Title: %s, Author: %s, Genre: %s, Available: %d\n",
               current->id, current->title, current->author, current->genre, current->available);
        current = current->next;
    }
}
//identifiant unique
void saveBooksToFile(Book *head)
{
    FILE *file = fopen("books.txt", "w");
    if (file != NULL)
    {
        Book *current = head;
        while (current != NULL)
        {
            fprintf(file, "%d,%s,%s,%s,%d\n", current->id, current->title, current->author, current->genre, current->available);
            current = current->next;
        }
        fclose(file);
    }
    else
    {
        printf("Error opening file!\n");
    }
}

// Functions for Linked List (Users)
void addUser(User **head, int id, const char *name, const char *contact)
{
    if (!isUserIdUnique(*head, id))
    {
        printf("Error: User ID %d already exists. Please use a unique ID.\n", id);
        return;
    }

    User *newUser = (User *)malloc(sizeof(User));
    newUser->id = id;
    strcpy(newUser->name, name);
    strcpy(newUser->contact, contact);
    newUser->next = *head;
    *head = newUser;

    printf("User with ID %d added successfully.\n", id);

    // Save to file
    FILE *file = fopen("users.txt", "a");
    if (file != NULL)
    {
        fprintf(file, "%d,%s,%s\n", id, name, contact);
        fclose(file);
    }
    else
    {
        printf("Error opening file!\n");
    }
}

void removeUser(User **head, int id)
{
    User *temp = *head, *prev = NULL;
    if (temp != NULL && temp->id == id)
    {
        *head = temp->next;
        free(temp);
        saveUsersToFile(*head); // Update the file after removal
        return;
    }

    while (temp != NULL && temp->id != id)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("User with ID %d not found.\n", id);
        return;
    }

    prev->next = temp->next;
    free(temp);
    saveUsersToFile(*head); // Update the file after removal
}

void updateUser(User *head, int id, const char *newName, const char *newContact)
{
    User *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            strcpy(current->name, newName);
            strcpy(current->contact, newContact);
            saveUsersToFile(head); // Update the file after updating
            break;
        }
        current = current->next;
    }
}

User *searchUserByName(User *head, const char *name)
{
    User *current = head;
    while (current != NULL)
    {
        if (strcasecmp(current->name, name) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void displayUsers(User *head)
{
    User *current = head;
    printf("Users in library:\n");
    while (current != NULL)
    {
        printf("ID: %d, Name: %s, Contact: %s\n",
               current->id, current->name, current->contact);
        current = current->next;
    }
}

void saveUsersToFile(User *head)
{
    FILE *file = fopen("users.txt", "w");
    if (file != NULL)
    {
        User *current = head;
        while (current != NULL)
        {
            fprintf(file, "%d,%s,%s\n", current->id, current->name, current->contact);
            current = current->next;
        }
        fclose(file);
    }
    else
    {
        printf("Error opening file!\n");
    }
}

// Functions for Stack
void push(StackNode **top, int bookId)
{
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->bookId = bookId;
    newNode->next = *top;
    *top = newNode;
}

int pop(StackNode **top)
{
    if (*top == NULL)
    {
        return -1;
    }
    StackNode *temp = *top;
    int bookId = temp->bookId;
    *top = temp->next;
    free(temp);
    return bookId;
}

void displayStack(StackNode *top)
{
    StackNode *current = top;
    printf("Recent Activities (Book IDs):\n");
    while (current != NULL)
    {
        printf("%d\n", current->bookId);
        current = current->next;
    }
}

// Functions for Queue
void enqueue(QueueNode **front, QueueNode **rear, int userId, int bookId)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->userId = userId;
    newNode->bookId = bookId;
    newNode->next = NULL;
    if (*rear == NULL)
    {
        *front = *rear = newNode;
        return;
    }
    (*rear)->next = newNode;
    *rear = newNode;
}

void dequeue(QueueNode **front, QueueNode **rear)
{
    if (*front == NULL)
    {
        return;
    }
    QueueNode *temp = *front;
    *front = (*front)->next;
    if (*front == NULL)
    {
        *rear = NULL;
    }
    free(temp);
}

void displayQueue(QueueNode *front)
{
    QueueNode *current = front;
    printf("Request Queue (User ID, Book ID):\n");
    while (current != NULL)
    {
        printf("User ID: %d, Book ID: %d\n", current->userId, current->bookId);
        current = current->next;
    }
}

// Functions for Binary Search Tree (BST)
void insertBookToBST(TreeNode **root, Book *book)
{
    if (*root == NULL)
    {
        TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
        newNode->book = book;
        newNode->left = newNode->right = NULL;
        *root = newNode;
        return;
    }

    if (strcmp(book->title, (*root)->book->title) < 0)
    {
        insertBookToBST(&(*root)->left, book);
    }
    else
    {
        insertBookToBST(&(*root)->right, book);
    }
}

Book *searchBookInBST(TreeNode *root, const char *title)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (strcmp(title, root->book->title) == 0)
    {
        return root->book;
    }
    else if (strcmp(title, root->book->title) < 0)
    {
        return searchBookInBST(root->left, title);
    }
    else
    {
        return searchBookInBST(root->right, title);
    }
}

void displayBST(TreeNode *root)
{
    if (root != NULL)
    {
        displayBST(root->left);
        printf("ID: %d, Title: %s, Author: %s, Genre: %s, Available: %d\n",
               root->book->id, root->book->title, root->book->author, root->book->genre, root->book->available);
        displayBST(root->right);
    }
}

