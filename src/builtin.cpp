#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <string.h>
using namespace std;

#include "parser.hpp"
#include "versioncontrol.hpp"

string license = "MIT License\n\nCopyright (c) 2021 fikret0\n\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files (the \"Software\"), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions:\n\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.\n\nTHE SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.";

vector<string> commands = {  // built-in command list
    "log", 
    "system", 
    "license", 
    "sleep", 
    "stdin", 
    "readin", 
    "version",
    
    // string operations
    "strconcat",
    "strcmp",
    "streq"
};

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
    else if(funcname == "strconcat"){
        string g = "";
        for(string arg : args){
            g += arg;
        }

        return g;
    }
    else if(funcname == "license"){
        return license;
    }
    else if(funcname == "sleep"){
        double timef = 1;
        if(!args[0].empty()){
            try{
                timef = stod(args[0]);
            }
            catch(const std::exception& e){
                return "0";
            }
        }

        string comm = "sleep " + to_string(timef);
        system(comm.c_str());

        return "1";
    }
    else if(funcname == "stdin"){
        if(!args[0].empty()){
            cout << args[1];
        }

        string ip;
        cin >> ip;

        return ip;
    }
    else if(funcname == "readin"){
        if(!args[0].empty()){
            cout << args[1];
        }

        string ip;
        cin.ignore();
        getline(cin, ip);

        return ip;
    }
    else if(funcname == "version"){
        return getVer();
    }
    else if(funcname == "strcmp"){
        return to_string(strcmp(args[0].c_str(), args[1].c_str()));
    }
    else if(funcname == "streq"){
        string base = args[0];
        for(string a : args){
            if(a != base){
                return "false";
            }
        }

        return "true";
    }

    return "0";
}