#include "testObject.h"          /* 测试Object类 */
#include "testException.h"       /* 测试Exception类及其子类 */

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}