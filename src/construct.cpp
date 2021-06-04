#include <vector>
#include <string>
#include <iostream> // for debugging
using namespace std;

// #include "construct.hpp"
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

void setStructureVal(string objname, string membername, string memberval){
    for(genericblock* block : genericStructures){
        if(block->name == objname){
            for(auto& member : block->members){
                if(member->name == membername){
                    member->value = memberval;
                    return;
                }
            }
        }
    }

    handleError(3); // no generic member found
}

void construct(vector<string> args){
    try{
        string defvalue = "type:undefined";

        genericblock* block;
        
        generictype t = parseGenericType(args[0]);
        
        if(t == generictype::none){
            handleError(2);
            return;
        }

        block->type = t;
        block->name = args[1];

        cout << block->type << " " << block->name << endl;

        for(int i = 2; i < args.size(); i++){
            /* valueblock vb = {
                .name = args[i],
                .value = defvalue
            }; */

            valueblock* vb;

            vb->name = args[i];
            vb->value = defvalue;

            block->members.push_back(vb);

            cout << vb->name << " " << vb->value << endl;
        }

        genericStructures.push_back(block);
    }
    catch(const std::exception& e){
        return;
    }
}
