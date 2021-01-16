#include "Object.h"
#include <cstdlib>

namespace QLib
{

void * Object::operator new(unsigned long int size) throw()
{
    return malloc(size);
}

void * Object::operator new[](unsigned long int size) throw()
{
    return malloc(size);
}

void Object::operator delete(void * p)
{
    free(p);
}

void Object::operator delete[](void * p)
{
    free(p);
}

Object:: ~Object()
{

}

}