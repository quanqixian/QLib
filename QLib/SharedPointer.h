#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include "Pointer.h"
#include "Exception.h"
#include <cstdlib>

namespace QLib
{

template <typename T>
class SharedPointer : public Pointer<T>
{
protected:
    int * m_ref;
    void assign(const SharedPointer<T>& obj);
public:
    SharedPointer(T * p = nullptr);
    SharedPointer(const SharedPointer<T>& obj);
    SharedPointer<T>& operator = (const SharedPointer<T>& obj);
    bool operator == ( const SharedPointer<T> & r) const;
    bool operator != ( const SharedPointer<T> & r) const;
    void clear();
    ~SharedPointer();
};

template <typename T>
SharedPointer<T>::SharedPointer(T * p) : m_ref(nullptr)
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

template <typename T>
void SharedPointer<T>::assign(const SharedPointer<T>& obj)
{
    this->m_ref = obj.m_ref;
    this->m_pointer = obj.m_pointer;
    if(this->m_ref)
    {
        (*this->m_ref)++;
    }
}

template <typename T>
SharedPointer<T>::SharedPointer(const SharedPointer<T>& obj) : Pointer<T>(nullptr)
{
    assign(obj);
}

template <typename T>
SharedPointer<T>& SharedPointer<T>::operator = (const SharedPointer<T>& obj)
{
    if(this!= &obj)
    {
        clear();
        assign(obj);
    }
    return *this;
}

template <typename T>
void SharedPointer<T>::clear()
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
            delete toDel;
        }
    }
}

template <typename T>
SharedPointer<T>::~SharedPointer()
{
    clear();
}

template <typename T>
bool SharedPointer<T>::operator == ( const SharedPointer<T> & r) const
{
    return this->get() == r.get();
}

template <typename T>
bool SharedPointer<T>::operator != (const SharedPointer<T> & r) const
{
    return !(*this == r);
}

}
#endif

