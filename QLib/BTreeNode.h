#ifndef BTREENODE_H_
#define BTREENODE_H_

#include "TreeNode.h"

namespace QLib
{

template <typename T>
class BTreeNode : public TreeNode<T>
{
public:
    BTreeNode<T> * left;
    BTreeNode<T> * right;
    BTreeNode();
    static BTreeNode<T> * NewNode();
};

template <typename T>
BTreeNode<T>::BTreeNode()
{
    left = nullptr;
    right = nullptr;
}

template <typename T>
BTreeNode<T> * BTreeNode<T>::NewNode()
{
    BTreeNode<T>* ret = new BTreeNode<T>();

    if(ret != nullptr)
    {
        ret->m_flag = true;
    }

    return ret;
}

}

#endif
