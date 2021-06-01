#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "parser.hpp"
#include "strh.hpp"

string trimToDelimiterNonStr(string origin, char del){
    string ext = "";

    bool ins = false;
    for(char c : origin){
        if(c == '"'){
            if(ins){
                ins = false;
            }
            else{
                ins = true;
            }
        }
        else if(!ins){
            if(c == del){
                break;
            }
        }

        ext += c;
    }

    return ext;
}

string getExceptStr(string exp){
    string sn = "";
    
    bool ins = false;
    for(char c : exp){
        if(c == '"'){
            if(ins){
                ins = false;
            }
            else{
                ins = true;
            }
        }
        else if(!ins){
            sn += c;
        }
    }

    return sn;
}

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

vector<string> parseFunctionArgs(string exp){ // func(1, "a", 47, 8 + 99)
    vector<string> srr = splitstrcount(exp, '(', 1);
    //string funcname = srr[0];
    vector<string> args;
    string stream;
    bool parsingStr = false;

    int functionQueue = 0;

    for(char c : srr[1]){ // abc(bbbbb("c"), 2)
        if(!parsingStr){
            if(c == ',' && functionQueue == 0){
                args.push_back(stream);
                stream = "";
                continue;
            }
            else if(c == ')'){
                if(functionQueue == 0){
                    args.push_back(stream);
                    stream = "";
                    break;
                }
                else{
                    functionQueue--;
                    stream += c;
                    continue;
                }
            }
        }

        if(c == '\"'){
            stream += c;

            if(parsingStr){
                //args.push_back(stream.str());
                parsingStr = false;
                continue;
            }
            else{
                parsingStr  = true;
                continue;
            }

            // LAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAN
        }
        else{
            if(!parsingStr){
                if(c == '('){
                    functionQueue++;
                }
                
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
