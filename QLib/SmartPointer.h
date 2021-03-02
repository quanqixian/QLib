#ifndef SMARTPOINTER_H_
#define SMARTPOINTER_H_
#include "Pointer.h"

namespace QLib
{

template <typename T>
class SmartPointer: public Pointer<T>
{
public:
    SmartPointer(T *p = nullptr);
    SmartPointer(const SmartPointer<T>& obj);
    SmartPointer<T>& operator = (const SmartPointer<T>& obj);
    ~SmartPointer();
};

template <typename T>
SmartPointer<T>::SmartPointer(T* p) : Pointer<T>(p)
{
}

template <typename T>
SmartPointer<T>::SmartPointer(const SmartPointer<T>& obj)
{
    this->m_pointer = obj.m_pointer;
    const_cast<SmartPointer<T>& >(obj).m_pointer = nullptr;
}

template <typename T>
SmartPointer<T>& SmartPointer<T>::operator = (const SmartPointer<T>& obj)
{
    if(this != & obj)
    {
        T *p = this->m_pointer;

        this->m_pointer = obj.m_pointer;
        const_cast<SmartPointer<T>& >(obj).m_pointer = nullptr;

        delete p;
    }

    return *this;
}

template <typename T>
SmartPointer<T>::~SmartPointer()
{
    delete this->m_pointer;
}

}
#endif
