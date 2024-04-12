#ifndef STUDENTCLASS_H_INCLUDED
#define STUDENTCLASS_H_INCLUDED
#include<iostream>
#include "Courses.h"
#include "getUserInput.h"

using namespace std;

/******************************
Course Class Start
*******************************/
class Course{//Course class
    friend ostream& operator<<(ostream&, Course&);
    friend ofstream& operator<<(ofstream&, Course&);
    friend istream& operator>>(istream&, Course&);
    friend ifstream& operator>>(ifstream&, Course&);
    private:
        string subject;
        int code, grade;
    public:
        Course(string = "", int = 0, int = 0);
        void setClasses(string, int);
        void setGrade();
        int getGrade();
};

//Course Exception Class Start
class CourseException: public runtime_error{//Course Exception runtime error class
    private:
        Course c;
        string message;
    public:
        CourseException(Course, string);
        void displayCourseException();
};

CourseException::CourseException(Course c, string s):runtime_error("Invalid Input"){//Course Exception class constructor
    this->c = c;
    message = s;
}

void CourseException::displayCourseException(){//Display course exception error message
    cout << message << endl;
}
//Course Exception Class End

Course::Course(string s, int c, int g){//Course class constructor
    subject = s;
    code = c;
    if (g<0||g>100){//check if grade is between 0 or 100
        string errorMessage;
        if(g>100){//set grade to 100 if entry is above 100
            errorMessage = "Grade cannot be greater than 100%.\nGrade is set to 100%";
            grade = 100;
        }
        else{//set grade to 0 if entry is below 0
            errorMessage = "Grade cannot be less than 0%\nGrade is set to 0%";
            grade = 0;
        }
        CourseException e(*this, errorMessage);
        throw e;//throw CourseException error
    }
    grade = g;
}

ostream& operator<<(ostream& out, Course& c){//insertion operator for course class
    out << c.subject << "-" << c.code << endl;
    out << "Grade: " << c.grade << "%" << endl;
    return out;
}

ofstream& operator<<(ofstream& out, Course& c){//insertion operator for course class, for text files
    out << c.subject << endl;
    out << c.code << endl;
    out << c.grade << endl;
    return out;
}

istream& operator>>(istream& in, Course& c){//extraction operator for course class
    string message =  c.subject + "-" + to_string(c.code) + " Grade: ";
    c.grade = getInput<int>(message);
    if (c.grade<0||c.grade>100){
        string errorMessage;
        if(c.grade>100){
            errorMessage = "Grade cannot be greater than 100%.\nGrade is set to 100%";
            c.grade = 100;
        }
        else{
            errorMessage = "Grade cannot be less than 0%\nGrade is set to 0%";
            c.grade = 0;
        }
        CourseException e(c, errorMessage);
        throw e;
    }
}

ifstream& operator>>(ifstream& in, Course& c){//extraction operator for course class, for text files
    in >> c.subject;
    in >> c.code;
    in >> c.grade;
}

void Course::setGrade(){//set grade for the course
    cout << "Enter the new grade for " << subject << "-" << code << ": ";
    cin >> grade;
    if (grade<0||grade>100){
        string errorMessage;
        if(grade>100){
            errorMessage = "Grade cannot be greater than 100%.\nGrade is set to 100%";
            grade = 100;
        }
        if(grade<0){
            errorMessage = "Grade cannot be less than 0%\nGrade is set to 0%";
            grade = 0;
        }
        CourseException e(*this, errorMessage);
        throw e;
    }
}

int Course::getGrade(){//return grade for the course
    return grade;
}

void Course::setClasses(string s, int i){//set the subject and code for a class
    subject = s;
    code = i;
}
/******************************
Course Class End
*******************************/

/******************************
Student Class Start
*******************************/
class Student{//Student class
    friend ostream& operator<<(ostream&, Student&);
    friend ofstream& operator<<(ofstream&, Student&);
    friend istream& operator>>(istream&, Student&);
    friend ifstream& operator>>(ifstream&, Student&);
    private:
        string firstName, lastName;
    public:
        Course classes[5];
        Student(string = "", string = "");
        void displayAverage();
        string getFirstAndLastName();
};

Student::Student(string fn, string ln){//student constructor
    firstName = fn;
    lastName = ln;
}

void Student::displayAverage(){//display average grade
    float avg = 0;
    for(int x=0; x<5; x++)
        avg += classes[x].getGrade();
    avg /= 5;
    cout << this->getFirstAndLastName() << " Average: " << setprecision(1) << fixed << avg << "%" << endl;
}

string Student::getFirstAndLastName(){//return first and last name
    return (firstName + " " + lastName);
}

ostream& operator<<(ostream& out, Student& s){//insertion operator for student class
    out << "First Name: " << s.firstName << endl;
    out << "Last Name: " << s.lastName << endl;
    for (int x=0; x<5; x++)
        out << s.classes[x] << endl;
    return out;
}

ofstream& operator<<(ofstream& out, Student& s){//insertion operator for course class, for text files
    out << s.firstName << endl << s.lastName << endl;
    for (int x=0; x<5; x++)
        out << s.classes[x];
    return out;
}

istream& operator>>(istream& in, Student& s){//extraction operator for course class
    cout << "Student's first name: ";
    in >> s.firstName;
    cout << "Student's last name: ";
    in >> s.lastName;
    for(int x=0; x<5; x++){
        s.classes[x].setClasses(subjects[x], courseCodes[x]);
        try{
            in >> s.classes[x];
            cout << endl;
        }
        catch(CourseException e){
            cout << "\a";
            cout << e.what() << endl;
            e.displayCourseException();
        }
    }
}

ifstream& operator>>(ifstream& in, Student& s){//extraction operator for course class, for text files
    in >> s.firstName;
    in >> s.lastName;
    for(int x=0; x<5; x++)
        in >> s.classes[x];
}
/******************************
Student Class End
*******************************/

#endif // STUDENTCLASS_H_INCLUDED
