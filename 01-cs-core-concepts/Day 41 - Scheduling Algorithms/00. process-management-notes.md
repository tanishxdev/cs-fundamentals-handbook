# Process Management

### 1. Medium-Term Scheduler (MTS) and Swapping

#### What is the Medium-Term Scheduler (MTS)?
The **Medium-Term Scheduler (MTS)** acts like a parking lot manager for your computer’s memory (RAM). When RAM gets overcrowded, the MTS temporarily moves processes to the disk’s **swap space** to free up memory and brings them back when space is available.

#### What Does It Do?
- **Swap Out**: Moves a memory-intensive process from RAM to the disk’s swap space, like parking a car in a remote lot to clear a crowded garage.
- **Swap In**: Retrieves a process from swap space back to RAM when memory is available, allowing it to resume execution.
- **Example**: On a phone with many open apps, the MTS might pause a background app (e.g., a music player) and move it to swap space to free RAM for a game.
- **Key Benefit**: Prevents memory overload, ensuring system stability and avoiding crashes.

#### Why Is It Important?
Without the MTS, excessive memory demands could crash apps or freeze the system. Swapping balances memory usage, like a librarian reorganizing shelves to fit more books.

![Swapping](https://cdn.hashnode.com/res/hashnode/image/upload/v1749394253875/233e7b9b-1029-4d38-a549-a980f948554f.png)

---

### 2. Context Switching Deep Dive

#### What Is Context Switching?
**Context switching** is when the OS pauses one process (e.g., a game) to let another (e.g., a browser) use the CPU. It’s like a teacher pausing one student’s speech to let another speak, then resuming the first.

#### How Does It Work?
1. **Save Current Process State**: The OS stores the running process’s details (e.g., program counter, CPU registers) in its **Process Control Block (PCB)**, like saving game progress.
2. **Load New Process State**: The OS loads the next process’s details from its PCB into the CPU, like loading a different game save.
3. **Update Process Table**: The OS updates its process list to reflect the new running process.

#### Performance Impact
- **Overhead**: Context switching consumes time as the CPU saves and loads states instead of executing tasks.
- **Duration**: Takes **1–10 microseconds** in modern systems, fast but cumulative with frequent switches.
- **Factors Affecting Speed**:
  - **RAM Type**: Faster RAM (e.g., DDR4) speeds up switching compared to older RAM (e.g., DDR3).
  - **CPU Registers**: More registers mean more data to save/load, slowing the process.
  - **PCB Complexity**: Larger PCBs (with extensive memory or file data) increase switching time.
- **Example**: Switching between a video call and a document editor involves context switching, causing slight delays on slower systems.

#### Why Is It Important?
Context switching enables **multitasking**, allowing multiple apps to run concurrently. However, excessive switching (e.g., with 50 open browser tabs) can slow performance due to overhead.

<aside>
💡

**Context Switching**: A core OS mechanism that enables a single CPU to handle multiple processes or threads concurrently, creating the illusion of simultaneous execution.

![Context Switching](https://cdn.hashnode.com/res/hashnode/image/upload/v1747886074945/66ae1a1b-8264-48cd-a310-b2058c83415d.png)

**Details**:
- **Saving State**: The OS saves the running process’s state (e.g., registers, stack pointer) in its PCB before switching.
- **Loading State**: The OS restores the next process’s state from its PCB, resuming where it left off.
- **Resuming Execution**: The new process continues as if uninterrupted.
- **Multitasking**: Enables running multiple apps without interference.
- **CPU Efficiency**: Keeps the CPU active, even when a process waits for I/O.
- **Fair Allocation**: Prevents any single process from monopolizing the CPU.
- **Overhead**: Frequent switches consume time, slightly impacting performance.

</aside>

---

### 3. Orphan Processes

#### What Is an Orphan Process?
An **orphan process** is a child process (e.g., a browser tab) whose parent process (e.g., the main browser) terminates prematurely. It’s like a child left at a playground after their parent leaves.

#### How Does the OS Handle It?
- The OS reassigns the orphan to the **init process** (PID 1), the “grandparent” of all processes.
- The orphan continues running normally, unaware of its parent’s exit.
- **Example**: A script spawns a background task (e.g., `sleep 300 &`) and exits, leaving the task as an orphan adopted by init.

#### Creation Example
```bash
# orphan.sh
sleep 300 &  # Starts a background process sleeping for 300 seconds
exit         # Parent script exits, orphaning the sleep process
```

#### Detecting Orphans
Use this command to identify processes adopted by init (PID 1):
```bash
ps -elf | awk '$5 == 1 && $3 != "systemd"'
```
- Shows processes with parent PID (`$5`) as 1, excluding the main init process (`systemd`).

#### Why Is It Important?
Orphans are typically harmless, as the OS manages them automatically. Understanding them aids in debugging scripts or apps that spawn child processes.

---

### 4. Zombie Processes

#### What Is a Zombie Process?
A **zombie process** is a terminated process that remains in the system because its parent hasn’t retrieved its **exit status**. It’s like a student who finished an exam but waits for the teacher to collect their paper.

#### Characteristics
- Marked as `<defunct>` in the process table (visible via `ps aux`).
- Occupies a **PID** but consumes no CPU or memory, as it’s already terminated.
- **Example**: A script spawns 50 background tasks that finish, but the parent doesn’t collect their exit statuses, leaving them as zombies.

#### Creation Example
```bash
# zombie.sh
for i in {1..50}; do
  sleep 1 &  # Spawns 50 quick-finishing background processes
done
sleep 100    # Parent waits, leaving children as zombies
```

#### Dangers
- **Process Table Exhaustion**: Too many zombies can deplete available PIDs, preventing new processes from starting, like running out of ticket numbers at a deli.
- **System Instability**: Excessive zombies may slow or destabilize the system.

#### Why Is It Important?
Zombies indicate poor programming, as parents should clean up child processes. While harmless in small numbers, they can cause issues if they accumulate.

---

### 5. Orphan vs. Zombie Processes: Key Comparisons

| **Feature** | **Orphan Process** | **Zombie Process** |
|-------------|--------------------|--------------------|
| **State**   | Still running      | Terminated         |
| **Parent**  | Reassigned to init (PID 1) | Original parent (not collecting exit status) |
| **Resources** | Uses CPU, memory, etc. | Uses only a PID |
| **Solution** | Handled by OS (adopted by init) | Parent must call `wait()` to clean up |

- **Orphan Example**: A browser crashes, but its download task continues under init.
- **Zombie Example**: A script’s child tasks finish but remain `<defunct>` until the script collects their status.

---

### 6. Practical Implications

#### Debugging Tools
- **Find Zombies**: Use `ps aux | grep Z` to identify zombies (look for `<defunct>`).
- **Visualize Process Hierarchy**: Use `pstree -p` to view parent-child relationships, spotting orphans under `init (1)`.

#### Programming Best Practices
- **Use `wait()`**: Ensure parent processes call `wait()` to collect child exit statuses, preventing zombies.
- **Handle SIGCHLD**: Implement signal handlers to detect child termination and clean up promptly.
- **Double-Fork for Daemons**: Use the double-fork technique for daemons to detach from parents and avoid zombies.

#### System Administration Tips
- **Monitor PID Limits**: Check `/proc/sys/kernel/pid_max` for the maximum PIDs. Excessive zombies can exhaust this limit.
- **Configure Swap Space**: Set swap space to **1.5–2x RAM size** (e.g., 12–16GB for 8GB RAM) to support MTS swapping without performance degradation.

---

### 7. Interview Questions (Simplified)

#### Q1: Why Can’t We Kill Zombie Processes?
- **Answer**: Zombies are already terminated, so they can’t be killed. They linger in the process table until the parent collects their exit status via `wait()`. If the parent is gone, the **init process** (PID 1) cleans them up.

#### Q2: How Does Swapping Affect System Performance?
- **Answer**: Swapping moves processes from fast RAM to slower disk storage, reducing performance due to slower disk I/O. However, it prevents crashes by freeing memory, allowing the system to continue running.

#### Q3: What Happens If init Dies?
- **Answer**: If the **init process** (PID 1) dies, the system triggers a **kernel panic** and crashes, as init manages all processes, adopts orphans, and handles system startup/shutdown.

---

### 8. Key Takeaways (Simplified)
- **Scheduler Hierarchy**:
  - **Long-Term Scheduler (LTS)**: Limits processes entering the system (like a club bouncer).
  - **Short-Term Scheduler (STS)**: Assigns CPU to processes (like a DJ picking songs).
  - **Medium-Term Scheduler (MTS)**: Manages memory via swapping (like a parking lot manager).
- **Process States**:
  - **Orphan**: A running process with a dead parent, adopted by init.
  - **Zombie**: A terminated process awaiting exit status collection.
- **Key Operations**:
  - **Context Switching**: Enables multitasking by switching processes.
  - **Process Cleanup**: Prevents zombies, ensuring system stability.

---

### 9. Airport Analogy: Who Decides What?
Imagine an airport where:
- **Planes** = Processes (apps or tasks).
- **Runway** = CPU (main resource for execution).
- **You (manager)** = OS schedulers.

You make two key decisions:
1. **Which plane flies next?** (Which process runs on the CPU?)
2. **Which planes go to parking?** (Which processes are swapped to disk?)

#### Who Decides What?
| **Decision** | **Scheduler** | **Explanation** |
|--------------|---------------|-----------------|
| **Which plane flies next?** | **Short-Term Scheduler (STS)** | Like a **control tower**, the STS quickly decides which plane (process) uses the runway (CPU) next, selecting from the **Ready Queue** (planes ready for takeoff). It operates every few milliseconds to keep the runway busy. |
| **Which planes go to parking?** | **Medium-Term Scheduler (MTS)** | Like a **parking lot manager**, the MTS moves idle planes (processes) to a parking area (swap space) when gates (RAM) are full. It runs occasionally to manage memory and brings planes back when space is available. |

#### Analogy Breakdown
- **Short-Term Scheduler (STS)**:
  - **Role**: Selects the next process for CPU execution.
  - **Speed**: Fast, making decisions in milliseconds.
  - **Focus**: Maximizes CPU usage by picking from the Ready Queue.
  - **Example**: Switching between a game and a browser, the STS assigns the CPU.
  - **Limitation**: Doesn’t control the number of processes in the system.
- **Medium-Term Scheduler (MTS)**:
  - **Role**: Manages memory by swapping processes to/from disk.
  - **Speed**: Slower, runs when memory is low.
  - **Focus**: Reduces **degree of multiprogramming** by moving processes to swap space.
  - **Example**: Pauses a music app to free RAM for a video editor.
  - **Used In**: Primarily time-sharing systems (e.g., laptops, phones).

#### Summary Table
| **Feature** | **Short-Term Scheduler** | **Medium-Term Scheduler** |
|-------------|--------------------------|---------------------------|
| **Also Known As** | CPU Scheduler | Swapping Scheduler |
| **Speed** | Very fast (milliseconds) | Slower (occasional) |
| **Frequency** | Frequent | When memory is tight |
| **Main Task** | Assigns CPU to processes | Swaps processes to/from disk |
| **Affects Multiprogramming** | Minimal control | Actively reduces |
| **Used In** | Most OSs | Time-sharing systems |
