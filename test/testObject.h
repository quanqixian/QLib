#ifndef _TEST_OBJECT_H_
#define _TEST_OBJECT_H_

#include "Object.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试Object类用于统一动态内存申请
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testObject, new_del)
{
    class Parent : public Object
    {
    public:
            int i;
            int j;
    };
    class Child : public Parent
    {
    public:
            int k;
    };

    Object *obj1 = new Parent();
    Object *obj2 = new Child();

    EXPECT_NE(obj1, nullptr);
    EXPECT_NE(obj2, nullptr);

    delete obj1;
    delete obj2;
#if 0
    /* 参考More Effective C++(条款三：绝对不要以多态方式处理数组) */
    Object *obj1Array = new Parent[10];
    Object *obj2Array = new Child[10];

    delete [] obj1Array;
    delete [] obj2Array;
#endif
    Parent *obj1Array = new Parent[10];
    Child *obj2Array = new Child[10];

    EXPECT_NE(obj1Array, nullptr);
    EXPECT_NE(obj2Array, nullptr);

    delete [] obj1Array;
    delete [] obj2Array;
}

#endif
