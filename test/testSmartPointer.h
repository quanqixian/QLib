#ifndef _TEST_SMARTPOINTER_H_
#define _TEST_SMARTPOINTER_H_

#include "SmartPointer.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试SmartPointe生命周期结束时主动释放堆空间
 *             在构造函数中设置count变量的值为1，在析构函数中设置count的值为2
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSmartPointer, testAutoFree)
{
    class Test
    {
    public:
        static int & getCount()
        {
            static int count = 0;
            return count;
        }
    public:
        Test()
        {
            getCount() = 1;
        }
        ~Test()
        {
            getCount() = 2;
        }
    };

    auto test = []()->void {
        SmartPointer<Test> sp1 = new Test();
        EXPECT_EQ(Test::getCount(), 1);
    };

    test();

    EXPECT_EQ(Test::getCount(), 2);
}

/**
 * @fn
 * @brief      测试SmartPointe生命周期结束时主动释放数组空间
 *             在构造函数中设置count变量的值+1，在析构函数中count的值-1
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSmartPointer, testAutoFreeArray)
{
    class Test
    {
    public:
        static int & getCount()
        {
            static int count = 0;
            return count;
        }
    public:
        Test()
        {
            getCount() ++;
        }
        ~Test()
        {
            getCount() --;
        }
    };

    auto test = []()->void {
        SmartPointer<Test, Deleter<Test[]>> sp1 = new Test[5];
        EXPECT_EQ(Test::getCount(), 5);
    };

    test();

    EXPECT_EQ(Test::getCount(), 0);
}
/**
 * @fn
 * @brief      测试SmartPointer类-> * 和get函数
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSmartPointer, testPointerOperator)
{
    struct Student
    {
        int age;
        int id;
    };

    SmartPointer<Student> sp1 = new Student();

    sp1->age = 10;
    (*sp1).id = 1;

    EXPECT_EQ(sp1->id, 1);
    EXPECT_EQ((*sp1).age, 10);

    EXPECT_EQ(sp1.get()->id, 1);
    EXPECT_EQ((*sp1.get()).age, 10);

	/* 测试const成员函数 */
    const  SmartPointer<Student> sp2 = new Student();
    sp2->age = 10;
    (*sp2).id = 1;

    EXPECT_EQ(sp2->id, 1);
    EXPECT_EQ((*sp2).age, 10);
}

/**
 * @fn
 * @brief      测试SmartPointer类拷贝构造
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSmartPointer, testCopyConstructor)
{
    SmartPointer<int> sp1 = new int;
    SmartPointer<int> sp2 = sp1;/* 拷贝构造 */
    EXPECT_TRUE(sp1.isNull());
    EXPECT_FALSE(sp2.isNull());

    SmartPointer<int> sp3(sp2);/* 拷贝构造 */

    EXPECT_TRUE(sp2.isNull());
    EXPECT_FALSE(sp3.isNull());
}

/**
 * @fn
 * @brief      测试SmartPointer类赋值操作符
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSmartPointer, testAssignmentOperator)
{
    SmartPointer<int> sp1 = new int;
    SmartPointer<int> sp2;
    EXPECT_FALSE(sp1.isNull());
    EXPECT_TRUE(sp2.isNull());

    sp2 = sp1;/* 测试赋值操作符 */

    EXPECT_TRUE(sp1.isNull());
    EXPECT_FALSE(sp2.isNull());
}

#endif
