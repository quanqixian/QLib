#ifndef TREENODE_H_
#define TREENODE_H_

#include "Object.h"

namespace QLib
{

template <typename T>
class TreeNode : public Object
{
protected:
    bool m_flag;
protected:
    TreeNode(TreeNode<T> &);
    TreeNode<T> & operator = (const TreeNode<T> &);
    void * operator new(long unsigned int size) throw(); /* 将new设置为保护成员函数 */
public:
    T value;
    TreeNode<T> * parent;
    TreeNode();
    bool flag();
    virtual ~TreeNode() = 0;
};

template<typename T>
TreeNode<T>::TreeNode()
{
    m_flag = false;
    parent = nullptr;
}

template<typename T>
void * TreeNode<T>::operator new(long unsigned int size) throw()
{
    return Object::operator new(size);
}

template<typename T>
bool TreeNode<T>::flag()
{
    return m_flag;
}

template<typename T>
TreeNode<T>::~TreeNode()
{

}

}

#endif
