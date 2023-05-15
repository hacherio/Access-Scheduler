# Access Scheduler Finalized Project

<h3>What is the project about?</h1>

This project is implemented in a way where it has a MLFQ scheduler and a mystery scheduler. The mystery scheduler is a bit different from the rest of other common schedulers we've known in CS 377. While the project is technically an extension to the CS 377 Scheduler project, it's implemented in way where the user can interact the terminal as if it's a login authenticator where different users make have certain access to folders depending on their privilege level. The workload from the txt file contains each user along with the proccess workloads assigned. 

How this is implemented is basically how each processes are ordered and prioritized on it's CPU performance and other aspects of the processes. Depending on the scheduling algorithm would depend on the aspects of the workload system. For example, it may consider the fairness, the waiting time or overhead, or just about any performance characteristics. Since the point of these schedulers is to order them based on efficiency (according to the algorithm), I've decided to add privilege levels for each of these workloads and order by effiecency.

If the process is prioritzed first, then the privilege level of this process should be 0. With that being said, the process would have access to all folders (level-#) since 0 is its "highest" and most prioritized form of privilege level. And if the user's level is 2, then it would only have access to folder level-2. Other folders, they won't be able to access it.

The point of this project is to understand how MLFQ is implemented when ordering these processes using queues and understanding how these schedulers determine the efficiency and performance of these processes. 


# List of concepts related

- CPU Scheduling

- Proceses and Process API

- File Systems: Files and Directories

- System Calls

- Direct Executions
