#include "Graph.h"

Graph::Graph(int containerWidth, int containerHeight): _containerWidth(containerWidth), _containerHeight(containerHeight){}

Graph::~Graph(){}

void Graph::SetDataSetChangedCallback(NewNodeListener callback){
    this->callback = callback;
}

//Load the graph by reading the distance matrix provided by user
void Graph::LoadFromTxtFile(const std::string filePath){
    std::ifstream filestream(filePath);
    std::string line;
    std::vector<int> currentRow;
    std::regex lineRegex("\\s+");
    std::sregex_token_iterator end;

    //The idea on these three next variables is to get the node with more connections which will be placed in the middle of the graph
    int centralNodeId = 0;
    int centralNodeInfCount = -1;
    int currentNodeId = 0;
    int currentNodeInfCount = 0;
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            currentRow.clear();
            std::sregex_token_iterator iter(line.begin(),
                line.end(),
                lineRegex,
                -1);
            
            for ( ; iter != end; ++iter){
                currentRow.emplace_back(std::stoi(*iter));
                if(currentRow.back() == -1){
                    currentNodeInfCount++;
                }
            }
            if(centralNodeInfCount == -1 || currentNodeInfCount <= centralNodeInfCount){
                centralNodeId = currentNodeId;
                centralNodeInfCount = currentNodeInfCount;
            }
            _distanceMatrix.emplace_back(currentRow);
            currentNodeId++;
            currentNodeInfCount = 0;
        }

        _numberOfNodes = _distanceMatrix.size();
        std::cout << "Loaded graph with " << _numberOfNodes << " nodes and the central node is " << centralNodeId << "\n";
        std::cout << "Assigning node positions...\n";
        //Creating the central node
        std::shared_ptr<Node> n = std::make_shared<Node>(centralNodeId);
        std::cout << "_containerWidth = " << _containerWidth << " _containerHeight = " << _containerHeight << std::endl;
        n->SetPosition(_containerWidth/2, _containerHeight/2);
       _nodes.emplace_back(std::move(n));
       int currentAngle = 0;
       auto _centralNodeLinks = _distanceMatrix.at(centralNodeId);
       int angleGrowRatio = 360 / _numberOfNodes;
       // Create nodes that are connected to centralNode increasing the angle of the position regarding it
        for(int node = 0; node < _numberOfNodes; node++){
            if(node != centralNodeId && _centralNodeLinks.at(node) != -1){
                std::shared_ptr<Node> nodePtr = std::make_shared<Node>(node);
                //TODO implement a way of user insert the wish scale, in this case is 50 in below lines
                nodePtr->SetPosition(
                    _nodes.front()->Location().x + _centralNodeLinks.at(node) * 50 * cos(currentAngle),
                    _nodes.front()->Location().y + _centralNodeLinks.at(node) * 50 * sin(currentAngle)
                );
                currentAngle += angleGrowRatio;
                _nodes.emplace_back(std::move(nodePtr));
            }
        }
        callback();
    }
}

std::vector<std::shared_ptr<Node>> Graph::GetNodes() const{
    std::vector<std::shared_ptr<Node>> toReturn;

    for(auto nptr : _nodes){
        toReturn.emplace_back(nptr);
    }
    //Similar to map std::transform(_nodes.begin(), _nodes.end(), back_inserter(points), [](Node node) { return node.Location(); });
    return toReturn;
}