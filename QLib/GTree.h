#ifndef GTREE_H
#define GTREE_H

#include "Tree.h"
#include "GTreeNode.h"
#include "LinkQueue.h"
#include "Exception.h"

namespace QLib
{

template <typename T>
class GTree : public Tree<T>
{
protected:
    LinkQueue<GTreeNode<T> *> m_queue;
public:
    GTree();
    bool insert(TreeNode<T>* node);
    bool insert(const T & value, TreeNode<T> * parent);

    void remove(GTreeNode<T> * node, GTree<T>* & ret);
    SharedPointer< Tree<T> > remove( const T & value);
    SharedPointer< Tree<T> > remove(TreeNode<T> * node);

    GTreeNode<T> * find(GTreeNode<T> * node, const T & value) const;
    GTreeNode<T> * find(const T & value) const;
    GTreeNode<T> * find(GTreeNode<T> * node, GTreeNode<T> * obj) const;
    GTreeNode<T> * find(TreeNode<T> * node) const;

    void clear();

    GTreeNode<T> * root() const;
    int degree(GTreeNode<T> * node) const;
    int degree() const;
    int count(GTreeNode<T> * node) const;
    int count() const;
    int height(GTreeNode<T> * node) const;
    int height() const;

    T current();
    bool begin();
    bool end();
    bool next();
    void free(GTreeNode<T> * node);

    ~GTree();
};

template <typename T>
GTree<T>::GTree()
{

}

template <typename T>
bool GTree<T>::insert(TreeNode<T>* node)
{
    bool ret = true;
    if(node != nullptr)
    {
        if(this->m_root == nullptr)
        {
            node->parent = nullptr;
            this->m_root = node;
        }
        else
        {
            GTreeNode<T> * np = find(node->parent);
            if(np != nullptr)
            {
                /**
                 * 查找该节点node是否已经在树中 
                 * 若已经在树中，则不需要插入node节点 
                 * 查找方法为：在node的父节点np中的子链表中查找（这个方法高效）
                 */
                GTreeNode<T> * n = dynamic_cast<GTreeNode<T>* >(node);
                if(np->child.find(n) < 0)/* 如果没有在链表中没有找到，则插入该链表中 */
                {
                    np->child.insert(n);
                }
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Invaild parent tree node...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Paremeter node connot be nullptr...");
    }
    return ret;
}

template <typename T>
bool GTree<T>::insert(const T & value, TreeNode<T> * parent)
{
    bool ret = true;

    GTreeNode<T> * node = GTreeNode<T>::NewNode();/* 使用工厂方法 */
    if(node != nullptr)
    {
        node->value = value;
        node->parent = parent;
        insert(node);
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create New GTreeNode...");
    }

    return ret;
}

template <typename T>
void GTree<T>::remove(GTreeNode<T> * node, GTree<T>* & ret)
{
    ret = new GTree<T>();
    if(ret != nullptr)
    {
        if(root() != node)
        {
            LinkList<GTreeNode<T> *> & child = dynamic_cast<GTreeNode<T> * >(node->parent)->child;/* 父节点的孩子链表 */
            child.remove(child.find(node));/* 删除链表中的node节点 */
            node->parent = nullptr;        /* 将node节点的parent 指针置为空 */
        }
        else
        {
            this->m_root = nullptr;
        }
        ret->m_root = node;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create  a GTree...");
    }
}

template <typename T>
SharedPointer< Tree<T> > GTree<T>::remove( const T & value)
{
    GTree<T>* ret = nullptr;
    GTreeNode<T>* node = find(value);
    if(node != nullptr)
    {
        remove(node, ret);
        m_queue.clear();
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "can not find node via value...");
    }
    return nullptr;
}

template <typename T>
SharedPointer< Tree<T> > GTree<T>::remove(TreeNode<T> * node)
{
    GTree<T>* ret = nullptr;
    if(find(node) != nullptr)
    {
        remove(dynamic_cast<GTreeNode<T> * >(node), ret);
        m_queue.clear();
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter node invalid...");
    }
    return nullptr;
}

template <typename T>
GTreeNode<T> * GTree<T>::find(GTreeNode<T> * node, const T & value) const
{
    GTreeNode<T> * ret = nullptr;
    if(node != nullptr)
    {
       if(node->value == value)
       {
           return node;
       }
       else
       {
           for(node->child.move(0); !node->child.end() && (ret == nullptr); node->child.next())
           {
               ret = find(node->child.current(), value);
           }
       }
    }
    return ret;
}

template <typename T>
GTreeNode<T> * GTree<T>::find(const T & value) const
{
    return find(root(), value);
}

template <typename T>
GTreeNode<T> * GTree<T>::find(GTreeNode<T> * node, GTreeNode<T> * obj) const
{
    GTreeNode<T> * ret = nullptr;
    if(node == obj)
    {
        return node;
    }
    else
    {
        if( node != nullptr)
        {
            for(node->child.move(0); !node->child.end() && (ret == nullptr); node->child.next())
            {
                ret = find(node->child.current(), obj);
            }
        }
    }
    return ret;
}

template <typename T>
GTreeNode<T> * GTree<T>::find(TreeNode<T> * node) const
{
    return find(root(), dynamic_cast<GTreeNode<T> * >(node));
}

template <typename T>
void GTree<T>::clear()
{
    free(root());
    this->m_root = nullptr;
    m_queue.clear();
}

template <typename T>
GTreeNode<T> * GTree<T>::root() const
{
    return dynamic_cast<GTreeNode<T> * >(this->m_root);
}

template <typename T>
int GTree<T>::degree(GTreeNode<T> * node) const
{
    int ret = 0;

    if(node != nullptr)
    {
        ret = node->child.length();
        for(node->child.move(0); !node->child.end(); node->child.next())
        {
            int d = degree(node->child.current());
            if(ret < d)
            {
                ret = d;
            }
        }
    }

    return ret;
}

template <typename T>
int GTree<T>::degree() const
{
    return degree(root());
}

template <typename T>
int GTree<T>::count(GTreeNode<T> * node) const
{
    int ret = 0;

    if(node != nullptr)
    {
        ret = 1;
        for(node->child.move(0); !node->child.end(); node->child.next())
        { 
            ret += count(node->child.current());
        }
    }

    return ret;
}

template <typename T>
int GTree<T>::count() const
{
    return count(root());
}

template <typename T>
int GTree<T>::height(GTreeNode<T> * node) const
{
    int ret = 0;

    if(node != nullptr)
    {
        for(node->child.move(0); !node->child.end(); node->child.next())
        {
            int h = height(node->child.current());
            if(ret < h)
            {
                ret = h;
            }
        }
        ret = ret + 1;
    }

    return ret;
}

template <typename T>
int GTree<T>::height() const
{
    return height(root());
}

template <typename T>
T GTree<T>::current()
{
    if(!end())
    {
       return m_queue.front()->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidOperationException, "NO value at current position...");
    }
}

template <typename T>
bool GTree<T>::begin()
{
    bool ret = (root() != nullptr);

    if(ret)
    {
        m_queue.clear();
        m_queue.add(root());
    }

    return ret;
}

template <typename T>
bool GTree<T>::end()
{
    return (m_queue.length() == 0);
}

template <typename T>
bool GTree<T>::next()
{
    bool ret = (m_queue.length() > 0);

    if(ret)
    {
        GTreeNode<T> * node = m_queue.front();
        m_queue.remove();
        for(node->child.move(0); !node->child.end(); node->child.next())
        {
            m_queue.add(node->child.current());
        }
    }

    return ret;
}

template <typename T>
void GTree<T>::free(GTreeNode<T> * node)
{
    if(node != nullptr)
    {
        for(node->child.move(0); !node->child.end(); node->child.next())
        {
            free(node->child.current());
        }
        if(node->flag())/* 添加判断条件，如果flag为真，即在堆空间中创建的对象，则需要delete空间 */
        {
            delete node;
        }
    }
}

template <typename T>
GTree<T>::~GTree()
{
    clear();
}

}/*end of namespace*/

#endif
