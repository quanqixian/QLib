#ifndef _QTHREAD_H_
#define _QTHREAD_H_

#include <pthread.h>

namespace QLib
{

class QThread
{
private:
    volatile bool m_isRunning = false;   /* 线程运行标志 */
    pthread_t m_threadID = 0;            /* 线程ID */
    static void * threadProcess(void * arg);
protected:
    virtual void run(void) = 0;          /* 由子类重写run函数 */
public:
    QThread();
    virtual ~QThread();
    bool start(void);
    bool wait();
    bool isRunning() const;
};

QThread::QThread()
{
}

bool QThread::start(void)
{
    if(m_isRunning == false)
    {
        /* 修改运行标志要在创建线程之前 */
        m_isRunning = true;

        /* 传入了this指针 */
        if(0 != pthread_create(&m_threadID, nullptr, threadProcess, this))
        {
            m_isRunning = false;
        }
    }

    return m_isRunning;
}

bool QThread::wait()
{
    void * thrdRet = nullptr;

    if(m_isRunning)
    {
        m_isRunning = false;
        pthread_join(m_threadID, &thrdRet);
    }

    return !m_isRunning;
}

bool QThread::isRunning() const
{
    return m_isRunning;
}

QThread::~QThread()
{
    wait();
}

void * QThread::threadProcess(void * arg)
{
    /* 根据不同的实例指针调用对应的成员函数 */
    QThread * pthis = static_cast<QThread*>(arg);
    pthis->run();
}

}

#endif
