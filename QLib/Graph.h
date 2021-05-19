#ifndef GRAPH_H
#define GRAPH_H

#include "Object.h"
#include "SharedPointer.h"
#include "Array.h"
#include "DynamicArray.h"
#include "LinkQueue.h"
#include "LinkStack.h"

namespace QLib
{

template <typename E>
struct Edge : public Object
{
    int b; /* 起点 */
    int e; /* 终点 */
    E data;/* 权值 */

    Edge(int begin = -1, int end = -1);
    Edge(int begin, int end, const E & value);
    bool operator == (const Edge<E> & obj);
    bool operator != (const Edge<E> & obj);
};

template <typename E>
Edge<E>::Edge(int begin, int end)
{
    b = begin;
    e = end;
}

template <typename E>
Edge<E>::Edge(int begin, int end, const E & value)
{
    b = begin;
    e = end;
    data = value;
}

template <typename E>
bool Edge<E>::operator == (const Edge<E> & obj)
{
    return (this->b == obj.b) && (this->e == obj.e);
}

template <typename E>
bool Edge<E>::operator != (const Edge<E> & obj)
{
    return !(*this == obj);
}

template <typename V, typename E>
class Graph : public Object
{
protected:
    template <typename T>
    DynamicArray<T> * toArray(LinkQueue<T> & queue)
    {
        DynamicArray<T> * ret = new DynamicArray<T>(queue.length());

        if(ret != nullptr)
        {
            for(int i = 0; i < ret->length(); i++, queue.remove())
            {
                ret->set(i, queue.front());
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create a ret Object...");
        }

        return ret;
    }
public:
    virtual V getVertex(int i) = 0;
    virtual bool getVertex(int i, V & value) = 0;
    virtual bool setVertex(int i, const V & value) = 0;

    virtual SharedPointer<Array<int> > getAdjacent(int i) = 0;
    virtual bool isAdjacent(int i, int j) = 0;

    virtual E getEdge(int i, int j) = 0;
    virtual bool getEdge(int i, int j, E & value) = 0;
    virtual bool setEdge(int i, int j, const E & value) = 0;
    virtual bool removeEdge(int i, int j) = 0;

    virtual int vCount() = 0;
    virtual int eCount() = 0;
    virtual int OD(int i) = 0;
    virtual int ID(int i) = 0;

    virtual int TD(int i)
    {
        return OD(i) + ID(i);
    }
    bool asUndirected();

    SharedPointer<Array<int> > BFS(int i);
    SharedPointer<Array<int> > DFS(int i);

    SharedPointer<Array<int> > dijkstra(int i, int j, const E & LIMIT);
};

template <typename V, typename E>
SharedPointer<Array<int> > Graph<V, E>::BFS(int i)
{
    DynamicArray<int> * ret = nullptr;

    if((i <= 0) && (i < vCount()))
    {
        LinkQueue<int> q;
        LinkQueue<int> r;
        DynamicArray<bool> visited(vCount());

        for(int j = 0; j < visited.length(); j++)
        {
            visited[j] = false;
        }

        q.add(i);

        while(q.length() > 0)
        {
            int v = q.front();
            q.remove();
            if(!visited[v])
            {
                SharedPointer<Array<int> > aj = getAdjacent(v);

                for(int j = 0; j < aj->length(); j++)
                {
                    q.add((*aj)[j]);
                }
                r.add(v);
                visited[v] = true;
            }
        }

        ret = toArray(r);
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
    }

    return ret;
}

template <typename V, typename E>
SharedPointer<Array<int> > Graph<V, E>::DFS(int i)
{
    DynamicArray<int> * ret = nullptr;

    if((i >= 0) && (i<vCount()))
    {
        LinkStack<int> s;
        LinkQueue<int> r;
        DynamicArray<bool> visited(vCount());

        for(int j = 0; j < visited.length(); j++)
        {
            visited[j] = false;
        }

        s.push(i);

        while(s.size() > 0)
        {
            int v = s.top();

            s.pop();
            if(!visited[v])
            {
                SharedPointer<Array<int> > aj = getAdjacent(v);
                for(int j = aj->length() - 1; j>=0; j--)
                {
                    s.push((*aj)[j]);
                }
                r.add(v);
                visited[v] = true;
            }
        }
        ret = toArray(r);
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index i is invalid...");
    }

    return ret;
}


template <typename V, typename E>
SharedPointer<Array<int> > Graph<V, E>::dijkstra(int i, int j, const E & LIMIT)
{
    LinkQueue<int> ret;

    if((0 <= i) && (i < vCount()) && (0 <= j) && (j < vCount()))
    {
        DynamicArray<E> dist(vCount());
        DynamicArray<int> path(vCount());
        DynamicArray<bool> mark(vCount());

        for(int k = 0; k < vCount(); k++)
        {
            mark[k] = false;
            path[k] = -1;

            dist[k] = isAdjacent(i, k) ? (path[k] = i, getEdge(i, k)) : LIMIT;
        }

        mark[i] = true;

        for(int k = 0; k < vCount(); k++)
        {
            E m = LIMIT;
            int u = -1;
            for(int w = 0; w < vCount(); w++)
            {
                if(!mark[w] && (dist[w] < m))
                {
                    m = dist[w];
                    u = w;
                }
            }

            if(u == -1)
            {
                break;
            }
            mark[u] = true;

            for(int w = 0; w < vCount(); w++)
            {
                if(!mark[w] && isAdjacent(u, w) && (dist[u] + getEdge(u, w) < dist[w]))
                {
                    dist[w] = dist[u] + getEdge(u, w);
                    path[w] = u;
                }
            }
        }

        LinkStack<int > s;
        s.push(j);
        for(int k = path[j]; k != -1; k = path[k])
        {
            s.push(k);
        }
        while(s.size() > 0)
        {
            ret.add(s.top());
            s.pop();
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Index<i, j> is invalid...");
    }

    if(ret.length() < 2)
    {
        THROW_EXCEPTION(ArithmeticException, "There is no path form i to j...");
    }

    return toArray(ret);
}

template <typename V, typename E>
bool Graph<V, E>::asUndirected()
{
    bool ret = true;

    for(int i = 0; i < vCount(); i++)
    {
        for(int j = 0; j < vCount(); j++)
        {
            if(isAdjacent(i, j))
            {
                ret = ret && isAdjacent(j, i);
                ret = ret && (getEdge(i, j) == getEdge(j, i));
            }
        }
    }

    return ret;

}

}

#endif
