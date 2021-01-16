![QWorkShop](./docs/00_README/pic/QWorkShop.png)

## 1.QLib库内容介绍

QLib是使用c++模板技术实现的一个轻量级的类"STL"库，实现了链表、栈、队列、树、图等数据结构。

## 2.QLib库包含的内容

- 创建顶层父类Object，保证单一继承树和规范动态内存申请行为
- 创建异常类族，使用异常处理机制分离正常逻辑和异常逻辑
- 创建智能指针类可以有效规避多重释放和内存泄漏的Bug
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

## 3.详细的说明文档

QLib中各个类的继承关系如下图：



在[docs](./docs)目录下存放了每个类的设计说明文档：

- [01.顶层父类Object的创建](./docs/01_顶层父类Object/01.顶层父类Object的创建.md)
- 02.[异常类的设计与实现](./docs/02_异常类的设计与实现/02.异常类的设计与实现.md)

## 4.单元测试

QLib使用第三方库googletest进行了各个类的单元测试：

- [顶层父类Object单元测试](./test/testObject.h)
- [异常类族单元测试](./test/testException.h)

## 5.编译

### 5.1编译所有

在QLib目录下执执行下面的编译命令，将编译第三方库和所有单元测试

```makefile
make
```

### 5.2执行单元测试

```makefile
make runTest
```

