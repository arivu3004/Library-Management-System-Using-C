#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 100
#define MAX_MEMBERS 50
#define MAX_ISSUES 200

typedef struct {
    int id;
    char title[100];
    char author[100];
    int quantity;
} Book;

typedef struct {
    int id;
    char name[100];
    char contact[15];
} Member;

typedef struct {
    int bookId;
    int memberId;
    char issueDate[15];
    int returned; // 0 = not returned, 1 = returned
} IssueRecord;

// Global arrays
Book books[MAX_BOOKS];
Member members[MAX_MEMBERS];
IssueRecord issues[MAX_ISSUES];
int bookCount = 0, memberCount = 0, issueCount = 0;

// ---------- File Handling ----------
void saveBooks() {
    FILE *fp = fopen("books.dat", "wb");
    fwrite(books, sizeof(Book), bookCount, fp);
    fclose(fp);
}

void loadBooks() {
    FILE *fp = fopen("books.dat", "rb");
    if (fp != NULL) {
        bookCount = fread(books, sizeof(Book), MAX_BOOKS, fp);
        fclose(fp);
    }
}

void saveMembers() {
    FILE *fp = fopen("members.dat", "wb");
    fwrite(members, sizeof(Member), memberCount, fp);
    fclose(fp);
}

void loadMembers() {
    FILE *fp = fopen("members.dat", "rb");
    if (fp != NULL) {
        memberCount = fread(members, sizeof(Member), MAX_MEMBERS, fp);
        fclose(fp);
    }
}

void saveIssues() {
    FILE *fp = fopen("issues.dat", "wb");
    fwrite(issues, sizeof(IssueRecord), issueCount, fp);
    fclose(fp);
}

void loadIssues() {
    FILE *fp = fopen("issues.dat", "rb");
    if (fp != NULL) {
        issueCount = fread(issues, sizeof(IssueRecord), MAX_ISSUES, fp);
        fclose(fp);
    }
}

// ---------- Book Functions ----------
void addBook() {
    if (bookCount >= MAX_BOOKS) {
        printf("Book storage full!\n");
        return;
    }
    Book b;
    printf("Enter Book ID: "); scanf("%d", &b.id);
    printf("Enter Title: "); scanf(" %[^\n]", b.title);
    printf("Enter Author: "); scanf(" %[^\n]", b.author);
    printf("Enter Quantity: "); scanf("%d", &b.quantity);

    books[bookCount++] = b;
    saveBooks();
    printf("Book added successfully!\n");
}

void updateBook() {
    int id;
    printf("Enter Book ID to update: "); scanf("%d", &id);
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            printf("Enter new Title: "); scanf(" %[^\n]", books[i].title);
            printf("Enter new Author: "); scanf(" %[^\n]", books[i].author);
            printf("Enter new Quantity: "); scanf("%d", &books[i].quantity);
            saveBooks();
            printf("Book updated!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

void deleteBook() {
    int id;
    printf("Enter Book ID to delete: "); scanf("%d", &id);
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id) {
            for (int j = i; j < bookCount - 1; j++) {
                books[j] = books[j + 1];
            }
            bookCount--;
            saveBooks();
            printf("Book deleted!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

void displayBooks() {
    printf("\n--- Available Books ---\n");
    for (int i = 0; i < bookCount; i++) {
        printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",
               books[i].id, books[i].title, books[i].author, books[i].quantity);
    }
}

// ---------- Member Functions ----------
void addMember() {
    if (memberCount >= MAX_MEMBERS) {
        printf("Member storage full!\n");
        return;
    }
    Member m;
    printf("Enter Member ID: "); scanf("%d", &m.id);
    printf("Enter Name: "); scanf(" %[^\n]", m.name);
    printf("Enter Contact: "); scanf("%s", m.contact);

    members[memberCount++] = m;
    saveMembers();
    printf("Member added successfully!\n");
}

// ---------- Issue/Return Functions ----------
void issueBook() {
    int bookId, memberId;
    char date[15];
    printf("Enter Book ID: "); scanf("%d", &bookId);
    printf("Enter Member ID: "); scanf("%d", &memberId);

    // Check book availability
    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == bookId) {
            if (books[i].quantity <= 0) {
                printf("Book not available!\n");
                return;
            }
            printf("Enter Issue Date (DD/MM/YYYY): "); scanf("%s", date);
            IssueRecord ir = {bookId, memberId, "", 0};
            strcpy(ir.issueDate, date);
            issues[issueCount++] = ir;
            books[i].quantity--;
            saveIssues();
            saveBooks();
            printf("Book issued successfully!\n");
            return;
        }
    }
    printf("Book not found!\n");
}

void returnBook() {
    int bookId, memberId;
    printf("Enter Book ID: "); scanf("%d", &bookId);
    printf("Enter Member ID: "); scanf("%d", &memberId);

    for (int i = 0; i < issueCount; i++) {
        if (issues[i].bookId == bookId && issues[i].memberId == memberId && issues[i].returned == 0) {
            issues[i].returned = 1;
            for (int j = 0; j < bookCount; j++) {
                if (books[j].id == bookId) {
                    books[j].quantity++;
                    break;
                }
            }
            saveIssues();
            saveBooks();
            printf("Book returned successfully!\n");
            return;
        }
    }
    printf("No matching issue record found!\n");
}

void showIssuedBooks() {
    int memberId;
    printf("Enter Member ID: "); scanf("%d", &memberId);
    printf("\n--- Books Issued to Member %d ---\n", memberId);
    for (int i = 0; i < issueCount; i++) {
        if (issues[i].memberId == memberId && issues[i].returned == 0) {
            printf("Book ID: %d | Issue Date: %s\n", issues[i].bookId, issues[i].issueDate);
        }
    }
}

// ---------- Search ----------
void searchBooks() {
    char keyword[100];
    printf("Enter keyword (title/author): ");
    scanf(" %[^\n]", keyword);

    printf("\n--- Search Results ---\n");
    for (int i = 0; i < bookCount; i++) {
        if (strstr(books[i].title, keyword) || strstr(books[i].author, keyword)) {
            printf("ID: %d | Title: %s | Author: %s | Quantity: %d\n",
                   books[i].id, books[i].title, books[i].author, books[i].quantity);
        }
    }
}

// ---------- Main Menu ----------
int main() {
    loadBooks();
    loadMembers();
    loadIssues();

    int choice;
    do {
        printf("\n--- Library Management System ---\n");
        printf("1. Add Book\n2. Update Book\n3. Delete Book\n4. Add Member\n");
        printf("5. Issue Book\n6. Return Book\n7. Display Books\n");
        printf("8. Show Issued Books (Member)\n9. Search Books\n0. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1: addBook(); break;
            case 2: updateBook(); break;
            case 3: deleteBook(); break;
            case 4: addMember(); break;
            case 5: issueBook(); break;
            case 6: returnBook(); break;
            case 7: displayBooks(); break;
            case 8: showIssuedBooks(); break;
            case 9: searchBooks(); break;
            case 0: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while(choice != 0);

    return 0;
}