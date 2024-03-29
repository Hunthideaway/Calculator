/*
Author: Randall Hunt, Raed Seraj
Program: CalcList.hpp 
Driver: Randall Hunt 
Navigator: Raed Seraj 
*/

#ifndef CALCLIST_H //check if it has been previously defined

#define CALCLIST_H //define

//headers
#include "CalcListInterface.hpp" //reference to header file
#include <iostream>              //basic input and output functions
#include <stdexcept>             //used by the library and porgram to report common errors
#include <sstream>               //enables interoperation between stream buffers and string objects
#include <iomanip>               //header that is used to manipulate the output

class CalcList : public CalcListInterface
{ //create a class CalcList, under parent class CalcListInterface

public:                    //public = access specifier, can access
    CalcList();  //empty list constructor
    ~CalcList(); //destructor - deallocate memory
    double total() const;                                          //declaring a variable, total, that is const (cant be modified directly by the user)
    void newOperation(const FUNCTIONS func, const double operand); //create a new operation
    void removeLastOperation();                                    //remove the last operation
    std::string toString(unsigned short precision) const;          //variable precision declared as a string


private: //private = access specifier, cannot access
    struct Calcnode
    {                            //structure Calcnode to store the data
        double previousValue;  //used to store the previous value
        double secondValue; //stores the value after operations
        double current;   //used to store current value before operations
        FUNCTIONS operation;      //declare operations, which will be used to reference different operations (+, -, *. / )
        Calcnode *previous = nullptr; //pointer for the previous value, initialized (nullptr = 0 as an address)
        Calcnode *next = nullptr; //pointer to the next value, intialized
    };

    double currentTotal; //declare value for total value
    Calcnode *header;          //pointer for the head node
    Calcnode *trailer;         //pointer for the trailer node
};

#endif //terminate