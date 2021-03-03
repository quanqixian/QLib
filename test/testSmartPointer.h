#ifndef _TEST_SMARTPOINTER_H_
#define _TEST_SMARTPOINTER_H_

#include "SmartPointer.h"
#include <iostream>
#include "gtest/gtest.h"

using namespace QLib;
using namespace std;

static int g_num = 0;

/**
 * @fn
 * @brief      测试SmartPointe生命周期结束时主动释放堆空间
 *             在构造函数中设置全局变量g_num的值为1，在析构函数中设置全局变量的值为2
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSmartPointer, testAutoFree)
{
    class Test
    {
    public:
        Test()
        {
            g_num = 1;
        }
        ~Test()
        {
            g_num = 2;
        }
    };

    auto test = []()->void {
        SmartPointer<Test> sp1 = new Test();
         EXPECT_EQ(g_num, 1);
    };

    test();

    EXPECT_EQ(g_num, 2);
}

/**
 * @fn
 * @brief      测试SmartPointer类->及*
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
