
#include "Node.h"


Node::Node(int row, int col, int distanceToS){
   this->row = row;
   this->col = col;
   this->distanceToS = distanceToS;
}
    
Node::~Node(){

   //TODO
}

int Node::getRow(){
   return row;
}

int Node::getCol(){
   return col;
}

int Node::getDistanceToS(){
   return distanceToS;
}

void Node::setDistanceToS(int distanceToS){
   this->distanceToS = distanceToS;
}
