#ifndef ARRAY_H_
#define ARRAY_H_

#include "Object.h"
#include "Exception.h"

namespace QLib
{

template <typename T>
class Array : public Object
{
protected:
    T * m_array;
public:
    virtual bool set(int i, const T & e);
    virtual bool get(int i, T & e) const;
    T & operator[](int i);
    const T & operator[](int i) const;
    virtual int length() const = 0;
};

template <typename T>
bool Array<T>::set(int i, const T & e)
{
    bool ret = ((0 <= i) && (i < length()));
    if(ret)
    {
        m_array[i] = e;
    }
    return ret;
}

template <typename T>
bool Array<T>::get(int i, T & e) const
{
    bool ret = ((0 <= i) && (i < length()));
    if(ret)
    {
        e = m_array[i];
    }
    return ret;
}

template <typename T>
T & Array<T>::operator[](int i)
{
    return const_cast< T &>(static_cast< const Array<T> & >(*this)[i]);
}

template <typename T>
const T & Array<T>::operator[](int i) const
{
    if((0 <= i) && (i < length()))
    {
        return m_array[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Parameter i is invalid...");
    }
}

}

#endif
