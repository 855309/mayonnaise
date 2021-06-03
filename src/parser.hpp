#include <vector>
#include <string>
using namespace std;

#include "construct.hpp"

string parseAndExecuteFunction(string exp);
vector<string> parseFunctionArgs(string exp);
bool convertBool(string exp);
double todouble(string vl);
string getExceptStr(string exp);
string trimToDelimiterNonStr(string origin, char del);
generictype parseGenericType(string exp);
