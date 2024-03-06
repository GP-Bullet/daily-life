### PCB

```rust
pub struct process_control_block {
    pub state: u64,                    // 进程状态
    pub flags: u64,                    // 进程标志
    pub preempt_count: i32,            // 抢占计数器
    pub cpu_id: u32,                   // 执行该进程的 CPU ID
    pub name: [::core::ffi::c_char; 16usize],    // 进程名称
    pub mm: *mut mm_struct,            // 内存管理结构体指针
    pub thread: *mut thread_struct,    // 线程结构体指针
    pub list: List,                    // 链表节点
    pub addr_limit: u64,               // 进程地址空间大小限制
    pub pid: ::core::ffi::c_long,      // 进程 ID
    pub priority: ::core::ffi::c_long, // 进程优先级
    pub virtual_runtime: i64,          // 进程虚拟运行时间
    pub rt_time_slice: i64,            // 实时进程时间片
    pub fds: *mut ::core::ffi::c_void, // 文件描述符表指针
    pub prev_pcb: *mut process_control_block,  // 上一个 PCB 指针
    pub next_pcb: *mut process_control_block,  // 下一个 PCB 指针
    pub parent_pcb: *mut process_control_block,// 父进程 PCB 指针
    pub exit_code: i32,                // 进程退出码
    pub policy: u32,                   // 进程调度策略
    pub wait_child_proc_exit: wait_queue_node_t,  // 等待子进程退出的等待队列节点
    pub worker_private: *mut ::core::ffi::c_void, // worker 线程私有数据指针
    pub signal: *mut signal_struct,    // 信号处理结构体指针
    pub sighand: *mut sighand_struct,  // 信号处理程序指针
    pub sig_blocked: sigset_t,         // 阻塞信号集合
    pub sig_pending: sigpending,       // 挂起信号集合
    pub migrate_to: u32,               // 要迁移到的 CPU ID
    pub fp_state: *mut ::core::ffi::c_void, // 浮点寄存器状态指针
}
```

## ched/core.rs源码

注：本章仅对core.rs源码做分析，其中不免涉及到cfs.rs和rt.rs的调用，将在之后做更多补充，（包括结构图）。


### **cpu_executing()**

*当前进程PCB中`cpu_id`若与指定`cpu_id`一致，获取当前进程的PCB*

### get_cpu_loads()

*返回给定 `cpu_id` 上等待运行的所有进程数量*

该数量由两部分组成：实时（real-time）调度器上等待的进程数、CFS（Completely Fair Scheduler）调度器上等待的进程数。

*补充*：

这个函数目前还没有考虑到很多因素，比如不同进程对 CPU 的使用权重不同、不同调度器对负载的影响等。所以它只能作为一个粗略的指标来使用，并不能完整地反应当前系统中 CPU 的真实负载情况。

如果要更好地衡量 CPU 的负载大小，可以考虑使用平均系统负载、处理器时间片等指标或其他，比如，在 Linux 操作系统中，负载大小通常是根据最近 1 分钟、5 分钟和 15 分钟内运行队列中的平均进程数来计算的。同时，还需要结合具体的场景和需求，选择合适的负载衡量方法。

### loads_balance()

*负载均衡*

将当前进程进行负载均衡迁移，当前进程设置 PF_NEED_MIGRATE 标记，内核会在适当的时候执行进程迁移操作，migrate_to 到负载最小的 CPU。

### trait **Scheduler**的 __sched()

 - 调用 RT 调度器中的pick_next_task_rt()函数来获取下一个要执行的进程控制块。
   如果存在可以运行的 `p` 进程，就将 `p` 存储在 `next` 变量中，然后将该进程重新放回队列头部，最后通过调用 `rt_scheduler.sched()` 函数进行调度
 - 如果没有可运行的 RT 进程，则说明 CFS 调度器中可能有任务需要执行。这时通过调用 `cfs_scheduler.sched()` 函数来进行调度
 - 最终返回一个可执行的进程控制块

这里也说明RT调度器的优先级高于CFS调度器

### sched_enqueue()

*将进程加入调度队列*

- 除没有设置PROC_RUNNING进程，都需要调度
- 分为CHED_NORMAL （标准模式）和SCHED_FIFO 或 SCHED_RR（实时模式）
- SCHED_NORMAL （标准模式），则将其加入到 CFS 调度器队列中，（如果需要重置运行时间，即需要负载均衡到其他CPU，则调用 `enqueue_reset_vruntime()` 函数进行操作。）
- SCHED_FIFO 或 SCHED_RR（实时模式），则将其加入到 RT 调度器队列中

### **sched_init()**

*初始化进程调度器模块*

包括cfs调度器初始化和rt调度器初始化

- CFS初始化
  CFS_SCHEDULER_PTR是个空指针，则创建一个`SchedulerCFS`的新实例，然后通过`Box::leak()`函数将其转换为裸指针（即将其所有权转`CFD_SCHEDULER_PTR`）
  这个操作很危险，因为裸指针的生命周期并没有明确规定，所以需要注意避免出现内存泄漏或多重释放的问题。
  
  
  
  我试着做如下修改：
  
  ```rust
  pub static mut CFS_SCHEDULER_PTR: Option<Box<SchedulerCFS>> = None;
  
  pub fn sched_cfs_init() {
      unsafe {
          if CFS_SCHEDULER_PTR.is_none() {
              let scheduler = Box::new(SchedulerCFS::new());
              CFS_SCHEDULER_PTR = Some(scheduler);
          } else {
              kBUG!("Try to init CFS Scheduler twice.");
              panic!("Try to init CFS Scheduler twice.");
          }
      }
  }
  ```
  
  可修改为如下代码，修改后的代码将全局变量声明为Option<Box<SchedulerCFS>>类型，并对其进行了封装，避免了使用裸指针的风险，但是在该例中，`RT_SCHEDULER_PTR`的生命周期确实需要与整个程序的运行周期相同，并且在调用`sched_rt_init()`之前没有设置它的值，那么使用裸指针来定义它是合适的。
  
- RT初始化：*初始化一个RT调度器并将其指针存储在全局变量`RT_SCHEDULER_PTR`中*

  

### **sched_update_jiffies**()

*时钟中断触发时，更新进程的时间片*

- SCHED_NORMAL策略：timer_update_jiffies()

  如果剩余可执行时间为 0，则将当前进程设置 `PF_NEED_SCHED` 标记位。

- SCHED_FIFO | SCHED_RR策略：当前进程的实时时间片数减一

### **sys_sched**()

*让系统立即运行调度器的系统调用*

> 注意调度期间关闭中断：
>
> 为了保证调度器在执行期间不会被打断。如果不关闭中断，当其他进程的中断处理程序被调用时，可能会干扰或修改当前进程的上下文信息，影响到调度的正确性和可靠性。
>
> 在进行进程切换时，也需要对各种锁和数据结构进行操作，这些操作如果同时被其他进程的中断处理程序所访问，可能会造成竞争和冲突。

- switch_process():这是实际完成进程切换的核心函数，但是我在找它的实现时，并没有找到它的具体实现，它应该包含汇编的上下文切换

![截图 2023-05-11 00-45-45.png](https://s2.loli.net/2023/05/11/ngbUAcsWZiw8QPO.png)
### **sched_migrate_process()**

*用于将进程等待迁移到另一个 CPU 核心*

### **sched_set_cpu_idle（）**

*将指定 CPU 的空闲进程设置为给定的PCB*
