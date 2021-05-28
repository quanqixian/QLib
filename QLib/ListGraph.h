#ifndef LISTGRAPH_H
#define LISTGRAPH_H

#include "Graph.h"
#include "LinkList.h"
#include "Exception.h"
#include "DynamicArray.h"

namespace QLib
{

template <typename V, typename E>
class ListGraph : public Graph<V, E>
{
protected:
    struct Vertex : public Object
    {
        V * data;
        LinkList<Edge<E> > edge;

        Vertex() : data(nullptr)
        {
        }
    };

    LinkList<Vertex * > m_list;
public:
    ListGraph(unsigned int n = 0);
    int addVertex();
    int addVertex(const V & value);
    void removeVertex();

    bool setVertex(int i, const V & value) override;
    V getVertex(int i) override;
    bool getVertex(int i, V & value) override;

    SharedPointer<Array<int> > getAdjacent(int i) override;
    bool isAdjacent(int i, int j) override;

    E getEdge(int i, int j) override;
    bool getEdge(int i, int j, E & value) override;
    bool setEdge(int i, int j, const E & value) override;
    bool removeEdge(int i, int j) override;

    int vCount() override;
    int eCount() override;
    int OD(int i) override;
    int ID(int i) override;
    ~ListGraph();
};

template <typename V, typename E>
ListGraph<V, E>::ListGraph(unsigned int n)
{
    for(unsigned int i = 0; i < n; i++)
    {
        addVertex();
    }
}

template <typename V, typename E>
int ListGraph<V, E>::addVertex()
{
    int ret = -1;

    Vertex * v = new Vertex();

    if(v != nullptr)
    {
        m_list.insert(v);

        ret = m_list.length() - 1;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create a new vertex...");
    }

    return ret;
}

template <typename V, typename E>
int ListGraph<V, E>::addVertex(const V & value)
{
    int ret = addVertex();

    if(ret >= 0)
    {
        setVertex(ret, value);
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "ret < 0");
    }

    return ret;
}

template <typename V, typename E>
bool ListGraph<V, E>::setVertex(int i, const V & value)
{
    bool ret = (0 <= i) && (i < vCount());

    if(ret)
    {
        Vertex * vertex = m_list.get(i);
        V * data = vertex->data;

        if(data == nullptr)
        {
            data = new V();
        }

        if(data != nullptr)
        {
            *data = value;

            vertex->data = data;
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create a new vertex value...");
        }
    }

    return ret;
}

template <typename V, typename E>
V ListGraph<V, E>::getVertex(int i)
{
    V ret;

    if(!getVertex(i, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ... ");
    }

    return ret;
}

template <typename V, typename E>
bool ListGraph<V, E>::getVertex(int i, V & value)
{
    bool ret = (0 <= i) && (i < vCount());

    if(ret)
    {
        Vertex * v = m_list.get(i);

        if(v->data != nullptr)
        {
            value = *(v->data);
        }
        else
        {
            THROW_EXCEPTION(InvalidOperationException, "No value assigned to this vertex ...");
        }
    }

    return ret;
}

template <typename V, typename E>
void ListGraph<V, E>::removeVertex()
{
    if(m_list.length() > 0)
    {
        int index = m_list.length() - 1;
        Vertex * v = m_list.get(index);      /* 用指针v指向链表的最后一个结点所指向的顶点内存空间 */

        if(m_list.remove(index))             /* remove链表中的vertex* */
        {
            for(int i = (m_list.move(0), 0); !m_list.end(); i++, m_list.next())
            {
                int pos = m_list.current()->edge.find(Edge<E>(i, index));

                if(pos >= 0)
                {
                    m_list.current()->edge.remove(pos);
                }
            }

            delete v->data;     /* 释放与顶点相关连的元素值的空间 */
            delete v;           /* 释放顶点自身所占用的空间 */
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "No vertex in current graph ...");
    }
}

template <typename V, typename E>
SharedPointer< Array<int> > ListGraph<V, E>::getAdjacent(int i)
{
    DynamicArray<int> * ret = nullptr;

    if((0 <= i) && (i < vCount()))
    {
        Vertex * vertex = m_list.get(i);

        ret = new DynamicArray<int>(vertex->edge.length());

        if(ret != nullptr)
        {
            for(int k = (vertex->edge.move(0), 0); !vertex->edge.end(); k++, vertex->edge.next())
            {
                ret->set(k, vertex->edge.current().e);
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create a new ret object ...");
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
    }

    return ret;
}

template <typename V, typename E>
bool ListGraph<V, E>::isAdjacent(int i, int j)
{
    bool ret = true;

    ret = ret && (0 <= i);
    ret = ret && (i < vCount());
    ret = ret && (0 <= j);
    ret = ret && (j < vCount());
    ret = ret && (m_list.get(i)->edge.find(Edge<E>(i, j)) >= 0);

    return ret;
}

template <typename V, typename E>
E ListGraph<V, E>::getEdge(int i, int j)
{
    E ret;

    if(!getEdge(i, j, ret))
    {
        THROW_EXCEPTION(InvalidParameterException, "Index <i, j> is invalid ...");
    }

    return ret;
}

template <typename V, typename E>
bool ListGraph<V, E>::getEdge(int i, int j, E & value)
{
    bool ret = ((0 <= i) && (i < vCount()) &&
                (0 <= j) && (j < vCount()));

    if(ret)
    {
        Vertex * vertex = m_list.get(i);
        int pos = vertex->edge.find(Edge<E>(i, j));

        if( pos >= 0)
        {
            value = vertex->edge.get(pos).data;
        }
        else
        {
            THROW_EXCEPTION(InvalidParameterException, "No value assigned to this edge ...");
        }
    }

    return ret;
}

template <typename V, typename E>
bool ListGraph<V, E>::setEdge(int i, int j, const E & value)
{
    bool ret = ((0 <= i) && (i < vCount()) &&
                (0 <= j) && (j < vCount()));

    if(ret)
    {
        Vertex * vertex = m_list.get(i);
        int pos = vertex->edge.find(Edge<E>(i, j));

        if(pos >= 0)
        {
            ret = vertex->edge.set(pos, Edge<E>(i, j, value));
        }
        else
        {
            ret = vertex->edge.insert(0, Edge<E>(i, j, value));
        }
    }

    return ret;
}

template <typename V, typename E>
bool ListGraph<V, E>::removeEdge(int i, int j)
{
    bool ret = ((0 <= i) && (i < vCount()) &&
                (0 <= j) && (j < vCount()));

    if(ret)
    {
        Vertex * vertex = m_list.get(i);
        int pos = vertex->edge.find(Edge<E>(i, j));

        if(pos >= 0)
        {
            ret = vertex->edge.remove(pos);
        }
    }

    return ret;
}

template <typename V, typename E>
int ListGraph<V, E>::vCount()
{
    return m_list.length();
}

template <typename V, typename E>
int ListGraph<V, E>::eCount()
{
    int ret = 0;

    for(m_list.move(0); !m_list.end(); m_list.next())
    {
        ret += m_list.current()->edge.length();
    }

    return ret;
}

template <typename V, typename E>
int ListGraph<V, E>::OD(int i)
{
    int ret = 0;

    if((0 <= i) && (i <= vCount()))
    {
        ret = m_list.get(i)->edge.length();
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
    }

    return ret;
}

template <typename V, typename E>
int ListGraph<V, E>::ID(int i)
{
    int ret = 0;

    if((0 <= i) && (i < vCount()))
    {
        for(m_list.move(0); !m_list.end(); m_list.next())
        {
            LinkList<Edge<E> > & edge = m_list.current()->edge;

            for(edge.move(0); !edge.end(); edge.next())
            {
                if(edge.current().e == i)
                {
                    ret++;
                    break;
                }
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid ...");
    }

    return ret;
}

template <typename V, typename E>
ListGraph<V, E>::~ListGraph()
{
    while(m_list.length() > 0)
    {
        Vertex * toDel = m_list.get(0);

        m_list.remove(0);

        delete toDel->data;
        delete toDel;
    }
}

}

#endif
