# 进程、线程相关编程实验

## 实验目的

本实验通过多个编程任务帮助学生深入了解 Linux 操作系统中的进程、线程及自旋锁的工作原理，并通过实验验证不同编程技巧与同步机制的效果。实验内容涵盖了进程的创建与管理、多线程编程及自旋锁的实现与应用等内容。

### 1.1 进程相关编程实验

#### 1.1.1 实验目的

- 熟悉 Linux 操作系统的基本环境和操作方法，了解进程调度和进程间变量管理机制。
- 通过编写进程调度相关程序，体会父子进程之间的关系和操作。

#### 1.1.2 实验内容

- 运行简单的进程调度程序，观察进程的 PID 和子进程的创建。
- 扩展实验：
  1. 在父子进程中增加全局变量操作。
  2. 修改程序，体会在子进程中调用 `system()` 和 `exec()` 系列函数。

#### 1.1.3 实验原理

- 进程、PID、`fork()` 函数的基本原理。
- 进程间同步和调度机制。

#### 1.1.4 实验步骤

1. 编写并多次运行进程调度实验程序。
```bash
[root@oslab lab1.1]# ./1.1
parent:pid = 24940
parent:pid1 = 24939
child:pid = 0
child:pid1 = 24940
```
2. 删除 `wait()` 函数并观察进程执行顺序的变化。
```bash
[root@oslab lab1.1]# ./1.2
parent:pid = 24942
child:pid = 0
parent:pid1 = 24941
child:pid1 = 24942
```
3. 修改程序，实现全局变量操作并分析结果。
```bash
[root@oslab lab1.1]# ./1.3
parent:pid = 24946
parent:pid1 = 24945
parent:num = -1,parent:*num = 0x42005c
child:pid = 0
child:pid1 = 24946
child:num = 1,child:*num = 0x42005c


```
4. 调用 `system()` 和 `exec()` 系列函数，观察其行为。

```bash
//system：
parent:pid = 24961
child:pid = 0
parent:pid1 = 24960
child:pid1 = 24961
child:calling system()
system_call: PID = 24962

//exec：
parent:pid = 24964
child:pid = 0
parent:pid1 = 24963
child:pid1 = 24964
child: calling exec()
system_call: PID = 24964
```


### 1.2 线程相关编程实验

#### 1.2.1 实验目的

- 了解线程共享进程信息及其可能导致的竞态条件。
- 学习如何使用互斥和同步机制来解决多线程编程中的问题。

#### 1.2.2 实验内容

1. 创建两个线程并操作共享变量，观察并分析结果。
2. 使用互斥锁或信号量来解决线程间同步问题。
3. 在线程中实现调用 `system()` 和 `exec()` 系列函数，并比较进程 PID 与线程 TID 的差异。

#### 1.2.3 实验原理

- 线程创建、共享变量操作、竞态条件及互斥机制。
- 通过信号量和 PV 操作实现线程同步。

#### 1.2.4 实验步骤

1. 设计并实现线程操作共享变量。
```bash
[root@oslab lab1.2]# ./2.1
Final value of shared_var: -28600

[root@oslab lab1.2]# ./2.1
Final value of shared_var: -19900
```
2. 修改程序，使用信号量进行同步，分析结果。
```bash
[root@oslab lab1.2]# ./2.2
thread1 is created successfully
thread2 is created successfully
Final value of shared_var: 0
```
3. 在线程中实现 `system()` 和 `exec()` 调用，分析输出。
```bash
//sys:
[root@oslab lab1.2]# ./2.3.1
thread1 is created successfully
thread1:Before system() call in thread_system: PID = 25042, TID = 25043
thread2 is created successfully
thread2:Before system() call in thread_system: PID = 25042, TID = 25044
In system_call program: PID = 25045
In system_call program: PID = 25046
Final value of shared_var: 0

//exec:
thread1 is created successfully
Before exec() call in thread_exec: PID = 25047, TID = 25048
In system_call program: PID = 25047
```
### 1.3 自旋锁实验

#### 1.3.1 实验目的

- 理解自旋锁的基本概念及其工作原理。
- 在多线程环境中使用自旋锁同步线程操作，提高程序性能。

#### 1.3.2 实验内容

1. 创建两个线程并使用自旋锁保护共享变量，避免竞态条件。
2. 在多个线程间同步访问资源，确保数据一致性。

#### 1.3.3 实验原理

- 自旋锁的工作原理和应用，如何通过忙等待机制实现线程同步。

#### 1.3.4 实验步骤

1. 实现自旋锁保护共享资源的访问。
2. 编写代码并进行多次测试，验证自旋锁的同步效果。
```bash
[root@oslab lab1.3]# ./spinlock
Shared value: 10000
```
## 编译与运行

### 编译程序

在 Linux 系统上使用 `gcc` 编译以下程序：

```bash
    ./run_1.1.sh
    ./run_1.2.sh
    ./run_1.3.sh
    ./run_1.4.sh
    gcc -o 1.5 1.5.c
    gcc -o 1.6 1.6.c
    ...
    make
```

## 文件目录

├── lab1.1
│   ├── 1.1  步骤一：编写并多次运行图 1-1 中代码
│   ├── 1.1.c    
│   ├── 1.1.log
│   ├── 1.1.txt
│   ├── 1.2    步骤二：删去 1-1 代码中的 wait()函数
│   ├── 1.2.c
│   ├── 1.2.txt
│   ├── 1.3    步骤三：修改 1-1 中代码，增加一个全局变量并在父子进程中对其进行不同的操作
│   ├── 1.3.c
│   ├── 1.3.txt
│   ├── 1.4    步骤四：在步骤三基础上，在 return 前增加对全局变量的操作
│   ├── 1.4.c
│   ├── 1.4.txt
│   ├── 1.5    步骤五：修改 1-1 程序，在子进程中调用 system()与 exec 族函数。
│   ├── 1.5.c
│   ├── 1.6
│   ├── 1.6.c
│   ├── run_1.1.sh
│   ├── run_1.2.sh
│   ├── run_1.3.sh
│   ├── run_1.4.sh
│   ├── system_call
│   └── system_call.c
├── lab1.2
│   ├── 2.1    步骤一：设计程序，创建两个子线程，两线程分别对同一个共享变量多次操
作
│   ├── 2.1.c
│   ├── 2.2    步骤二：修改程序，定义信号量 signal，使用 PV 操作实现共享变量的访问
与互斥。
│   ├── 2.2.c
│   ├── 2.3    步骤三：在第一部分实验了解了 system()与 exec 族函数的基础上，将这两
个函数的调用改为在线程中实现
│   ├── 2.3.1
│   ├── 2.3.1.c
│   ├── 2.3.2
│   ├── 2.3.2.c
│   ├── 2.3.c
│   ├── Makefile
│   ├── system_call
│   ├── system_call.c
│   └── test.c
├── lab1.3
│   ├── Makefile
│   ├── spinlock    根据实验内容要求，编写模拟自旋锁程序代码 spinlock.c
│   └── spinlock.c
└── README.md

