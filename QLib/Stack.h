#ifndef STATCK_H
#define STATCK_H

#include "Object.h"

namespace QLib
{

template <typename T>
class Stack : public Object
{
public:
    virtual void push(const T & e) = 0;
    virtual void pop() = 0;
    virtual T top() const = 0;
    virtual void clear() = 0;
    virtual int size() const = 0;
};

}
#endif
