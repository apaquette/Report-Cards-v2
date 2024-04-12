/******************************************************************************
Final Assignment
Alexandre Paquette
Date: April 17, 2021
Class: CIS163
Program Description:
This program is designed to allow a user to enter student records for given
classes. The program can display all student records, a specific student record,
a student's average grade, or an average class grade. It will also allow the user
to update a student's grade for any class. This program will store an infinite
number of students in a text file. The user can clear the text file or delete
specific entries from the text file.
*******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include "getUserInput.h"
#include "StudentClass.h"
#include "Courses.h"
using namespace std;

#ifdef _WIN32
    #define CLEAR_COMMAND "cls"
#elif __APPLE__
    #define CLEAR_COMMAND "clear"
#elif __linux__
    #define CLEAR_COMMAND "clear"
#else
    #error "Unsupported operating system"
#endif

//Global Constants
const int EXIT = 8;
const string fileName = "students.txt";

//non-menu functions start
int countStudents(){                                                //count the number of students in the text file
    Student temp;
    int count=0;
    ifstream readingFile;
    readingFile.open(fileName);

    while(readingFile >> temp)//counts how many times the text file can be imported into a Student variable
        count++;

    readingFile.close();

    return count;
}

int menuItems(){                                                    //determines the menu options based on whether there are students in the text file
    ifstream readingFile;

    readingFile.open(fileName);

    if(readingFile.peek() == ifstream::traits_type::eof())//return 2 if the file is empty
        return 2;

    return EXIT;
}

void calculateClassAverage(int selection){                          //calculate the average and display the results
    int count=countStudents(), avg=0;
    Student students[count];
    ifstream readingFile;
    readingFile.open(fileName);

    for(int x=0; x<count; x++){
        readingFile >> students[x]; //imports student from text file
        avg += students[x].classes[selection-1].getGrade(); //add student grade to average variables
    }
    readingFile.close();

    avg /= count;   //Class average = total grades / number of students

    cout << subjects[selection-1] << "-" << courseCodes[selection-1] << " Average: " << setprecision(1) << fixed << avg << "%" << endl;


}

void getStudents(Student students[], int count){                    //gets the students from the text file and populates a student array
    ifstream readingFile;
    readingFile.open(fileName);
    for(int x=0; x<count; x++)//populates a student array with entries from the text file
        readingFile >> students[x];
    readingFile.close();
}

string generateStudentMenu(Student students[], int numStudents){    //generate Menu of all students
    string message = "Select a student:\n";
    for (int x=0; x<numStudents;x++){//generates formated student entries for menu selection
        message += to_string(x+1);
        message += " - ";
        message += students[x].getFirstAndLastName();
        message += "\n";
    }
    message += to_string(numStudents+1);
    message += " - Exit\nEnter: ";

    return message;
}

void clearFile(){                                                   //Clear file of all entries
    ofstream writingFile;
    writingFile.open(fileName);
    writingFile.close();
}
//non-menu functions end

//menu functions start
void createStudentRecord(){     //1 - Create Student Record
    ofstream writingFile;
    Student students;

    writingFile.open(fileName, ios_base::app);    //open file to append
    try{
        cin >> students;
    }
    catch(CourseException e){
        cout << "\a";
        cout << e.what() << endl;
        e.displayCourseException();
        cout << endl;
    }
    writingFile << students << endl;

    writingFile.close();
}

void updateGrades(){            //2 - Update Grades
    int count = countStudents(), input;
    Student students[count];
    getStudents(students, count);

    do{//select menu option
        string message = generateStudentMenu(students, count);
        input = getInput<int>(message, 1, count+1);
        system(CLEAR_COMMAND);  //clear terminal for ease of use
        if(input != count+1){
            message = "Select a course:\n";
            for (int x=0; x<5;x++){
                message += to_string(x+1);
                message += " - ";
                message += subjects[x];
                message += "-";
                message += to_string(courseCodes[x]);
                message += "\n";
            }
            message += "6 - Exit\nEnter: ";
            int classSelection;
            do{
                classSelection = getInput<int>(message, 1, 6);
                system(CLEAR_COMMAND);  //clear terminal for ease of use
                if(classSelection != 6){
                    try{
                        students[input-1].classes[classSelection-1].setGrade();
                    }
                    catch(CourseException e){
                        cout << "\a";
                        cout << e.what() << endl;
                        e.displayCourseException();
                        cout << endl;
                    }
                    ofstream writingFile;
                    writingFile.open(fileName);
                    for(int x = 0; x<count; x++)
                        writingFile << students[x] << endl;
                    writingFile.close();
                }
            }while(classSelection != 6);
        }
    }while(input != count+1);
}

void displayStudentRecord(){    //3 - Display Student Record
    int count = countStudents(), input;
    Student students[count];
    getStudents(students, count);
    string message = generateStudentMenu(students, count);

    do{//select menu option
        input = getInput<int>(message, 1, count+1);
        system(CLEAR_COMMAND);  //clear terminal for ease of use
        if(input != count+1)
            cout << students[input-1];
    }while(input != count+1);
}

void displayAllStudentRecords(){//4 - Display all Student Records
    Student student;
    ifstream readingFile;

    readingFile.open(fileName);//open students text file for reading

    while(readingFile >> student)//list all students in the text file
        cout << student << endl;

    readingFile.close();
}

void displayClassAverage(){     //5 - Display Class Average
    int input;

    string message = "Select a course:\n";
    for (int x=0; x<5;x++){
        message += to_string(x+1);
        message += " - ";
        message += subjects[x];
        message += "-";
        message += to_string(courseCodes[x]);
        message += "\n";
    }
    message += "6 - Exit\nEnter: ";

    do{//select menu option
        input = getInput<int>(message, 1, 6);
        system(CLEAR_COMMAND);  //clear terminal for ease of use
        if(input != 6)
            calculateClassAverage(input);
    }while(input != 6);
}

void displayStudentAverage(){   //6 - Display Student Average
    int count = countStudents(), input;
    Student students[count];
    getStudents(students, count);

    //menu selection creation start
    string message = generateStudentMenu(students, count);

    do{//select menu option
        input = getInput<int>(message, 1, count+1);
        system(CLEAR_COMMAND);  //clear terminal for ease of use
        if(input != count+1)
            students[input-1].displayAverage();
    }while(input != count+1);
}

void deleteRecords(){           //7 - Delete a specific record or all records
    int input;
    do{
        string message = "Delete Records\n1 - Student Records\n2 - All Records\n3 - Exit\nEnter: ";
        input = getInput<int>(message, 1, 3);
        system(CLEAR_COMMAND);  //clear terminal for ease of use
        if(input == 1){
            int count;
            do{//select menu option
                count = countStudents();
                Student students[count];
                getStudents(students, count);
                message = generateStudentMenu(students, count);
                input = getInput<int>(message, 1, count+1);
                system(CLEAR_COMMAND);  //clear terminal for ease of use
                if(input != count+1){
                    for(int x = input-1; x<count-1; x++)
                        students[x] = students[x+1];
                    ofstream writingFile;
                    writingFile.open(fileName);
                    for(int x = 0; x<count-1; x++)
                        writingFile << students[x] << endl;
                    writingFile.close();
                }
            }while(input != count+1);
        }
        if(input == 2){
            input = getInput<int>("Are you sure you want to delete all Student Records?\n!!!This cannot be undone!!!\n1 - Yes\n2 - No\nEnter: ", 1,2);
            system(CLEAR_COMMAND);  //clear terminal for ease of use
                if(input == 1)
                    clearFile();
            break;
        }
    }while(input !=3);
}
//menu functions end

int main(){                     //Main Menu
    int lastItem, input;
    string menu;
    do{//main menu loop
        lastItem = menuItems();

        if(lastItem != EXIT){//Restrict menu to create student record if no records exist
            menu = "Main Menu\n1 - Create Student Record\n2 - Exit\nEnter: ";//main menu
            input = getInput<int>(menu, 1,lastItem);//get user input, only accept inputs between 1 and 5
            system(CLEAR_COMMAND);  //clear terminal for ease of use
            if(input == 1)
                createStudentRecord();
        }
        else{//enable display options once at least one student record exists
            menu = "Main Menu\n1 - Create Student Record\n2 - Update Student Grade\n3 - Display Student Record\n4 - Display all Student Records\n5 - Display a Class's Average\n6 - Display a Student's Average\n7 - Delete Records\n"+ to_string(lastItem) +" - Exit\nEnter: ";//main menu
            input = getInput<int>(menu, 1,lastItem);//get user input, only accept inputs between 1 and 5
            system(CLEAR_COMMAND);  //clear terminal for ease of use
            switch(input){
                case 1://Create a Student Record
                    createStudentRecord();
                    break;
                case 2://Update student Grade
                    updateGrades();
                    break;
                case 3://Display Student Record
                    displayStudentRecord();
                    break;
                case 4://Display all Student Records
                    displayAllStudentRecords();
                    break;
                case 5://Display a class's average
                    displayClassAverage();
                    break;
                case 6://Display a student's average
                    displayStudentAverage();
                    break;
                case 7://Delete Records
                    deleteRecords();
                    break;
                case EXIT://Exit
                    break;
            }
        }
    }while(input != lastItem);
    cout << "Have a nice day!";
    return 0;
}
