/* 
* @author: fikret0
* @date:   ?/??/1945
* @desc:   mayonnaise
*/

#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <queue>
using namespace std;

#include "strh.hpp"
#include "parser.hpp"
#include "../lib/exprtk.hpp"
#include "builtin.hpp"
#include "runtime.hpp"
using namespace exprtk;

vector<char> prohibitedChars = {' ', '(', ')', '[', ']', '*', ',', '.', '='};
vector<mvariable> variables;
vector<mfunction> functions;
string returnval = "";
bool debug = false;

#pragma region functiondefs

bool isFunction(string exp);

bool isArithmetic(string exp);

int executeExpression(string expression);

string getExpressionVal(string exp);

#pragma endregion // allaj88

string getArithmeticVal(string aexpr){
    symbol_table<double> symbol_table;
    for(mvariable v : variables){
        double vll = todouble(v.value);
        symbol_table.add_constant(v.name, vll);
        //cout << v.name << ": " << vll << endl;
    }
    //symbol_table.add_constant(); // juan374623784

    expression<double> expression;
    expression.register_symbol_table(symbol_table);

    parser<double> parser;
    parser.compile(aexpr, expression);

    double val = expression.value();

    if(floor(val) == val){
        int vx = val;
        return to_string(vx);
    }

    return to_string(val);
}

// BELER LIBRARY YA KUSURA BAKMA
bool getBoolVal(string exp){
    if(exp == "true"){
        return true;
    }
    else if(exp == "false"){
        return false;
    }
    else{
        string arrVal = getArithmeticVal(exp);
        if(arrVal == "1"){
            return true;
        }
        else{
            return false;
        }
    }
}


string getVarVal(string name){ // YaAllahu38
    for(mvariable v : variables){
        if(v.name == name){
            return v.value;
        }
    }

    return ""; // bi hata var
}

bool varExists(string name){
    for(mvariable v : variables){
        if(v.name == name){
            return true;
        }
    }

    return false;
}

string parseAndExecuteFunction(string exp){
    returnval = "";
    vector<string> srr = splitstrcount(exp, '(', 1);
    string funcname = srr[0];
    vector<string> args = parseFunctionArgs(exp);
    for(int i = 0; i < args.size(); i++){
        args[i] = getExpressionVal(args[i]);
        
        /*if(isArithmetic(args[i])){
            args[i] = getArithmeticVal(args[i]);
        }
                                                        // BISMILLAHIRAHMANI-ALLAH
        for(mvariable var : variables){
            if(args[i] == var.name){
                args[i] = var.value;
            }
        }*/
    }
    
    vector<string> defs;

    for(int i = 0; i < args.size(); i++){
        string def = "arg" + to_string(i + 1);
        defs.push_back(def);
        mvariable juan;
        juan.name = def;
        juan.value = args[i];

        variables.push_back(juan);
    }

    if(builtinEx(funcname)){
        return execbuiltin(funcname, args);
    }

    for(mfunction fn : functions){
        if(fn.name == funcname){
            for(string cd : fn.code){
                int code = executeExpression(cd);
                if(code == 960){
                    break;
                }
            }
            break;
        }
    }

    for(int i = 0; i < variables.size(); i++){
        for(string d : defs){
            if(variables[i].name == d){
                variables.erase(variables.begin() + i);
                //cout << "def deleted: " << d << endl;
            }
        }
    }

    return returnval;
}

string getNormalExpVal(string exp){
    if(exp[0] == '\"' && exp[exp.size() - 1] == '\"'){
        return exp.substr(1, exp.size() - 2);
    }
    else if(exp[0] == '\'' && exp[exp.size() - 1] == '\''){
        return exp.substr(1, exp.size() - 2);
    }
    else{
        return exp;
    }
}

bool identifierValid(string idf){
    if(trim(idf) == ""){
        return false;
    }

    for(char c : trim(idf)){
        for(char pb : prohibitedChars){ // beler alaj iste burda
            if(pb == c){
                return false; // au44
            }
        }
    }

    return true;
}

int assignVar(string name, string value){
    mvariable var;
    var.name = name;
    /*if(isFunction(value)){
        var.value = parseAndExecuteFunction(value);
        //cout << "assigned func " << name << " to " << var.value << endl;
    }
    else if(isArithmetic(value)){
        var.value = getArithmeticVal(value);
        //cout << "assigned arithmetic " << name << " to " << value << endl;
    }
    else{
        var.value = getNormalExpVal(value);
        //cout << "assigned normal " << name << " to " << var.value << endl;
    }*/
    var.value = getExpressionVal(value);

    for(int i = 0; i < variables.size(); i++){
        if(variables[i].name == name){
            variables[i].value = var.value;
            return 0;
        }
    }

    variables.push_back(var);
    return 0;
}

bool isFunction(string exp){
    bool fnd1 = false;
    bool fnd2 = false;
    for(char l : exp){
        if(l == '('){
            fnd1 = true;
        }

        if(l == ')'){
            fnd2 = true;
        }
    }

    if(!fnd1 && !fnd2){
        return false; // pardon ama lavasa sarip yedim
    }                 // elimde degil abi

    vector<string> leftprp = splitstrcount(exp, '(', 1);
    vector<string> rightprp = splitstrcount(exp, ')', 1);

    if(identifierValid(leftprp[0])){
        return true;
    }
    else{
        return false;
    }
}

vector<string> arithmeticTerms = { "+", "-", "*", "/", "%", ">", "<", "=" };
bool isArithmetic(string exp){
    string trm = getExceptStr(trim(exp));
    for(string term : arithmeticTerms){
        if(trm.find(term) != string::npos){
            return true;
        }
    }

    return false;
}

string getExpressionVal(string exp){
    if(varExists(exp)){
        return getVarVal(exp);
    }

    if(isFunction(exp)){
        return parseAndExecuteFunction(exp);
    }
    else if(isArithmetic(exp)){
        return getArithmeticVal(exp);
    }
    else{
        return getNormalExpVal(exp);
    }

    return "";
}

vector<string> pArgsVal(string exp){
    vector<string> args = parseFunctionArgs(exp);
    for(int i = 0; i < args.size(); i++){
        args[i] = getExpressionVal(args[i]);
    }

    return args;
}

bool definefunction = false; // a-def
mfunction currentFunction;

bool defineFor = false;   // a-for
forblock currentFor;
int forQueue = 0;

bool defineif = false; // a-if
ifblock currentIf;
int ifQueue = 0;

bool defineRangeLoop = false;
rangeloopblock currentRangeLoop;
int rangeQueue = 0;

// comment delimiter
char commentDel = '#'; 

void execFor(forblock block){
    while(getBoolVal(block.exp)){
        //cout << getBoolVal(block.exp) << endl;
        for(string cd : block.code){
            executeExpression(cd);
        }
    }
}

void execIf(ifblock block){
    if(getBoolVal(block.exp)){
        for(string cd : block.code){
            executeExpression(cd);
        }
    }
}

rangeobj parseRange(string exp){
    rangeobj g;
    vector<string> args = pArgsVal(exp);

    g.start = stoi(args[0]);
    g.end = stoi(args[1]);

    return g;
}

void execRangeLoop(rangeloopblock block){
    //cout << block.range.start << " " << block.range.end << " " << block.var << endl;

    /*for(string s : block.code){
        cout << s << endl;
    }*/

    for(int index = block.range.start; index < block.range.end; index++){
        assignVar(block.var, to_string(index));
        //cout << "breakpoint" << endl;
        for(string cd : block.code){
            executeExpression(cd);
        }
    }
}

int executeExpression(string fexp){
    if(trim(fexp)[0] == '#'){
        return 0;
    }
    
    string expression = trim(trimToDelimiterNonStr(fexp, commentDel));
    /*cout << expression << endl;
    return 0;*/

    //cout << isArithmetic(expression) << endl;

    /*for(string x : parseFunctionArgs(expression)){
        cout << x << endl;
    }
    return 0;*/

    vector<string> spaceparts = splitstr(expression, ' ');
    vector<string> eqparts = splitstrcount(expression, '=', 1);

    if(definefunction){
        currentFunction.code.push_back(expression);
        if(spaceparts[0] == "enddef"){
            definefunction = false;
            functions.push_back(currentFunction);
            return 0;
        }
        else{
            return 1000;
        }
    }

    if(defineFor){
        if(spaceparts[0] == "endfor"){
            if(forQueue != 0){
                forQueue--;
                currentFor.code.push_back(expression);
                return 1000;
            }
            else{
                defineFor = false;
                /*for(string s : currentFor.code){
                    cout << s << endl;
                }*/
                forblock cb = currentFor;

                currentFor.code.clear();
                currentFor.exp.clear();

                execFor(cb);
                return 0;
            }
        }
        else{
            if(spaceparts[0] == "for"){
                forQueue++;
            }

            currentFor.code.push_back(expression);
            return 1000;
        }
    }

    if(defineif){
        if(spaceparts[0] == "endif"){
            if(ifQueue != 0){
                ifQueue--;
                currentIf.code.push_back(expression);
                return 1000;
            }
            else{
                defineif = false;

                ifblock cb = currentIf;

                currentIf.code.clear();
                currentIf.exp.clear();

                execIf(cb);
                return 0;
            }
        }
        else{
            if(spaceparts[0] == "if"){
                ifQueue++;
            }

            currentIf.code.push_back(expression);
            return 1000;
        }
    }

    if(defineRangeLoop){
        if(spaceparts[0] == "endrange"){
            if(rangeQueue != 0){
                rangeQueue--;
                currentRangeLoop.code.push_back(expression);
                return 1000;
            }
            else{
                defineRangeLoop = false;

                rangeloopblock cb = currentRangeLoop;

                currentRangeLoop.code.clear();
                currentRangeLoop.var.clear();

                currentRangeLoop.range.start = 0;
                currentRangeLoop.range.end = 0;

                execRangeLoop(cb);
                return 0;
            }
        }
        else{
            if(spaceparts[0] == "rangeloop"){
                rangeQueue++;
            }

            currentRangeLoop.code.push_back(expression);
            return 1000;
        }
    }

    if(spaceparts[0] == "vars"){
        for(mvariable v : variables){
            cout << v.name << ": " << v.value << endl;
        }
        return 0;
    }

    if(identifierValid(trim(eqparts[0]))){
        if(eqparts.size() > 1){
            assignVar(trim(eqparts[0]), trim(eqparts[1]));
        }
        else{
            return 300;
        }
    }
    else if(isFunction(expression)){
        parseAndExecuteFunction(expression);
    }
    else if(spaceparts[0] == "def")
    {
        definefunction = true;
        currentFunction.name = spaceparts[1];
        return 1000;
    }
    else if(spaceparts[0] == "if"){
        defineif = true;
        vector<string> oneSpaceParts = splitstrcount(expression, ' ', 1);

        currentIf.exp = oneSpaceParts[1];
        return 1000;
    }
    else if(spaceparts[0] == "for"){
        defineFor = true;
        vector<string> oneSpaceParts = splitstrcount(expression, ' ', 1);

        currentFor.exp = oneSpaceParts[1];
        return 1000;
    }
    else if(spaceparts[0] == "rangeloop"){
        defineRangeLoop = true;
        vector<string> rangeParts = splitstrcount(expression, ' ', 3); // rangeloop <var> in <range>
        
        currentRangeLoop.var = rangeParts[1];
        currentRangeLoop.range = parseRange(rangeParts[3]);
        
        return 1000;
    }
    else if(spaceparts[0] == "return"){
        returnval = "";
        string wf = splitstrcount(expression, ' ', 1)[1];
        returnval = getExpressionVal(wf);

        return 960;
    }
    else{
        return 1;
    }
    
    return 0;
}
