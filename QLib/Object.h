#ifndef OBJECT_H_
#define OBJECT_H_

namespace QLib
{

class Object
{
public:
    void * operator new(unsigned long int size) throw();  /* throw()表示当前的函数不会抛出任何异常 */
    void * operator new[](unsigned long int size) throw();

    void operator delete(void * p);
    void operator delete[](void * p);

    virtual ~Object() = 0;
};

}
#endif