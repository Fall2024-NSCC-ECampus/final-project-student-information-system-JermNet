#include "student.cpp"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
using namespace std;

class StudentManager {
  // Dynamic array stuff, student pointer, number of students, etc.
  private:
    Student** students;
    int size, numberOfStudents;
    // The weights of each grade, made static so they apply across everything
    static double midtermGrade1Weight, midtermGrade2Weight, finalWeight;
    // File name the data will be saved to
    const string fileName = "students.dat";
  public:
    // Constructor with default arraylist size of 5
    StudentManager(int size = 5) {
      this->size = size;
      numberOfStudents = 0;
      students = new Student*[size];
    }

    // This is a "destructor", used an instance of this class is deleted. In this case, it deletes the students and array to avoid memory issues
    ~StudentManager() {
      for (int i = 0; i < numberOfStudents; i++) {
        delete students[i];
      }
      delete[] students;
    }

    // Resize the array should it be full
    void resize() {
      if (numberOfStudents == size) {
        size *= 2;
        Student** newStudents = new Student*[size];
        for (int i = 0; i < numberOfStudents; i++) {
          newStudents[i] = students[i];
        }
        delete[] students;
        students = newStudents;
      }
    }

    // Method to save the students, called in all methods that create a change
    void save() {
      ofstream outFile(fileName);
      // If it doesn't exist, send an error
      if (!outFile) {
        cerr << "Can't open file " << fileName << endl;
        return;
      }
      for (int i = 0; i < numberOfStudents; i++) {
        outFile << students[i]->getFirstName() << " "
                << students[i]->getLastName() << " "
                << students[i]->getStudentNumber() << " "
                << students[i]->getMidtermGrade1() << " "
                << students[i]->getMidtermGrade2() << " "
                << students[i]->getFinalGrade() << endl;
      }
      outFile.close();
    }

    // Add a student if one doesn't already exist by id.
    bool addStudent(string firstName="", string lastName="", int studentNumber=0, double midtermGrade1=0, double midtermGrade2=0, double finalGrade=0) {
      if (findStudentById(studentNumber) != nullptr) {
        return false;
      }
      // If not returning false, the student can be added, but first we have to check if there's room and resize if there isn't
      if (numberOfStudents == size) {
        resize();
      }
      // Add the student and increase the numberOfStudents variable
      students[numberOfStudents] = new Student(firstName, lastName, studentNumber, midtermGrade1, midtermGrade2, finalGrade);
      numberOfStudents++;
      save();
      return true;
    }

    bool deleteStudentById(int studentNumber) {
      // Index of the student to delete, since it starts at negative 1, if it stays at negative 1, the the student doesn't exist
      // We have to have an index for this method anyway, so it's more effiecent to check if the student exists this way instead of findById
      int deleteIndex = -1;

      // Find the student
      for (int i = 0; i < numberOfStudents; i++) {
        if (students[i]->getStudentNumber() == studentNumber) {
          deleteIndex = i;
          break;
        }
      }
      if (deleteIndex == -1) {
        return false;
      }

      // Delete the student
      delete students[deleteIndex];

      // Shift the students around to fill the array
      for (int i = deleteIndex; i < numberOfStudents-1; i++) {
        students[i] = students[i+1];
      }

      // Not required, but since we're working with nullptr to see if a student exists, it's good to have
      students[numberOfStudents-1] = nullptr;

      // Decrease the number of students
      numberOfStudents--;
      save();
      return true;
    }

    // Check if a student exists by studentNumber
    Student* findStudentById(int studentNumber) {
      for (int i = 0; i < numberOfStudents; i++) {
        if (students[i]->getStudentNumber() == studentNumber) {
			return students[i];
        }
      }
      return nullptr;
    }

    // Delete all students and reset everything back to initial state (size = 5, numberOfStudents = 0)
    void deleteAllStudents() {
      for (int i = 0; i < numberOfStudents; i++) {
        delete students[i];
      }
      numberOfStudents = 0;
      size = 5;
      delete[] students;
      students = new Student*[size];
      save();
    }

    // Sort the students by name. The first if is for the last name, the else if is if the have the same last name, and so we sort by first name
    void sortStudentsByName() {
      for (int i = 0; i < numberOfStudents - 1; i++) {
        for (int j = i + 1; j < numberOfStudents; j++) {
          if (students[i]->getLastName() > students[j]->getLastName()) {
            swap(students[i], students[j]);
          }
          else if (students[i]->getLastName() == students[j]->getLastName() && students[i]->getFirstName() > students[j]->getFirstName()) {
            swap(students[i], students[j]);
          }
        }
      }
      save();
    }

    string printStudent(int studentNumber) {
      if (findStudentById(studentNumber) != nullptr) {
        return students[studentNumber]->toString();
      }
      return "That student does not exist!";
    }

    string printAllStudents() {
      if (numberOfStudents == 0) {
        return "There are no students!";
      }

      string result = "";
      for (int i = 0; i < numberOfStudents; i++) {
        result += students[i]->toString() + "\n\n";
      }
      return result;
    }

    string printAllStudentsWithGrade() {
      if (numberOfStudents == 0) {
        return "There are no students!";
      }

      string result = "";
      for (int i = 0; i < numberOfStudents; i++) {
        result += students[i]->toString() + "\nLetter grade: " + getLetterGrade(students[i]->getStudentNumber()) +
          "\nPercent grade: " + to_string(getFinalGrade(students[i]->getStudentNumber())) + "\n\n";
      }
      return result;
    }

    // Set and get the different weights, also check to make sure the weights line up properly
    static bool setWeights(double weight1, double weight2, double weight3) {
      if (weight1 + weight2 + weight3 == 100) {
        midtermGrade1Weight = weight1;
        midtermGrade2Weight = weight2;
        finalWeight = weight3;
        return true;
      }
      return false;
    }

    double getMidtermGrade1Weight() {
      return midtermGrade1Weight;
    }

    double getMidtermGrade2Weight() {
      return midtermGrade2Weight;
    }

    double getFinalWeight() {
      return finalWeight;
    }

    // Get the final grade with a students marks and the weights for each one
    double getFinalGrade(int studentNumber) {
      if (findStudentById(studentNumber) == nullptr) {
        return 0;
      }
      // Doing this way instead of the way done in students since it's easier for this
      double total = (findStudentById(studentNumber)->getMidtermGrade1() * midtermGrade1Weight +
              findStudentById(studentNumber)->getMidtermGrade2() * midtermGrade2Weight +
              findStudentById(studentNumber)->getFinalGrade() * finalWeight) / 100;
      return round(total*10) / 10.0;
    }

    // Return a letter grade for a student, uses getFinalGrade to check against.
    string getLetterGrade(int studentNumber) {
      double grade = getFinalGrade(studentNumber);
      if (grade > 90) {
        return "A";
      } else if (grade <= 90 && grade > 80) {
        return "B";
      } else if (grade <= 80 && grade > 70) {
        return "C";
      } else if (grade <= 70 && grade >= 60) {
        return "D";
      } else if (grade < 60) {
        return "F";
      }
      // Have this just in case, and so the method is always potentially returning something,
      // even if the logic of this class prevents this from happening.
      return "Err";
    }

    // Change student data, all booleans since we have to check if students already exist or not
    bool changeFirstName(int studentNumber, string firstName) {
      if (findStudentById(studentNumber) == nullptr) {
        return false;
      }
      findStudentById(studentNumber)->setFirstName(firstName);
      save();
      return true;
    }

    bool changeLastName(int studentNumber, string lastName) {
      if (findStudentById(studentNumber) == nullptr) {
        return false;
      }
      findStudentById(studentNumber)->setLastName(lastName);
      save();
      return true;
    }

    // For this one, if the first number doesn't exist, there's no student, and if the second one does exists, we can't change because student numbers are unique
    bool changeStudentNumber(int studentNumber, int newStudentNumber) {
      if (findStudentById(studentNumber) == nullptr || findStudentById(newStudentNumber) != nullptr) {
        return false;
      }
      findStudentById(studentNumber)->setStudentNumber(newStudentNumber);
      save();
      return true;
    }

    // Built in check in the students change grade methods, so we can use an or in the if statement
    bool changeMidtermGrade1(int studentNumber, double midtermGrade1) {
      if (findStudentById(studentNumber) == nullptr||!findStudentById(studentNumber)->setMidtermGrade1(midtermGrade1)) {
        return false;
      }
      save();
      return true;
    }

    bool changeMidtermGrade2(int studentNumber, double midtermGrade2) {
      if (findStudentById(studentNumber) == nullptr||!findStudentById(studentNumber)->setMidtermGrade2(midtermGrade2)) {
        return false;
      }
      save();
      return true;
    }

    bool changeFinalGrade(int studentNumber, double finalGrade) {
      if (findStudentById(studentNumber) == nullptr||!findStudentById(studentNumber)->setFinalGrade(finalGrade)) {
        return false;
      }
      save();
      return true;
    }
};

// Defaults for the static variables, out here since they're static
double StudentManager::midtermGrade1Weight = 25.0;
double StudentManager::midtermGrade2Weight = 25.0;
double StudentManager::finalWeight = 50.0;