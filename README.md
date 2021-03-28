![QWorkShop](./docs/00_README/pic/QWorkShop.png)

## 1.QLib库概述

使用c++模板技术实现的一个“数据结构”库，实现了链表、栈、队列、树、图等。

## 2.QLib库包含的内容

- 顶层父类-保证单一继承树和规范动态内存申请行为
- 异常类族-使用异常处理机制分离正常逻辑和异常逻辑
- 智能指针类-用于规避多重释放和内存泄漏的Bug
- 线性表的静态/动态顺序存储结构类、线性表的单/双向/循环链式存储结构类
- 数组类和线性表类的插入、删除、查找、获取、设置、遍历、反转、长度、清空等操作的实现
- 创建栈类族，包含顺序栈和链式栈存储结构类，有栈创建、销毁、清空、进栈、出栈、栈顶元素获取、栈大小
- 创建队列类族，包含顺序队列和链式队列存储结构类，有队列创建,销毁、清空、进队、出队、获取队头、队列长度、判断队列是否为空，以及栈与队列的相互转换
- 创建字符串类族、重载实现其比较、加法、赋值、插入、判断、去空等操作
- KMP算法、递归思想的应用实现链表反转、排序合并、八皇后问题
- 排序类的实现，选择排序、插入排序、冒泡排序，希尔排序归并排序、快速排序等排序算法的实现
- 通用树类的实现，实现了树的查找、插入、清除、删除、结点数/高度/度的获取、树的层次遍历等操作
- 二叉树类的实现，实现了树的查找.插入.清除、删除、结点数/高度/度的获取、树的层次遍历和典型遍历、克隆、比较、相加、线索化等操作
- 图类的实现，其中有图的遍历、最小生成树、最短路径算法的实现
- 基于RAII机制的QMutex和QMutexLocker、仿Qt的线程类QThread

## 3.详细的说明文档

QLib中各个类的继承关系如下图：



在[docs](./docs)目录下存放了每个类的设计说明文档：

- [01.顶层父类Object的创建](./docs/01_顶层父类Object/01.顶层父类Object的创建.md)
- [02.异常类的设计与实现](./docs/02_异常类的设计与实现/02.异常类的设计与实现.md)
- [03-1.智能指针的设计与实现1-SmartPointer](./docs/03_智能指针的设计与实现/03.智能指针的设计与实现1-SmartPointer.md)
- [03-2.智能指针的设计与实现2-SharedPointer](./docs/03_智能指针的设计与实现/03.智能指针的设计与实现2-SharedPointer.md)
- [04-1.线性表的抽象实现](./docs/04_顺序表/04-1.线性表的抽象实现.md)
- [04-2.顺序表的抽象实现](./docs/04_顺序表/04_2顺序表的抽象实现/04-2.顺序表的抽象实现.md)
- [04-3.静态顺序表和动态顺序表的实现](./docs/04_顺序表/04_3静态顺序表和动态顺序表/04-3.静态顺序表和动态顺序表.md)
- [05.数组类的设计与实现](./docs/05_数组类的设计与实现/05.数组类的设计与实现.md)
- [基于RAII机制的QMutex和QMutexLocker设计与实现](./docs/QMutex和QMutexLocker设计与实现/基于RAII机制的QMutex和QMutexLocker设计与实现.md)
- [仿Qt的线程类QThread设计与实现](./docs/QThread线程类的设计与实现/QThread线程类的设计与实现.md)

## 4.单元测试

QLib使用第三方库googletest进行了各个类的单元测试：

- [顶层父类Object单元测试](./test/testObject.h)
- [异常类族单元测试](./test/testException.h)
- [智能指针-SmartPointer单元测试](./test/testSmartPointer.h)
- [智能指针-SharedPointer单元测试](./test/testSharedPointer.h)
- [顺序表-StaticList单元测试](./test/testStaticList.h)
- [顺序表-DynamicList单元测试](./test/testDynamicList.h)
- [数组类-StaticArray单元测试](./test/testStaticArray.h)
- [数组类-DynamicArray单元测试](./test/testDynamicArray.h)
- [线程类QThread单元测试](./test/testQThread.h)

## 5.编译

### 5.1编译所有

在QLib目录下执执行下面的编译命令，将编译第三方库和所有单元测试

```shell
make
```

### 5.2执行单元测试

```shell
make runTest
```

