#ifndef _TEST_DYNAMIC_LIST_H_
#define _TEST_DYNAMIC_LIST_H_

#include "DynamicList.h"
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
TEST(testDynamicList, testBasicUse)
{
    DynamicList<int>list(5);
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
        EXPECT_EQ(list.get(i), i);
        EXPECT_EQ(list.find(i), i);
    }
    EXPECT_EQ(list.find(100), -1);

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
TEST(testDynamicList, testArrayOperator)
{
    DynamicList<int>list(5);
    
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
    const DynamicList<int> &listRef = list;
    EXPECT_EQ(listRef[2], 2);
}

/**
 * @fn
 * @brief      测试resize
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testDynamicList, testResize)
{
    DynamicList<int>list(5);
    
    /* 必须先插入元素才能使用数组操作符 */
    for(int i = 0; i < list.capacity(); i++)
    {
        EXPECT_TRUE(list.insert(i));
        EXPECT_EQ(list.length(), i + 1);
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

    list.resize(6);
    list.insert(5);
    throwFlag = false;
    try
    {
        list[5] = 0;
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_FALSE(throwFlag);
}

/**
 * @fn
 * @brief      测试 类类型元素的查找
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testDynamicList, testFindClassType)
{
    class Test : public Object
    {
        int i;
    public:
        Test(int v = 0)
        {
            i = v;
        }
        bool operator == (const Test& obj)
        {
            return this->i == obj.i;
        }
    };
    class TestB : public Object
    {
    };
    DynamicList<Test>list(5);

    for(int i = 0; i < list.capacity(); i++)
    {
        EXPECT_TRUE(list.insert(Test(i)));
        EXPECT_EQ(list.find(Test(i)), i);
    }

    EXPECT_EQ(list.find(Test(100)), -1);

    /* 继承父类中默认的相等比较操作符，使编译不会报错 */
    DynamicList<TestB>listB(5);
}

#endif
