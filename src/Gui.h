#include <wx/wx.h>
#include<memory>
#include "Graph.h"

class GraphTheoryPanel : public wxPanel
{

private:
    std::unique_ptr<Graph> graph;
public:
    // constructor / desctructor
    GraphTheoryPanel(wxFrame* parent);

    void doubleClickListener(wxMouseEvent & evt);

    void paintEvent(wxPaintEvent & evt);
    void paintNow();
    void render(wxDC& dc);
    DECLARE_EVENT_TABLE()
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