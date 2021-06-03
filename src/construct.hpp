#include <vector>
#include <string>
#include <map>
using namespace std;

// structures
enum generictype{
    none = 0,
    mstruct = 1,
    mclass = 2
};

struct genericblock{
    generictype type;
    string name;
    vector<pair<string, string>> members;
};

// functions
void construct(vector<string> args);
