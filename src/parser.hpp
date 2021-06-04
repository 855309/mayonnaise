#include <vector>
#include <string>
using namespace std;

#include "construct.hpp"

string parseAndExecuteFunction(string exp);
vector<string> parseFunctionArgs(string exp);
bool convertBool(const string& exp);
double todouble(string vl);
string getExceptStr(const string& exp);
string trimToDelimiterNonStr(string origin, char del);
generictype parseGenericType(string exp);
