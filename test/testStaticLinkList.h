#ifndef _TEST_STATICLINKLIST_H_
#define _TEST_STATICLINKLIST_H_

#include "StaticLinkList.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试StaticLinkList插入元素数量超出容量时抛出异常
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticLinkList, insertException)
{
    StaticLinkList<int, 5> list;

    /* 插入元素 */
    for(int i = 0; i < 5; i++)
    {
        list.insert(i);
    }

    bool throwFlag = false;

    /* 测试插入元素超出容量时抛出异常 */
    try
    {
        list.insert(5);
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_TRUE(throwFlag);
}

/**
 * @fn
 * @brief      测试StaticLinkList增删改查等
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticLinkList, insertRemoveSetGet)
{
    StaticLinkList<int, 5> list;

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
 * @brief      测试StaticLinkList头插、查找
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticLinkList, headInsertandFind)
{
    StaticLinkList<int, 5> list;

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
 * @brief      测试StaticLinkList遍历相关函数
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticLinkList, ergodic)
{
    StaticLinkList<int, 5> list;

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
