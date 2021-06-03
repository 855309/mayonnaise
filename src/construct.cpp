#include <vector>
#include <string>
using namespace std;

#include "construct.hpp"
#include "parser.hpp"
#include "error.hpp"

//////////////////////////////////////////////////////////////
//                    FUNCTION STRUCTURE                    //
//                                                          //
// construct ( arg1,        arg2,          arg3...arg99  )  //
//             ^            ^              ^                //
//             object type  |              |                //
//                          object name    |                //
//                                         member names     //
//////////////////////////////////////////////////////////////

vector<genericblock*> genericStructures;

vector<genericblock*> getGenericStructures(){
    return genericStructures;
}

void construct(vector<string> args){
    try{
        string defvalue = "";

        genericblock* block;
        
        generictype t = parseGenericType(args[0]);
        
        if(t == generictype::none){
            handleError(2);
            return;
        }

        block->type = t;
        block->name = args[1];

        for(int i = 2; i < args.size(); i++){
            block->members.push_back(pair<string, string>(args[i], defvalue));
        }

        genericStructures.push_back(block);
    }
    catch(const std::exception& e){
        return;
    }
}
