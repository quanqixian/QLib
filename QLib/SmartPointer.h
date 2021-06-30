#ifndef SMARTPOINTER_H_
#define SMARTPOINTER_H_
#include "Pointer.h"

namespace QLib
{

template<typename T, class Del = Deleter<T> >
class SmartPointer: public Pointer<T, Del>
{
public:
    SmartPointer(T *p = nullptr);
    SmartPointer(const SmartPointer<T, Del>& obj);
    SmartPointer<T, Del>& operator = (const SmartPointer<T, Del>& obj);
    ~SmartPointer();
};

template<typename T, class Del>
SmartPointer<T, Del>::SmartPointer(T * p) : Pointer<T, Del>(p)
{
}

template<typename T, class Del>
SmartPointer<T, Del>::SmartPointer(const SmartPointer<T, Del>& obj)
{
    this->m_pointer = obj.m_pointer;
    const_cast<SmartPointer<T, Del>& >(obj).m_pointer = nullptr;
}

template<typename T, class Del>
SmartPointer<T, Del>& SmartPointer<T, Del>::operator = (const SmartPointer<T, Del>& obj)
{
    if(this != & obj)
    {
        T *p = this->m_pointer;

        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T, Del>& >(obj).m_pointer = nullptr;

        this->m_deleter(p);
    }

    return *this;
}

template<typename T, class Del>
SmartPointer<T, Del>::~SmartPointer()
{
    this->m_deleter(this->m_pointer);
}

}
#endif
