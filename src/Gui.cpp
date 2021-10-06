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
    graph = std::make_unique<Graph>();
    graph->SetDataSetChangedCallback([&](){
        this->paintNow();
    });

    this->Bind(wxEVT_PAINT, &GraphTheoryPanel::paintEvent, this);
    this->Bind(wxEVT_LEFT_DOWN, &GraphTheoryPanel::PanelClickListener, this);
}

// wxWidgets FRAME
GraphTheoryFrame::GraphTheoryFrame(const wxString &title) : wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(width, height))
{
    wxInitAllImageHandlers();
    toolbar = new wxToolBar(this, wxID_ANY);
    wxBitmap add(wxT("../resources/add.png"), wxBITMAP_TYPE_PNG);
    wxBitmap remove(wxT("../resources/exit.png"), wxBITMAP_TYPE_PNG);
    wxBitmap link(wxT("../resources/link.png"), wxBITMAP_TYPE_PNG);
    toolbar->AddTool(ADD_NODE_EVENT, wxT("Add node"), add);
    toolbar->AddTool(REMOVE_NODE_EVENT, wxT("Remove node"), remove);
    toolbar->AddTool(LINK_NODE_EVENT, wxT("Link nodes"), link);
    toolbar->Realize();

    this->Bind(wxEVT_TOOL, &GraphTheoryFrame::OnHandleToolbarEvent, this, ADD_NODE_EVENT);
    this->Bind(wxEVT_TOOL, &GraphTheoryFrame::OnHandleToolbarEvent, this, REMOVE_NODE_EVENT);
    this->Bind(wxEVT_TOOL, &GraphTheoryFrame::OnHandleToolbarEvent, this, LINK_NODE_EVENT);

    wxBoxSizer *vbox = new wxBoxSizer(wxVERTICAL);

    GraphTheoryPanel* panel = new GraphTheoryPanel(this);
    vbox->Add(toolbar, 6, wxEXPAND | wxALL, 0);
    vbox->Add(panel, 1, wxEXPAND | wxALL, 0);
    SetSizer(vbox);
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
    auto points = graph->GetNodes();
    int nodeRadius = graph->NodeRadius();
    wxColour colour(0, 0, 255);

    dc.SetPen(*wxBLUE_PEN);
    dc.SetBrush(*wxBLUE_BRUSH);

    for(auto p : points){
        dc.DrawCircle( p.Location(), nodeRadius );
    }
}

void GraphTheoryPanel::PanelClickListener(wxMouseEvent & evt){
    wxClientDC dc(this);
    if(_parent->Mode() == ModeControl::NONE){

    }else if(_parent->Mode() == ModeControl::ADD_NODE){
        graph->CreateNode(evt.GetLogicalPosition(dc));
        _parent->ResetMode();
    }
}

void GraphTheoryFrame::OnHandleToolbarEvent(wxCommandEvent& event){
    int id = event.GetId();
    switch (id){
        case ADD_NODE_EVENT:
            if(currentMode == ModeControl::NONE){
                currentMode = ModeControl::ADD_NODE;
            }
        break;
    }
}