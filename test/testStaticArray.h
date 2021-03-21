#ifndef _TEST_STATIC_ARRAY_H_
#define _TEST_STATIC_ARRAY_H_

#include "StaticArray.h"
#include "Exception.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试 set get 获取长度
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticArray, testSetGetLength)
{
    StaticArray<int, 5>array;
    EXPECT_EQ(array.length(), 5);

    for(int i = 0; i < array.length(); i++)
    {
        EXPECT_TRUE(array.set(i, i));
    }

    for(int i = 0; i < array.length(); i++)
    {
        int temp = 0;
        EXPECT_TRUE(array.get(i, temp));
        EXPECT_EQ(temp, i);
    }
}

/**
 * @fn
 * @brief      测试数组操作符
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticArray, testArrayOperator)
{
    StaticArray<int, 5>array;

    for(int i = 0; i < array.length(); i++)
    {
        array[i] = i;
    }

    for(int i = 0; i < array.length(); i++)
    {
        EXPECT_EQ(array[i], i);
    }

    bool throwFlag = false;
    try
    {
        array[5] = 0;
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_TRUE(throwFlag);

    /* 测试const对象使用数组操作符 */
    const StaticArray<int, 5> &arrayRef = array;
    EXPECT_EQ(arrayRef[2], 2);
}

/**
 * @fn
 * @brief      测试拷贝构造
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticArray, testCopyConstructor)
{
    StaticArray<int, 5>arrayA;
    for(int i = 0; i < arrayA.length(); i++)
    {
        arrayA[i] = i;
    }

    StaticArray<int, 5> arrayB(arrayA);
    for(int i = 0; i < arrayB.length(); i++)
    {
        EXPECT_EQ(arrayA[i], arrayB[i]);
    }

    StaticArray<int, 5> arrayC = arrayA;
    for(int i = 0; i < arrayB.length(); i++)
    {
        EXPECT_EQ(arrayA[i], arrayC[i]);
    }
}

/**
 * @fn
 * @brief      测试赋值操作符
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticArray, testAssignmentOperator)
{
    StaticArray<int, 5>arrayA, arrayB;
    for(int i = 0; i < arrayA.length(); i++)
    {
        arrayA[i] = i;
        arrayB[i] = i * 100;
    }

    arrayB = arrayA;

    for(int i = 0; i < arrayA.length(); i++)
    {
        EXPECT_EQ(arrayA[i], arrayB[i]);
    }
}

#endif
