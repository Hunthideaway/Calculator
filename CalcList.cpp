
#include "CalcList.hpp"

//constructor implementation

CalcList:: CalcList(){

    //creating header and trailer nodes
    header = new Calcnode;
    trailer= new Calcnode;

    header->next=trailer; //making header point to trailer and vice versa
    trailer->prev=header; 

}

//destructor implementation

CalcList:: ~CalcList(){
    while (!checkEmpty()){
        deleteNode(header->next);  //starts deleting from the node after header
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

//Utility Functions
void CalcList::addNode(Calcnode* node, const double& value){
        numOperations++;                                        //everytime a operation is done the counter is incremented
}

void CalcList::deleteNode(Calcnode* node){
        numOperations--;                        //everytime a operation is removed the counter is incremented
}


double CalcList::total() const{
   
}

void CalcList::newOperation(const FUNCTIONS func, const double operand){

}

void CalcList::removeLastOperation(){

}

std::string CalcList:: toString(unsigned short precision) const{

}