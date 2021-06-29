#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include "Pointer.h"
#include "Exception.h"
#include <cstdlib>

namespace QLib
{

template<typename T, class Del = Deleter<T> >
class SharedPointer : public Pointer<T, Del>
{
protected:
    int * m_ref;
    void assign(const SharedPointer<T, Del>& obj);
public:
    SharedPointer(T * p = nullptr);
    SharedPointer(const SharedPointer<T, Del>& obj);
    SharedPointer<T, Del>& operator = (const SharedPointer<T, Del>& obj);
    bool operator == ( const SharedPointer<T, Del> & r) const;
    bool operator != ( const SharedPointer<T, Del> & r) const;
    void clear();
    ~SharedPointer();
};

template<typename T, class Del>
SharedPointer<T, Del>::SharedPointer(T * p) : m_ref(nullptr)
{
    if(p)
    {
        this->m_ref =static_cast<int * >(malloc(sizeof(int)));
        if(this->m_ref)
        {
            *(this->m_ref) = 1;
            this->m_pointer = p;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create SharedPointer.");
        }
    }
}

template<typename T, class Del>
void SharedPointer<T, Del>::assign(const SharedPointer<T, Del>& obj)
{
    this->m_ref = obj.m_ref;
    this->m_pointer = obj.m_pointer;
    if(this->m_ref)
    {
        (*this->m_ref)++;
    }
}

template<typename T, class Del>
SharedPointer<T, Del>::SharedPointer(const SharedPointer<T, Del>& obj) : Pointer<T, Del>(nullptr)
{
    assign(obj);
}

template<typename T, class Del>
SharedPointer<T, Del>& SharedPointer<T, Del>::operator = (const SharedPointer<T, Del>& obj)
{
    if(this!= &obj)
    {
        clear();
        assign(obj);
    }
    return *this;
}

template<typename T, class Del>
void SharedPointer<T, Del>::clear()
{
    T * toDel = this->m_pointer;
    int * ref = this->m_ref;

    this->m_pointer = nullptr;
    this->m_ref = nullptr;
    if(ref)
    {
        (*ref)--;
        if(*ref == 0)
        {
            free(ref);
            this->m_deleter(toDel);
        }
    }
}

template<typename T, class Del>
SharedPointer<T, Del>::~SharedPointer()
{
    clear();
}

template<typename T, class Del>
bool SharedPointer<T, Del>::operator == ( const SharedPointer<T, Del> & r) const
{
    return this->get() == r.get();
}

template<typename T, class Del>
bool SharedPointer<T, Del>::operator != (const SharedPointer<T, Del> & r) const
{
    return !(*this == r);
}

}
#endif

