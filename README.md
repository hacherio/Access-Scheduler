# Access Scheduler Finalized Project

## What is the project about?

This project is implemented in a way where it has an MLFQ scheduler and a mystery scheduler. The MLFQ scheduler is known to have fairness, good response time and contain queues of different priorities. There is the mystery scheduler which is a little different from the rest of the schedulers from CS 377. While the project is an extension to the CS 377 Scheduler project, it's implemented in way where the user can interact with the terminal as if it's a login authenticator. There is a list of users who will have different privilege levels to access specific folders. The workloads from a txt file contains each user that are connected to each process workload assigned. 

Each processes are ordered and prioritized by their CPU performance and other aspects of the processes. For example, it may consider the fairness, the waiting time or overhead, or any other CPU performance characteristics. Since the point of these schedulers is to order them based on efficiency (according to the algorithm), I've decided to integrate privilege levels for each of these workloads and order them by efficiency.

If the process is prioritized first, then the privilege level of this process should be 0. With that being said, the process would have access to all folders (level-#) since 0 is its "highest" and most prioritized form of privilege level. And if the user's level is 2, then it would only have access to folder level-2. Other folders, they won't be able to access it.

The main idea of this project is to understand how MLFQ is implemented when ordering these processes using queues and understanding how these schedulers determine the efficiency and performance of these processes based on its algorithm.
__________________________________________________________________
## Instructions to get started:
### Installation
1. Clone repositoy
```
git clone https://github.com/hacherio/Access-Scheduler
```
__________________________________________________________________
### Make
2. Type make to build the project
```
make
```
__________________________________________________________________
### BEFORE YOU RUN: REMOVE ALL TXT FILES IN THE LEVEL FOLDERS!!!
__________________________________________________________________
### Run
3. Run login_app with any user (preferably on loginStorage.txt)
```
./login_app username@elnux
```
3. Type in password (preferably on loginStorage.txt)
```
./login_app username@elnux
```
3. Choose scheduler options (MLF or Mystery function):
```
1 
```
OR
```
2
```
__________________________________________________________________
### Output
#### It should display something similar to this:
>Your account's privilege level is 2<br>
>Folder level-2 and higher are accessible<br>
>Successfully logged in!<br>


>Workload:<br>
>        Arrival=0, Duration=3, Privilege=2<br>
>        Arrival=0, Duration=4, Privilege=0<br>
>        Arrival=0, Duration=6, Privilege=1<br>


>Processes:<br>
>        User Privilege=0, arrival=0, duration=0, first_run=1, completion=9<br>
>        User Privilege=1, arrival=0, duration=0, first_run=7, completion=12<br>
>        User Privilege=2, arrival=0, duration=0, first_run=0, completion=13<br>


>Average Turnaround Time: 11.3333<br>
>Average Response Time:   2.66667 <br>

### Edit workload txt
#### If you want to test different outputs, follow this format:
>username password startTime burstTime privilegeLevel<br>


>nha pwd 0 3 2 <br>
>amy is 0 4 0 <br>
>cam bad 0 6 1 <br>
__________________________________________________________________
## List of concepts related

- CPU Scheduling

- Proceses and Process API

- File Systems: Files and Directories

- System Calls

- Direct Executions
__________________________________________________________________
## Citation
* [Geeks For Geeks MLFQ](https://www.geeksforgeeks.org/multilevel-feedback-queue-scheduling-mlfq-cpu-scheduling/)
* [Scheduling Textbook](https://pages.cs.wisc.edu/~remzi/OSTEP/cpu-sched-mlfq.pdf)







