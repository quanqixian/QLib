#ifndef _TEST_SHAREDPOINTER_H_
#define _TEST_SHAREDPOINTER_H_

#include "SharedPointer.h"
#include "gtest/gtest.h"

using namespace QLib;
using namespace std;

/**
 * @fn
 * @brief      测试SharedPointer生命周期结束时主动释放堆空间
 *             在构造函数中设置全局变量g_num的值为1，在析构函数中设置全局变量的值为2
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSharedPointer, testAutoFree)
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
        SharedPointer<Test> sp1 = new Test();
        EXPECT_EQ(Test::getCount(), 1);
    };

    test();

    EXPECT_EQ(Test::getCount(), 2);
}

/**
 * @fn
 * @brief      测试SharedPointer类->及*
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSharedPointer, testPointerOperator)
{
    struct Student
    {
        int age;
        int id;
    };

    SharedPointer<Student> sp1 = new Student();

    sp1->age = 10;
    (*sp1).id = 1;

    EXPECT_EQ(sp1->id, 1);
    EXPECT_EQ((*sp1).age, 10);
}

/**
 * @fn
 * @brief      测试SharedPointer类拷贝构造
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSharedPointer, testCopyConstructor)
{
    SharedPointer<int> sp1 = new int;
    *sp1 = 2;
    SharedPointer<int> sp2 = sp1;/* 拷贝构造 */
    EXPECT_FALSE(sp1.isNull());
    EXPECT_FALSE(sp2.isNull());

    SharedPointer<int> sp3(sp2);/* 拷贝构造 */

    EXPECT_FALSE(sp2.isNull());
    EXPECT_FALSE(sp3.isNull());

    EXPECT_EQ(*sp2, *sp1);
    EXPECT_EQ(*sp3, *sp1);
}

/**
 * @fn
 * @brief      测试SharedPointer类赋值操作符
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSharedPointer, testAssignmentOperator)
{
    SharedPointer<int> sp1 = new int;
    SharedPointer<int> sp2 = NULL;
    EXPECT_FALSE(sp1.isNull());
    EXPECT_TRUE(sp2.isNull());

    sp2 = sp1;/* 测试赋值操作符 */

    EXPECT_FALSE(sp1.isNull());
    EXPECT_FALSE(sp2.isNull());
}


/**
 * @fn
 * @brief      测试SharedPointer == 和 !=
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testSharedPointer, testEQorNE)
{
    SharedPointer<int> sp1 = new int;
    SharedPointer<int> sp2 = NULL;
    EXPECT_FALSE(sp2 == sp1);

    sp2 = sp1;
    EXPECT_TRUE(sp2 == sp1);

    sp1.clear();
    EXPECT_TRUE(sp2 != sp1);

}
#endif
