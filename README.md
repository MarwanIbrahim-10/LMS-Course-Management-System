# Learning Management System (LMS)
1. Introduction
The Learning Management System (LMS) is designed to streamline the process of managing students, instructors, and courses in an educational setting. With functionalities ranging from data import/export, management of entities, to schedule handling, the LMS aims to provide a comprehensive solution for academic institutions.

2. System Overview
The LMS system comprises of three primary entities:

'Data': A foundational class.
'Student': Represents the learners.
'Instructor': Symbolizes the teaching staff.
'Course': Each subject or topic offered is an object of this class.
'LMS': The central hub coordinating among all entities.

3. System Components

Following the shown UML Diagram, the structural system of all classes and their relationship can be illustrated:

![LMS_UMl.drawio](images\LMS_UML.drawio.png)

3.1 Student
Attributes:

First Name
Last Name
Year of Study
NetID
Enrolled Courses
Methods:

printStudentInfo(): Displays student's information.
isEnrolledIn(courseCode): Checks if student is enrolled in a particular course.
enrollIn(courseCode): Enrolls student in a course.
dropCourse(courseCode): Removes student from a course.
getEnrolledCourses(): Returns a list of courses the student is enrolled in.

3.2 Instructor
Attributes:

First Name
Last Name
Employee ID
Methods:

getFirstName(): Returns the first name.
getLastName(): Returns the last name.
getFullName(): Returns the full name.
getEmployeeID(): Returns the employee ID.

3.3 Course
Attributes:

Course Code
Course Name
Instructor
Days of the Week
Start Time
End Time
Description
Methods:

DisplayCourseInfo(): Displays detailed information about the course.
SetDescription(description): Sets a description for the course.

3.4 Data (Abstract Class)
Attributes:

First Name
Last Name
NetID
Methods:

getID(): Abstract method to retrieve ID.

3.5 LMS
Attributes:

List of Students
List of Instructors
List of Courses
Methods:

CRUD operations (Create, Read, Update, Delete) for students, instructors, and courses.
Data import/export from/to CSV files.
Schedule handling for students.

4. Functionalities
Loading and Saving Data: The LMS system loads and saves data from/to CSV files.
Managing Students: Add, find, remove, and enroll students. Display a student's schedule.
Managing Instructors: Add, find, and remove instructors.
Managing Courses: Add, find, remove, and assign instructors to courses.

5. Object-Oriented Paradigms

[a]Classes and Objects: Structuring the System
Classes encapsulate data for the object and methods to manipulate that data. In the LMS:

[i]Data: A foundational class.
[ii]Student: Represents the learners.

```c++
Student::Student(const std::string& fname, const std::string& lName, int sYear, const std::string& netID)
        : studentYear(sYear) {
        firstName = fname;
        lastName = lName;
        NetID = netID;
    }
```

[iii]Instructor: Symbolizes the teaching staff.

```c++
Instructor::Instructor(const std::string& fName, const std::string& lName, const std::string& empID)
        : firstName(fName), lastName(lName), employeeID(empID) {}
```

[iv]Course: Each subject or topic offered is an object of this class.

```c++
Course::Course(const std::string& code, const std::string& name, const Instructor& instructor,
               const std::vector<std::string>& daysOfWeek, const std::string& startTime,
               const std::string& endTime, const std::string& description)
    : courseCode(code), courseName(name), courseInstructor(instructor.getEmployeeID()),
      courseDaysOfWeek(daysOfWeek), courseStartTime(startTime), courseEndTime(endTime),
      courseDescription(description) {}
```

[v]LMS: The central hub coordinating among all entities.

```c++
LMS::LMS() {
    ...
    loadStudentsFromCSV("students.csv");
    loadInstructorsFromCSV("instructors.csv");
    loadCoursesFromCSV("courses.csv");
}
```

[b] Encapsulation: Ensuring Data Integrity
The classes use private member variables to store their state and provide public methods to access and modify that state. This ensures data integrity by restricting direct access to an object's attributes.

```c++
class Instructor {
private:
    std::string firstName;
    std::string lastName;
    std::string employeeID;
public:
    std::string getFirstName() const;
    ...
};
```

[c] Inheritance: Reusing and Extending
The power of inheritance is evident where the Student class extends the Data class, thus avoiding redundancy and ensuring a hierarchical structure.

```c++
// Override the virtual function from the Data class
const std::string& Student::getID() const;
```

[d] Polymorphism: The method getID in the Student class is overridden, implying the existence of a virtual function in a base class.
The LMS showcases:
    . Function Overriding: The Student class overrides the getID method.

    ```c++
    const std::string& getID() const override {
    return NetID;
    }
    ```

    . Virtual Functions: The Data class uses a pure virtual function, ensuring adaptability for derived classes.

[e] Association: The Course class has an association with the Instructor class, as it stores the employeeID of the Instructor that's teaching the course.

```c++
class Course {
private:
    std::string courseInstructor;
    ...
};
```

The LMS system's classes are intertwined. The Course class, for instance, associates with Instructor, indicating course instructors.

6.  Incorporating Optimization Techniques

[a] Data Structure Choices: Vector for Efficiency
The use of std::vector in the LMS class for storing lists of students, instructors, and courses ensures that data is stored contiguously, which is beneficial for memory access and search operations.

```c++
std::vector<Student*> students;
std::vector<Instructor*> instructors;
std::vector<Course*> courses;
```

[b] Memory Management: No Leaks Allowed
The destructor in the LMS class ensures that dynamically allocated memory (for students, instructors, and courses) is released, preventing potential memory leaks.

```c++
LMS::~LMS() {
    for (auto student : students) delete student;
    for (auto instructor : instructors) delete instructor;
    for (auto course : courses) delete course;
}
```

[c] Persistence: Storing Data for Continuity
The LMS system persists data across sessions by interfacing with CSV files. This feature is invaluable, ensuring the longevity of data and reflecting changes across sessions.

```c++
void LMS::loadStudentsFromCSV(const std::string& filename);
void LMS::saveStudentsToCSV(const std::string& filename);
```


7. User Guide

  Run the program using the following command
    
    ```console

    g++ main.cpp LMS.cpp -O2 -o LMS 
    ./LMS

    ```
  The program will process all entries from students.csv, courses.csv, and instructors.csv and build the system objects using these data.
  In order to add/remove students and instructors from the system, follow the example in the main.cpp file to add the desired student information - due to currently not having a suitable GUI, using methods from LMS.h should be visible and understanding enough to create your own processes.


8. Conclusion
The LMS provides a comprehensive solution for managing students, instructors, and courses in educational settings. Continuous improvements can make it an invaluable tool for educational administrators. Incorporating object-oriented programming concepts and optimization techniques, the LMS system emerges as a modern, efficient, and scalable solution. Through careful design choices and meticulous implementation, it stands ready to support educational institutions in the digital age.

