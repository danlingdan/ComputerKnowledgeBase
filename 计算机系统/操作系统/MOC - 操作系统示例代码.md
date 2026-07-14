---
domain: 计算机系统
type: MOC
node_size: 65
status: 已完成
course: 操作系统
aliases:
  - Operating System Code Examples
  - 操作系统代码索引
tags:
  - 操作系统
  - 示例代码
source:
  - Silberschatz, Operating System Concepts (10th Edition)
  - D:\Learn\Operation System\Code
version: 教学修正版，核实于 2026-07-14
created: 2026-07-14
updated: 2026-07-14
---

# MOC - 操作系统示例代码

本索引把教材配套示例代码连接到相应知识点。源码独立保存在“示例代码”目录，章节正文只说明机制、运行顺序和关键陷阱，从而避免同一份代码被重复复制。

> [!warning] 使用边界
> 这些程序用于观察系统调用和线程 API，不是生产级实现。POSIX 示例应在 Linux、WSL 或其他 POSIX 环境编译；Windows 示例需要 Windows SDK 与 MSVC；实时调度策略可能需要额外权限。

## 第三章：进程与进程间通信

| 知识点 | 示例 | 关键观察 |
| --- | --- | --- |
| [[第三章 进程#3.3.1 进程创建|进程创建]] | [fork-exec.c](示例代码/03-进程/3.3.1/fork-exec.c)、[create-process.c](示例代码/03-进程/3.3.1/create-process.c) | POSIX 的 fork—exec 两阶段模型与 Windows 单次创建模型 |
| [[第三章 进程#3.5.1 例子：POSIX共享内存|POSIX 共享内存]] | [posix-shm-producer.c](示例代码/03-进程/3.5.1/posix-shm-producer.c)、[posix-shm-consumer.c](示例代码/03-进程/3.5.1/posix-shm-consumer.c) | 创建、定长、映射、解除映射和删除对象 |
| [[第三章 进程#3.6.1 套接字|套接字]] | [DateServer.java](示例代码/03-进程/3.6.1/DateServer.java)、[DateClient.java](示例代码/03-进程/3.6.1/DateClient.java) | TCP 服务器的 bind/listen/accept 与客户端 connect/read |
| [[第三章 进程#3.6.3.1 普通管道|普通管道]] | [posix-pipe.c](示例代码/03-进程/3.6.3.1/posix-pipe.c) | 关闭未使用端点与 EOF |
| [[第三章 进程#3.6.3.1 普通管道|Windows 匿名管道]] | [windows-anonymous-pipe-parent.c](示例代码/03-进程/3.6.3.1/windows-anonymous-pipe-parent.c)、[windows-anonymous-pipe-child.c](示例代码/03-进程/3.6.3.1/windows-anonymous-pipe-child.c) | 句柄继承和标准输入重定向 |

> [!note] 原始材料分类修正
> 原目录 `3.6.3.2` 中的 Windows 程序调用的是 `CreatePipe()`，实际创建的是匿名管道，并非 `CreateNamedPipe()` 命名管道，因此修正版归入 3.6.3.1。

## 第四章：线程库

| 平台 | 示例 |
| --- | --- |
| POSIX Pthreads | [pthread-sum.c](示例代码/04-线程/4.4/pthread-sum.c) |
| Windows 线程 API | [windows-thread-sum.c](示例代码/04-线程/4.4/windows-thread-sum.c) |
| Java 线程 API | [Driver.java](示例代码/04-线程/4.4/Driver.java) |

三份程序都由工作线程计算 $1+2+\cdots+n$，主线程等待结果，适合比较线程创建、参数传递与 join/wait 的 API 差异。

## 第五章：线程与实时调度

- [[第五章 进程调度#5.4.2 Pthread调度|Pthread 竞争范围]]：[pthread-scope.c](示例代码/05-调度/5.4.2/pthread-scope.c)。
- [[第五章 进程调度#5.6.6 POSIX实时调度|POSIX 实时调度]]：[posix-realtime-scheduling.c](示例代码/05-调度/5.6.6/posix-realtime-scheduling.c)。

> [!warning] 权限与实现差异
> `PTHREAD_SCOPE_PROCESS` 在一些实现中不受支持；`SCHED_FIFO` 通常要求实时调度权限。示例会检查并报告错误，不应把请求成功当作跨平台保证。

## 第九章：Windows 共享内存

- [[第九章 虚拟内存管理#9.7.2 共享内存 Windows API|文件映射对象]]：[windows-shared-memory-producer.c](示例代码/09-虚拟内存/9.7.2/windows-shared-memory-producer.c)、[windows-shared-memory-consumer.c](示例代码/09-虚拟内存/9.7.2/windows-shared-memory-consumer.c)。
- 先启动生产者并保持窗口，再启动消费者；生产者退出后，若没有其他进程持有句柄，基于分页文件的命名映射对象会消失。

## 原始材料修正记录

- 将文件名中的 “Pthreand” 统一为 “Pthread”，并补齐线程入口声明、返回值检查和属性销毁。
- 修复 Java 客户端读取后输出空行的问题，并把 `DataServer/DataClient` 更名为与内容一致的 `DateServer/DateClient`。
- 修复 POSIX 共享内存对象名称、消费者打开权限、映射权限、指针运算和资源释放。
- 将原“Windows 命名管道”代码按实际 API 归类为匿名管道，并修复句柄继承与可变宽字符命令行。
- Windows 共享内存改用有明确大小的分页文件映射，并让生产者保持对象存活直至消费者完成读取。
- 实时调度示例显式设置 `PTHREAD_EXPLICIT_SCHED`、策略与合法优先级，并报告权限不足，而不是静默退回普通策略。

## 验证状态

- POSIX C：已在 WSL/Linux 下使用 `cc -std=c11 -Wall -Wextra -Werror` 编译；进程、共享内存、管道、线程求和和竞争范围示例均已实际运行。
- Java：已使用 `javac 21.0.11` 编译，线程求和及日期客户机—服务器已实际运行。
- Windows C：已完成 API、类型和资源生命周期静态检查；当前机器未安装 MSVC/Windows SDK 编译环境，因此保留为平台待编译项。

## 编译与运行

### Linux / WSL（Bash）

```bash
cc -std=c11 -Wall -Wextra fork-exec.c -o fork-exec
cc -std=c11 -Wall -Wextra posix-shm-producer.c -o producer -lrt
cc -std=c11 -Wall -Wextra posix-shm-consumer.c -o consumer -lrt
cc -std=c11 -Wall -Wextra posix-pipe.c -o posix-pipe
cc -std=c11 -Wall -Wextra -pthread pthread-sum.c -o pthread-sum
cc -std=c11 -Wall -Wextra -pthread pthread-scope.c -o pthread-scope
cc -std=c11 -Wall -Wextra -pthread posix-realtime-scheduling.c -o posix-rt
```

共享内存示例先运行 `./producer`，再运行 `./consumer`。现代 glibc 可能不再需要 `-lrt`。

### Java 21+（PowerShell 或 Bash）

```powershell
javac DateServer.java DateClient.java
java DateServer
# 在另一个终端运行：
java DateClient

javac Driver.java
java Driver 10
```

### Windows SDK / MSVC（Developer PowerShell）

```powershell
cl /W4 /utf-8 create-process.c
cl /W4 /utf-8 windows-thread-sum.c
cl /W4 /utf-8 windows-anonymous-pipe-child.c
cl /W4 /utf-8 windows-anonymous-pipe-parent.c
cl /W4 /utf-8 windows-shared-memory-producer.c
cl /W4 /utf-8 windows-shared-memory-consumer.c
```

> [!tip] 推荐观察方式
> 先预测输出与阻塞点，再运行程序；随后故意注释掉一次 `close()`、`CloseHandle()`、`join()` 或等待操作，观察资源生命周期和同步语义如何变化。
