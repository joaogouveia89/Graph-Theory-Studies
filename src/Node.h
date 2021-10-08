#include <wx/gdicmn.h>

class Node
{
private:
    int _id;
    wxPoint _location;
public:
    Node(int id);
    wxPoint Location() const { return _location; }
    int Id() const { return _id; }
    ~Node();
    void SetPosition(int x, int y);
};