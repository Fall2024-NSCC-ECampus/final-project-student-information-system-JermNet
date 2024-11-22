#include <iostream>
#include <limits>
#include "studentmanager.h"

using namespace std;

int main() {
    StudentManager studentManager;
    int answer;
    string firstName, lastName;
    int studentNumber, newStudentNumber;
    double midtermGrade1, midtermGrade2, finalGrade;

    while (true) {
        try {
            cout << "\nWhat would you like to do?" << endl
                 << "1. Print all Student data" << endl
                 << "2. Sort the list of students in alphabetical order of last name" << endl
                 << "3. Add a new student" << endl
                 << "4. Calculate the letter grade of all students" << endl
                 << "5. Change the information of a previous student" << endl
                 << "6. Print the data of a specific student" << endl
                 << "7. Remove a student from the list" << endl
                 << "8. Delete ALL student data" << endl
                 << "9. Change grading scheme" << endl
                 << "10. Load from file" << endl
                 << "11. Exit" << endl;

            cin >> answer;
            if (cin.fail()) throw runtime_error("Invalid input. Please enter a valid menu number.");

            switch (answer) {
                case 1:
                    cout << studentManager.printAllStudents() << endl;
                    break;

                case 2:
                    studentManager.sortStudentsByName();
                    cout << "Students have been sorted!" << endl;
                    break;

                case 3: {
                    cout << "Enter the first name: " << endl;
                    cin >> firstName;
                    cout << "Enter the last name: " << endl;
                    cin >> lastName;

                    cout << "Enter the student number: " << endl;
                    cin >> studentNumber;
                    if (cin.fail()) throw runtime_error("Invalid student number!");

                    cout << "Enter the first midterm grade: " << endl;
                    cin >> midtermGrade1;
                    if (midtermGrade1 < 0 || midtermGrade1 > 100) throw runtime_error("Midterm grade must be between 0 and 100.");

                    cout << "Enter the second midterm grade: " << endl;
                    cin >> midtermGrade2;
                    if (midtermGrade2 < 0 || midtermGrade2 > 100) throw runtime_error("Midterm grade must be between 0 and 100.");

                    cout << "Enter the final grade: " << endl;
                    cin >> finalGrade;
                    if (finalGrade < 0 || finalGrade > 100) throw runtime_error("Final grade must be between 0 and 100.");

                    if (studentManager.addStudent(firstName, lastName, studentNumber, midtermGrade1, midtermGrade2, finalGrade)) {
                        cout << "Student added!" << endl;
                    } else {
                        cout << "Could not add student! Ensure grades are valid and student number is unique." << endl;
                    }
                    break;
                }

                case 4:
                    cout << studentManager.printAllStudentsWithGrade() << endl;
                    break;

                case 5: {
                    cout << "Enter the student number of the student to modify: " << endl;
                    cin >> studentNumber;
                    if (cin.fail()) throw runtime_error("Invalid student number!");

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
                            if (cin.fail()) throw runtime_error("Invalid option!");

                            if (answer == 7) break;

                            switch (answer) {
                                case 1:
                                    cout << "Enter the new first name: " << endl;
                                    cin >> firstName;
                                    studentManager.changeFirstName(studentNumber, firstName);
                                    cout << "First name changed!" << endl;
                                    break;

                                case 2:
                                    cout << "Enter the new last name: " << endl;
                                    cin >> lastName;
                                    studentManager.changeLastName(studentNumber, lastName);
                                    cout << "Last name changed!" << endl;
                                    break;

                                case 3:
                                    cout << "Enter the new student number: " << endl;
                                    cin >> newStudentNumber;
                                    if (studentManager.changeStudentNumber(studentNumber, newStudentNumber)) {
                                        cout << "Student number changed!" << endl;
                                    } else {
                                        cout << "Student with this number already exists!" << endl;
                                    }
                                    break;

                                case 4:
                                    cout << "Enter the new first midterm grade: " << endl;
                                    cin >> midtermGrade1;
                                    if (studentManager.changeMidtermGrade1(studentNumber, midtermGrade1)) {
                                        cout << "Grade updated!" << endl;
                                    } else {
                                        cout << "Invalid grade!" << endl;
                                    }
                                    break;

                                case 5:
                                    cout << "Enter the new second midterm grade: " << endl;
                                    cin >> midtermGrade2;
                                    if (studentManager.changeMidtermGrade2(studentNumber, midtermGrade2)) {
                                        cout << "Grade updated!" << endl;
                                    } else {
                                        cout << "Invalid grade!" << endl;
                                    }
                                    break;

                                case 6:
                                    cout << "Enter the new final grade: " << endl;
                                    cin >> finalGrade;
                                    if (studentManager.changeFinalGrade(studentNumber, finalGrade)) {
                                        cout << "Grade updated!" << endl;
                                    } else {
                                        cout << "Invalid grade!" << endl;
                                    }
                                    break;

                                default:
                                    cout << "Invalid option!" << endl;
                                    break;
                            }
                        }
                    }
                    break;
                }

                case 6:
                    cout << "Enter the student number: " << endl;
                    cin >> studentNumber;
                    if (cin.fail()) throw runtime_error("Invalid student number!");

                    if (studentManager.findStudentById(studentNumber) != nullptr) {
                        cout << studentManager.findStudentById(studentNumber)->toString() << endl;
                    } else {
                        cout << "Student does not exist!" << endl;
                    }
                    break;

                case 7:
                    cout << "Enter the student number to remove: " << endl;
                    cin >> studentNumber;
                    if (cin.fail()) throw runtime_error("Invalid student number!");

                    if (studentManager.deleteStudentById(studentNumber)) {
                        cout << "Student removed!" << endl;
                    } else {
                        cout << "Student does not exist!" << endl;
                    }
                    break;

                case 8:
                    cout << "Are you sure you want to delete ALL data?" << endl
                         << "1. Yes" << endl
                         << "2. No" << endl;
                    cin >> answer;
                    if (answer == 1) {
                        studentManager.deleteAllStudents();
                        cout << "All data deleted!" << endl;
                    } else if (answer == 2) {
                        cout << "Operation canceled." << endl;
                    } else {
                        throw runtime_error("Invalid choice!");
                    }
                    break;

                case 9:
                    cout << "Enter weights for midterm 1, midterm 2, and final (must sum to 100): " << endl;
                    cin >> midtermGrade1 >> midtermGrade2 >> finalGrade;
                    if (midtermGrade1 + midtermGrade2 + finalGrade != 100) {
                        throw runtime_error("Weights must sum to 100!");
                    }
                    if (studentManager.setWeights(midtermGrade1, midtermGrade2, finalGrade)) {
                        cout << "Grading scheme updated!" << endl;
                    }
                    break;

                case 10:
                    studentManager.load();
                    cout << "Data loaded from file!" << endl;
                    break;

                case 11:
                    cout << "Exiting program." << endl;
                    return 0;

                default:
                    cout << "Invalid option!" << endl;
                    break;
            }
        } catch (const exception& e) {
            cout << "Error: " << e.what() << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    return 0;
}
