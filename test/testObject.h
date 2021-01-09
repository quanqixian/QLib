#ifndef _TEST_OBJECT_H_
#define _TEST_OBJECT_H_

#include "Object.h"
#include <iostream>
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
    class Parent:public Object
    {
    public:
            int i;
            int j;
    };
    class Child:public Parent
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
}

#endif
