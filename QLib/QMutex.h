#ifndef _QMUTEX_H_
#define _QMUTEX_H_

#include "Object.h"
#include <pthread.h>

namespace QLib
{

class QMutex : public Object
{
public:
    enum RecursionMode {NonRecursive, Recursive};
public:
    explicit QMutex(RecursionMode mode = NonRecursive);
    ~QMutex();
    void lock();
    void unlock();
    bool tryLock();
    bool isRecursive() const;
private:
    QMutex(QMutex &);
    QMutex& operator = (const QMutex &);
    friend class QMutexLocker;
private:
    pthread_mutex_t m_mutex;
    RecursionMode m_recursionMode;
};

QMutex::QMutex(RecursionMode mode) : m_recursionMode(mode)
{
    if(m_recursionMode == Recursive)
    {
        pthread_mutexattr_t mutexattr;
        pthread_mutexattr_init(&mutexattr);
        pthread_mutexattr_settype(&mutexattr, PTHREAD_MUTEX_RECURSIVE);
        pthread_mutex_init(&m_mutex, &mutexattr);
        pthread_mutexattr_destroy(&mutexattr);
    }
    else
    {
        pthread_mutex_init(&m_mutex, NULL);
    }
}

QMutex::~QMutex()
{
    pthread_mutex_destroy(&m_mutex);
}

void QMutex::lock()
{
    pthread_mutex_lock(&m_mutex);
}

void QMutex::unlock()
{
    pthread_mutex_unlock(&m_mutex);
}

bool QMutex::tryLock()
{
    return (0 == pthread_mutex_trylock(&m_mutex));
}

bool QMutex::isRecursive() const
{
    return (m_recursionMode == Recursive);
}

class QMutexLocker : public Object
{
public:
    inline explicit QMutexLocker(QMutex * m);
    inline ~QMutexLocker();
    inline void unlock();
    inline void relock();
    inline QMutex * mutex() const;
private:
    QMutexLocker(const QMutexLocker &);
    QMutexLocker & operator = (const QMutexLocker &);
    QMutex* val;
};

inline QMutexLocker::QMutexLocker(QMutex * m) : val(nullptr)
{
    if(m)
    {
        val = m;
        val->lock();
    }
}

inline QMutexLocker::~QMutexLocker()
{
    if(val)
    {
        val->unlock();
    }
}

inline void QMutexLocker::unlock()
{
    if(val)
    {
        val->unlock();
    }
}

inline void QMutexLocker::relock()
{
    if(val)
    {
        val->lock();
    }
}

inline QMutex * QMutexLocker::mutex() const
{
    return val;
}

}
#endif
