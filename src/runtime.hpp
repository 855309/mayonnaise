#include <string>
using namespace std;

int executeExpression(string expression);

struct mvariable{
    string name;
    string value;
};

struct forblock{
    string exp;
    vector<string> code;
};

struct rangeobj{
    int start;
    int end;
};

struct rangeloopblock{
    rangeobj range;
    string var;
    vector<string> code;
};

struct ifblock{
    string exp;
    vector<string> code;
};

struct mfunction{
    string name;
    vector<string> code;
};