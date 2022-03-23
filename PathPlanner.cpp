
#include "PathPlanner.h"

#include <iostream>




PathPlanner::PathPlanner(Env envir, int rows, int cols){

    // stores total size of rows and columns of map
    this->rows = rows;
    this->cols = cols;
    this->env = envir;
    
   
}

PathPlanner::~PathPlanner(){

    
}

void PathPlanner::initialPosition(int row, int col){
    
    /* 
    * scans through map for coordinates of start symbol
    * and the stores those row and column coorindates
    */

    for (int i = 0; i < row;i++){
        for(int j = 0; j < col;j++){
            if (env[i][j] == SYMBOL_START){
                startRow = i;
                startCol = j;
            }
        }
    }
}

void PathPlanner::finalPosition(int row, int col){
    
    /* 
    * scans through map for coordinates of goal symbol
    * and the stores those row and column coorindates
    */

    for (int i = 0; i< row;i++){
        for(int j = 0; j < col;j++){
            if (env[i][j] == SYMBOL_GOAL){
                finalRow = i;
                finalCol = j;
            }
        }
    }
}

NodeList* PathPlanner::getReachableNodes(){
    // calls function to store starting coordinates
    NodeList* openList = new NodeList();
    NodeList* closeList = new NodeList();

    this->initialPosition(rows,cols);
   

    /* 
    * creates first node for openlist which contains coordinates
    * for starting position
    */
    
    Node* p = new Node(startRow,startCol, 0);
    
    openList->addBack(p);
    

    bool noPValue = false;
   
    while (!noPValue){
        
        int col = p->getCol();
        int row =  p->getRow();
        int dis = p->getDistanceToS();
        
        bool pValue = true;
        
        // up
        if (env[row - 1][col] != SYMBOL_WALL){
            Node*q = new Node(row - 1, col, dis + 1);
            openList->addBack(q);
        } // right
        
        if (env[row][col + 1] != SYMBOL_WALL){
             Node*q = new Node(row, col + 1, dis + 1);
             openList->addBack(q);
        } // down
    
        if (env[row + 1][col] != SYMBOL_WALL){
            Node*q = new Node(row + 1, col, dis + 1);
            openList->addBack(q);
        } // left
    
        if (env[row][col - 1] != SYMBOL_WALL){
           Node*q = new Node(row, col - 1, dis + 1);
           openList->addBack(q);
        }
        


        closeList->addBack(p);
        
    
        int length = openList->getLength();

        for (int i = 0; i < length; i++){
            if (!closeList->containsNode(openList->get(i)) && pValue){
                p = openList->get(i);
                pValue = false;
            }
            else if ((i == length - 1) && pValue) {
                noPValue = true;
            }
        }   

    } 


    delete openList;
    return closeList;

}

NodeList* PathPlanner::getPath(){

    
    NodeList* closeList = this->getReachableNodes();
    NodeList* path = new NodeList();
    
    this->finalPosition(rows,cols);
   
    // adds goal node to start of nodelist
    int length = closeList->getLength();
    Node* goal = new Node(finalRow, finalCol, 0);
    
    for (int i = 0; i < length; i++){
        if((closeList->get(i)->getCol() == goal->getCol()) 
          && (closeList->get(i)->getRow() == goal->getRow()))
        {
            Node* g = closeList->get(i);
            path->addBack(g);
        }
    }
    
    Node* currNode = path->get(0);
    
    while (currNode != closeList->get(0)){
        
        int currNodeCol = currNode->getCol();
        int currNodeRow = currNode->getRow();
        int currNodeDis = currNode->getDistanceToS();
        
        for (int i = 0; i < length; i++)
        {
            int nextNodeCol = closeList->get(i)->getCol();
            int nextNodeRow = closeList->get(i)->getRow();
            int nextNodeDis = closeList->get(i)->getDistanceToS();
            // up
            if((nextNodeRow == currNodeRow - 1) && (nextNodeCol == currNodeCol) 
              && (nextNodeDis == currNodeDis - 1))
            {
                currNode = closeList->get(i);
                path->addBack(currNode);
            }
            // right
            else if((nextNodeRow == currNodeRow) && (nextNodeCol == currNodeCol - 1) 
              && (nextNodeDis == currNodeDis - 1))
            {
                currNode = closeList->get(i);
                path->addBack(currNode);
            }
             // down
            else if((nextNodeRow == currNodeRow + 1) && (nextNodeCol == currNodeCol) 
              && (nextNodeDis == currNodeDis - 1))
            {
                currNode = closeList->get(i);
                path->addBack(currNode);
            }
             // left
            else if((nextNodeRow == currNodeRow) && (nextNodeCol == currNodeCol + 1) 
              && (nextNodeDis == currNodeDis - 1))
            {
                currNode = closeList->get(i);
                path->addBack(currNode);
            }
        }

    }
    
    path->reverse();
    delete currNode;
    return path;
   
}

