#ifndef STATICLIST_H
#define STATICLIST_H

#include "SeqList.h"

namespace QLib
{

template <typename T, int N>
class StaticList : public SeqList<T>
{
protected:
    T m_space[N];
public:
    StaticList();
    int capacity() const;
};

StaticList<T>::StaticList()
{
    this->m_array = m_space;
    this->m_length = 0;
}

int StaticList<T>::capacity() const
{
    return N;
}

}

#endif
