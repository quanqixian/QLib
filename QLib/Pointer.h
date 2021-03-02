#ifndef POINTER_H_
#define POINTER_H_

namespace QLib
{

template<typename T>
class Pointer
{
protected:
    T * m_pointer;
public:
    Pointer(T* p = nullptr);
    T * operator->();
    T * operator->() const;
    T & operator *();
    T & operator *() const;
    bool isNull() const;
    T * get()const;
};

template <typename T>
Pointer<T>::Pointer(T * p)
{
    m_pointer = p;
}

template <typename T>
T * Pointer<T>:: operator ->()
{
    return m_pointer;
}

template <typename T>
T * Pointer<T>::operator ->() const
{
    return m_pointer;
}

template<typename T>
T & Pointer<T>::operator *()
{
    return *m_pointer;
}

template<typename T>
T & Pointer<T>::operator * () const
{
    return *m_pointer;
}

template<typename T>
bool Pointer<T>::isNull() const
{
    return (m_pointer == nullptr);
}

template <typename T>
T * Pointer<T>::get() const
{
    return m_pointer;
}

}

#endif
