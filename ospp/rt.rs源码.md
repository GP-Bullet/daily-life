### sched/rt.rs源码

#### RTQueue

```rust
struct RTQueue {
    /// 队列的锁
    lock: RawSpinlock,
    /// 存储进程的双向队列
    queue: LinkedList<&'static mut process_control_block>,
}
```

`RTQueue` 结构体包含以下函数：

1. `new()` 函数用于创建一个新的 `RTQueue` 实例，并初始化其中的成员变量。
2. `enqueue()` 函数将一个PCB加入到队列的末尾。如果队列为空或者进程是IDLE进程，则什么都不做。
3. `dequeue()` 函数从队列头部取出下一个要执行的PCB如果队列不为空），否则返回 `None` 。
4. `enqueue_front()` 函数将一个PCB加入到队列的头部。
5. `get_rt_queue_size()` 函数返回当前队列中进程的数量。

#### SchedulerRT

- `new()`：*创建实时进程队列和负载统计队列，为每个 CPU 核心创建 MAX_RT_PRIO 个优先级队列*。

  `result.cpu_queue` 看作一个二维数组，其中有 `MAX_CPU_NUM` 行和 `MAX_RT_PRIO` 列（代表优先级）。每个 `(i, j)` 元素对应着第 `i` 个 CPU 核心的第 `j` 个优先级队列。

- `pick_next_task_rt()`：*按优先级挑选下一个可执行的实时进程。*

- `rt_queue_len()`：*获取指定 CPU 上的所有实时进程队列中的进程总数。*

- `load_list_len()`：*获取负载统计队列长度。*

- `enqueue_front()`：*将PCB插入CPU优先级队列头部。*

- `enqueue`:*将PCB加入到对应CPU的队列中*

##### sched()

- 取出当前进程的 PCB，将其 PF_NEED_SCHED 标记置为 0；

- 调用 `pick_next_task_rt` 函数挑选下一个进程，如果没有可运行的实时进程，则抛出错误；

- SCHED_FIFO 策略，判断被挑选的进程是否比当前进程优先级高

  如果不是，则将被挑选的进程重新加入到就绪队列中等待下次执行，

  如果是，则将当前进程重新加入到就绪队列中，并返回被挑选的进程的 PCB；

- SCHED_FIFO 策略，判断被挑选的进程与当前进程的优先级

  如果被挑选进程的优先级比当前进程高或者相等，则判断其时间片是否已耗尽，如果时间片未耗尽，则将当前进程重新加入到就绪队列中，并返回被挑选的进程的 PCB；否则将被挑选进程重新加入到就绪队列中等待下次执行，

  如果被挑选进程的优先级比当前进程低，则将被挑选进程重新加入到就绪队列的队首等待下次执行。

- 如果没有可执行的进程，则返回 None。

疑问：

1.哪里是共享资源要加锁？

2.如何保证优先级队列的顺序？

3.优先级高低，以及SCHED_NORMAL/SCHED_FIFO/SCHED_FIFO/的定义位置

4.实时进程时间片默认100,普通进程默认10,是否合理？

5.官方文挡提到的饥饿问题我没有发现是否已解决，文档是否待更新