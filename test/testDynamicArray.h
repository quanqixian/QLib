#ifndef _TEST_DYNAMIC_ARRAY_H_
#define _TEST_DYNAMIC_ARRAY_H_

#include "DynamicArray.h"
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
TEST(testDynamicArray, testSetGetLength)
{
    DynamicArray<int>array(5);
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
TEST(testDynamicArray, testArrayOperator)
{
    DynamicArray<int>array(5);

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
    const DynamicArray<int> &arrayRef = array;
    EXPECT_EQ(arrayRef[2], 2);
}

/**
 * @fn
 * @brief      测试拷贝构造
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testDynamicArray, testCopyConstructor)
{
    DynamicArray<int>arrayA(5);
    for(int i = 0; i < arrayA.length(); i++)
    {
        arrayA[i] = i;
    }

    DynamicArray<int> arrayB(arrayA);
    for(int i = 0; i < arrayB.length(); i++)
    {
        EXPECT_EQ(arrayA[i], arrayB[i]);
    }

    DynamicArray<int> arrayC = arrayA;
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
TEST(testDynamicArray, testAssignmentOperator)
{
    DynamicArray<int>arrayA(5), arrayB(10), arrayC(1);
    for(int i = 0; i < arrayA.length(); i++)
    {
        arrayA[i] = i;
        arrayB[i] = i * 100;
    }

    arrayB = arrayA;
    arrayC = arrayA;

    ASSERT_EQ(arrayA.length(), arrayB.length());
    ASSERT_EQ(arrayB.length(), arrayC.length());

    for(int i = 0; i < arrayA.length(); i++)
    {
        EXPECT_EQ(arrayA[i], arrayB[i]);
        EXPECT_EQ(arrayB[i], arrayC[i]);
    }
}

/**
 * @fn
 * @brief      测试resize
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testDynamicArray, testResize)
{
    DynamicArray<int>array(5);

    for(int i = 0; i < array.length(); i++)
    {
        array[i] = i;
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

    array.resize(6);

    throwFlag = false;
    try
    {
        array[5] = 0;
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_FALSE(throwFlag);
}

#endif
