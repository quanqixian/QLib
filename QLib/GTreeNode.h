#ifndef GREENODE_H_
#define GREENODE_H_

#include "Tree.h"
#include "LinkList.h"

namespace QLib
{

template <typename T>
class GTreeNode : public TreeNode<T>
{
public:
    LinkList< GTreeNode<T>* > child;
    static GTreeNode<T> * NewNode();/* 工厂方法 */
};

GTreeNode<T> * GTreeNode<T>::NewNode()
{
    GTreeNode<T> * ret = new GTreeNode<T>();

    if(ret != nullptr)
    {
        ret->m_flag = true;
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "NO memory to create new GTreeNode... ");
    }

    return ret;
}

}

#endif
