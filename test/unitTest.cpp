#include "testObject.h"          /* 测试Object类 */
#include "testException.h"       /* 测试Exception类及其子类 */
#include "testSmartPointer.h"    /* 测试SmartPointer类 */
#include "testSharedPointer.h"   /* 测试SharedPointer类 */
#include "testStaticList.h"      /* 测试StaticList类 */
#include "testDynamicList.h"     /* 测试DynamicList类 */

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
