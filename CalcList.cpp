#include "CalcList.hpp"

//constructor implementation

CalcList:: CalcList(){
    
    //creating header and trailer nodes
    header = new Calcnode;
    trailer= new Calcnode;


    header->next=trailer; //making header point to trailer and vice versa
    trailer->previous=header; 

}

//destructor implementation

CalcList:: ~CalcList(){

    while (!checkEmpty()){//this loops continues as long as the list is not empty
        delete(header->next);  //starts deleting from the node after header
    }
    //lastly delete header and trailer to realease all memory
    delete header;
    delete trailer;
}

//check empty function implementation

bool CalcList:: checkEmpty() const {
    if (header->next==trailer){
        return true;
    }
    return false;  //returns true if header and trailer pointing to each other, which means list is empty OR else returns false
}



double CalcList::total() const{
   return currentTotal; //returns the current total 
}

void CalcList::newOperation(const FUNCTIONS func, const double operand){
    Calcnode* x = new Calcnode; //create a new node, x
    Calcnode* last = nullptr; //pointer to node before the trailer 
    x->previousValue = currentTotal; //store the previous value, being the current total 
    x->current = operand; //store the current value within operand for use within the operations 

    //identify which operation the user is attempting and then calculate it 
    if(func == ADDITION) { //if the user enters addition 
        currentTotal += operand; //add the current total and the user input together and store 
        x->operation = ADDITION; //store the operation 
    }
    else if(func == SUBTRACTION) { //if the user enters subtraction 
        currentTotal -= operand; //subtract the current total and the user input and then store them
        x->operation = SUBTRACTION; //store the operation 
    }
    else if(func == MULTIPLICATION) { //if the user enters mutliplication 
        currentTotal *= operand; //multiply the current total by the user input 
        x->operation = MULTIPLICATION; //store the operation 
    }
    else if(func == DIVISION ) { //if the user enters division 
        if (operand == 0 ) { //if the user enters 0 
            delete x; //delete the value 
            throw std::invalid_argument("You cannot divide by zero!!"); //inform the user that you cannot divide by 0 
            return; //end the program 
        }
        else { //else if the number is not 0 
            currentTotal /= operand; //divide the previous value by the current value 
            x->operation = DIVISION; //store the operaton 
        }
    }
    x->secondValue = currentTotal; //this updates the current total after the operation
    last = trailer->previous; //storing the last node 
    last->next = x; //links the last node to x 
    x->previous = last; //links the previous node to last 
    x->next = trailer; //links the next value to the trailer
    trailer->previous = x; //links trailer to x 

}

void CalcList::removeLastOperation(){ 

    Calcnode* none = header; //variable that will be used if there is no operation 
    Calcnode* previous = trailer->previous->previous; //this pointer references the node before the one that will be deleted 
    Calcnode* nodeDelete = previous->next; //this pointer stores the node that will be deleted 

    if(none->next->next == trailer) { //if there are no operations that can be removed, do the following
        throw std::invalid_argument("No operation available to remove!!"); //inform the user that there is no operation that can be removed
        return; //end the program 
    }
    else{
    currentTotal = previous->secondValue; //this removes the last operation 
    previous->next=trailer; //unlink the previous node 
    trailer->previous = previous; //unlink the previous node 
    delete nodeDelete; //delete the node 
    }
}

std::string CalcList:: toString(unsigned short precision) const{

}