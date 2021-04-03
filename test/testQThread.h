#ifndef _TEST_QTHREAD_H_
#define _TEST_QTHREAD_H_

#include "QThread.h"
#include "gtest/gtest.h"

using namespace QLib;

/**
 * @fn
 * @brief      测试QThread类的基本使用
 * @param[in]
 * @param[out]
 * @retval
 */
TEST(testQThread, basicUse)
{
    class TesetThread : public QThread
    {
        int m_count = 0;
    public:
        int getCount()
        {
            return m_count;
        }
    protected:
        void run()
        {
            while(m_count <100000)
            {
                m_count++;
            }
        }
    };

    TesetThread t;

    t.start();
    t.wait();

    EXPECT_EQ(t.getCount(), 100000);
    EXPECT_EQ(t.isRunning(), false);
}

#endif
