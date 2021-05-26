#ifndef _TEST_CIRCLELIST_H_
#define _TEST_CIRCLELIST_H_

#include "CircleList.h"
#include "gtest/gtest.h"
#include <iostream>

using namespace QLib;

/**
 * @fn
 * @brief      测试CircleList增删改查等
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testCircleList, testAsLinkList01)
{
    CircleList<int> list;

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
 * @brief      测试CircleList头插、查找
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testCircleList, testAsLinkList02)
{
    CircleList<int> list;

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
 * @brief      测试CircleList遍历相关函数
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testCircleList, ergodic)
{
    CircleList<int> list;

    /* 插入元素 */
    for(int i = 0; i < 5; i++)
    {
        list.insert(i);
    }

    for(int i = 0; i< 15; i++)
    {
        EXPECT_EQ(list.get(i), i%5);
    }

    /* 遍历链表 */
    for(int i = (list.move(0, 1), 0); (!list.end()) && (i < 5); list.next())
    {
        EXPECT_EQ(list.current(), i);
        i++;
    }
}

/**
 * @fn
 * @brief      测试约瑟夫环
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testCircleList, JosephRing)
{
    CircleList<int> list;

    /* 插入元素 */
    for(int i = 1; i <= 41; i++)
    {
        list.insert(i);
    }

    int array[] = {3, 6, 9, 12, 15, 18, 21, 24, 
        27, 30, 33, 36, 39, 1, 5, 10, 14, 19, 23,
        28, 32, 37, 41, 7, 13, 20, 26, 34, 40, 8,
        17, 29, 38, 11, 25, 2, 22, 4, 35, 16, 31};

    /**
     * 已知n个人（以编号1， 1，2，...，n分别表示）围坐在一张圆桌周围。
     * 编号为1的人开始从1报数，数到m的那个人出列；他的下一个人又从1开始报数，
     * 数到m的那个人又出列；依此规律重复下去，直到圆桌周围的人全部出列。
     */
    for(int i = (list.move(0, 3-1), 0); !list.end(); list.remove(list.find(list.current())))
    {
        list.next();

        ASSERT_FALSE(i>= 41);
        EXPECT_EQ(list.current(), array[i]);
        i++;
    }
}
#endif
