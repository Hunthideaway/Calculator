/*
Authors: Raed Seraj, Randall Hunt 
Program: Calculator
Driver: Randall Hunt 
Navigator: Raed Seraj 
*/
#include "CalcList.hpp"

CalcList::CalcList()//constructor implementation
{
    Calcnode* def = new Calcnode; //creating default node 

    header = new Calcnode; //initialize the header 
    trailer = new Calcnode; //initialize the trailer 
    def->previousValue = 0; //declare the default value 
    def->secondValue = 0; //declare the default value 
    def->current = 0; //declare the default value 
    def->operation = ADDITION; //declare the default value 
    currentTotal = 0; //initialize the currentTotal by setting it to 0 

    // connect head and trailer to default node
    def->previous = header;
    def->next = trailer;
    header->next = def;
    trailer->previous = def;
}

CalcList::~CalcList() //destructor implementation
{
    Calcnode* node = header; //start the node at the header 
    Calcnode* temp; //create a temperary variable to store the variable before deleting 
    while (node != trailer) //loop that continues while the node doesnt equal the trailer 
    {
        temp = node->next;//the variable temp stores the value of the next node 
        delete node; //we delete the node 
        node = temp; //the node is set to the next value 
    }
    delete trailer; //once we have deleted all other values, delete the trailer 
}

double CalcList::total() const //total 
{
    return currentTotal; //returns the current total
}

void CalcList::newOperation(const FUNCTIONS func, const double operand)
{
    Calcnode* x = new Calcnode;      //create a new node, x
    Calcnode* last = nullptr;        //pointer to node before the trailer
    x->previousValue = currentTotal; //store the previous value, being the current total
    x->current = operand;            //store the current value within operand for use within the operations

    //identify which operation the user is attempting and then calculate it
    if (func == ADDITION)
    {                            //if the user enters addition
        currentTotal += operand; //add the current total and the user input together and store
        x->operation = ADDITION; //store the operation
    }
    else if (func == SUBTRACTION)
    {                               //if the user enters subtraction
        currentTotal -= operand;    //subtract the current total and the user input and then store them
        x->operation = SUBTRACTION; //store the operation
    }
    else if (func == MULTIPLICATION)
    {                                  //if the user enters mutliplication
        currentTotal *= operand;       //multiply the current total by the user input
        x->operation = MULTIPLICATION; //store the operation
    }
    else if (func == DIVISION)
    { //if the user enters division
        if (operand == 0)
        {                                                               //if the user enters 0
            delete x;                                                   //delete the value
            throw std::invalid_argument("You cannot divide by zero!!"); //inform the user that you cannot divide by 0
            return;                                                     //end the program
        }
        else
        {                            //else if the number is not 0
            currentTotal /= operand; //divide the previous value by the current value
            x->operation = DIVISION; //store the operaton
        }
    }
    x->secondValue = currentTotal; //this updates the current total after the operation
    last = trailer->previous;      //storing the last node
    last->next = x;                //links the last node to x
    x->previous = last;            //links the previous node to last
    x->next = trailer;             //links the next value to the trailer
    trailer->previous = x;         //links trailer to x
}

void CalcList::removeLastOperation()
{
    Calcnode* none = header;                          //variable that will be used if there is no operation
    Calcnode* previous = trailer->previous->previous; //this pointer references the node before the one that will be deleted
    Calcnode* nodeDelete = previous->next;            //this pointer stores the node that will be deleted

    if (none->next->next == trailer)
    {                                                                      //if there are no operations that can be removed, do the following
        throw std::invalid_argument("No operation available to remove!!"); //inform the user that there is no operation that can be removed
        return;                                                            //end the program
    }
        currentTotal = previous->secondValue; //this removes the last operation
        previous->next = trailer;             //unlink the previous node
        trailer->previous = previous;         //unlink the previous node
        delete nodeDelete;                    //delete the node
}


std::string CalcList::toString(unsigned short precision) const
{
    int count = 0; // number of nodes (doesn't count head, trailer or default node)
    Calcnode* countNodes = header->next; //this is used to count the number of nodes 
    while (countNodes->next != trailer) //loop that continues until it reaches the trailer
    {
        countNodes = countNodes->next; //points to the next node 
        count++; //increment 
    }

    std::stringstream a; //declare the variable for the string
    a.precision(precision); //string precision, setting the number of decimals 
    Calcnode* beforeEnd = trailer->previous; //pointer to the node before the trailer

    while (beforeEnd->previous != header)
    { //as long as the node is not the header, do the following
    //print the values for the nodes 
        if (beforeEnd->operation == ADDITION)
        { //if the users operation is addition, do the following
            a << count << std::fixed << ": " << beforeEnd->previousValue << "+" << beforeEnd->current << "=" << beforeEnd->secondValue << std::endl;
        }//
        else if (beforeEnd->operation == SUBTRACTION)
        { //if the users operation is addition, do the following
            a << count << std::fixed << ": " << beforeEnd->previousValue << "-" << beforeEnd->current << "=" << beforeEnd->secondValue << std::endl;
        }
        else if (beforeEnd->operation == MULTIPLICATION)
        { //if the users operation is mitliplication do the following
            a << count << std::fixed << ": " << beforeEnd->previousValue << "*" << beforeEnd->current << "=" << beforeEnd->secondValue << std::endl;
        }
        else if (beforeEnd->operation == DIVISION)
        { //if the users operation is division do the following
            a << count << std::fixed << ": " << beforeEnd->previousValue << "/" << beforeEnd->current << "=" << beforeEnd->secondValue << std::endl;
        }

        count--; //decrement 
        beforeEnd = beforeEnd->previous; //after the first operation, move onto the next one
    }
    return a.str(); //return the string
}
