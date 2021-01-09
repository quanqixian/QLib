## 1.文件说明

这个目标存放了QLib中各个类的单元测试。

## 2.编译单元测试

```shell
make
```

## 3.运行单元测试

### 3.1运行所有单元测试

执行命令：

```
make runTest
```

或直接执行可执行程序：

```shell
./test
```

### 3.2运行部分单元测试

使用gtest命令行参数  `--gtest_filter=`,例如只执行`testObject.h`中的单元测试:

```shell
./test  --gtest_filter=testObject*
```

