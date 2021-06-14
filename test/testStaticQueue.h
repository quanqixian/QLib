#ifndef _TEST_STATICQUEUE_H__
#define _TEST_STATICQUEUE_H_

#include "StaticQueue.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试 StaticQueue 基本使用
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticQueue, lengthAddRemoveFrontClearCapacity)
{
    bool throwFlag = false;

    StaticQueue<int, 5> queue;

    EXPECT_EQ(queue.capacity(), 5);
    EXPECT_EQ(queue.length(), 0);

    /* 测试空队列出队抛出异常 */
    try
    {
        queue.remove();
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_TRUE(throwFlag);

    /* 进队列 */
    for(int i = 0; i < 5; i++)
    {
        queue.add(i);
        EXPECT_EQ(queue.length(), i + 1);
    }

    /* 测试队列满时入队则抛出异常 */
    throwFlag = false;
    try
    {
        queue.add(5);
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_TRUE(throwFlag);

    for(int i = 0; queue.length() > 0; i++)
    {
        int val = queue.front();
        EXPECT_EQ(val, i);
        queue.remove();
    }
    EXPECT_EQ(queue.length(), 0);


    queue.add(5);
    EXPECT_EQ(queue.length(), 1);
    queue.clear();
    EXPECT_EQ(queue.length(), 0);
}

#endif
