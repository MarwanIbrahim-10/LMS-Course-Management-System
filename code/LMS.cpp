#include "LMS.h"


Instructor::Instructor(const std::string& fName, const std::string& lName, const std::string& empID)
        : firstName(fName), lastName(lName), employeeID(empID) {}

std::string Instructor::getFirstName() const {
    return firstName;
}

std::string Instructor::getLastName() const {
    return lastName;
}

std::string Instructor::getFullName() const {
    return firstName + " " + lastName;
}

std::string Instructor::getEmployeeID() const {
    return employeeID;
}




Course::Course(const std::string& code, const std::string& name, const Instructor& instructor,
               const std::vector<std::string>& daysOfWeek, const std::string& startTime,
               const std::string& endTime, const std::string& description)
    : courseCode(code), courseName(name), courseInstructor(instructor.getEmployeeID()),
      courseDaysOfWeek(daysOfWeek), courseStartTime(startTime), courseEndTime(endTime),
      courseDescription(description) {
}

Course::~Course() {}

// Display course information in a structured format
void Course::DisplayCourseInfo() {
        std::cout << "Course Code: " << courseCode << std::endl;
        std::cout << "Course Name: " << courseName << std::endl;
        std::cout << "Instructor: " << courseInstructor << std::endl;
        std::cout << "Days of the Week: ";
        for (const std::string& day : courseDaysOfWeek) {
            std::cout << day << " ";
        }
        std::cout << std::endl;
        std::cout << "Start Time: " << courseStartTime << std::endl;
        std::cout << "End Time: " << courseEndTime << std::endl;
        std::cout << "Description: " << courseDescription << std::endl;
    }


// Setter method to update course description
void Course::SetDescription(const std::string& description) {
        courseDescription = description;
    }


// Getter methods for Course attributes
const std::string& Course::getCourseName() const {
        return courseName;
    }

const std::string& Course::getCourseCode() const {
        return courseCode;
    }

const std::vector<std::string>& Course::getDaysOfWeek() const {
        return courseDaysOfWeek;
    }

const std::string& Course::getStartTime() const {
        return courseStartTime;
    }

const std::string& Course::getEndTime() const {
        return courseEndTime;
    }

const std::string& Course::getCourseInstructor() const {
        return courseInstructor;
    }

const std::string& Course::getDescription() const {
        return courseDescription;
    }

// Constructor to initialize a Student object
Student::Student(const std::string& fname, const std::string& lName, int sYear, const std::string& netID)
        : studentYear(sYear) {
        firstName = fname;
        lastName = lName;
        NetID = netID;
    }

// Display student information in a structured format
void Student::printStudentInfo() const {
        std::cout << "First Name: " << firstName << std::endl;
        std::cout << "Last Name: " << lastName << std::endl;
        std::cout << "NetID: " << NetID << std::endl;
    }

// Override the virtual function from the Data class to provide specific implementation for Student
const std::string& Student::getID() const  {   
    return NetID;
}

// Check if the student is enrolled in a specific course
bool Student::isEnrolledIn(const std::string& courseCode) const {
        return std::find(enrolledCourseCodes.begin(), enrolledCourseCodes.end(), courseCode) != enrolledCourseCodes.end();
    }

// Enroll a student in a specific course
void Student::enrollIn(const std::string& courseCode) {
        enrolledCourseCodes.push_back(courseCode);
        std::cout << "Enrollment in course Success" << std::endl;
    }

// Getter methods for Student attributes
const std::vector<std::string>& Student::getEnrolledCourses() const {
        return enrolledCourseCodes;
    }

const std::string& Student::getFirstName() const {
        return firstName;
    }

const std::string& Student::getLastName() const {
        return lastName;
    }

int Student::getYear() const {
        return studentYear;
    }

// Drop a student from a specific course
bool Student::dropCourse(const std::string& courseCode) {
        auto courseIt = std::find(enrolledCourseCodes.begin(), enrolledCourseCodes.end(), courseCode);
        if (courseIt != enrolledCourseCodes.end()) {
            enrolledCourseCodes.erase(courseIt);
            return true;  
        }
        return false; 
    }

Course* LMS::findCourseByCode(const std::string& courseCode) const {
    auto it = std::find_if(courses.begin(), courses.end(), [&courseCode](Course* course) {
        return course->getCourseCode() == courseCode;
    });

    return it != courses.end() ? *it : nullptr;
}


LMS::LMS() {
        students.reserve(20); 
        instructors.reserve(20);
        courses.reserve(20);

        //std::cout << "Before loading students from CSV" << std::endl;
        loadStudentsFromCSV("students.csv");
        //std::cout << "After loading students from CSV" << std::endl;

       // std::cout << "Before loading instructors from CSV" << std::endl;
        loadInstructorsFromCSV("instructors.csv");
        //std::cout << "After loading instructors from CSV" << std::endl;

       // std::cout << "Before loading courses from CSV" << std::endl;
        loadCoursesFromCSV("courses.csv");
        //std::cout << "After loading courses from CSV" << std::endl;
    }

    // Destructor to deallocate memory used by dynamically allocated objects
LMS::~LMS() {
        for (auto student : students) delete student;
        for (auto instructor : instructors) delete instructor;
        for (auto course : courses) delete course;
    }

    // Load data from CSV files
void LMS::loadStudentsFromCSV(const std::string& filename) {
        std::ifstream file(filename);
        std::string line, token;
        std::getline(file, line);  // Skip the header line

        while (std::getline(file, line)) {
            std::istringstream ss(line);
            std::vector<std::string> tokens;

            while (std::getline(ss, token, ',')) {
                tokens.push_back(token);
            }

            Student* newStudent = new Student(tokens[0], tokens[1], std::stoi(tokens[2]), tokens[3]);
            students.push_back(newStudent);
        }
    }

void LMS::loadInstructorsFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, token;
    std::getline(file, line);  // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        Instructor* newInstructor = new Instructor(tokens[0], tokens[1], tokens[2]);
        instructors.push_back(newInstructor);
        }
    }



void LMS::loadCoursesFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line, token;
    std::getline(file, line);  // Skip the header line

    while (std::getline(file, line)) {
        std::istringstream ss(line);
        std::vector<std::string> tokens;

        while (std::getline(ss, token, ',')) {
            tokens.push_back(token);
        }

        if (tokens.size() != 7) {
            // Ensure that there are 7 fields in the CSV line
            std::cerr << "Invalid CSV line: " << line << std::endl;
            continue;
        }

        // Extract and assign values to variables
        std::string code = tokens[0];
        std::string name = tokens[1];
        std::string instructorEmpID = tokens[2];

        // Parse the days of the week
        std::string daysOfWeekStr = tokens[3];
        std::istringstream daysStream(daysOfWeekStr);
        std::vector<std::string> daysOfWeek;
        while (std::getline(daysStream, token, '&')) {
            daysOfWeek.push_back(token);
        }

        std::string startTime = tokens[4];
        std::string endTime = tokens[5];

        // Remove quotes from the description
        std::string description = tokens[6];
        description = description.substr(1, description.size() - 2);

        Instructor* instructor = findInstructorByID(instructorEmpID);
        if (!instructor) {
            std::cerr << "Instructor with Employee ID " << instructorEmpID << " not found. Skipping course " << code << std::endl;
            continue;
        }

        // Create and add the course with the extracted values
        Course* newCourse = new Course(code, name, *instructor, daysOfWeek, startTime, endTime, description);
        courses.push_back(newCourse);
    }
}



// Save data to CSV files
void LMS::saveStudentsToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << " for writing." << std::endl;
        return;
    }

    file << "FirstName,LastName,Year,NetID\n";
    for (const auto& student : students) {
        file << student->getFirstName() << "," << student->getLastName() << "," << student->getYear() << "," << student->getID() << "\n";
    }
}

void LMS::saveInstructorsToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << " for writing." << std::endl;
        return;
    }

    file << "FirstName,LastName,EmployeeID,NetID\n";
    for (const auto& instructor : instructors) {
        file << instructor->getFirstName() << "," << instructor->getLastName() << "," << instructor->getEmployeeID() << "," << instructor->getEmployeeID() << "\n";
    }
}

void LMS::saveCoursesToCSV(const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening " << filename << " for writing." << std::endl;
        return;
    }

    file << "CourseCode,CourseName,InstructorEmpID,DaysOfWeek,StartTime,EndTime,Description\n";
    for (const auto& course : courses) {
        file << course->getCourseCode() << "," 
             << course->getCourseName() << "," 
             << course->getCourseInstructor() << ",";

        // This loop writes the days of the week
        for (size_t i = 0; i < course->getDaysOfWeek().size(); ++i) {
            file << course->getDaysOfWeek()[i];
            if (i != course->getDaysOfWeek().size() - 1) {
                file << ",";
            }
        }
        file << "," << course->getStartTime() 
             << "," << course->getEndTime() 
             << "," << course->getDescription() << "\n";
    }
}


// Add new entities to the system
void LMS::addStudent(const std::string& fname, const std::string& lName, int sYear, const std::string& netID) {
    // Check if a student with the same NetID already exists
    for (Student* existingStudent : students) {
        if (existingStudent->getID() == netID) {
            // You can choose to update the existing student's information here if needed
            std::cout << "A student with NetID " << netID << " already exists." << std::endl;
            return;
        }
    }

    // If no existing student found with the same NetID, add the new student
    Student* newStudent = new Student(fname, lName, sYear, netID);
    students.push_back(newStudent);
    std::cout << "Added Student: " << fname << " with ID: " << newStudent->getID() << std::endl;
    saveStudentsToCSV("students.csv"); // Save updated students to CSV
    std::cout << "Total students: " << students.size() << std::endl;
}


void LMS::addInstructor(const std::string& fname, const std::string& lName, const std::string& empid) {
    // Check if an instructor with the same EmpID already exists
    for (Instructor* existingInstructor : instructors) {
        if (existingInstructor->getEmployeeID() == empid) {
            // You can choose to update the existing instructor's information here if needed
            std::cout << "An instructor with EmpID " << empid << " already exists." << std::endl;
            return;
        }
    }

    // If no existing instructor found with the same EmpID, add the new instructor
    Instructor* newInstructor = new Instructor(fname, lName, empid);
    instructors.push_back(newInstructor);
    std::cout << "Added Instructor: " << fname << std::endl;
    saveInstructorsToCSV("instructors.csv"); // Save updated instructors to CSV
}



void LMS::addCourse(const std::string& code, const std::string& name, Instructor& instructor,
                    const std::vector<std::string>& daysOfWeek, const std::string& startTime,
                    const std::string& endTime, const std::string& description) {
    // Check if a course with the same CourseCode already exists
    for (Course* existingCourse : courses) {
        if (existingCourse->getCourseCode() == code) {
            // You can choose to update the existing course's information here if needed
            std::cout << "A course with CourseCode " << code << " already exists." << std::endl;
            return;
        }
    }

    // If no existing course found with the same CourseCode, add the new course
    Course* newCourse = new Course(code, name, instructor, daysOfWeek, startTime, endTime, description);
    courses.push_back(newCourse);
    std::cout << "Added Course: " << name << std::endl;
    saveCoursesToCSV("courses.csv"); // Save updated courses to CSV
}



// Helper functions to find entities by their IDs
Student* LMS::findStudentByID(const std::string& id) {
    for (Student* student : students) {
       // std::cout << "Checking student with ID: " << student->getID() << std::endl;
        if (student->getID() == id) {
            return student;
        }
    }
    return nullptr;
}

Instructor* LMS::findInstructorByID(const std::string& id) {
    for (Instructor* instructor : instructors) {
        if (instructor->getEmployeeID() == id) {
            return instructor;
        }
    }
    return nullptr;
}


Course* LMS::findCourseByID(const std::string& id) {
        for (Course* course : courses) {
            if (course->getCourseCode() == id) {
                return course;
            }
        }
        return nullptr;
    }


// Remove entities from the system
bool LMS::removeStudentByNetID(const std::string& netID) {
    auto it = std::remove_if(students.begin(), students.end(),
                             [&netID](Student* student) { return student->getID() == netID; });
    if (it != students.end()) {
        delete *it;  // Free the memory
        students.erase(it, students.end());
        saveStudentsToCSV("students.csv");
        return true;
    }
    return false;
}

bool LMS::removeInstructorByEmpID(const std::string& empID) {
    auto it = std::remove_if(instructors.begin(), instructors.end(),
                             [&empID](Instructor* instructor) { return instructor->getEmployeeID() == empID; });
    if (it != instructors.end()) {
        delete *it;  // Free the memory
        instructors.erase(it, instructors.end());
        saveInstructorsToCSV("instructors.csv");
        return true;
    }
    return false;
}

bool LMS::removeCourseByCode(const std::string& code) {
    auto it = std::remove_if(courses.begin(), courses.end(),
                             [&code](Course* course) { return course->getCourseCode() == code; });
    if (it != courses.end()) {
        delete *it;  // Free the memory
        courses.erase(it, courses.end());
        saveCoursesToCSV("courses.csv");
        return true;
    }
    return false;
}

// Check for scheduling clashes for a student
bool LMS::clashCheck(const Student& student, const Course& newCourse) const {
        for (const auto& courseCode : student.getEnrolledCourses()) {
            const Course* course = findCourseByCode(courseCode);
            if (course && !(newCourse.getEndTime() < course->getStartTime() ||
                            newCourse.getStartTime() > course->getEndTime())) {
                return true;
            }
        }
        return false;
    }


// Enroll a student from a course
void LMS::enrollStudent(Student& student, Course& course) {
        if (!student.isEnrolledIn(course.getCourseCode())) {
            student.enrollIn(course.getCourseCode());
        } else {
            std::cout << "Student already enrolled in this course!" << std::endl;
        }
    }

// Drop a student from a course
void LMS::dropStudent(const std::string& studentID, const std::string& courseCode) {
        Student* student = findStudentByID(studentID);
        if (student && student->dropCourse(courseCode)) {
            std::cout << "Dropped student from course: " << courseCode << std::endl;
        } else {
            std::cout << "Failed to drop student from course: " << courseCode << std::endl;
        }
    }


// Print the schedule for a student
void LMS::printSchedule(const std::string& studentID) {
    Student* student = findStudentByID(studentID);
    if (student) {
        std::cout << "Schedule for: " << student->getFirstName() << " " << student->getLastName() << std::endl;
        const std::vector<std::string>& enrolledCourses = student->getEnrolledCourses();
        for (const std::string& courseCode : enrolledCourses) {
            Course* course = findCourseByCode(courseCode);
            if (course) {
                course->DisplayCourseInfo(); // Changed to lowercase method name
                std::cout << std::endl;
                std::cout << "------------------------------------" << std::endl;
            }
        }
    }
}



// Getter methods to retrieve lists of students, instructors, and courses
const std::vector<Student*>& LMS::getStudents() const {
        return students;
    }

const std::vector<Instructor*>& LMS::getInstructors() const {
        return instructors;
    }

const std::vector<Course*>& LMS::getCourses() const {
        return courses;
    }