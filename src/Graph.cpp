#include "Graph.h"

Graph::Graph(){

}

Graph::~Graph(){
    
}

void Graph::CreateNode(wxPoint nodePoint){
    Node n(nodePoint);
    _nodes.emplace_back(std::move(n));
    callback();
}

void Graph::SetDataSetChangedCallback(NewNodeListener callback){
    this->callback = callback;
}

std::vector<wxPoint> Graph::GetNodesPoints(){
    std::vector<wxPoint> points;
    std::transform(_nodes.begin(), _nodes.end(), back_inserter(points), [](Node node) { return node.Location(); });
    return points;
}