#ifndef _TEST_LINKSTACK_H__
#define _TEST_LINKSTACK_H__

#include "LinkStack.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试 LinkStack 基本使用
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testLinkStack, PushPopTopSizeClear)
{
    bool throwFlag = false;

    LinkStack<int> stack;
    EXPECT_EQ(stack.size(), 0);

    /* 测试空栈pop抛出异常 */
    try
    {
        stack.pop();
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_TRUE(throwFlag);

    /* 进栈 */
    for(int i = 0; i < 5; i++)
    {
        stack.push(i);
        EXPECT_EQ(stack.size(), i + 1);
    }

    for(int i = 0; stack.size() > 0; i++)
    {
        int val = stack.top();
        EXPECT_EQ(val, 4 - i);
        stack.pop();
    }
    EXPECT_EQ(stack.size(), 0);

    stack.push(5);
    EXPECT_EQ(stack.size(), 1);
    stack.clear();
    EXPECT_EQ(stack.size(), 0);
}

#endif
