## 1.目标及原理

**目标**

​	仿照Qt5.7中的`QMutex`和`QMutexLocker`，使用c++类封装linux平台下的互斥量api，实现类似类似QMutex和QMutexLocker的类。

**什么是RAII？**

​	RAII是**Resource Acquisition Is Initialization**（ “资源获取就是初始化”）的简称，是C++语言的一种管理资源、避免泄漏的惯用法。利用的就是C++构造的对象最终会被销毁的原则。RAII的做法是使用一个对象，在其**构造时获取对应的资源**，在对象生命期内控制对资源的访问，使之始终保持有效，最后**在对象析构的时候，释放构造时获取的资源**。

**递归锁和非递归锁**

- **递归锁**：同一个线程在不解锁的情况下，可以多次获取锁定同一个递归锁，而且不会产生死锁。
- **非递归锁**：在不解锁的情况下，当同一个线程多次获取同一个递归锁时，会产生死锁。
- 通常，递归锁是在非递归互斥锁加引用计数器来实现的。简单的说，在加锁前，先判断上一个加锁的线程和当前加锁的线程是否为同一个。如果是同一个线程，则仅仅引用计数器加1。如果不是的话，则引用计数器设为1，记录当前线程号，并加锁。
- linux下的互斥量pthread_mutex_t是非递归锁，但是可以通过在创建互斥量时设置**PTHREAD_MUTEX_RECURSIVE**属性，将pthread_mutex_t设置为递归锁。

## 2.Qt中的QMutex和QMutexLocker代码分析

**Qt5.7中QMutex类的原代码文件**

[**qmutex.h**](./code/qmutex.h)

### 2.1 禁用拷贝构造函数和赋值操作符

​	禁用拷贝构造函数和赋值操作，可以防止互斥锁被错误的加锁或释放多次。`QMutex`和`QMutexLocker`中使用`Q_DISABLE_COPY`宏来生成拷贝构造函数和赋值操作符，并将它们声明为private。

```c++
/*
   Some classes do not permit copies to be made of an object. These
   classes contains a private copy constructor and assignment
   operator to disable copying (the compiler gives an error message).
*/
#define Q_DISABLE_COPY(Class) \
    Class(const Class &) Q_DECL_EQ_DELETE;\
    Class &operator=(const Class &) Q_DECL_EQ_DELETE;
```

```c++
class Q_CORE_EXPORT QMutex : public QBasicMutex
{
	//...
private:
    Q_DISABLE_COPY(QMutex)
    friend class QMutexLocker;
};

class Q_CORE_EXPORT QMutexLocker
{
	//...
private:
    Q_DISABLE_COPY(QMutexLocker)
    quintptr val;
};
```

### 2.2 递归锁和非递归锁

QMutex中定义了递归和非递归两种模式，并且默认为非递归。

```c++
class Q_CORE_EXPORT QMutex
{
public:
    enum RecursionMode { NonRecursive, Recursive };

    inline explicit QMutex(RecursionMode mode = NonRecursive) Q_DECL_NOTHROW { Q_UNUSED(mode); }
    //...
}
```

### 2.3 QMutex中互斥锁的基本操作

QMutex中声明了互斥锁的基本操作：lock、unlock、trylock等，这些功能由QMutex的父类QBasicMutex实现。

```c++
    void lock() QT_MUTEX_LOCK_NOEXCEPT;
    bool tryLock(int timeout = 0) QT_MUTEX_LOCK_NOEXCEPT;
    void unlock() Q_DECL_NOTHROW;
```

### 2.4 QMutexLocker的实现

​	QMutexLocker的主要功能是用于自动释放互斥锁。在构造函数将传入互斥锁指针QBasicMutex *m赋值给成员变量val，并执行上锁操作，析构函数中执行解锁。

```c++
    inline explicit QMutexLocker(QBasicMutex *m) QT_MUTEX_LOCK_NOEXCEPT
    {
        Q_ASSERT_X((reinterpret_cast<quintptr>(m) & quintptr(1u)) == quintptr(0),
                   "QMutexLocker", "QMutex pointer is misaligned");
        val = quintptr(m);
        if (Q_LIKELY(m)) {
            // call QMutex::lock() instead of QBasicMutex::lock()
            static_cast<QMutex *>(m)->lock();
            val |= 1;
        }
    }
    inline ~QMutexLocker() { unlock(); }
```

## 3.编程实现

只需要根据上面分析的实现要点，仿照实现类似的功能。

[**QMutex**]()

