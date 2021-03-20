#ifndef DYNAMICARRAY_H_
#define DYNAMICARRAY_H_

#include "Array.h"
#include "Exception.h"

namespace QLib
{

template <typename T>
class DynamicArray : public Array<T>
{
protected:
    int m_length;
protected:
    T * copy(T * array, int len, int newLen);
    void update(T * array, int length);
    void init(T * array, int length);
public:
    DynamicArray(int length);
    DynamicArray(const DynamicArray<T> & obj);
    DynamicArray<T>& operator = (const DynamicArray<T> & obj);
    int length() const;
    void resize(int length);
    ~DynamicArray();
};

template <typename T>
T * DynamicArray<T>::copy(T * array, int len, int newLen)
{
    T* ret = new T[newLen];
    if(ret != nullptr)
    {
        int size = len < newLen? len : newLen;
        for(int i = 0; i < size; i++)
        {
            ret[i] = array[i];
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to copy DynamicArray.");
    }
    return ret;
}

template <typename T>
void DynamicArray<T>::update(T * array, int length)
{
    if(array != nullptr)
    {
        T* temp = this->m_array;

        this->m_array = array;
        this->m_length = length;

        delete [] temp;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to update DynamicArray.");
    }
}

template <typename T>
void DynamicArray<T>::init(T * array, int length)
{
    if(array != NULL)
    {
        this->m_array = array;
        this->m_length = length;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to init DynamicArray.");
    }
}

template <typename T>
DynamicArray<T>::DynamicArray(int length)
{
    init(new T[length], length);
}

template <typename T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> & obj)
{
    init(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_lenth);
}

template <typename T>
DynamicArray<T>& DynamicArray<T>::operator = (const DynamicArray<T> & obj)
{
    if(this != &obj)
    {
        update(copy(obj.m_array, obj.m_length, obj.m_length), obj.m_length);
    }
    return *this;
}

template <typename T>
int DynamicArray<T>::length() const
{
    return m_length;
}

template <typename T>
void DynamicArray<T>::resize(int length)
{
    if(length != m_length)
    {
        update(copy(this->m_array, this->m_length, length), length);
    }
}

template <typename T>
DynamicArray<T>::~DynamicArray()
{
    delete[] this->m_array;
}

}

#endif
