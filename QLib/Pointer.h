#ifndef POINTER_H_
#define POINTER_H_

#include "Object.h"

namespace QLib
{

template <typename T>
struct Deleter
{
    void operator()(T * ptr) const
    {
        delete ptr;
    }
};

template <typename U> /* 数组类型特化 */
struct Deleter<U[]>
{
     void operator()(U * ptr) const
     {
         delete [] ptr;
     }
};

template<typename T, class Del = Deleter<T> >
class Pointer : public Object
{
protected:
    T * m_pointer;
    Del m_deleter; /* 删除器 */
public:
    Pointer(T* p = nullptr);
    T * operator->();
    T * operator->() const;
    T & operator *();
    T & operator *() const;
    bool isNull() const;
    T * get()const;
};


template<typename T, class Del>
Pointer<T, Del>::Pointer(T* p) : m_pointer(p)
{

}

template<typename T, class Del>
T * Pointer<T, Del>::operator ->()
{
    return m_pointer;
}

template<typename T, class Del>
T * Pointer<T, Del>::operator ->() const
{
    return m_pointer;
}

template<typename T, class Del>
T & Pointer<T, Del>::operator *()
{
    return *m_pointer;
}

template<typename T, class Del>
T & Pointer<T, Del>::operator * () const
{
    return *m_pointer;
}

template<typename T, class Del>
bool Pointer<T, Del>::isNull() const
{
    return (m_pointer == nullptr);
}

template<typename T, class Del>
T * Pointer<T, Del>::get() const
{
    return m_pointer;
}

}

#endif
