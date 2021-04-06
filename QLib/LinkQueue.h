#ifndef LINKQUEUE_H
#define LINKQUEUE_H

#include "Queue.h"
#include "LinuxList.h"
#include "Exception.h"

namespace QLib
{

template <typename T>
class LinkQueue : public Queue<T>
{
protected:
    struct Node : public Object
    {
        list_head head;
        T value;
    };
    list_head m_header;
    int m_length;
public:
    LinkQueue();
    void add(const T & e);
    void remove();
    T front() const;
    void clear();
    int length() const;
    ~LinkQueue();
};

template <typename T>
LinkQueue<T>::LinkQueue()
{
    INIT_LIST_HEAD(&m_header);
    m_length = 0;
}

template <typename T>
void LinkQueue<T>::add(const T & e)
{
    Node *node = new Node();
    if(node != nullptr)
    {
        node->value = e;
        list_add_tail(&(node->head), &m_header);
        m_length++;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to add element in LinkQueue...");
    }
}

template <typename T>
void LinkQueue<T>::remove()
{
    if(m_length > 0)
    {
        list_head * toDel = m_header.next;
        list_del(toDel);
        m_length--;
        delete list_entry(toDel, Node, head);
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "No element in current link queue...");
    }
}

template <typename T>
T LinkQueue<T>::front() const
{
    if(m_length>0)
    {
        return list_entry(m_header.next, Node, head)->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "No element in current link queue...");
    }
}

template <typename T>
void LinkQueue<T>::clear()
{
    while(m_length > 0)
    {
        remove();
    }
}

template <typename T>
int LinkQueue<T>::length() const
{
    return m_length;
}

template <typename T>
LinkQueue<T>::~LinkQueue()
{
    clear();
}

}
#endif
