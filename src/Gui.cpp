#include"Gui.h"
#include<wx/filename.h>
#include<wx/stdpaths.h>

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
GraphTheoryPanel::GraphTheoryPanel(GraphTheoryFrame* parent) : wxPanel(parent, wxID_ANY){
    _parent = parent;
    
    if(wxGetApp().argc != 2){
        std::cout << "Please indicate the path of matrix file\n";
        exit(0);
    }
    wxString  graphFilePath(wxGetApp().argv[1]);
    auto containerSize = parent->GetSize();
    graph = std::make_unique<Graph>(containerSize.x, containerSize.y);

    graph->SetDataSetChangedCallback([&](){
        this->paintNow();
    });

    graph->LoadFromTxtFile(std::string(graphFilePath.mb_str()));

    this->Bind(wxEVT_PAINT, &GraphTheoryPanel::paintEvent, this);
}

// wxWidgets FRAME
GraphTheoryFrame::GraphTheoryFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    ShowFullScreen(true);
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
    auto nodes = graph->GetNodes();
    int nodeRadius = graph->NodeRadius();
    wxColour colour(0, 0, 255);

    dc.SetPen(*wxBLUE_PEN);
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.SetTextForeground(*wxWHITE);

    for(auto p : nodes){
        dc.DrawCircle( p.Location(), nodeRadius );
        dc.SetPen(*wxWHITE_PEN);
        wxString labelId = wxString::Format(wxT("%i"),p.Id());
        wxPoint labelPosition;
        labelPosition.x = p.Location().x - GetTextExtent(labelId).x/2;
        labelPosition.y = p.Location().y - GetTextExtent(labelId).y/2;
        dc.DrawText(labelId, labelPosition);
    }
}
