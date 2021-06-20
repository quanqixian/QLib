#include "testObject.h"          /* 测试Object类 */
#include "testException.h"       /* 测试Exception类及其子类 */
#include "testSmartPointer.h"    /* 测试SmartPointer类 */
#include "testSharedPointer.h"   /* 测试SharedPointer类 */
#include "testStaticList.h"      /* 测试StaticList类 */
#include "testDynamicList.h"     /* 测试DynamicList类 */
#include "testStaticArray.h"     /* 测试StaticArray类 */
#include "testDynamicArray.h"    /* 测试DynamicArray类 */
#include "testLinkList.h"        /* 测试单链表类 */
#include "testStaticLinkList.h"  /* 测试静态单链表 */
#include "testDualLinkList.h"    /* 测试双向链表类 */
#include "testCircleList.h"      /* 测试循环单链表类 */
#include "testLinuxList.h"       /* 测试Linux内核链表 */
#include "testStaticStack.h"     /* 测试顺序栈 */
#include "testLinkStack.h"       /* 测试链式栈 */
#include "testStaticQueue.h"     /* 测试顺序队列 */
#include "testLinkQueue.h"       /* 测试链式队列 */
#include "testSort.h"            /* 测试排序 */
#include "testMatrixGraph.h"     /* 测试邻接矩阵图 */   
// #include "testListGraph.h"       /* 测试邻接链表图 */
#include "testQThread.h"         /* 测试QThread类 */

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
