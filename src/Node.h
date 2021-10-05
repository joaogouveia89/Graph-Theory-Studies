#include <wx/gdicmn.h>

class Node
{
private:
    wxPoint _location;
public:
    Node(wxPoint location);
    wxPoint Location() const { return _location; }
    ~Node();
};