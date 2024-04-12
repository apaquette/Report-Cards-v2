#ifndef GETUSERINPUT_H_INCLUDED
#define GETUSERINPUT_H_INCLUDED
#include<iostream>
#include<limits>
using namespace std;

void invalidInput(){//handle invalid inputs
    cin.clear();//clear cin
    cin.ignore(numeric_limits<streamsize>::max(),'\n');//ignore size limits
    system("CLS");  //clear terminal for ease of use
    cout << "!!!\aInvalid input!!!\n";//output error to terminal
}

template<class T>//get any input from the user
T getInput(string message){
    T input;
    do{
        if(cin.fail())
            invalidInput();
        cout << message;
        cin >> input;
    }while(cin.fail());
    return input;
}

template<class T>//get an input between two values
T getInput(string message, const T minValue, const T maxValue){
    T input;
    do{//loop while input is invalid
        cout << message;
        cin >> input;
        if(cin.fail() || input > maxValue||input < minValue)
            invalidInput();
    }while(cin.fail() || input > maxValue || input < minValue);
    return input;
}

template<class T>//get an input with a list of legal/illegal value. Bool determines which.
T getInput(string message, const bool legal, const T value[], int size=1){
    T input;
    bool illegal;
    do{//loop while input is invalid
        illegal = true;

        cout << message;
        cin >> input;

        for (int x=0; x<size; x++)//check whether the entered value is allowed
            if((legal && input == value[x])||(!legal && input != value[x]))//determine whether the input is legal
                illegal = false;
        if(cin.fail()||illegal)//if input is invalid data type OR illegal, run invalid input function
                invalidInput();
    }while(cin.fail()||illegal);
    return input;
}

#endif // GETUSERINPUT_H_INCLUDED
