## 1.文件说明

这个目录存放了单元测试需要使用的第三方库`googletest`源码包及编译脚本。

| 文件                             | 说明     |
| -------------------------------- | -------- |
| googletest-release-1.10.0.tar.gz | 源码包   |
| build.sh                         | 编译脚本 |

源码包来自：https://github.com/google/googletest/

## 2.编译和清理

编译：

```shell
./build.sh  build
```

清理：

```shell
./build.sh  clean
```

## 3.安装路径

编译结果将被放在当前脚本所在目录下的`install`文件夹