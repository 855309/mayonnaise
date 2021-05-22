#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "parser.hpp"
#include "strh.hpp"

bool convertBool(string exp){
    stringstream st;
    st << exp;
    bool s;
    st >> s;
    return s;
}

double todouble(string vl){
    stringstream ss;
    ss << vl;
    double v;
    ss >> v;
    return v;
}

vector<string> parseFunctionArgs(string exp){ // print(5, "string")
    vector<string> srr = splitstrcount(exp, '(', 1);
    //string funcname = srr[0];
    vector<string> args;
    string stream;
    bool parsingStr = false;
    for(char c : srr[1]){
        if(!parsingStr){
            if(c == ','){
                args.push_back(stream);
                stream = "";
                continue;
            }
            else if(c == ')'){
                args.push_back(stream);
                stream = "";
                break;
            }
        }

        if(c == '\"'){
            if(parsingStr){
                //args.push_back(stream.str());
                parsingStr = false;
                continue;
            }
            else{
                parsingStr  = true;
                continue;
            }
        }
        else{
            if(!parsingStr){
                if(c != ' '){
                    stream += c;
                }
            }
            else{
                stream += c;
            }
        }
    }

    return args;
}
