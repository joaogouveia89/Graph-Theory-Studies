#include<vector>
#include <wx/gdicmn.h>
#include <iostream>
#include <functional>
#include<memory>
#include<algorithm>
#include<math.h>

#include "Node.h"

typedef std::function<void ()> NewNodeListener;  

class Graph
{
private:
    std::vector<Node> _nodes;
    NewNodeListener callback;
public:
    Graph();
    ~Graph();

    void SetDataSetChangedCallback(NewNodeListener callback);

    std::vector<Node> GetNodes() const;

    int NodeRadius() const { return 10; }

    bool CreateNode(wxPoint nodePoint);
};