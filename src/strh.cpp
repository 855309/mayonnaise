#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

#include "strh.hpp"

string ltrim(string s) {
    s.erase(s.begin(), find_if(s.begin(), s.end(),
            not1(ptr_fun<int, int>(isspace))));
    return s;
}

string rtrim(string s) {
    s.erase(find_if(s.rbegin(), s.rend(),
            not1(ptr_fun<int, int>(isspace))).base(), s.end());
    return s;
}

string trim(string s) {
    return ltrim(rtrim(s));
}

vector<string> splitstr(string origin, char delimiter)
{
    string text = origin + delimiter;

    stringstream stream;
    vector<string> strVector;

    for (auto c : text)
    {
        if (c == delimiter)
        {
            strVector.push_back(stream.str());
            stream.str("");
        }
        else
        {
            stream << c;
        }
    }

    return strVector;
}

vector<string> splitstrcount(string origin, char delimiter, int count)
{
    string text = origin;

    stringstream stream;
    vector<string> strVector;

    bool finished = false;

    for (auto c : text)
    {
        if (strVector.size() == count)
        {
            finished = true;
        }

        if (c == delimiter)
        {
            if (finished)
            {
                stream << c;
            }
            else
            {
                strVector.push_back(stream.str());
                stream.str("");
            }
        }
        else
        {
            stream << c;
        }
    }

    strVector.push_back(stream.str());

    return strVector;
}