# Library-Management-System-Using-C
This C console-based Library Management System manages books, members, and issue records. It supports adding, updating, deleting books, registering members, issuing and returning books, displaying availability, searching by title or author, and showing member-issued books. Arrays store data, structures organize records, and file handling .
1. Data Structures
- Book → stores ID, title, author, and available quantity.
- Member → stores ID, name, and contact number.
- IssueRecord → stores which book was issued to which member, the issue date, and whether it has been returned.
2. Storage
- Uses arrays with fixed limits:
- books[100]
- members[50]
- issues[200]
- Uses binary files (books.dat, members.dat, issues.dat) for persistence so data is not lost when the program exits.
3. Core Operations
- Add Book / Member → inserts new records into arrays and saves them to file.
- Update Book → modifies book details by searching with ID.
- Delete Book → removes a book by shifting array elements.
- Issue Book → checks if quantity > 0, records issue details, decreases quantity.
- Return Book → marks issue as returned, increases book quantity.
- Display Books → shows all available books with details.
- Show Issued Books (Member) → lists books currently issued to a specific member.
- Search Books → searches by keyword in title or author.
4. File Handling
- Uses fwrite and fread to save/load structures in binary format.
- Ensures data persists across program runs.
5. Menu System
- Console-driven menu with options (1–9, 0 to exit).
- Each choice calls the corresponding function.
