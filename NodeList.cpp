#include "NodeList.h"
#include <iostream>



NodeList::NodeList(){
    this->nodes = new Node*();
    this->length = 0;
}


NodeList::~NodeList(){

    delete[] nodes;


}

NodeList::NodeList(NodeList& other){

    length = other.length;
    nodes = new Node*(*other.nodes);

}


int NodeList::getLength(){

    return length;
   
}


NodePtr NodeList::get(int i){

    return nodes[i];

}

void NodeList::addBack(NodePtr newNode){

    Node** temp = new Node*[length + 1];

    if(this->length == 0){
        nodes[0] = newNode;
        this->length++;
    }
    else{
        for (int i = 0; i < length;i++){
            temp[i] = nodes[i];
        }
        temp[this->length] = newNode;
        nodes = temp;
        this->length++;
    }

}

bool NodeList::containsNode(NodePtr node){
    bool doesContain = false;
    for (int i = 0; i < length; i++ ){
        if ((nodes[i]->getCol() == node->getCol()) && (nodes[i]->getRow()==node->getRow())){
            doesContain = true;
        }
    }
    return doesContain;
   
}

void NodeList::clear(){

    for (int i = 0; i < length; i++){
        nodes[i] = nullptr;
    }
    length = 0;
   
}

void NodeList::reverse(){

    Node* temp = nullptr;

    for (int i = 0; i < length / 2; i ++){
        temp = nodes[i];
        nodes[i] = nodes[length - 1 - i];
        nodes[length - 1 - i] = temp;
    }
}