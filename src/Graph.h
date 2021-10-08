#include<vector>
#include <wx/gdicmn.h>
#include <iostream>
#include <functional>
#include<memory>
#include<algorithm>
#include<math.h>
#include <fstream>
#include <regex>
#include<vector>

#include "Node.h"

typedef std::function<void ()> NewNodeListener;  

class Graph
{
private:
    std::vector<Node> _nodes;
    std::vector<std::vector<int>> _distanceMatrix;
    NewNodeListener callback;
    int _containerWidth, _containerHeight, _numberOfNodes;
public:
    Graph(int containerWidth, int containerHeight);
    ~Graph();

    void SetDataSetChangedCallback(NewNodeListener callback);

    std::vector<Node> GetNodes() const;

    void LoadFromTxtFile(const std::string filePath);


    int NodeRadius() const { return 20; }
};