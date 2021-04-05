#ifndef SEQLIST_H
#define SEQLIST_H

#include "List.h"
#include "Exception.h"

namespace QLib
{

template <typename T>
class SeqList : public List<T>
{
protected:
    T * m_array;/* 顺序存储空间的指针，具体空间分配由子类实现 */
    int m_length;
public:
    bool insert(int i, const T & e) override;
    bool insert(const T & e) override;
    bool remove(int i) override;
    bool set(int i, const T & e) override;
    bool get(int i, T & e) const override;
    T get(int i) const override;
    int length() const override;
    void clear() override;
    int find(const T & e) const override;

    /* 顺序存储线性表的数组访问方式 */
    T & operator[] (int i);
    const T & operator[](int i) const;

    /* 顺序存储空间的容量 */
    virtual int capacity() const = 0;
};

template <typename T>
bool SeqList<T>::insert(int i, const T & e)
{
    bool ret = ((0 <= i) && (i <= m_length));
    ret = ret && ((m_length + 1) <= capacity());

    if(ret)
    {
        for(int p = m_length - 1; p >= i; p--)
        {
            m_array[p + 1] = m_array[p];
        }
        m_array[i] = e;
        m_length++;
    }

    return ret;
}

template <typename T>
bool SeqList<T>::insert(const T & e)
{
    return insert(m_length, e);
}

template <typename T>
bool SeqList<T>::remove(int i)
{
    bool ret = ((0 <=i ) && (i < m_length));

    if(ret)
    {
        for(int p = i; p < m_length - 1; p++)
        {
            m_array[p] = m_array[p + 1];
        }
        m_length--;
    }

    return ret;
}

template <typename T>
bool SeqList<T>::set(int i, const T & e)
{
    bool ret = ((0 <= i) && (i < m_length));

    if(ret)
    {
        m_array[i] = e;
    }

    return ret;
}

template <typename T>
bool SeqList<T>::get(int i, T & e) const
{
    bool ret = ((0 <= i) && (i < m_length));

    if(ret)
    {
        e = m_array[i];
    }

    return ret;
}

template <typename T>
T SeqList<T>::get(int i) const
{
    T ret;
    if(get(i, ret))
    {
        return ret;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element.");
    }
}

template <typename T>
int SeqList<T>::length() const
{
    return m_length;
}

template <typename T>
void SeqList<T>::clear()
{
    m_length = 0;
}

template <typename T>
T& SeqList<T>::operator[](int i)
{
    return const_cast<T &>((static_cast< const SeqList<T> & >(*this) )[i]);
}

template <typename T>
const T& SeqList<T>::operator[](int i) const
{
    if((0 <= i) && (i < m_length))
    {
        return m_array[i];
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Paramenter i is invalid");
    }
}

template <typename T>
int SeqList<T>::find(const T & e) const
{
    int ret = -1;

    for(int i = 0; i < m_length; i++)
    {
        if(m_array[i] == e)
        {
            ret = i;
            break;
        }
    }

    return ret;
}

}

#endif
