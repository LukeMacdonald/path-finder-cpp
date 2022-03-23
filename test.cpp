#include <iostream>
using namespace std;

int main(){

    char c = 'c';
    char b = 'b';
    char d = 'd';
    char* ptr = &c;
    char* ptr2 = &b;
    char* ptr3 = &d;


    char** nodeList;
    
    nodeList[0] = ptr;
    nodeList[1] = ptr2;
    nodeList[2] = ptr3;

    for (int i = 0; i < 3; i++){
        cout<< *nodeList[i];
    }
}