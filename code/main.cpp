#include "LMS.h"

int main() {
    std::cout << "Program Started" << std::endl;

    LMS lmsSystem;
    std::cout << "LMS created" << std::endl;

    // Add students
    lmsSystem.addStudent("Sara", "Conner", 2023, "SC2244");
    lmsSystem.addStudent("Mil", "Gibbson", 2022, "MG6754");
    lmsSystem.addStudent("Alice", "Johnson", 2023, "AJ2023");
    lmsSystem.addStudent("Bob", "Smith", 2023, "BS1234");

    // Add instructors
    lmsSystem.addInstructor("Prof", "Jason", "PM1234");
    lmsSystem.addInstructor("Dr", "Stevens", "DS5678");
    lmsSystem.addInstructor("Prof", "Mathews", "PM2233");

    // Find John by ID
    Student* john = lmsSystem.findStudentByID("JD933");
    if (!john) {
        std::cout << "John not found!" << std::endl;
    } else {
        std::cout << "John found with ID: " << john->getID() << std::endl;
    }

    // Add more courses with descriptions
    Instructor* profJason = lmsSystem.findInstructorByID("PM1234");
    if (profJason) {
        lmsSystem.addCourse("PHY201", "Advanced Physics", *profJason, {"Tue", "Thu"}, "09:00", "10:30", "Advanced physics topics.");
        lmsSystem.addCourse("COMP101", "Computer Science 1", *profJason, {"Mon", "Wed"}, "11:00", "12:30", "Introduction to programming.");
        lmsSystem.addCourse("MATH201", "Advanced Calculus", *profJason, {"Tue", "Thu"}, "14:00", "15:30", "Advanced calculus topics.");
        lmsSystem.addCourse("ENG101", "English Composition", *profJason, {"Mon", "Wed"}, "16:00", "17:30", "Writing and composition.");

        Instructor* profMathews = lmsSystem.findInstructorByID("PM2233");
        if (profMathews) {
            lmsSystem.addCourse("CHEM201", "Advanced Chemistry", *profMathews, {"Mon", "Wed"}, "13:00", "14:30", "Advanced chemistry topics.");
        }
    }

    // Enroll John in more courses
    if (john) {
        lmsSystem.enrollStudent(*john, *lmsSystem.findCourseByID("ARA101"));
        lmsSystem.enrollStudent(*john, *lmsSystem.findCourseByID("MATH201"));
        lmsSystem.enrollStudent(*john, *lmsSystem.findCourseByID("PHY201"));
        lmsSystem.enrollStudent(*john, *lmsSystem.findCourseByID("COMP101"));
    } else {
        std::cout << "John not found!" << std::endl;
    }

    // Add more students
    lmsSystem.addStudent("Eva", "Miller", 2022, "EC999");
    lmsSystem.addStudent("Chris", "Brown", 2023,"CC123");

    // Find Eva and Chris by ID
    Student* eva = lmsSystem.findStudentByID("EC999");
    Student* chris = lmsSystem.findStudentByID("CC123");

     if (eva && chris) {
        lmsSystem.enrollStudent(*eva, *lmsSystem.findCourseByID("MATH201"));
        lmsSystem.enrollStudent(*eva, *lmsSystem.findCourseByID("ENG101"));
        lmsSystem.enrollStudent(*chris, *lmsSystem.findCourseByID("COMP101"));
        lmsSystem.enrollStudent(*chris, *lmsSystem.findCourseByID("PHY201"));
    } else {
        std::cout << "Eva and Chris not found!" << std::endl;
    }

    // Print schedules for John, Eva, and Chris
    std::cout << "John's Schedule:" << std::endl;
    lmsSystem.printSchedule("JD933");

    if (eva) {
        std::cout << "Eva's Schedule:" << std::endl;
        lmsSystem.printSchedule(eva->getID());
    }

    if (chris) {
        std::cout << "Chris's Schedule:" << std::endl;
        lmsSystem.printSchedule(chris->getID());
    }

    std::cout << "Program finished" << std::endl;
    return 0;
}
