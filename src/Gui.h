#include <wx/wx.h>
#include<memory>
#include<string>
#include <fstream>
#include "Graph.h"

class GraphTheoryFrame; // forward declaration

class GraphTheoryPanel : public wxPanel
{

private:
    std::unique_ptr<Graph> graph;
    GraphTheoryFrame* _parent;
public:
    // constructor / desctructor
    GraphTheoryPanel(GraphTheoryFrame* parent);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);
};

// frame containing all control elements
class GraphTheoryFrame : public wxFrame
{
public:
    // constructor / desctructor
    GraphTheoryFrame(const wxString &title);

};

class GraphApp : public wxApp
{
public:
    // events
    virtual bool OnInit();
};