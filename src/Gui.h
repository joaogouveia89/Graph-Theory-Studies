#include <wx/wx.h>
#include<memory>
#include "Graph.h"

#define ADD_NODE_EVENT 1989
#define REMOVE_NODE_EVENT 1990
#define LINK_NODE_EVENT 1991

class GraphTheoryFrame; // forward declaration

enum class ModeControl{
    ADD_NODE,
    REMOVE_NODE,
    LINK_NODE,
    NONE
};


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
    void PanelClickListener(wxMouseEvent & evt);
};

// frame containing all control elements
class GraphTheoryFrame : public wxFrame
{
public:
    // constructor / desctructor
    GraphTheoryFrame(const wxString &title);
    wxToolBar* toolbar;
    ModeControl currentMode { ModeControl::NONE };

    ModeControl Mode() const{ return currentMode; }
    void ResetMode() { currentMode = ModeControl::NONE; }

    void OnHandleToolbarEvent(wxCommandEvent& event);
};

class GraphApp : public wxApp
{
public:
    // events
    virtual bool OnInit();
};