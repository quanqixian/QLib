## 1.目标

​	仿照Qt中QThread的使用方法，使用C++封装linux的的线程api，实现一个使用起来类似的线程类。由于QThread内部机制比较复杂，这里仅仅模仿它的使用方法，不去研究它的实现原理。

## 2.Qt中QThread的基本用法

​	Qt中一个QThread对象管理一个线程。QThread的执行从run()函数的执行开始，当需要实现一个线程类时，**只需要继承QThread类，并重新实现虚函数run**，然后就可以调用QThread的方法完成线程的启动、停止、同步等。

void run()

> 线程体函数，用于定义线程功能（执行流）

void start()

> 启动函数，将线程入口地址设置为run函数

bool QThread::wait(QDeadlineTimer deadline = QDeadlineTimer(QDeadlineTimer::Forever))

> 等待一个线程的结束,线程间同步的操作

## 3.编程实现一个类似QThread的类

- [QThread](../../QLib/QThread.h)

实现要点：

- 静态成员函数

pthread_create函数的参数要求必须传入静态成员函数的指针。类的普通成员函数会隐含一个this参数，因此需要实例才能调用。这里的关键是将实例指针传入静态成员函数，这样就可以不依赖静态成员变量，而是根据不同的实例指针调用对应的成员函数。

- 虚析构函数

一定要将QThread类的析构函数设置为虚函数，避免由于父类指针指向子类引用，在析构时发生内存泄漏问题
