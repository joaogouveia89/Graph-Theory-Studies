#include <wx/gdicmn.h>

class Node
{
private:
    wxPoint _location;
    bool _selected { false };
public:
    Node(wxPoint location);
    wxPoint Location() const { return _location; }
    bool IsSelected() const { return _selected; }
    ~Node();
};