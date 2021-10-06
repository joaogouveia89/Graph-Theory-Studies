#include "Graph.h"

Graph::Graph(){

}

Graph::~Graph(){
    
}

bool Graph::CreateNode(wxPoint nodePoint){
    //checking wether the nodePoint already has an created node, if so, return false
    // thanks to https://stackoverflow.com/questions/481144/equation-for-testing-if-a-point-is-inside-a-circle
    int nodeRadius = NodeRadius();
    int condition;
    for(auto n : _nodes){
        condition = pow((nodePoint.x - n.Location().x), 2) + pow((nodePoint.y - n.Location().y), 2);
        if(condition < pow(nodeRadius, 2) * 3){
            return false;
        }
    }
    Node n(nodePoint);
    _nodes.emplace_back(std::move(n));
    callback();
    return true;
}

void Graph::SetDataSetChangedCallback(NewNodeListener callback){
    this->callback = callback;
}

std::vector<Node> Graph::GetNodes() const{
    //Similar to map std::transform(_nodes.begin(), _nodes.end(), back_inserter(points), [](Node node) { return node.Location(); });
    return _nodes;
}