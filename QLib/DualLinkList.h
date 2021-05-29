#ifndef DUALLINKLIST_H
#define DUALLINKLIST_H

#include "List.h"
#include "Exception.h"

namespace QLib
{

template <typename T>
class DualLinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node * next;
        Node * pre;
    };
    mutable struct : public Object
    {
        char resrved[sizeof(T)];
        Node * next;
        Node * pre;
    }m_header;

    int m_length;
    Node * m_current;
    int m_step;
protected:
    Node * position(int i) const;
    virtual Node * create();
    virtual void destroy(Node * pn);
public:
    DualLinkList();
    bool insert(const T & e);
    bool insert(int i, const T & e);
    bool remove(int i);
    bool set(int i, const T & e);
    virtual T get(int i) const;
    bool get(int i, T & e) const;
    int find(const T & e) const;
    int length() const;
    void clear();

    virtual bool move(int i, int step = 1);
    virtual bool end();
    virtual bool next();
    virtual bool pre();
    virtual T current();
    ~DualLinkList();
};

template <typename T>
DualLinkList<T>::DualLinkList()
{
    m_header.next = nullptr;
    m_header.pre = nullptr;
    m_length = 0;
    m_step = 1;
    m_current = nullptr;
}

template<typename T>
typename DualLinkList<T>::Node * DualLinkList<T>::position(int i) const
{
    Node* ret = reinterpret_cast<Node * >(&m_header);

    for(int pos = 0; pos < i; pos++)
    {
        ret = ret->next;
    }

    return ret;
}

template <typename T>
typename DualLinkList<T>::Node * DualLinkList<T>::create()
{
    return new Node();
}

template <typename T>
void DualLinkList<T>::DualLinkList::destroy(Node * pn)
{
    delete pn;
}

template <typename T>
bool DualLinkList<T>::insert(int i, const T & e)
{
    bool ret = ((i >= 0) && (i <= m_length));
    if(ret)
    {
        Node * node = create();
        if(node != nullptr)
        {
            Node * current = position(i);
            Node * next = current->next;

            node->value = e;
            node->next = next;
            current->next = node;
            if(current != reinterpret_cast<Node *>(&m_header))
            {
                node->pre = current;
            }
            else
            {
                node->pre = nullptr;
            }
            if(next != nullptr)
            {
                next->pre = node;
            }
            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element...");
        }
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::insert(const T & e)
{
    return insert(m_length, e);
}

template <typename T>
bool DualLinkList<T>::remove(int i)
{
    bool ret = ((i >= 0) && (i < m_length));

    if(ret)
    {
        Node * current = position(i);
        Node * toDel = current->next;
        Node * next = toDel->next;

        if(m_current == toDel)/* 如果游标指针指向要删除的指针 */
        {
            m_current = toDel->next;/* 移动游标指针 */
        }
        current->next = next;
        if(next != nullptr)
        {
            next->pre = toDel->pre;
        }
        m_length--;
        destroy(toDel);
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::set(int i, const T & e)
{
    bool ret = ((i >= 0) && (i < m_length));

    if(ret)
    {
        position(i)->next->value = e;
    }

    return ret;
}

template <typename T>
T DualLinkList<T>::get(int i) const
{
    T ret;
    if(get(i, ret))
    {
        return ret;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "Invalid parameter i to get element");
    }
}

template <typename T>
bool DualLinkList<T>::get(int i, T & e) const
{
    bool ret = ((i >= 0) && (i < m_length));

    if(ret)
    {
        e = position(i)->next->value;
    }

    return ret;
}

template <typename T>
int DualLinkList<T>::find(const T&e) const
{
    int ret = -1;
    int pos = 0;
    Node *node = m_header.next;

    while(node)
    {
        if(node->value == e)
        {
            ret = pos;
            break;
        }
        else
        {
            node = node->next;
            pos++;
        }
    }

    return ret;
}

template <typename T>
int DualLinkList<T>::length() const
{
    return m_length;
}

template <typename T>
void DualLinkList<T>::clear()
{
    while(this->m_length > 0)
    {
        remove(0);
    }
}

template <typename T>
bool DualLinkList<T>::move(int i, int step)
{
    bool ret = (i >= 0) && (i < m_length) && (step > 0);

    if(ret)
    {
        m_current = position(i)->next;
        m_step = step;
    }

    return ret;
}

template <typename T>
bool DualLinkList<T>::end()
{
    return m_current == nullptr;
}

template <typename T>
bool DualLinkList<T>::next()
{
    int i = 0;

    while((i < m_step) && (!end()))
    {
        m_current = m_current->next;
        i++;
    }

    return (i == m_step);
}

template <typename T>
bool DualLinkList<T>::pre()
{
    int i = 0;

    while((i < m_step) && (!end()))
    {
        m_current = m_current->pre;
        i++;
    }

    return (i == m_step);
}

template <typename T>
T DualLinkList<T>::current()
{
    if(!end())
    {
        return m_current->value;
    }
    else
    {
        THROW_EXCEPTION(IndexOutOfBoundsException, "No value at current position...");
    }
}

template <typename T>
DualLinkList<T>::~DualLinkList()
{
    clear();
}

}

#endif
