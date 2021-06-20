#ifndef _TEST_LINKQUEUE_H__
#define _TEST_LINKQUEUE_H__

#include "LinkQueue.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试 LinkQueue 基本使用
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testLinkQueue, lengthAddRemoveFrontClear)
{
    bool throwFlag = false;

    LinkQueue<int> queue;

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
