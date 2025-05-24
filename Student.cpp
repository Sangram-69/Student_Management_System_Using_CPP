#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>


// Define the Student class
class Student {
private:
    std::string rollNumber;
    std::string name;
    std::string address;
    std::string contactNumber;

public:
    // Constructor
    Student(const std::string& rollNumber, const std::string& name, const std::string& address, const std::string& contactNumber)
        : rollNumber(rollNumber), name(name), address(address), contactNumber(contactNumber) {}

    // Getter methods
    std::string getRollNumber() const { return rollNumber; }
    std::string getName() const { return name; }
    std::string getAddress() const { return address; }
    std::string getContactNumber() const { return contactNumber; }

    // Setter methods
    void setAddress(const std::string& newAddress) { address = newAddress; }
    void setContactNumber(const std::string& newContactNumber) { contactNumber = newContactNumber; }

    // Display student information
    void display() const {
        std::cout << "Roll Number: " << rollNumber << std::endl;
        std::cout << "Name: " << name << std::endl;
        std::cout << "Address: " << address << std::endl;
        std::cout << "Contact Number: " << contactNumber << std::endl;
    }
};

// Function to add a new student
void addStudent(std::vector<Student>& students) {
    std::string rollNumber, name, address, contactNumber;
    std::cout << "Enter Roll Number: ";
    std::cin >> rollNumber;
    std::cout << "Enter Name: ";
    std::cin >> name;
    std::cout << "Enter Address: ";
    std::cin>> address;
    std::cout << "Enter Contact Number: ";
    std::cin >> contactNumber;

    // Create a new Student object
    Student newStudent(rollNumber, name, address, contactNumber);

    // Add the student to the vector
    students.push_back(newStudent);

    std::cout << "Student added successfully!" << std::endl;
}

// Function to update student information
void updateStudent(std::vector<Student>& students) {
    std::string rollNumber;
    std::cout << "Enter Roll Number of the student to update: ";
    std::cin >> rollNumber;

    // Find the student in the vector based on the roll number
    auto it = std::find_if(students.begin(), students.end(), [&](const Student& student) {
        return student.getRollNumber() == rollNumber;
    });

    if (it != students.end()) {
        std::string newAddress, newContactNumber;
        std::cout << "Enter new Address: ";
        std::cin.ignore();  // Ignore any leftover newline characters
        std::getline(std::cin, newAddress);
        std::cout << "Enter new Contact Number: ";
        std::cin >> newContactNumber;

        // Update the student information
        it->setAddress(newAddress);
        it->setContactNumber(newContactNumber);

        std::cout << "Student information updated successfully!" << std::endl;
    } else {
        std::cout << "Student not found!" << std::endl;
    }
}

// Function to delete a student
void deleteStudent(std::vector<Student>& students) {
    std::string rollNumber;
    std::cout << "Enter Roll Number of the student to delete: ";
    std::cin >> rollNumber;

    // Find the student in the vector based on the roll number
    auto it = std::find_if(students.begin(), students.end(), [&](const Student& student) {
        return student.getRollNumber() == rollNumber;
    });

    if (it != students.end()) {
        // Erase the student from the vector
        students.erase(it);
        std::cout << "Student deleted successfully!" << std::endl;
    } else {
        std::cout << "Student not found!" << std::endl;
    }
}

// Function to search for a student
void searchStudent(const std::vector<Student>& students) {
    std::string searchQuery;
    std::cout << "Enter Roll Number or Name to search: ";
    std::cin >> searchQuery;

    // Find the students matching the search query
    std::vector<Student> matchedStudents;
    for (const auto& student : students) {
        if (student.getRollNumber() == searchQuery || student.getName() == searchQuery) {
            matchedStudents.push_back(student);
        }
    }

    if (!matchedStudents.empty()) {
        std::cout << "Found " << matchedStudents.size() << " student(s) matching the search query:" << std::endl;
        for (const auto& student : matchedStudents) {
            student.display();
            std::cout << std::endl;
        }
    } else {
        std::cout << "No students found!" << std::endl;
    }
}

// Function to display all students
void displayAllStudents(const std::vector<Student>& students) {
    if (students.empty()) {
        std::cout << "No students found!" << std::endl;
        return;
    }

    std::cout << "Displaying all students:" << std::endl;
    for (const auto& student : students) {
        student.display();
        std::cout << std::endl;
    }
}

// Function to save student records to a file
void saveToFile(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream outputFile(filename);
    if (outputFile.is_open()) {
        for (const auto& student : students) {
            outputFile << student.getRollNumber() << ","
                       << student.getName() << ","
                       << student.getAddress() << ","
                       << student.getContactNumber() << "\n";
        }
        outputFile.close();
        std::cout << "Student records saved to file: " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

// Function to load student records from a file
void loadFromFile(std::vector<Student>& students, const std::string& filename) {
    std::ifstream inputFile(filename);
    if (inputFile.is_open()) {
        students.clear();  // Clear existing student records

        std::string line;
        while (std::getline(inputFile, line)) {
            std::stringstream ss(line);
            std::string rollNumber, name, address, contactNumber;

            std::getline(ss, rollNumber, ',');
            std::getline(ss, name, ',');
            std::getline(ss, address, ',');
            std::getline(ss, contactNumber, ',');

            Student student(rollNumber, name, address, contactNumber);
            students.push_back(student);
        }
        inputFile.close();
        std::cout << "Student records loaded from file: " << filename << std::endl;
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
}

int main() {
    std::vector<Student> students;

    // Load student records from a file (optional)
    // loadFromFile(students, "student_records.txt");

    int choice;
    do {
        std::cout << "----- Student Management System -----" << std::endl;
        std::cout << "1. Add Student" << std::endl;
        std::cout << "2. Update Student" << std::endl;
        std::cout << "3. Delete Student" << std::endl;
        std::cout << "4. Search Student" << std::endl;
        std::cout << "5. Display All Students" << std::endl;
        std::cout << "6. Save to File" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                updateStudent(students);
                break;
            case 3:
                deleteStudent(students);
                break;
            case 4:
                searchStudent(students);
                break;
            case 5:
                displayAllStudents(students);
                break;
            case 6:
                saveToFile(students, "student_records.txt");
                break;
            case 7:
                std::cout << "Exiting..." << std::endl;
                break;
            default:
                std::cout << "Invalid choice! Please try again." << std::endl;
                break;
        }

        std::cout << std::endl;
    } while (choice != 7);

    return 0;
}
