//
// Created by kyle on 7/16/18.
//

#ifndef SPACEBOIS_COMMAND_H
#define SPACEBOIS_COMMAND_H

#include <functional>
#include <iostream>

class Command {
public:
    virtual void execute() = 0;

};

class CustomCommand : public Command {
public:
    CustomCommand(std::function<void()> f) :func(std::move(f)) {}

    void execute () override { func(); }

private:
    std::function<void()> func;

};

typedef std::reference_wrapper<Command> CommandRef;
bool operator==(const Command& lhs, const Command& rhs);

#endif //SPACEBOIS_COMMAND_H
