#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathPlanner.h"

// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printPath(Env env, NodeList* solution, int rows, int cols);
void delete_env(Env env,int rows,int cols);
Env make_env(const int rows, const int cols,std::string envir);

int main(int argc, char** argv){

  char symbol;
    int rows = 1;
    int cols = 1;
    std::string map = "";

    while(std::cin.get(symbol)){
        if (symbol == '\n'){
            rows++;
        }
        else{
            cols++;
        }
        map += symbol;
    }
    
    cols /= rows;

    // Load Environment 
    Env env = make_env(rows, cols, map);
    
    // Solve using forwardSearch
    PathPlanner* pathplanner = new PathPlanner(env, rows, cols);

    NodeList* reachablePositions = nullptr; 
    reachablePositions = pathplanner->getReachableNodes();

    // Get the path
    // THIS WILL ONLY WORK IF YOU'VE FINISHED MILESTONE 3
    NodeList* solution = pathplanner->getPath();

    //print the path
    printPath(env, solution,rows, cols);
   
    delete pathplanner;
    delete reachablePositions;
    delete solution; 
    delete_env(env,rows,cols);

}

void printPath(Env env, NodeList* solution, int row, int col) {
    int length = solution->getLength();
    
    for (int i = 0; i < length - 1; i++){
        int col1 = solution->get(i)->getCol();
        int col2 = solution->get(i + 1)->getCol();
        int row1 = solution->get(i)->getRow();
        int row2 = solution->get(i + 1)->getRow();
        if (env[row1][col1]!= SYMBOL_START)
        {
            if (row2 == row1 - 1){
                env[row1][col1] = '^';
            }
            else if (col2 == col1 + 1){
                env[row1][col1] = '>';
            }
            else if (row2 == row1 + 1){
                env[row1][col1] = 'v';
            }
            else if (col2 == col1 - 1){
                env[row1][col1] = '<';
            }
        }
    }

    for (int j = 0; j < row;j++){
        for(int k = 0; k < col;k++){
            std::cout << env[j][k];
           
    }if (j < row - 1){
        std::cout << std::endl;
    }
    }
}

Env make_env(const int rows, const int cols,std::string map) {
 
    Env env = nullptr;

    if (rows >= 0 && cols >= 0) {
        env = new char*[rows];
        for (int i = 0; i != rows; ++i) {
            env[i] = new char[cols];
        }
    }
    char p[map.length()];
    int pItem = 0;
 
    for (int i = 0; i < sizeof(p); i++) {
        if (map[i] != '\n'){
            p[pItem] = map[i];
            pItem++;
        }
    }
    
    int counter = 0;
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols;j++){
            env[i][j] = p[counter];
            counter++;
        }
    } 
   return env;
}
void delete_env(Env env, int rows, int cols) {
   if (rows >= 0 && cols >= 0) {
      for (int i = 0; i != rows; ++i) {
         delete env[i];
      }
      delete env;
   }

   return;
}




