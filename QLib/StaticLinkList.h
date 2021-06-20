#ifndef STATICLINKLIST_H
#define STATICLINKLIST_H

#include "LinkList.h"

namespace QLib
{

template <typename T, int N>/* N用来定义预留空间大小使用 */
class StaticLinkList : public LinkList<T>
{
protected:
    typedef typename LinkList<T>::Node Node; /* 重命名 */
    struct SNode : public Node
    {
        /* void* loc 是调用构造函数的内存地址*/
        void * operator new(unsigned long int size, void * loc)
        {
            (void)size;
            return loc;
        }
    };
    unsigned char m_space[sizeof(SNode) * N];/* 预留空间大小 */
    int m_used[N];                           /* 标记数组 */
protected:
    Node * create();                         /* 重写create() */
    void destroy(Node * pn);                 /*重写destroy() */
public:
    StaticLinkList();
    ~StaticLinkList();
    int capacity();
};

template <typename T, int N>
typename LinkList<T>::Node * StaticLinkList<T, N>::create() /* 重写create函数 */
{
    SNode * ret = nullptr;

    for(int i = 0; i < N; i++)
    {
        if(!m_used[i])
        {
            ret = reinterpret_cast<SNode*>(m_space) + i;
            ret = new(ret)SNode();/* 括号内的地址用于指定想在那一块内存空间中调用构造函数 */
            m_used[i] = 1;
            break;
        }
    }

    return ret;
}

template <typename T, int N>
void StaticLinkList<T, N>::destroy(Node * pn)/* 重写destroy() */
{
    SNode * space = reinterpret_cast<SNode *>(m_space);
    SNode * psn = dynamic_cast<SNode *>(pn);

    for(int i = 0; i < N; i++)
    {
        if(psn == (space + i))
        {
            m_used[i] = 0;
            psn->~SNode();/* 通过对象指针主动调用对象析构函数*/
            break;        /* 空间归还即可调出循环 */
        }
    }
}

template <typename T, int N>
StaticLinkList<T, N>::StaticLinkList()
{
    for(int i = 0; i < N; i++)
    {
        m_used[i] = 0;
    }
}

template <typename T, int N>
int StaticLinkList<T, N>::capacity()
{
    return N;
}

template <typename T, int N>
StaticLinkList<T, N>::~StaticLinkList()
{
    this->clear();
}

}

#endif
