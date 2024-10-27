#include <iostream>
#include "studentmanager.cpp"
using namespace std;

int main() {
    StudentManager studentManager;
    int answer;
    string firstName, lastName;
    int studentNumber, newStudentNumber;
    double midtermGrade1, midtermGrade2, finalGrade;

    // Menu with the methods of the StudentManager class
    while (true) {
        cout << "What would you like to do?" << endl
        << "1. Print all Student data" << endl
        << "2. Sort the list of students in alphabetical order of last name" << endl
        << "3. Add a new student" << endl
        << "4. Calculate the letter grade of all students" << endl
        << "5. Change the information of a previous student" << endl
        << "6. Print the data of a specific student" << endl
        << "7. Remove a student from the list" << endl
        << "8. Delete ALL student data" << endl
        << "9. Change grading scheme" << endl
        << "10. Exit" << endl;
        cin >> answer;
        if (answer == 1) {
            cout << studentManager.printAllStudents() << endl;
        } else if (answer == 2) {
            studentManager.sortStudentsByName();
            cout << "Students have been sorted!" << endl;
        } else if (answer == 3) {
            cout << "Enter the first name: " << endl;
            cin >> firstName;
            cout << "Enter the last name: " << endl;
            cin >> lastName;
            cout << "Enter the student number: " << endl;
            cin >> studentNumber;
            cout << "Enter the first midterm grade: " << endl;
            cin >> midtermGrade1;
            cout << "Enter the second midterm grade: " << endl;
            cin >> midtermGrade2;
            cout << "Enter the final grade: " << endl;
            cin >> finalGrade;
            if (studentManager.addStudent(firstName, lastName, studentNumber, midtermGrade1, midtermGrade2, finalGrade)) {
                cout << "Student added!" << endl;
            } else {
                cout << "Student could not be added! Make sure your grades are 0-100 and does not have an already existing student number!" << endl;
            }
        } else if (answer == 4) {
            cout << studentManager.printAllStudentsWithGrade() << endl;
        } else if (answer == 5) {
            cout << "Enter the student number of the student you want to change the information of: " << endl;
            cin >> studentNumber;
            if (studentManager.findStudentById(studentNumber) == nullptr) {
                cout << "Student does not exist!" << endl;
            } else {
                while (true) {
                    cout << "What information would you like to change?" << endl
                    << "1. First name" << endl
                    << "2. Last name" << endl
                    << "3. Student number" << endl
                    << "4. First midterm grade" << endl
                    << "5. Second midterm grade" << endl
                    << "6. Final grade" << endl
                    << "7. Exit" << endl;
                    cin >> answer;
                    if (answer == 1) {
                        cout << "Enter the new first name: " << endl;
                        cin >> firstName;
                        // Since we already checked if the student exists, we don't have to put this in an if statement
                        studentManager.changeFirstName(studentNumber, firstName);
                        cout << "First name changed!" << endl;
                    } else if (answer == 2) {
                        cout << "Enter the new last name: " << endl;
                        cin >> lastName;
                        studentManager.changeLastName(studentNumber, lastName);
                        cout << "Last name changed!" << endl;
                    } else if (answer == 3) {
                        cout << "Enter the new student number: " << endl;
                        cin >> newStudentNumber;
                        if (studentManager.changeStudentNumber(studentNumber, newStudentNumber)) {
                            cout << "Student number changed!" << endl;
                        } else {
                            cout << "Student with that student number already exists!" << endl;
                        }
                    } else if (answer == 4) {
                        cout << "Enter the new first midterm grade: " << endl;
                        cin >> midtermGrade1;
                        if (studentManager.changeMidtermGrade1(studentNumber, midtermGrade1)) {
                            cout << "Midterm grade changed!" << endl;
                        } else {
                            cout << "Not a valid grade value!" << endl;
                        }
                    } else if (answer == 5) {
                        cout << "Enter the new second midterm grade: " << endl;
                        cin >> midtermGrade2;
                        if (studentManager.changeMidtermGrade2(studentNumber, midtermGrade2)) {
                            cout << "Midterm grade changed!" << endl;
                        } else {
                            cout << "Not a valid grade value!" << endl;
                        }
                    } else if (answer == 6) {
                        cout << "Enter the new final grade: " << endl;
                        cin >> finalGrade;
                        if (studentManager.changeFinalGrade(studentNumber, finalGrade)) {
                            cout << "Final grade changed!" << endl;
                        } else {
                            cout << "Not a valid grade value!" << endl;
                        }
                    } else if (answer == 7) {
                        break;
                    } else {
                        cout << "Not a valid option!";
                    }
                }
            }
        } else if (answer == 6) {
            cout << "What's the student number of the student you want to view?" << endl;
            cin >> studentNumber;
            if (studentManager.findStudentById(studentNumber) != nullptr) {
                cout << studentManager.findStudentById(studentNumber)->toString() << endl;
            } else {
                cout << "That student does not exist!" << endl;
            }
        } else if (answer == 7) {
            cout << "What is the student number of the student you want to remove?" << endl;
            cin >> studentNumber;
            if (studentManager.deleteStudentById(studentNumber)) {
                cout << "Student has been removed!" << endl;
            } else {
                cout << "That student does not exist!" << endl;
            }
        } else if (answer == 8) {
            cout << "This is serious! Are you sure you want to delete ALL student data?" << endl
            << "1. Yes" << endl
            << "2. No" << endl;
            cin >> answer;
            if (answer == 1) {
                studentManager.deleteAllStudents();
                cout << "All student data has been deleted!" << endl;
            } else if (answer == 2) {
                cout << "Student data will not be deleted." << endl;
            } else {
                cout << "That is not a valid option!" << endl;
            }
        } else if (answer == 9) {
            cout << "Please enter the weight of the first midterm, second midterm and third midterm " << endl
            << "(use numbers that add up to 100)" << endl;
            cin >> midtermGrade1;
            cin >> midtermGrade2;
            cin >> finalGrade;
            if(studentManager.setWeights(midtermGrade1, midtermGrade2, finalGrade)) {
                cout << "Weight changed!" << endl;
            } else {
                cout << "Weights did not add to 1! Please try again!" << endl;
            }
        } else if (answer == 10) {
            break;
        } else {
            cout << "Not a valid option!" << endl;
        }
    }

    return 0;
}