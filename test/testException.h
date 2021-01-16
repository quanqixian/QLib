#ifndef _TEST_EXCEPTION_H_
#define _TEST_EXCEPTION_H_

#include "Exception.h"
#include <iostream>
#include "gtest/gtest.h"
#include <cstring>
using namespace QLib;

/**
 * @fn
 * @brief      测试 Exception
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testException, ExceptionPointer)
{

    Exception * pEx = nullptr;
    EXPECT_EQ(pEx, nullptr);
}

/**
 * @fn
 * @brief      测试 ArithmeticException
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testException, ArithmeticException)
{
    /**
     * 基本使用测试
     */
    try
    {
        THROW_EXCEPTION(ArithmeticException,"test");
    }
    catch(const ArithmeticException& e)
    {
        EXPECT_EQ(strcmp(e.message(), "test"), 0);
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }

    /**
     * 测试构造函数
     */
    ArithmeticException e1;
    EXPECT_EQ(e1.message(), nullptr);
    EXPECT_EQ(e1.location(), nullptr);

    ArithmeticException e2("Message");
    EXPECT_NE(e2.message(), nullptr);
    EXPECT_EQ(e2.location(), nullptr);
    EXPECT_EQ(strcmp(e2.message(), "Message"), 0);

    ArithmeticException e3("File", 10);
    EXPECT_EQ(e3.message(), nullptr);
    EXPECT_NE(e3.location(), nullptr);

    ArithmeticException e4("Message", "File", 10);
    EXPECT_NE(e4.message(), nullptr);
    EXPECT_NE(e4.location(), nullptr);
    EXPECT_EQ(strcmp(e4.message(), "Message"), 0);
    EXPECT_EQ(strcmp(e4.location(), "File:10"), 0);

    /**
     * 测试拷贝构造函数
     */
    ArithmeticException e5(e4);
    EXPECT_NE(e4.location(), e5.location());
    EXPECT_NE(e4.message(), e5.message());
    EXPECT_EQ(strcmp(e4.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e4.location(), e5.location()), 0);

    /**
     * 测试赋值操作符
     */
    e1 = e5;
    EXPECT_NE(e1.message(), nullptr);
    EXPECT_NE(e1.location(), nullptr);
    EXPECT_EQ(strcmp(e1.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e1.location(), e5.location()), 0);
}

/**
 * @fn
 * @brief      测试 NullPointerException
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testException, NullPointerException)
{
    /**
     * 基本使用测试
     */
    try
    {
        THROW_EXCEPTION(NullPointerException,"test");
    }
    catch(const NullPointerException& e)
    {
        EXPECT_EQ(strcmp(e.message(), "test"), 0);
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }

    /**
     * 测试构造函数
     */
    NullPointerException e1;
    EXPECT_EQ(e1.message(), nullptr);
    EXPECT_EQ(e1.location(), nullptr);

    NullPointerException e2("Message");
    EXPECT_NE(e2.message(), nullptr);
    EXPECT_EQ(e2.location(), nullptr);
    EXPECT_EQ(strcmp(e2.message(), "Message"), 0);

    NullPointerException e3("File", 10);
    EXPECT_EQ(e3.message(), nullptr);
    EXPECT_NE(e3.location(), nullptr);

    NullPointerException e4("Message", "File", 10);
    EXPECT_NE(e4.message(), nullptr);
    EXPECT_NE(e4.location(), nullptr);
    EXPECT_EQ(strcmp(e4.message(), "Message"), 0);
    EXPECT_EQ(strcmp(e4.location(), "File:10"), 0);

    /**
     * 测试拷贝构造函数
     */
    NullPointerException e5(e4);
    EXPECT_NE(e4.location(), e5.location());
    EXPECT_NE(e4.message(), e5.message());
    EXPECT_EQ(strcmp(e4.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e4.location(), e5.location()), 0);

    /**
     * 测试赋值操作符
     */
    e1 = e5;
    EXPECT_NE(e1.message(), nullptr);
    EXPECT_NE(e1.location(), nullptr);
    EXPECT_EQ(strcmp(e1.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e1.location(), e5.location()), 0);
}

/**
 * @fn
 * @brief      测试 IndexOutOfBoundsException
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testException, IndexOutOfBoundsException)
{
    /**
     * 基本使用测试
     */
    try
    {
        THROW_EXCEPTION(IndexOutOfBoundsException,"test");
    }
    catch(const IndexOutOfBoundsException & e)
    {
        EXPECT_EQ(strcmp(e.message(), "test"), 0);
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }

    /**
     * 测试构造函数
     */
    IndexOutOfBoundsException e1;
    EXPECT_EQ(e1.message(), nullptr);
    EXPECT_EQ(e1.location(), nullptr);

    IndexOutOfBoundsException e2("Message");
    EXPECT_NE(e2.message(), nullptr);
    EXPECT_EQ(e2.location(), nullptr);
    EXPECT_EQ(strcmp(e2.message(), "Message"), 0);

    IndexOutOfBoundsException e3("File", 10);
    EXPECT_EQ(e3.message(), nullptr);
    EXPECT_NE(e3.location(), nullptr);

    IndexOutOfBoundsException e4("Message", "File", 10);
    EXPECT_NE(e4.message(), nullptr);
    EXPECT_NE(e4.location(), nullptr);
    EXPECT_EQ(strcmp(e4.message(), "Message"), 0);
    EXPECT_EQ(strcmp(e4.location(), "File:10"), 0);

    /**
     * 测试拷贝构造函数
     */
    IndexOutOfBoundsException e5(e4);
    EXPECT_NE(e4.location(), e5.location());
    EXPECT_NE(e4.message(), e5.message());
    EXPECT_EQ(strcmp(e4.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e4.location(), e5.location()), 0);

    /**
     * 测试赋值操作符
     */
    e1 = e5;
    EXPECT_NE(e1.message(), nullptr);
    EXPECT_NE(e1.location(), nullptr);
    EXPECT_EQ(strcmp(e1.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e1.location(), e5.location()), 0);
}

/**
 * @fn
 * @brief      测试 NoEnoughMemoryException
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testException, NoEnoughMemoryException)
{
    /**
     * 基本使用测试
     */
    try
    {
        THROW_EXCEPTION(NoEnoughMemoryException,"test");
    }
    catch(const NoEnoughMemoryException & e)
    {
        EXPECT_EQ(strcmp(e.message(), "test"), 0);
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }

    /**
     * 测试构造函数
     */
    NoEnoughMemoryException e1;
    EXPECT_EQ(e1.message(), nullptr);
    EXPECT_EQ(e1.location(), nullptr);

    NoEnoughMemoryException e2("Message");
    EXPECT_NE(e2.message(), nullptr);
    EXPECT_EQ(e2.location(), nullptr);
    EXPECT_EQ(strcmp(e2.message(), "Message"), 0);

    NoEnoughMemoryException e3("File", 10);
    EXPECT_EQ(e3.message(), nullptr);
    EXPECT_NE(e3.location(), nullptr);

    NoEnoughMemoryException e4("Message", "File", 10);
    EXPECT_NE(e4.message(), nullptr);
    EXPECT_NE(e4.location(), nullptr);
    EXPECT_EQ(strcmp(e4.message(), "Message"), 0);
    EXPECT_EQ(strcmp(e4.location(), "File:10"), 0);

    /**
     * 测试拷贝构造函数
     */
    NoEnoughMemoryException e5(e4);
    EXPECT_NE(e4.location(), e5.location());
    EXPECT_NE(e4.message(), e5.message());
    EXPECT_EQ(strcmp(e4.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e4.location(), e5.location()), 0);

    /**
     * 测试赋值操作符
     */
    e1 = e5;
    EXPECT_NE(e1.message(), nullptr);
    EXPECT_NE(e1.location(), nullptr);
    EXPECT_EQ(strcmp(e1.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e1.location(), e5.location()), 0);
}

/**
 * @fn
 * @brief      测试 InvalidParameterException
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testException, InvalidParameterException)
{
    /**
     * 基本使用测试
     */
    try
    {
        THROW_EXCEPTION(InvalidParameterException,"test");
    }
    catch(const InvalidParameterException & e)
    {
        EXPECT_EQ(strcmp(e.message(), "test"), 0);
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }

    /**
     * 测试构造函数
     */
    InvalidParameterException e1;
    EXPECT_EQ(e1.message(), nullptr);
    EXPECT_EQ(e1.location(), nullptr);

    InvalidParameterException e2("Message");
    EXPECT_NE(e2.message(), nullptr);
    EXPECT_EQ(e2.location(), nullptr);
    EXPECT_EQ(strcmp(e2.message(), "Message"), 0);

    InvalidParameterException e3("File", 10);
    EXPECT_EQ(e3.message(), nullptr);
    EXPECT_NE(e3.location(), nullptr);

    InvalidParameterException e4("Message", "File", 10);
    EXPECT_NE(e4.message(), nullptr);
    EXPECT_NE(e4.location(), nullptr);
    EXPECT_EQ(strcmp(e4.message(), "Message"), 0);
    EXPECT_EQ(strcmp(e4.location(), "File:10"), 0);

    /**
     * 测试拷贝构造函数
     */
    InvalidParameterException e5(e4);
    EXPECT_NE(e4.location(), e5.location());
    EXPECT_NE(e4.message(), e5.message());
    EXPECT_EQ(strcmp(e4.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e4.location(), e5.location()), 0);

    /**
     * 测试赋值操作符
     */
    e1 = e5;
    EXPECT_NE(e1.message(), nullptr);
    EXPECT_NE(e1.location(), nullptr);
    EXPECT_EQ(strcmp(e1.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e1.location(), e5.location()), 0);
}

/**
 * @fn
 * @brief      测试 InvalidOperationException
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testException, InvalidOperationException)
{
    /**
     * 基本使用测试
     */
    try
    {
        THROW_EXCEPTION(InvalidOperationException,"test");
    }
    catch(const InvalidOperationException & e)
    {
        EXPECT_EQ(strcmp(e.message(), "test"), 0);
    }
    catch(...)
    {
        ASSERT_TRUE(true);
    }

    /**
     * 测试构造函数
     */
    InvalidOperationException e1;
    EXPECT_EQ(e1.message(), nullptr);
    EXPECT_EQ(e1.location(), nullptr);

    InvalidOperationException e2("Message");
    EXPECT_NE(e2.message(), nullptr);
    EXPECT_EQ(e2.location(), nullptr);
    EXPECT_EQ(strcmp(e2.message(), "Message"), 0);

    InvalidOperationException e3("File", 10);
    EXPECT_EQ(e3.message(), nullptr);
    EXPECT_NE(e3.location(), nullptr);

    InvalidOperationException e4("Message", "File", 10);
    EXPECT_NE(e4.message(), nullptr);
    EXPECT_NE(e4.location(), nullptr);
    EXPECT_EQ(strcmp(e4.message(), "Message"), 0);
    EXPECT_EQ(strcmp(e4.location(), "File:10"), 0);

    /**
     * 测试拷贝构造函数
     */
    InvalidOperationException e5(e4);
    EXPECT_NE(e4.location(), e5.location());
    EXPECT_NE(e4.message(), e5.message());
    EXPECT_EQ(strcmp(e4.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e4.location(), e5.location()), 0);

    /**
     * 测试赋值操作符
     */
    e1 = e5;
    EXPECT_NE(e1.message(), nullptr);
    EXPECT_NE(e1.location(), nullptr);
    EXPECT_EQ(strcmp(e1.message(), e5.message()), 0);
    EXPECT_EQ(strcmp(e1.location(), e5.location()), 0);
}

#endif
