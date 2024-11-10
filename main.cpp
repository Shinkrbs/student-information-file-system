#include <iostream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <string>
#include <algorithm>

// Problems:
    // find a way to increment the record number per new data //Fixed
    // find a way to make edit function "functional" //Fixed
    // fix add data function wherein the input should be checked if valid or not // Too advanced?
    // fix problem in displaying data afteer a certain function is finished running // Fixed
    // fix bug wherein rec_ctr does not go back to 0 when program is in a loop// Fixed
    // Make a feature wherein every new function is called the screen is cleared // Done
    // Make a function for running the program // Done

struct student
{
    std::string studentId;
    std::string surname;
    std::string firstname;
    std::string birthdate;
    std::string gender;
};
// Main Run Function
void run_program(std::filesystem::path dir, std::string file_name, std::vector <student> &student_vector, int rec_ctr, const int width);
// Outer Functions
const std::string active_file(std::filesystem::path dir);
const int display_vector(std::string file_name, std::vector <student> &student_vector, int rec_ctr, const int width);
// Main Functions
void display_files(std::filesystem::path dir);
void create_file(std::filesystem::path dir);
void open_exfile(std::filesystem::path dir, std::string file_name, std::vector <student> &student_vector, int rec_ctr, const int width);
void delete_file(std::filesystem::path dir);
void manage_data(std::string file_name, std::filesystem::path dir, std::vector <student> &student_vector, int rec_ctr, const int width);
// Within Manage Data Functions
void add_data(int rec_ctr, std::vector <student> &student_vector);
void read_data(std::filesystem::path dir, std::string file_name, std::vector <student> &student_vector);
void edit_data(std::vector <student> &student_vector);
void delete_data(std::vector <student> &student_vector);
void sort_data(std::vector <student> &student_vector);
void save_data(std::filesystem::path dir, std::string file_name, std::vector <student> &student_vector);

int main()
{
    // Directory Path of Text Files
    std::filesystem::path dir = "C:\\Users\\shin\\Documents\\BSCS 2nd Year\\Fundamentals of Database Systems\\Exercise One";
    std::string file_name = active_file(dir);
    //Main Student Vector
    std::vector <student> student_vector;
    // Record Counter
    int rec_ctr = 1;
    // Set Width
    const int width = 12;
    // Main Run Function for Application
    run_program(dir, file_name, student_vector, rec_ctr, width);
    return 0;
}

void run_program(std::filesystem::path dir, std::string file_name, std::vector <student> &student_vector, int rec_ctr, const int width)
{
    int choice;
    while(choice != 4)
    {
        std::cout << std::endl << "Active File: [" << file_name << "]" << std::endl;
        std::cout << "------------------------------------------------------------------------------" << std::endl;
        std::cout << "[1] Create New File" << std::setw(width + 15) << " [2] Open an Existing File" << 
            std::setw(width + 5) << " [3] Manage Data" << std::setw(width - 2) <<  " [4] Exit" << std::endl;
        std::cout << "------------------------------------------------------------------------------" << std::endl; 
        std::cout << "Input Choice: ";
        std::cin >> choice;

        switch (choice)
        {
        case 1:
            std::system("cls");
            create_file(dir);
            break;
        case 2:
            std::system("cls");
            open_exfile(dir, file_name, student_vector, rec_ctr, width);
            break;
        case 3:
            std::system("cls");
            manage_data(file_name, dir, student_vector, rec_ctr, width);
            break;
        case 4:
            std::system("cls");
            std::cout << "Program Closed Successfully!" << std::endl;
            std::cout << "------------------------------------------------------------------------------";
            break;
        default:
            std::system("cls");
            std::cout << "Invalid Input Please Try Again." << std::endl;
            std::cout << "------------------------------------------------------------------------------";
            break;
        }
    }
}

const std::string active_file(std::filesystem::path dir)
{
    display_files(dir);
    std::string file_name = "";

    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Select File: ";
    std::cin >> file_name;
    
    //Constructs full directory path of file
    std::filesystem::path file_path = dir / file_name;
    // Checker if file is in directory or not
    if(std::filesystem::exists(file_path) && std::filesystem::is_regular_file(file_path))
    {
        std::system("cls");
        std::cout << "File Selected!" << std::endl;
        return file_name;
    }
    else
    {
        std::cout << "File Not Found in Directory." << std::endl;
        return "";
    }
}
// Displays the Contents of the Student Vector
const int display_vector(std::string file_name, std::vector <student> &student_vector, int rec_ctr, const int width)
{
    std::cout << std::endl << "Active File: [" << file_name << "]";
    std::cout << std::endl << "------------------------------------------------------------------------------" << std::endl;
    std::cout << std::setw(width) << "Rec" << std::setw(width) << "Student Id" << std::setw(width) << "Surname"
        << std::setw(width) << "Firstname" << std::setw(width) << "Birth Date" << std::setw(width) << "Sex" << std::endl;
    std::cout << "------------------------------------------------------------------------------" << std::endl;

    for (const auto &student : student_vector)
    {
        std::cout << std::setw(width) << rec_ctr << std::setw(width) << student.studentId << std::setw(width) << student.surname
            << std::setw(width) << student.firstname << std::setw(width) << student.birthdate << std::setw(width) << student.gender << std::endl;
        rec_ctr++;
    }
    std::cout << "------------------------------------------------------------------------------" << std::endl;
    return rec_ctr;
}
//Finds the directory of the file and displays the file
void display_files(std::filesystem::path dir)
{
    std::cout << "Files: " << std::endl;
    std::cout << "-------------------------------------------" << std::endl;
    // Iterate through the directory
    for(const auto& entry : std::filesystem::directory_iterator(dir))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") 
            std::cout << "[" <<  entry.path().filename().string() << "]" << std::endl;
    }
}

void create_file(std::filesystem::path dir)
{
    // Asks for name of file
    std::string file_name = "";
    std::cout << "-------------------------------------------" << std::endl;
    std::cout << "Input Name of File (include .txt): ";
    std::cin >> file_name;

    // Adds name of file to directory and make file in the directory
    std::filesystem::path file_path = dir / file_name;
    std::ofstream file(file_path);

    // Checker if file is succesfully made or not
    if(file.is_open())
    {
        std::cout << "File created successfully!\n" << std::endl;
        file.close();
    }
    else
        std::cout << "Unable to create file.\n" << std::endl;
}

void open_exfile(std::filesystem::path dir, std::string file_name, std::vector <student> &student_vector, int rec_ctr, const int width)
{
    // Clear Vector to Avoid Duplication
    student_vector.clear();
    read_data(dir, file_name, student_vector);
    display_vector(file_name, student_vector, 1, width);
}

void delete_file(std::filesystem::path dir)
{
    // Asks for name of file
    std::string file_name = "";
    std::cout << "\nInput File to Delete: ";
    std::cin >> file_name;
     
    // Construct full path of file
    std::filesystem::path file_path = dir / file_name;

    // Delete the file
    if(std::filesystem::remove(file_path))
        std::cout << "File deleted succesfully!\n" << std::endl;
    else
        std::cout << "File not found/Unable to delete file.\n" << std::endl;
}

void manage_data(std::string file_name, std::filesystem::path dir, std::vector <student> &student_vector, int rec_ctr, const int width)
{
    char selection = ' ';

    open_exfile(dir, file_name, student_vector, rec_ctr, width);

    //Update Record Counter
    rec_ctr =  student_vector.size() + 1;

    while (selection != 'X' && selection != 'x') // Loop until the user chooses to exit
    {
        std::cout << "[A]dd" << std::setw(width) << "[E]dit" << std::setw(width) << "[D]elete" << std::setw(width)
                  << "[S]ort" << std::setw(width) << "Sa[V]e" << std::setw(width) << "E[X]it" << std::endl;
        std::cout << "Input Selection: ";
        std::cin >> selection;
 
        std::system("cls"); 

        switch (selection)
        {
        case 'A': case 'a':
            add_data(rec_ctr, student_vector);
            rec_ctr = student_vector.size() + 1; // Update the record counter
            display_vector(file_name, student_vector, rec_ctr = 1, width); // Ensures That Every Display Rec# Will Start at One
            break;

        case 'E': case 'e':
            display_vector(file_name, student_vector, rec_ctr = 1, width);
            edit_data(student_vector);
            rec_ctr = 1;
            display_vector(file_name, student_vector, rec_ctr = 1, width);
            break;

        case 'D': case 'd':
            display_vector(file_name, student_vector, rec_ctr, width);
            delete_data(student_vector);
            rec_ctr = 1;
            display_vector(file_name, student_vector, rec_ctr, width);
            break;

        case 'S': case 's':
            sort_data(student_vector);
            rec_ctr = 1;
            display_vector(file_name, student_vector, rec_ctr, width);
            break;

        case 'V': case 'v':
            save_data(dir, file_name, student_vector);
            rec_ctr = 1;
            open_exfile(dir, file_name, student_vector, rec_ctr, width);
            break;

        case 'X': case 'x':
            break;

        default:
            std::cout << "Invalid Selection. Please Try Again." << std::endl;
            display_vector(file_name, student_vector, rec_ctr, width);
            break;
        }
    }
}
// Within Manage Data Functions

// Ask User for Information
void add_data(int rec_ctr, std::vector <student> &student_vector)
{
    student temp_stud;
    
    std::cout << "\nRec[" << rec_ctr << "]" << std::endl;
    
    do {
        std::cout << "Student ID: ";
        std::cin >> temp_stud.studentId;
        if (temp_stud.studentId.empty())
            std::cout << "Student ID cannot be empty. Please enter a valid Student ID.\n";
    } while (temp_stud.studentId.empty());

    do {
        std::cout << "Surname: ";
        std::cin >> temp_stud.surname;
        if (temp_stud.surname.empty())
            std::cout << "Surname cannot be empty. Please enter a valid Surname.\n";
    } while (temp_stud.surname.empty());

    do {
        std::cout << "Firstname: ";
        std::cin >> temp_stud.firstname;
        if (temp_stud.firstname.empty())
            std::cout << "Firstname cannot be empty. Please enter a valid Firstname.\n";
    } while (temp_stud.firstname.empty());

    do {
        std::cout << "Birthdate (MM-DD-YY): ";
        std::cin >> temp_stud.birthdate;
        if (temp_stud.birthdate.empty())
            std::cout << "Birthdate cannot be empty. Please enter a valid Birthdate.\n";
        // Add more validation for date format if necessary
    } while (temp_stud.birthdate.empty());

    do {
        std::cout << "Sex (Male/Female): ";
        std::cin >> temp_stud.gender;
        if (temp_stud.gender != "Male" && temp_stud.gender != "Female")
            std::cout << "Invalid input. Please enter 'M' for Male or 'F' for Female.\n";
    } while (temp_stud.gender != "Male" && temp_stud.gender != "Female");

    student_vector.push_back(temp_stud); 
    std::cout << "Added the Information Successfully!\n";
}
// Reads the data from the file // For checking 
void read_data(std::filesystem::path dir, std::string file_name, std::vector <student> &student_vector)
{
    std::filesystem::path file_path = dir / file_name;
    // Read the Contents of the File
    std::ifstream file(file_path);
    if(file.is_open())
    {
        // Extracts Data in File Line by Line
        student temp_student;
        std::string line;

        while (std::getline(file, line))
        {
            std::istringstream iss(line);

            if (std::getline(iss, temp_student.studentId, ','))
                if (std::getline(iss, temp_student.surname, ','))
                    if (std::getline(iss, temp_student.firstname, ','))
                        if (std::getline(iss, temp_student.birthdate, ','))
                            if (std::getline(iss, temp_student.gender, ','))
                                // Rmmove Later
                                student_vector.push_back(temp_student);
        }
        //std::cout << "Successfully Read the Data!"; // For Debug Purposes:}
        file.close();
    }
    else
        std::cout << "Unable to Open File.";
}
// Edit Data from the File
void edit_data(std::vector <student> &student_vector)
{
    int recfor_edit = 0;
    bool decision = true;
    std::cout << "Input Record Number to Edit: ";
    std::cin >> recfor_edit;

    recfor_edit -= 1;
    student& temp_student = student_vector.at(recfor_edit); // Reference to the student

    std::cout << "\nRec[" << recfor_edit + 1 << "]" << std::endl;

    std::cout << "Student ID [" << temp_student.studentId << "]: ";
    std::string input;
    std::getline(std::cin >> std::ws, input);
    if (!input.empty()) 
        temp_student.studentId = input;
    else
        decision = false;

    std::cout << "Surname [" << temp_student.surname << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
        temp_student.surname = input;
    else
        decision = false;

    std::cout << "Firstname [" << temp_student.firstname << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
        temp_student.firstname = input;
    else
        decision = false;

    std::cout << "Birthdate (MM-DD-YY) [" << temp_student.birthdate << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
        temp_student.birthdate = input;
    else
        decision = false;

    std::cout << "Sex (Male/Female) [" << temp_student.gender << "]: ";
    std::getline(std::cin, input);
    if (!input.empty()) 
        temp_student.gender = input;
    else
        decision = false;

    if(decision)
        std::cout << "Edited Successfully!\n";
    else    
        std::cout << "Unable to Edit\n";
}
// Delete a data from vector
void delete_data(std::vector <student> &student_vector)
{
    // Check First if Vector is Empty
    if(student_vector.empty())
    {
        std::cout << "No Records to Delete\n";
        return;
    }

    int indexTo_delete;
    std::cout << "Input Record Number to Delete: ";\
    std::cin >> indexTo_delete;

    // Delete Data From Vector
    if(indexTo_delete >= 0 && indexTo_delete < student_vector.size())
    {
        student_vector.erase(student_vector.begin() + indexTo_delete - 1);
        std::cout << "Record Deleted Succesfully\n";
    }
    else
        std::cout << "Invalid Input.\n";
}
// Sort the Data in Alphabetical Order by Surname
void sort_data(std::vector <student> &student_vector)
{
    std::sort(student_vector.begin(), student_vector.end(), [](const student &a, const student &b) 
    {
        if (a.surname == b.surname)
            return a.firstname < b.firstname;
        return a.surname < b.surname;
    });
    std::cout << "Sorted Successfully!\n";
}

void save_data(std::filesystem::path dir, std::string file_name, std::vector <student> &student_vector)
{
    // Create Full Path of File
    std::filesystem::path file_path = dir / file_name;

    // Open The File and Append the data
    std::ofstream file(file_path);

    // Check if File is Open and Add Data to the File
    if(file.is_open())
    {
        for (const auto& student : student_vector)
        {
            file << student.studentId << "," 
                 << student.surname << ","
                 << student.firstname << "," 
                 << student.birthdate << "," 
                 << student.gender << "\n";
        }
        file.close();
        std::cout << "Data Saved Successfully!\n";
    }
    else
        std::cout << "Unable to Save Information to File.\n";
}
