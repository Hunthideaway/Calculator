/*
Author: Randall Hunt 
Program: CalcList.hpp 
Description: Header for CalcList.cpp to reference.
*/

#ifndef CALCLIST_H //check if it has been previously defined 

#define CALCLIST_H //define 

//headers 
#include "CalcListInterface.hpp" //reference to header file 
#include <iostream> //basic input and output functions 
#include <stdexcept> //used by the library and porgram to report common errors 
#include <sstream> //enables interoperation between stream buffers and string objects
#include <iomanip> //header that is used to manipulate the output

class CalcList : public CalcListInterface { //create a class CalcList, under parent class CalcListInterface 
public: //public = access specifier, can access
    int numOperations=0; //variable keeps trak of the number of operations

    CalcList(); //empty list constructor 
    ~CalcList(); //destructor - deallocate memory 

    //overridden function from abstract parent class shown below
    
    double total() const; //declaring a variable, total, that is const (cant be modified directly by the user)
    void newOperation(const FUNCTIONS func, const double operand); //create a new operation 
    void removeLastOperation();  //remove the last operation
    std::string toString(unsigned short precision) const; //variable precision declared as a string
    

    //adding Utility functions
    void addNode(Calcnode* node, const double& value);  //adds a new node right before the trailer
    void deleteNode(Calcnode* node);   //deletes the node that is before the trailer i.e the last one

    bool checkEmpty() const;   //checks if the list is empty of not


private: //private = access specifier, cannot access 

    struct Calcnode { //structure Calcnode to store the data 
        double prevValue=0.0; //used to store the previous value 

        double afterValue=0.0; //stores the value after operations 

        double operandUsed=0.0; //used to store current value before operations 

        FUNCTIONS operation; //declare operations, which will be used to reference different operations (+, -, *. / )
        Calcnode* prev = nullptr; //pointer for the previous value, initialized (nullptr = 0 as and address)
        Calcnode* next = nullptr; //pointer to the next value, intialized 
    };

    double currentTotal; //declare value for total value
    Calcnode* head; //pointer for the head value
    Calcnode* trailer; //pointer for the trailer value  

};


#endif //terminate 