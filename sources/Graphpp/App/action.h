#ifndef ACTION_H
#define ACTION_H

class Action
{
public:
    virtual ~Action(){}
    virtual void execute() = 0;
    virtual void undo() = 0;
};

#endif // ACTION_H
