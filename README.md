# MySTL
>作者：超炫风景
>
>更新时间：2017.4.2
>
>软件版本 V1.3

### 项目介绍

MySTL基于STL 的 SGI版本，参考侯捷老师的《STL源码剖析》以及《C++primer 5th》以及一些github开源代码，忽略掉一些针对操作系统和多线程优化的代码，旨在重现STL的基本框架和算法。同时将自己在编写过程中的感悟和理解记录下来形成文档。以加深对C++和算法的理解。

### 实现进度

##### 已实现的功能模块

1.Simple_allocator：简单实例空间分配器

2.Allocator: 次级空间分配器，包括一级和二级空间分配器

3.Construct：stl标准构造和析构函数

4.Type_traits: POD与no POD 类型萃取器

5.iterator：最简单的一个迭代器版本

6.Uninitialized：内存初始化工具

7.Vector:  Vector容器80%

##### 已实现的测试模块

1.test_Allocator: 空间分配器测试代码

2.test_simple_allocator:  简单空间分配器测试代码

3.test_vector:  vector容器测试代码(40%)

##### 待开发的模块

1.高级iterator

2.vector反向迭代器

### 文档进度

1.空间分配器开发文档（基本完成）



