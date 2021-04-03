#ifndef LINKLIST_H_
#define LINKLIST_H_

#include "List.h"
#include "Exception.h"

namespace QLib
{

template<typename T>
class LinkList : public List<T>
{
protected:
    struct Node : public Object
    {
        T value;
        Node * next;
    };

    mutable struct : public Object
    {
        char reserved[sizeof(T)];
        Node * next;
    }m_header;

    int m_length;
protected:
    Node * position(int i) const;
public:
    LinkList();
    bool insert(int i, const T & e) override;
    bool insert(const T & e) override;
    bool remove(int i) override;
    bool set(int i, const T & e) override;
    bool get(int i, T & e) const override;
    T get(int i) const override;
    int length() const override;
    void clear() override;
    ~LinkList();
};

template<typename T>
typename LinkList<T>::Node * LinkList<T>::position(int i) const
{
    Node * ret = reinterpret_cast<Node *>(&m_header);

    for(int p = 0; p < i; p++)
    {
        ret = ret->next;
    }

    return ret;
}

template<typename T>
LinkList<T>::LinkList()
{
    m_header.next = nullptr;
    m_length = 0;
}

template<typename T>
bool LinkList<T>::insert(int i, const T & e)
{
    bool ret = ((0 <= i) && (i <= m_length));

    if(ret)
    {
        Node * node = new Node();
        if(node != nullptr)
        {
            Node * current = position(i);
            node->value = e;
            node->next = current->next;
            current->next = node;

            m_length++;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to insert new element...");
        }
    }

    return ret;
}

template<typename T>
bool LinkList<T>::insert(const T & e)
{
    return insert(m_length, e);
}

template<typename T>
bool LinkList<T>::remove(int i)
{
    bool ret = ((0 <= i) && (i < m_length));

    if(ret)
    {
        Node * current = position(i);
        Node * toDel = current->next;
        current->next = toDel->next;

        delete toDel;
        m_length--;
    }

    return ret;
}

template<typename T>
bool LinkList<T>::set(int i, const T & e)
{
    bool ret = ((0 <= i) && (i < m_length));

    if(ret)
    {
        position(i)->next->value = e;
    }

    return ret;
}

template<typename T>
bool LinkList<T>::get(int i, T & e) const
{
    bool ret = ((0 <= i) && (i < m_length));

    if(ret)
    {
        e = position(i)->next->value;
    }

    return ret;
}

template<typename T>
T LinkList<T>::get(int i) const
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

template<typename T>
int LinkList<T>::length() const
{
    return m_length;
}

template<typename T>
void LinkList<T>::clear()
{
    while(m_header.next)
    {
        Node * toDel = m_header.next;
        m_header.next = toDel->next;
        delete toDel;
    }

    m_length = 0;
}

template<typename T>
LinkList<T>::~LinkList()
{
    clear();
}

}

#endif
