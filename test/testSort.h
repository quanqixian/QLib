#ifndef _TEST_SORT_H_
#define _TEST_SORT_H_

#include "Sort.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试选择排序
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSort, selectSort)
{
    int array[10] = {1, 3 ,5, 7, 9, 0, 2, 4, 6, 8};

    Sort<int>::selectSort(array, 10);
    for(int i = 0;i < 10; i++)
    {
        EXPECT_EQ(array[i], i);
    }

    Sort<int>::selectSort(array, 10, false);
    for(int i = 9, j = 0; i > 0; i--, j++)
    {
        EXPECT_EQ(array[j], i);
    }
}

/**
 * @fn
 * @brief      测试插入排序
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSort, insertSort)
{
    int array[10] = {1, 3 ,5, 7, 9, 0, 2, 4, 6, 8};

    Sort<int>::insertSort(array, 10);
    for(int i = 0;i < 10; i++)
    {
        EXPECT_EQ(array[i], i);
    }

    Sort<int>::insertSort(array, 10, false);
    for(int i = 9, j = 0; i > 0; i--, j++)
    {
        EXPECT_EQ(array[j], i);
    }
}

/**
 * @fn
 * @brief      测试冒泡排序
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSort, bubbleSort)
{
    int array[10] = {1, 3 ,5, 7, 9, 0, 2, 4, 6, 8};

    Sort<int>::bubbleSort(array, 10);
    for(int i = 0;i < 10; i++)
    {
        EXPECT_EQ(array[i], i);
    }

    Sort<int>::bubbleSort(array, 10, false);
    for(int i = 9, j = 0; i > 0; i--, j++)
    {
        EXPECT_EQ(array[j], i);
    }
}

/**
 * @fn
 * @brief      测试快速排序
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSort, quickSort)
{
    int array[10] = {1, 3 ,5, 7, 9, 0, 2, 4, 6, 8};

    Sort<int>::quickSort(array, 10);
    for(int i = 0;i < 10; i++)
    {
        EXPECT_EQ(array[i], i);
    }

    Sort<int>::quickSort(array, 10, false);
    for(int i = 9, j = 0; i > 0; i--, j++)
    {
        EXPECT_EQ(array[j], i);
    }
}
#endif
