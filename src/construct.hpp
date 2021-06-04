#include <vector>
#include <string>
#include <map>
using namespace std;

// Basic value block.
// Members: name, value.
struct valueblock{
    string name;
    string value;
};

// Generic type.
enum generictype{
    none = 0,
    mstruct = 1,
    mclass = 2
};

// Simple generic block.
struct genericblock{
    generictype type;
    string name;
    vector<valueblock*> members;
};

// functions
void construct(vector<string> args);
void setStructureVal(string objname, string membername);

// callback
vector<genericblock*> getGenericStructures();
