#ifndef _TEST_STATIC_LIST_H_
#define _TEST_STATIC_LIST_H_

#include "StaticList.h"
#include "Exception.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试 增、删、改、查、获取长度、获取容量、清空
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticList, testBasicUse)
{
    StaticList<int, 5>list;
    EXPECT_EQ(list.capacity(), 5);

    for(int i = 0; i < list.capacity(); i++)
    {
        EXPECT_TRUE(list.insert(i));
        EXPECT_EQ(list.length(), i + 1);
    }

    for(int i = 0; i < list.length(); i++)
    {
        int temp = 0;
        EXPECT_TRUE(list.get(i, temp));
        EXPECT_EQ(temp, i);
    }

    EXPECT_TRUE(list.remove(0));
    EXPECT_EQ(list.length(), 4);

    for(int i = 0; i < list.length(); i++)
    {
        int temp = 0;
        EXPECT_TRUE(list.get(i, temp));
        EXPECT_EQ(temp, i + 1);
    }

    list.clear();
    EXPECT_EQ(list.length(), 0);

    for(int i = 0; i < list.capacity(); i++)
    {
        EXPECT_TRUE(list.insert(0, i));
        EXPECT_EQ(list.length(), i + 1);
    }
    EXPECT_FALSE(list.insert(6, 0));

    for(int i = 0; i < list.length(); i++)
    {
        int temp = 0;
        EXPECT_TRUE(list.get(i, temp));
        EXPECT_EQ(temp, 4 - i);
    }

    {
        int temp = 0;
        EXPECT_TRUE(list.set(0, 10));

        EXPECT_TRUE(list.get(0, temp));
        EXPECT_EQ(temp, 10);

        EXPECT_FALSE(list.set(10, 10));
    }
}

/**
 * @fn
 * @brief      测试数组操作符
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticList, testArrayOperator)
{

    StaticList<int, 5>list;
    
    /* 必须先插入元素才能使用数组操作符 */
    for(int i = 0; i < list.capacity(); i++)
    {
        EXPECT_TRUE(list.insert(i));
        EXPECT_EQ(list.length(), i + 1);
    }

    for(int i = 0; i < list.length(); i++)
    {
        EXPECT_EQ(list[i], i);
    }

    bool throwFlag = false;
    try
    {
        list[5] = 0;
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_TRUE(throwFlag);

    /* 测试const对象使用数组操作符 */
    const StaticList<int, 5> &listRef = list;
    EXPECT_EQ(listRef[2], 2);
}

#endif
