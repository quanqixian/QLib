#ifndef _TEST_STATICSTACK_H_
#define _TEST_STATICSTACK_H_

#include "StaticStack.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试 StaticStack 基本使用
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testStaticStack, capacityPushPopTopSizeClear)
{
    bool throwFlag = false;

    StaticStack<int, 5> stack;

    EXPECT_EQ(stack.capacity(), 5);
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

    /* 测试栈满时push则抛出异常 */
    throwFlag = false;
    try
    {
        stack.push(5);
    }
    catch(const Exception & e)
    {
        throwFlag = true;
    }
    EXPECT_TRUE(throwFlag);

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
