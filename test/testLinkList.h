#ifndef _TEST_LINKLIST_H_
#define _TEST_LINKLIST_H_

#include "LinkList.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试LinkList增删改查等
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testLinkList, insertRemoveSetGet)
{
    LinkList<int> list;

    /* 插入元素 */
    for(int i = 0; i < 5; i++)
    {
        list.insert(i);
    }

    /* 获取元素 */
    for(int i = 0; i < 5; i++)
    {
        int val = 0;
        EXPECT_TRUE(list.get(i, val));
        EXPECT_EQ(val, i);

        EXPECT_EQ(list.get(i), i);
    }

    /* 设置元素值 */
    for(int i = 0; i < 5; i++)
    {
        EXPECT_TRUE(list.set(i, i * i));
    }

    /* 获取元素 */
    for(int i = 0; i < 5; i++)
    {
        EXPECT_EQ(list.get(i), i * i);
    }

    /* 获取链表长度 */
    EXPECT_EQ(list.length(), 5);

    /* 删除元素 */
    list.remove(0);

    /* 获取元素 */
    for(int i = 0; i < list.length(); i++)
    {
        EXPECT_EQ(list.get(i), (i + 1) * (i + 1));
    }

    /* 获取链表长度 */
    EXPECT_EQ(list.length(), 4);

    /* 清空链表 */
    list.clear();

    /* 获取链表长度 */
    EXPECT_EQ(list.length(), 0);
}

/**
 * @fn
 * @brief      测试LinkList头插、查找
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testLinkList, headInsertandFind)
{
    LinkList<int> list;

    /* 头插法插入元素 */
    for(int i = 0; i < 5; i++)
    {
        list.insert(0, i);
    }

    /* 获取元素 */
    for(int i = 0; i < 5; i++)
    {
        EXPECT_EQ(list.get(i), 4 - i);
    }

    /* 查找元素 */
    EXPECT_EQ(list.find(4), 0);
    EXPECT_EQ(list.find(0), 4);
    EXPECT_EQ(list.find(100), -1);
}

/**
 * @fn
 * @brief      测试LinkList遍历相关函数
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testLinkList, ergodic)
{
    LinkList<int> list;

    /* 插入元素 */
    for(int i = 0; i < 5; i++)
    {
        list.insert(i);
    }

    /* 遍历链表 */
    for(int i = (list.move(0, 1), 0); !list.end(); list.next())
    {
        EXPECT_EQ(list.current(), i);
        i++;
    }
}

#endif
