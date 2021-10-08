#include "Node.h"

Node::Node(int id): _id(id) {}

Node::~Node(){
    
}

void Node::SetPosition(int x, int y){
    _location.x = x;
    _location.y = y;
}