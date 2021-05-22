#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

#include "parser.hpp"

vector<string> commands = { "log", "system" };

bool builtinEx(string cm){
    for(string c : commands){
        if(cm == c){
            return true;
        }
    }
    
    return false;
}

string execbuiltin(string funcname, vector<string> args){
    if(funcname == "log"){
        cout << args[0];
        if(args.size() > 1){
            if(!convertBool(args[1])){
                return "1";
            }
        }
        cout << endl;
        return "1";
    }
    else if(funcname == "system"){
        system(args[0].c_str());
        return "1";
    }

    return "0";
}