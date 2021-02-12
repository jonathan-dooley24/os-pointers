// compile: g++ -std=c++11 -o pointers pointers.cpp
#include <iostream>
#include <string>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <iomanip>

typedef struct Student {
    int id;
    char *f_name;
    char *l_name;
    int n_assignments; 
    double *grades;
} Student;

int promptInt(std::string message, int min, int max);
double promptDouble(std::string message, double min, double max);
void calculateStudentAverage(void *object, double *avg);

int main(int argc, char **argv)
{
    Student student;
    //allocate space for pointers in struct student
    student.f_name = new char[128];
    student.l_name = new char[128];
    student.grades = new double[10];

    // Sequence of user input -> store in fields of `student`
    student.id = promptInt("Please enter the student's id number: ", 0, 999999999);

    //may need error-checking to ensure data type for user response
    std::cout << "Please enter the student's first name: ";
    std::cin >> student.f_name;
    std::cout << "Please enter the student's last name: ";
    std::cin >> student.l_name;

    student.n_assignments = promptInt("Please enter how many assignments were graded: ", 1 , 134217728);
    printf("\n");

    std::string message;
    for(int i = 0; i < student.n_assignments; i++){
        std::stringstream message_stream;
        message_stream << "Please enter grade for assignment " << i << ": "; //build the string stream
        message = message_stream.str(); //set message to the string stream value
        student.grades[i] = promptDouble(message, 0.0, 1000.0);
    }

    // Call `CalculateStudentAverage(???, ???)`
    double average = 0.0; //necessary so that ave_ptr is not null. needs initializaion
    double* ave_ptr = &average;
    Student* student_ptr = &student;
    calculateStudentAverage(student_ptr, ave_ptr);

    // Output `average`
    std::cout << "\nStudent: " << student.f_name << " " << student.l_name << " [" << student.id << "]\n  Average grade: "
        << std::fixed << std::setprecision(1) << *ave_ptr << "\n";
    return 0;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid int
   max: maximum value to accept as a valid int
*/
int promptInt(std::string message, int min, int max)
{
    std::string response;
    int int_response = -1; //needs initialization as the return value
    while(1){
        int digits = 0; //counter used to verify that response can be converted to an int
        std::cout << message; //prompt message to console
        std::cin >> response; //store response
        for(int i = 0; i < response.length(); i++){ //for each element in string response
            if(isdigit(response[i])){ //if this element is a digit
                digits++;
            }
        }
        if(digits == response.length()){ //if response is only digits, can be converted to int
            int_response = stoi(response);

            if(int_response < min || int_response > max){ //if response was in digits, but out of bounds
                std::cout << "Sorry, I cannot understand your answer\n";
            }
            else{
                break; //exit loop. response was valid.
            }     
        }
        else{ //response contained non-digits. Unable to convert to int
            std::cout << "Sorry, I cannot understand your answer\n";
        }
    }
    return int_response;
}

/*
   message: text to output as the prompt
   min: minimum value to accept as a valid double
   max: maximum value to accept as a valid double
*/
double promptDouble(std::string message, double min, double max)   
{
    std::string response;
    double dbl_response = -1.0; //needs initialization as the return value
    while(1){
        int digits = 0; //counter used to verify that response can be converted to an int
        int decimal_pt = 0;
        std::cout << message; //prompt message to console
        std::cin >> response; //store response       
        for(int i = 0; i < response.length(); i++){ //for each element in string response
            if(isdigit(response[i])){ //if this element is a digit
                digits++;
            }
            else if((response[i] == '.')  && (i != 0 && i != response.length()-1)){ //else if response element is a decimal pt and not in first or last spot
                decimal_pt++;
            }
        }
        if((decimal_pt == 0 || decimal_pt == 1) && (digits + decimal_pt == response.length())){ //if response is only digits and at most 1 decimal point, convert to dbl
            dbl_response = strtod(response.c_str(), nullptr);

            if(dbl_response < min || dbl_response > max){ //if response was in digits, but out of bounds
                std::cout << "Sorry, I cannot understand your answer\n";
            }
            else{
                break; //exit loop. response was valid.
            }     
        }
        else{ //response contained non-digits. Unable to convert to int
            std::cout << "Sorry, I cannot understand your answer\n";
        }
    }
    return dbl_response;
}

/*
   object: pointer to anything - your choice! (but choose something that will be helpful)
   avg: pointer to a double (can store a value here)
*/
void calculateStudentAverage(void *object, double *avg)
{
    // void* object points to the mem address of student
    Student* stu = (Student*)object; //use stu to take mem address of student and get a pointer to student
    double average = 0.0;
    for(int i = 0; i < stu->n_assignments; i++){
        average += stu->grades[i]; //'stu->grades[i]' is equivalent to '*stu.grades[i]'
    }
    average = average / stu->n_assignments; //divide by total num to get average
    *avg = average; //store avg as the mem address of the newly calculated product
}