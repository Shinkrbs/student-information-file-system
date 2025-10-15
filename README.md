# Simple Student Record Management System (C++)

This is a basic console application written in C++ for managing student records. It allows users to perform fundamental CRUD (Create, Read, Update, Delete) operations on student data, which is stored in `.txt` files.

---

## About The Project

This program provides a command-line interface to handle simple student databases. Each student record contains a student ID, surname, first name, birthdate, and gender. The data is saved in a comma-separated format within text files.


The project was built to demonstrate fundamental C++ concepts, including:
* File I/O with `<fstream>`
* Directory and file management with `<filesystem>`
* Data structuring with `struct`
* Data handling with `std::vector`
* Sorting algorithms with `std::sort`

---

## Features

* **File Management**:
    * Create new `.txt` files to store records.
    * Open and read from existing files.
    * Select an "active file" to work with.
* **Data Management**:
    * **Add**: Append new student records to the list.
    * **Edit**: Modify the details of an existing record.
    * **Delete**: Remove a student record.
    * **Sort**: Arrange records alphabetically by surname.
    * **Save**: Write all changes back to the active `.txt` file.

---

## Getting Started

To compile and run this program locally, you'll need a C++ compiler that supports the C++17 standard (for the `<filesystem>` library).

### Prerequisites

* A modern C++ compiler (like g++, Clang, or MSVC).

### How to Compile and Run

1.  **Update the Directory Path:**
    Before compiling, you **must** change the hardcoded directory path in the `main()` function to a valid path on your own computer.
    ```cpp
    // In main() function
    std::filesystem::path dir = "C:\\Your\\Path\\To\\The\\Files";
    ```

2.  **Compile the Code:**
    Open a terminal or command prompt, navigate to the project directory, and run the following command (using g++ as an example):
    ```sh
    g++ -std=c++17 your_source_file.cpp -o student_manager
    ```
    *(Replace `your_source_file.cpp` with the actual name of your file.)*

3.  **Run the Executable:**
    Once compiled, run the program:
    ```sh
    ./student_manager
    ```
    *(On Windows, you might just run `student_manager.exe`)*

---

## How to Use

When you run the application, you will be presented with the main menu.

1.  **Select a File**: The program will first ask you to select an active file from the directory you specified.
2.  **Main Menu**: Choose an option:
    * `[1] Create New File`: Creates a new, empty `.txt` file in your directory.
    * `[2] Open an Existing File`: Loads the records from the selected active file.
    * `[3] Manage Data`: Opens the data management submenu for the active file.
    * `[4] Exit`: Closes the program.
3.  **Manage Data Submenu**: If you select `[3]`, you can perform operations on the loaded records:
    * `[A]dd`: Prompts you to enter details for a new student.
    * `[E]dit`: Asks for a record number to modify.
    * `[D]elete`: Asks for a record number to remove.
    * `[S]ort`: Sorts all records by surname.
    * `Sa[V]e`: Saves all current data (including additions, edits, and deletions) back to the `.txt` file, overwriting its previous content.
    * `E[X]it`: Returns to the main menu.
