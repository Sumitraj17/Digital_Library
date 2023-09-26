# Digital_Library

This is a simple console-based library management system implemented in C. It allows librarians to manage books, track borrowing history, and manage fines for customers. Customers can borrow books, check available books, and view their outstanding fines.

## Features

- **Customer Management**: New customers can be registered, and existing customers can log in using their customer ID or name ID.

- **Book Management**: Librarians can add new books to the library's record, including book titles, authors, IDs, and stock quantities.

- **Borrowing**: Customers can borrow books from the library. The system keeps track of borrowing history.

- **Fines**: Customers are charged fines for overdue books. Fines can be managed and viewed by librarians.

## Usage

1. Compile the code using a C compiler (e.g., GCC).

   ```bash
   gcc library_management.c -o library_management
   ```

2. Run the executable.

   ```bash
   ./library_management
   ```

3. Choose between the "Customer" and "Librarian" options to access different functionalities.

## Customer Functions

- **New Customer**: Register as a new customer by providing your name, contact number, and date of birth. You will receive a customer ID and name ID.

- **Existing Customer**: Log in using your customer ID or name ID. You can then check available books, borrow books, and view outstanding fines.

## Librarian Functions

- **Enter Book in Record**: Librarians can add new books to the library's record, including book titles, authors, IDs, and stock quantities.

- **Borrowing History**: View the borrowing history, including customer names, book names, and borrowing dates.

- **Fine System**: Manage and view outstanding fines for customers. Librarians can add fines to customer accounts.

- **Customers**: View customer data, including names, contact numbers, dates of birth, the number of books borrowed, and outstanding fines.

- **New Customers**: View the list of new customers along with their names, contact numbers, and dates of birth.

## License

This project is open-source and available under the MIT License. Feel free to use, modify, and distribute it as needed.

**Note**: This is a basic implementation and does not cover all aspects of a real-world library management system. It's intended for educational purposes and as a starting point for further development.
