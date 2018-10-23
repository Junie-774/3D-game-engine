//
// Created by kyle on 8/21/18.
//

#ifndef SPACEBOIS_SCRIPT_H
#define SPACEBOIS_SCRIPT_H

#include <string>

class Script {
public:

    virtual void start() = 0;
    virtual void update() = 0;
    virtual void end() = 0;

};
typedef std::reference_wrapper<Script> ScriptRef;


#endif //SPACEBOIS_SCRIPT_H
