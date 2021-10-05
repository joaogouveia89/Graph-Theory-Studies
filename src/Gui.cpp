#include"Gui.h"

// size of window
const int width = 800;
const int height = 600;

// wxWidgets APP
IMPLEMENT_APP(GraphApp);


bool GraphApp::OnInit()
{
    // create window with name and show it
    GraphTheoryFrame* mainFrame = new GraphTheoryFrame(wxT("Graph Theory"));
    mainFrame->Show(true);

    return true;
}

// wxWidgets FRAME
GraphTheoryPanel::GraphTheoryPanel(wxFrame* parent) : wxPanel(parent){
    graph = std::make_unique<Graph>();
    graph->SetDataSetChangedCallback([&](){
        this->paintNow();
    });
}

// wxWidgets FRAME
GraphTheoryFrame::GraphTheoryFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    GraphTheoryPanel* panel = new GraphTheoryPanel(this);
    this->Centre();
}

void GraphTheoryPanel::paintEvent(wxPaintEvent &evt)
{
    wxPaintDC dc(this);
    render(dc);
}

void GraphTheoryPanel::paintNow()
{
    wxClientDC dc(this);
    render(dc);
}

void GraphTheoryPanel::render(wxDC &dc)
{
    auto points = graph->GetNodesPoints();
    int nodeRadius = graph->NodeRadius();

    for(auto p : points){
        dc.DrawCircle( p, nodeRadius );
    }
}

void GraphTheoryPanel::doubleClickListener(wxMouseEvent & evt){
    wxClientDC dc(this);
    graph->CreateNode(evt.GetLogicalPosition(dc));
}

BEGIN_EVENT_TABLE(GraphTheoryPanel, wxPanel)
EVT_PAINT(GraphTheoryPanel::paintEvent) // catch paint events
EVT_LEFT_DCLICK(GraphTheoryPanel::doubleClickListener)
END_EVENT_TABLE()