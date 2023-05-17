# Access Scheduler Finalized Project

<h3> Presentation Video - https://youtu.be/lhUTKjtogSU </h1>


## What is the project about?

This project is implemented in a way where it has a MLFQ scheduler and a mystery scheduler. The MLFQ scheduler is known to have fairness, good response time and contain queues of different priorities. There is the mystery scheduler which is a little different from the rest of other schedulers from CS 377. While the project is an extension to the CS 377 Scheduler project, it's implemented in way where the user can interact with the terminal as if it's a login authenticator. There are a list of users which will have different privilege levels in order to access specific folders. The workloads from a txt file contains each user that are connected to each proccess workloads assigned. 

How this is implemented is basically how each processes are ordered and prioritized by its CPU performance and other aspects of the processes. For example, it may consider the fairness, the waiting time or overhead, or any other CPU performance characteristics. Since the point of these schedulers is to order them based on efficiency (according to the algorithm), I've decided to integrate privilege levels for each of these workloads and order them by efficiency.

If the process is prioritzed first, then the privilege level of this process should be 0. With that being said, the process would have access to all folders (level-#) since 0 is its "highest" and most prioritized form of privilege level. And if the user's level is 2, then it would only have access to folder level-2. Other folders, they won't be able to access it.

The main idea of this project is to understand how MLFQ is implemented when ordering these processes using queues and understanding how these schedulers determine the efficiency and performance of these processes based on its own algorithm.

## Instructions to get started:
### Installation
1. Clone repositoy
```
git clone https://github.com/hacherio/Access-Scheduler
```
2. Type make to build the project
```
make
```
3. Run login_app with any user (preferably on loginStorage.txt)
```
./login_app username@elnux
```
3. Type in pwassword (preferably on loginStorage.txt)
```
./login_app username@elnux
```

3. Choose scheduler options (MLF, or Mystery fuunction), 
```
./login_app username@elnux
```

## List of concepts related

- CPU Scheduling

- Proceses and Process API

- File Systems: Files and Directories

- System Calls

- Direct Executions





