#ifndef BTREE_H_
#define BTREE_H_

#include "Tree.h"
#include "BTreeNode.h"
#include "Exception.h"
#include "LinkQueue.h"
#include "DynamicArray.h"

namespace QLib
{

enum BTTraversal
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
};

enum BTNodePos
{
    ANY,
    LEFT,
    RIGHT
};

template <typename T>
class BTree : public Tree<T>
{
protected:
    LinkQueue<BTreeNode<T> * > m_queue;
protected:
    virtual BTreeNode<T> * find(BTreeNode<T> * node, const T & value) const;
    virtual BTreeNode<T> * find(BTreeNode<T> * node, BTreeNode<T> * obj) const;
    virtual bool insert(BTreeNode<T> * n, BTreeNode<T> * np, BTNodePos pos);
    virtual void remove(BTreeNode<T> * node, BTree<T> * & ret);
    virtual void free(BTreeNode<T> * node);

    int count(BTreeNode<T> * node) const;
    int height(BTreeNode<T> * node) const;
    int degree(BTreeNode<T> * node) const;

    void preOrderTraversal(BTreeNode<T> * node, LinkQueue<BTreeNode<T> * > & queue);
    void InOrderTraversal(BTreeNode<T> * node, LinkQueue<BTreeNode<T> * > & queue);
    void postOrderTraversal(BTreeNode<T> * node, LinkQueue<BTreeNode<T> * > & queue);
    void levelOrderTraversal(BTreeNode<T> * node, LinkQueue<BTreeNode<T> * > & queue);
    void traversal(BTTraversal order, LinkQueue<BTreeNode<T> * > & queue);

    BTreeNode<T> * clone(BTreeNode<T> * node ) const;
    bool equal(BTreeNode<T> * lh, BTreeNode<T> * rh) const;
    BTreeNode<T> * add(BTreeNode<T> * lh, BTreeNode<T> * rh) const;
    BTreeNode<T> * connect(LinkQueue<BTreeNode<T> * > & queue);
public:
    bool insert(TreeNode<T> * node);
    virtual bool insert(TreeNode<T> * node, BTNodePos pos);
    bool insert(const T & value, TreeNode<T> * parent);
    virtual bool insert(const T & value, TreeNode<T> * parent, BTNodePos pos);

    SharedPointer<Tree<T> > remove(const T & value);
    SharedPointer<Tree<T> > remove(TreeNode<T> * node);

    BTreeNode<T> * find(const T & value) const;
    BTreeNode<T> * find(TreeNode<T> * node) const;

    BTreeNode<T> * root() const;
    int degree() const;
    int count() const;
    int height() const;
    void clear();

    bool begin();
    bool end();
    bool next();
    T current();

    SharedPointer<Array<T> > traversal(BTTraversal order);
    SharedPointer< BTree<T> > clone() const;

    bool operator == (const BTree<T> & btree);
    bool operator != (const BTree<T> & btree);
    SharedPointer<BTree<T> > add(const BTree<T> & btree) const;
    BTreeNode<T> * thread(BTTraversal order);

    ~BTree();
};

template <typename T>
BTreeNode<T> * BTree<T>::find(BTreeNode<T> * node, const T & value) const
{
    BTreeNode<T> * ret = nullptr;

    if(node != nullptr)
    {
        if(node->value == value)
        {
            ret = node;
        }
        else
        {
            if(ret == nullptr)
            {
                ret = find(node->left, value);
            }
            if(ret == nullptr)
            {
                ret=find(node->right, value);
            }
        }
    }

    return ret;
}

template <typename T>
BTreeNode<T> * BTree<T>::find(BTreeNode<T> * node, BTreeNode<T> * obj) const
{
    BTreeNode<T> * ret = nullptr;

    if(node == obj)
    {
        ret = node;
    }
    else
    {
        if(node != nullptr)
        {
            if(ret == nullptr)
            {
                ret = find(node->left, obj);
            }
            if(ret == nullptr)
            {
                ret = find(node->right, obj);
            }
        }
    }

    return ret;
}

template <typename T>
bool BTree<T>::insert(BTreeNode<T> * n, BTreeNode<T> * np, BTNodePos pos)
{
    bool ret = true;

    if( pos == ANY)
    {
        if(np->left == nullptr)
        {
            np->left = n;
        }
        else if(np->right == nullptr)
        {
            np->right = n;
        }
        else
        {
            ret = false;
        }
    }
    else if(pos == LEFT)
    {
        if(np->left == nullptr)
        {
            np->left = n;
        }
        else
        {
            ret = false;
        }
    }
    else if(pos == RIGHT)
    {
        if(np->right == nullptr)
        {
            np->right = n;
        }
        else
        {
            ret = false;
        }
    }
    else
    {
        ret = false;
    }

    return ret;
}

template <typename T>
void BTree<T>::remove(BTreeNode<T> * node, BTree<T> * & ret)
{
    ret = new BTree<T>();
    if(ret == nullptr)
    {
         THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree...");
    }
    else
    {
        if(root() == node)
        {
            this->m_root = nullptr;
        }
        else
        {
            BTreeNode<T> * parent = dynamic_cast<BTreeNode<T> * >(node->parent);
            if(parent->left == node)
            {
                parent->left = nullptr;
            }
            else if(parent->right == node)
            {
                parent->right = nullptr;
            }
            node->parent = nullptr;
        }
        ret->m_root = node;
    }
}

template <typename T>
void BTree<T>::free(BTreeNode<T> * node)
{
    if(node != nullptr)
    {
        free(node->left);
        free(node->right);

        if(node->flag())
        {
            delete node;
        }
    }
}

template <typename T>
int BTree<T>::count(BTreeNode<T> * node) const
{
    return (node != nullptr) ? (count(node->left) + count(node->right) + 1) : 0;
}

template <typename T>
int BTree<T>::height(BTreeNode<T> * node) const
{
    int ret = 0;

    if(node != nullptr)
    {
        int lh = height(node->left);
        int rh = height(node->right);
        ret = ((lh > rh) ? lh : rh) + 1;
    }

    return ret;
}

template <typename T>
int BTree<T>::degree(BTreeNode<T> * node) const
{
    int ret = 0;
    /**
    if(node != nullptr)
    {
        int dl = degree(node->left);
        int dr = degree(node->right);
        ret =(!!node->left + !!node->right);  // !!将非零值变为1,0值还是0
        if(ret < dl) {ret = dl;}
        if(ret < dr) {ret = dr;}
    }
    */

    /* 二叉树的度最多为2，根据此特性进行优化 */
    if( node != nullptr)
    {
        BTreeNode<T> * child[] = {node->left, node->right};
        ret = (!!node->left + !!node->right);
        for(int i = 0; (i < 2) && (ret < 2); i++)
        {
            int d = degree(child[i]);
            if(ret < d)
            {
                ret = d;
            }
        }
    }

    return ret;
}

template <typename T>
void BTree<T>::preOrderTraversal(BTreeNode<T> * node, LinkQueue<BTreeNode<T> * > & queue)
{
    if(node != nullptr)
    {
        queue.add(node);
        preOrderTraversal(node->left, queue);
        preOrderTraversal(node->right, queue);
    }
}

template <typename T>
void BTree<T>::InOrderTraversal(BTreeNode<T> * node, LinkQueue<BTreeNode<T> * > & queue)
{
    if(node != nullptr)
    {
        InOrderTraversal(node->left, queue);
        queue.add(node);
        InOrderTraversal(node->right, queue);
    }
}

template <typename T>
void BTree<T>::postOrderTraversal(BTreeNode<T> * node, LinkQueue<BTreeNode<T> * > & queue)
{
    if(node != nullptr)
    {
        postOrderTraversal(node->left, queue);
        postOrderTraversal(node->right, queue);
        queue.add(node);
    }
}

template <typename T>
void BTree<T>::levelOrderTraversal(BTreeNode<T> * node, LinkQueue<BTreeNode<T> * > & queue)
{
    if( node != nullptr)
    {
        LinkQueue<BTreeNode<T> * > tmp;
        tmp.add(root());
        while(tmp.length() > 0)
        {
            BTreeNode<T> * n = tmp.front();
            if(n->left != nullptr)
            {
                tmp.add(n->left);
            }
            if(n->right != nullptr)
            {
                tmp.add(n->right);
            }
            tmp.remove();
            queue.add(n);
        }
    }
}

template <typename T>
BTreeNode<T> * BTree<T>::clone(BTreeNode<T> * node ) const
{
    BTreeNode<T> * ret = nullptr;

    if(node != nullptr)
    {
        ret = BTreeNode<T>::NewNode();
        if(ret != nullptr)
        {
            ret->value = node->value;
            ret->left = clone(node->left);
            ret->right = clone(node->right);
            if(ret->left != nullptr)
            {
                ret->left->parent = ret;
            }
            if(ret->right != nullptr)
            {
                ret->right->parent = ret;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new node...");
        }
    }

    return ret;
}

template <typename T>
bool BTree<T>::equal(BTreeNode<T> * lh, BTreeNode<T> * rh) const
{
    if(lh == rh)
    {
        return true;
    }
    else if((lh != nullptr) && (rh != nullptr))
    {
        return (lh->value == rh->value) && equal(lh->left, rh->left) && equal(lh->right, rh->right);
    }
    else
    {
        return false;
    }
}

template <typename T>
BTreeNode<T> * BTree<T>::add(BTreeNode<T> * lh, BTreeNode<T> * rh) const
{
    BTreeNode<T> * ret = nullptr;

    if((lh == nullptr) && (rh != nullptr))
    {
        ret = clone(rh);
    }
    else if ((lh != nullptr) && (rh == nullptr))
    {
        ret = clone(lh);
    }
    else if ((lh != nullptr) && (rh != nullptr))
    {
        ret = BTreeNode<T>::NewNode();
        if(ret != nullptr)
        {
            ret->value = lh->value + rh->value;
            ret->left = add(lh->left, rh->left);
            ret->right = add(lh->right, rh->right);
            if(ret->left != nullptr)
            {
                ret->left->parent = ret;
            }
            if( ret->right != nullptr)
            {
                ret->right->parent = ret;
            }
        }
        else
        {
            THROW_EXCEPTION(NoEnoughMemoryException, "No memory to veate new node...");
        }
    }

    return ret;
}

template <typename T>
void BTree<T>::traversal(BTTraversal order, LinkQueue<BTreeNode<T> * > & queue)
{
    switch(order)
    {
    case PreOrder:
        preOrderTraversal(root(), queue);
        break;
    case InOrder:
        InOrderTraversal(root(),queue);
        break;
    case PostOrder:
        postOrderTraversal(root(), queue);
        break;
    case LevelOrder:
        levelOrderTraversal(root(), queue);
        break;
    default:
        THROW_EXCEPTION(InvalidParameterException, "Parameter order is invalid...");
        break;
    }
}

template <typename T>
BTreeNode<T> * BTree<T>::connect(LinkQueue<BTreeNode<T> * > & queue)
{
    BTreeNode<T> * ret = nullptr;

    if(queue.length() > 0)
    {
        ret = queue.front();
        BTreeNode<T> * slider = queue.front();
        queue.remove();
        slider->left = nullptr;
        while(queue.length() > 0)
        {
            slider->right = queue.front();
            queue.front()->left = slider;
            slider = queue.front();
            queue.remove();
        }
        slider->right = nullptr;
    }

    return ret;
}

template <typename T>
bool BTree<T>::insert(TreeNode<T> * node)
{
    return insert(node, ANY);
}

template <typename T>
bool BTree<T>::insert(TreeNode<T> * node, BTNodePos pos)
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
            BTreeNode<T> * np = find(node->parent);
            if(np != nullptr)
            {
                ret = insert(dynamic_cast<BTreeNode<T> * >(node), np, pos);
            }
            else
            {
                THROW_EXCEPTION(InvalidParameterException, "Invaild parent tree node...");
            }
        }
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter node can not be nullptr");
    }

    return ret;
}

template <typename T>
bool BTree<T>::insert(const T & value, TreeNode<T> * parent)
{
    return insert(value, parent, ANY);
}

template <typename T>
bool BTree<T>::insert(const T & value, TreeNode<T> * parent, BTNodePos pos)
{
    bool ret = true;

    BTreeNode<T> * node = BTreeNode<T>::NewNode();
    if(node == nullptr)
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No meory oto create new node...");
    }
    else
    {
        node->value = value;
        node->parent = parent;
        ret = insert(node, pos);
        if(!ret)
        {
            delete node;
        }
    }

    return ret;
}

template <typename T>
SharedPointer<Tree<T> > BTree<T>::remove(const T & value)
{
    BTree<T> * ret = nullptr;

    BTreeNode<T> * node = find(value);
    if(node == nullptr)
    {
       THROW_EXCEPTION(InvalidParameterException, "Can not find the tree node via value...");
    }
    else
    {
        remove(node, ret);
        m_queue.clear();
    }

    return ret;
}

template <typename T>
SharedPointer<Tree<T> > BTree<T>::remove(TreeNode<T> * node)
{
    BTree<T> * ret = nullptr;

    node = find(node);
    if( node == nullptr)
    {
        THROW_EXCEPTION(InvalidParameterException, "Parameter node is invalie...");
    }
    else
    {
        m_queue.clear();
        remove(dynamic_cast<BTreeNode<T> *>(node), ret);
    }

    return ret;
}

template <typename T>
BTreeNode<T> * BTree<T>::find(const T & value) const
{
    return find(root(), value);
}

template <typename T>
BTreeNode<T> * BTree<T>::find(TreeNode<T> * node) const
{
    return find(root(), dynamic_cast<BTreeNode<T> * >(node));
}

template <typename T>
BTreeNode<T> * BTree<T>::root() const
{
    return dynamic_cast<BTreeNode<T> * >(this->m_root);
}

template <typename T>
int BTree<T>::degree() const
{
    return degree(root());
}

template <typename T>
int BTree<T>::count() const
{
    return count(root());
}

template <typename T>
int BTree<T>::height() const
{
    return height(root());
}

template <typename T>
void BTree<T>::clear()
{
    free(root());
    this->m_root = nullptr;
}

template <typename T>
bool BTree<T>::begin()
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
bool BTree<T>::end()
{
    return (m_queue.length() == 0);
}

template <typename T>
bool BTree<T>::next()
{
    bool ret = (m_queue.length() > 0);

    if(ret)
    {
        BTreeNode<T> * node = m_queue.front();
        m_queue.remove();
        if( node->left != nullptr)
        {
            m_queue.add(node->left);
        }
        if( node->right != nullptr)
        {
            m_queue.add(node->right);
        }
    }

    return ret;
}

template <typename T>
T BTree<T>::current()
{
    if(!end())
    {
        return m_queue.front()->value;
    }
    else
    {
        THROW_EXCEPTION(InvalidParameterException, "No value at current poaistion...");
    }
}

template <typename T>
SharedPointer<Array<T> > BTree<T>::traversal(BTTraversal order)
{
    DynamicArray<T> * ret = nullptr;
    LinkQueue<BTreeNode<T>* > queue;

    traversal(order,queue);

    ret = new DynamicArray<T>(queue.length());
    if(ret != nullptr)
    {
        for(int i = 0; i < ret->length(); i++, queue.remove())
        {
            ret->set(i, queue.front()->value);
        }
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create return array...");
    }

    return ret;
}

template <typename T>
SharedPointer< BTree<T> > BTree<T>::clone() const
{
    BTree<T> * ret = new BTree<T>();

    if(ret != nullptr)
    {
        ret->m_root = clone(root());
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree ...");
    }

    return ret;
}

template <typename T>
bool BTree<T>::operator == (const BTree<T> & btree)
{
    return equal(root(), btree.root());
}

template <typename T>
bool BTree<T>::operator != (const BTree<T> & btree)
{
    return !(*this == btree);
}

template <typename T>
SharedPointer<BTree<T> > BTree<T>::add(const BTree<T> & btree) const
{
    BTree<T> * ret = new BTree<T>();

    if(ret != nullptr)
    {
        ret->m_root = add(root(), btree.root());
    }
    else
    {
        THROW_EXCEPTION(NoEnoughMemoryException, "No memory to create new tree...");
    }

    return ret;
}

template <typename T>
BTreeNode<T> * BTree<T>::thread(BTTraversal order)
{
    BTreeNode<T> * ret = nullptr;
    LinkQueue<BTreeNode<T> * >queue;

    traversal(order,queue);
    ret = connect(queue);
    this->m_root = nullptr;
    m_queue.clear();

    return ret;
}

template <typename T>
BTree<T>::~BTree()
{
    clear();
    m_queue.clear();
}

}/* end of namespace */


#endif
