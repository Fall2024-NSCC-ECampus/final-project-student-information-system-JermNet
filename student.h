#include <string>

// To get values to 2 decimal places
#include <iomanip>
#include <sstream>
using namespace std;
#ifndef STUDENT_H
#define STUDENT_H
class Student {
  private:
    string firstName, lastName;
    int studentNumber;
    // This could potentially be an array of grades, but since we know we're only working with 3, this is fine
    double midtermGrade1, midtermGrade2, finalGrade;
    // Default student number increaser since student numbers aren't supposed to stay the same
  	static int defaultStudentNumber;
  public:
    // Constructor with inbuilt defaults
    Student(string firstName = "", string lastName = "", int studentNumber = defaultStudentNumber++, double midtermGrade1 = 0, double midtermGrade2 = 0,
      double finalGrade = 0) {
      this->firstName = firstName;
      this->lastName = lastName;
      this->studentNumber = studentNumber;
      this->midtermGrade1 = midtermGrade1;
      this->midtermGrade2 = midtermGrade2;
      this->finalGrade = finalGrade;
    }

    // Setters and getters
    string getFirstName() {
      return firstName;
    }

    string getLastName() {
      return lastName;
    }

    int getStudentNumber() {
      return studentNumber;
    }

    double getMidtermGrade1() {
      return midtermGrade1;
    }

    double getMidtermGrade2() {
      return midtermGrade2;
    }

    double getFinalGrade() {
      return finalGrade;
    }

    void setFirstName(string firstName) {
      this->firstName = firstName;
    }

    void setLastName(string lastName) {
      this->lastName = lastName;
    }

    void setStudentNumber(int studentNumber) {
      this->studentNumber = studentNumber;
    }

    bool setMidtermGrade1(double midtermGrade1) {
      if (midtermGrade1 > 100 || midtermGrade1 < 0) {
        return false;
      }
      this->midtermGrade1 = midtermGrade1;
      return true;
    }

    bool setMidtermGrade2(double midtermGrade2) {
      if (midtermGrade2 > 100 || midtermGrade2 < 0) {
        return false;
      }
      this->midtermGrade2 = midtermGrade2;
      return true;
    }

    bool setFinalGrade(double finalGrade) {
      if (finalGrade > 100 || finalGrade < 0) {
        return false;
      }
      this->finalGrade = finalGrade;
      return true;
    }

    // toString to get all of the data in a nice format
    string toString() {
      stringstream ss;
      // Numbers fixes to one decimal place
      ss << fixed << setprecision(1);
      ss << firstName << " " << lastName << "\nStudent number: " << studentNumber
         << "\nMidterm grade 1: " << midtermGrade1
         << "\nMidterm grade 2: " << midtermGrade2
         << "\nFinal grade: " << finalGrade;
      return ss.str();
    }

};
int Student::defaultStudentNumber = 0;
#endif //STUDENT_H