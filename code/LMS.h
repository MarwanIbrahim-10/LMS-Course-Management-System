// LMS.h

#ifndef LMS_H
#define LMS_H

// Header files for standard library and STL containers
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <type_traits>
#include <fstream>
#include <sstream>

// Forward declarations for the classes
class Student;
class Instructor;
class Course;

// Abstract class that serves as a base for entities with identification details (like Student)
class Data {
protected:
    std::string firstName;
    std::string lastName;
    std::string NetID;

public:
    // Pure virtual function to retrieve the ID of an entity
    virtual const std::string& getID() const = 0;
};

// Represents an Instructor with name and employeeID attributes
class Instructor {
private:
    std::string firstName;
    std::string lastName;
    std::string employeeID;

public:
    // Constructor to initialize an Instructor object
    Instructor(const std::string& fName, const std::string& lName, const std::string& empID);


    // Getter methods for Instructor attributes
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getFullName() const;
    std::string getEmployeeID() const;


};

// Represents a Course with various attributes like course code, name, instructor, schedule details, etc.
class Course {
public:
    // Constructor to initialize a Course object
    Course(const std::string& code, const std::string& name, const Instructor& instructor,
           const std::vector<std::string>& daysOfWeek, const std::string& startTime,
           const std::string& endTime, const std::string& description = "");

    // Destructor
    ~Course();

    // Display course information in a structured format
    void DisplayCourseInfo();

    // Setter method to update course description
    void SetDescription(const std::string& description);

    // Getter methods for Course attributes
    const std::string& getCourseName() const;
    const std::string& getCourseCode() const;
    const std::vector<std::string>& getDaysOfWeek() const;
    const std::string& getStartTime() const;
    const std::string& getEndTime() const;
    const std::string& getCourseInstructor() const;
    const std::string& getDescription() const;

private:
    std::string courseCode;
    std::string courseName;
    std::string courseInstructor;
    std::vector<std::string> courseDaysOfWeek;
    std::string courseStartTime;
    std::string courseEndTime;
    std::string courseDescription;
};

// Represents a Student with various attributes and functionality to manage courses
class Student : public Data {
public:
    // Constructor to initialize a Student object
    Student(const std::string& fname, const std::string& lName, int sYear, const std::string& netID);

    // Display student information in a structured format
    void printStudentInfo() const;

    // Override the virtual function from the Data class to provide specific implementation for Student
    const std::string& getID() const override;

    // Check if the student is enrolled in a specific course
    bool isEnrolledIn(const std::string& courseCode) const;

    // Enroll a student in a specific course
    void enrollIn(const std::string& courseCode);

    // Getter methods for Student attributes
    const std::vector<std::string>& getEnrolledCourses() const;
    const std::string& getFirstName() const;
    const std::string& getLastName() const;
    int getYear() const;

    // Drop a student from a specific course
    bool dropCourse(const std::string& courseCode);

private:
    int studentYear;
    std::vector<std::string> enrolledCourseCodes;
};

// Represents the Learning Management System (LMS) with functionality to manage students, instructors, and courses
class LMS {
private:
    std::vector<Student*> students;
    std::vector<Instructor*> instructors;
    std::vector<Course*> courses;

    // Helper function to find a course by its code
    Course* findCourseByCode(const std::string& courseCode) const;

public:
    // Constructor to initialize the LMS object and load data from CSV files
    LMS();

    // Destructor to deallocate memory used by dynamically allocated objects
    ~LMS();

    // Load data from CSV files
    void loadStudentsFromCSV(const std::string& filename);
    void loadInstructorsFromCSV(const std::string& filename);
    void loadCoursesFromCSV(const std::string& filename);

    // Save data to CSV files
    void saveStudentsToCSV(const std::string& filename);
    void saveInstructorsToCSV(const std::string& filename);
    void saveCoursesToCSV(const std::string& filename);

  
    // Add new entities to the system
    void addStudent(const std::string& fname, const std::string& lName, int sYear, const std::string& netID);
    void addInstructor(const std::string& fname, const std::string& lName, const std::string& empid);
    void addCourse(const std::string& code, const std::string& name, Instructor& instructor,
                   const std::vector<std::string>& daysOfWeek, const std::string& startTime,
                   const std::string& endTime, const std::string& description);

    // Helper functions to find entities by their IDs
    Student* findStudentByID(const std::string& id);
    Instructor* findInstructorByID(const std::string& id);
    Course* findCourseByID(const std::string& id);

    // Remove entities from the system
    bool removeStudentByNetID(const std::string& netID);
    bool removeInstructorByEmpID(const std::string& empID);
    bool removeCourseByCode(const std::string& code);

    // Check for scheduling clashes for a student
    bool clashCheck(const Student& student, const Course& newCourse) const;

    // Enroll or drop a student from a course
    void enrollStudent(Student& student, Course& course);
    void dropStudent(const std::string& studentID, const std::string& courseCode);

    // Print the schedule for a student
    void printSchedule(const std::string& studentID);

    // Getter methods to retrieve lists of students, instructors, and courses
    const std::vector<Student*>& getStudents() const;
    const std::vector<Instructor*>& getInstructors() const;
    const std::vector<Course*>& getCourses() const;
};

#endif // LMS_H
