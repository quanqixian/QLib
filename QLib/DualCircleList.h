#ifndef DUALCIRCLELIST_H
#define DUALCIRCLELIST_H

#include "LinuxList.h"
#include "DualLinkList.h"

namespace QLib
{

template  <typename T>
class DualCircleList : public DualLinkList<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };
    list_head m_header;
    list_head * m_current;
    list_head * position(int i) const;
    int mod(int i) const;
public:
    DualCircleList();
    bool insert(const T & e);
    bool insert(int i, const T & e);
    bool remove(int i);
    bool set(int i, const T & e);
    T get(int i)const;
    bool get(int i, T & e) const;
    int find(const T & e) const;
    int length() const;
    void clear();

    bool move(int i, int step = 1);
    bool end();
    bool next();
    bool pre();
    T current();
    ~DualCircleList();
};

template<typename T>
list_head * DualCircleList<T>::position(int i) const
{
    list_head * ret = const_cast<list_head * >(&m_header);

    for(int pos = 0; pos < i; pos++)
    {
        ret = ret->next;
    }

    return ret;
}

template <typename T>
int DualCircleList<T>::mod(int i) const
{
    return (this->m_length == 0) ? 0 : (i % this->m_length);
}

template <typename T>
DualCircleList<T>::DualCircleList()
{
    m_current = nullptr;
    this->m_length = 0;
    this->m_step = 1;
    INIT_LIST_HEAD(&m_header);
}

template <typename T>
bool DualCircleList<T>::insert(const T & e)
{
    return inset(this->m_length, e);
}

template<typename T>
bool DualCircleList<T>::insert(int i, const T & e)
{
    bool ret = true;
    i = i % (this->m_length + 1);
    Node * node = new Node();

    if(node != nullptr)
    {
        node->value = e;
        list_add_tail(&(node->head), position(i)->next);
        this->m_length++;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element in DualCircleList...");
    }

    return ret;
}

template <typename T>
bool DualCircleList<T>::remove(int i)
{
    bool ret = true;
    i = mod(i);
    ret = ((0 <= i) && (i < this->m_length));

    if(ret)
    {
        list_head * toDel = position(i)->next;
        if(this->m_current == toDel)
        {
            this->m_current = this->m_current->next;
        }
        list_del(toDel);
        this->m_length--;
        delete list_entry(toDel, Node, head);
    }

    return ret;
}

template <typename T>
bool DualCircleList<T>::set(int i, const T & e)
{
    bool ret = true;
    i = mod(i);
    ret = ((0 <= i) && (i < this->m_length));

    if(ret)
    {
        list_entry(position(i)->next, Node, head)->value = e;
    }

    return ret;
}

template <typename T>
T DualCircleList<T>::get(int i) const
{
    T ret;
    if(get(i, ret))
    {
        return ret;
    }
    else 
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element... ");
    }
    return ret;
}

template <typename T>
bool DualCircleList<T>::get(int i, T & e) const
{
    bool ret = true;
    i = mod(i);
    ret = ((0 <= i) && (i < this->m_length));

    if(ret)
    {
        e = list_entry(position(i)->next, Node, head)->value;
    }

    return ret;
}

template <typename T>
int DualCircleList<T>::find(const T & e) const
{
    int ret = -1;
    int i = 0;
    list_head * slider = nullptr;

    list_for_each(slider, &m_header)
    {
        if(list_entry(slider, Node, head)->value == e)
        {
            ret = i;
            break;
        }
        i++;
    }

    return ret;
}

template <typename T>
int DualCircleList<T>::length() const
{
    return this->m_length;
}

template <typename T>
void DualCircleList<T>::clear()
{
    while(this->m_length > 0)
    {
        remove(0);
    }
}

template <typename T>
bool DualCircleList<T>::move(int i, int step)
{
    bool ret = true;
    i = mod(i);
    ret = ret && (i >= 0) && (i < this->m_length) && (step>0);

    if(ret)
    {
        this->m_current = position(i)->next;
        this->m_step = step;
    }

    return ret;
}

template <typename T>
bool DualCircleList<T>::end()
{
    return (this->m_length == 0) || (this->m_current == nullptr);
}

template<typename T>
bool DualCircleList<T>::next()
{
    int i = 0;
    while((i < this->m_step) && (!end()))
    {
        if(this->m_current != &this->m_header)
        {
            this->m_current = this->m_current->next;
            i++;
        }
        else
        {
            this->m_current=this->m_current->next;
        }
    }

    if(this->m_current == &this->m_header)
    {
        this->m_current = this->m_current;
    }

    return (i == this->m_step);
}

template <typename T>
bool DualCircleList<T>::pre()
{
    int i = 0;
    while((i < this->m_step) && (!end()))
    {
        if(this->m_current != &this->m_header)
        {
            this->m_current = this->m_current->prev;
            i++;
        }
        else
        {
            this->m_current=this->m_current->prev;
        }
    }

    if(this->m_current == &this->m_header)
    {
        this->m_current = this->m_current->prev;
    }

    return (i == this->m_step);
}

template <typename T>
T DualCircleList<T>::current()
{
    if(!end())
    {
        return list_entry(this->m_current, Node, head)->value;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "No value at current position...");
    }
}

template <typename T>
DualCircleList<T>::~DualCircleList()
{
    clear();
}

}
#endif
