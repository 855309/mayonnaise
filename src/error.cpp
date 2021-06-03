#include <vector>
#include <string>
#include <iostream>
using namespace std;

#include "error.hpp"

vector<int> nonErrorCodes = { 0, 1000 };

void handleError(int code = 1){
    for(int ec : nonErrorCodes){
        if(ec == code){
            return;
        }
    }

    string errorMessage = "Static unknown failure.";

    if(code == 1){
        errorMessage = "Unrecognizable code block.";
    }
    else if(code == 2){
        errorMessage = "Generic type failure.";
    }

    cerr << " Error code: " << code << endl;

    exit(code); // exit the program after writing the failure to stderr
}