#include <login.h>
#include <fstream>
#include <iostream>
#include <list>
#include <queue>
#include <string>
#include <algorithm>
#include <cmath>

// for color coding text taken from ansi code
#define red     "\x1b[31m"
#define green   "\x1b[32m"
#define blue    "\x1b[34m"
#define yellow    "\x1b[33m"

#define reset   "\x1b[0m" // to set to default

using namespace std;

pqueue_arrival read_workload(string filename) {
  // queue: <Process, vector<Process>, ArrivalComparator>
  pqueue_arrival workload;
  int arrival, duration, privilege;
  string user;
  string pwd;
  ifstream file(filename);
  // file doesnt exist/empty, return as is
  if(!file)
    return workload;
  // loop through each word and initialize
  while(file >> user && file >> pwd && file >> arrival && file >> duration && file >> privilege){
    Process p;
    p.user = user;
    p.pwd = pwd;
    p.duration = duration;
    p.arrival = arrival;
    // privilege by accessing folder levels
    p.privilege = privilege;
    // initialize -5 as flag to track new arrival of other schedulers
    p.first_run = -5;
    p.mystery += 1; // my own scheduler -> counter number of processes
    // if intensive, needs a lot of CPU resources (more completion time)
    // if interactive, less CPU time is needed hence it being smaller
    p.intensive = false;
    workload.push(p);
  }
  file.close();
  return workload;
}

void show_workload(pqueue_arrival workload) {
  pqueue_arrival xs = workload;
  cout << "\n";
  cout << yellow << "Workload:" << reset << endl;
  while (!xs.empty()) {
    Process p = xs.top();
    cout << yellow << "\t Arrival=" << p.arrival << ", Duration="
    << p.duration  << ", Privilege=" <<  p.privilege << reset << endl;
    xs.pop();
  }
}

void show_processes(list<Process> processes) {
  list<Process> xs = processes;
  list<Process> xs_new = processes;
  cout << yellow << "Processes:" << reset << endl;
  while (!xs.empty()) {
    Process p = xs.front();
    cout << yellow <<"\t User Privilege=" << p.privilege << ", arrival=" << p.arrival << ", duration=" << p.duration
         << ", first_run=" << p.first_run << ", completion=" << p.completion << reset
         << endl;
    xs.pop_front();
  }
}


list<Process> mlfq(pqueue_arrival workload, int boostTime) {
  list<Process> complete;
  const int levels = 4;
  // priority levels of each queue
  queue<Process> q[levels];
  int curArrival = 0;
  // time slice for each queue:
  // jobs with higher priority has more cpu time 
  int slice[levels] = {1, 2, 4, 6};
  int boostCounter = boostTime/slice[0]; // used as countdown
  int privilegeCounter = 0; // used to order privilege level
  // checks if workload or any of the queues from the list are empty
  // uses algorithm library to shorten loop quque
  while (any_of(begin(q), end(q), [](const auto& listQ) { return !listQ.empty(); }) || !workload.empty()) {
    // does priority boost on queue if the counter runs out
    boostCounter--; //decrements each time
    if (boostCounter == 0) {
      // all lowest queues gets boosted up to highest priority
      for (int i = 1; i < levels; i++) {
        while(!q[i].empty()) {
          Process p = q[i].front();
          // reset priority to highest level
          p.priority = 0; 
          q[i].pop();
          q[0].push(p);  // 0 is highest priority
        }
      }
      // reset boost counter to the calculated intervial slice
      boostCounter = boostTime/slice[0]; 
    }

    // order the process by smallest arrival time
    while (!workload.empty() && workload.top().arrival <= curArrival) {
      Process p = workload.top();
      // start from highest priority
      p.priority = 0; 
      workload.pop();
      q[0].push(p);
    }

    // go thru processes in each of the queues
    for (int i = 0; i < levels; i++) {
      if (!q[i].empty()) {
        Process p = q[i].front();
        q[i].pop();
        // update the first_run with current arrival 
        p.first_run = curArrival; 
        // decrement leftover duration each time slice
        p.duration -= slice[i];
        // checks if duration is 0, push to processes completion 
        if(p.duration <= 0) {
          // process completed: add slice, arrival, duration
          p.completion = curArrival + slice[i] + p.duration;
          p.privilege = privilegeCounter++;
          complete.push_back(p);
        } 
        else { 
          // checks the type of process (intensive/interactive) and finish leftover duration
          // intensive requires more time -> therefore higher priority
          // interactive requres less time -> prioritized less
          if ((i < levels-1) && p.intensive)
            p.priority = i + 1; // higher priority
          else if (i > 0)
            p.priority = i - 1; // lower priority
          q[p.priority].push(p);
        }
      }
    }
    // adds up current time until all workloads are empty
    curArrival++;
  }
  return complete;
}

// new created scheduler 
list<Process> mystery(pqueue_arrival workload) {
  // Initialize the values for each process
  Process slice;
  int curArrival = 0;
  int timeSlice = slice.mystery; // init time slice
  int privilegeCounter = 0;
  list<Process> complete;
  pqueue_mystery orderMys;
  while (!workload.empty() || !orderMys.empty()) {
    Process p;
    // get new arriving processes to queue
    while (!workload.empty() && workload.top().arrival <= curArrival) {
      p = workload.top();
      orderMys.push(p);
      workload.pop();
    }

    // get process with the smallest mystery num
    Process curProcess;
    if(!orderMys.empty()) {
      curProcess = orderMys.top();
      orderMys.pop();

      if(curProcess.first_run < 0)
        curProcess.first_run = curArrival;

      // update all processes nums
      curProcess.duration -= 1;
      curArrival += 1;
      // check if lefotwover time to goes over
      if (curProcess.duration > 0) {
        orderMys.push(curProcess);
      } 
      else{
        curProcess.privilege = privilegeCounter++;
        curProcess.completion = curArrival;
        complete.push_back(curProcess);
      }
    } 
    else
      curArrival += timeSlice;
  }
  return complete;
}

int authenticateUser(string user, string pwd, list<Process> processes){
  for (auto p = processes.begin(); p != processes.end(); p++) {
    if (p->user == user && p->pwd == pwd){
      cout << "\n";
      cout << green << "Your account's privilege level is " << p->privilege << reset << "\n";
      cout <<  green << "Folder level-" << p->privilege << " and higher are accessible" <<  reset;
      return p->privilege; // authenticated successfully
    }
  }
  // flag -1 for no auth, other nums > -1 are is privilege level
  return -1;   // not authenticated
}


float avg_turnaround(list<Process> processes) {
  // Tturnaround = complete - arrival
  int numProcess = 0;
  float turnTime = 0;
  while(!processes.empty()){
    Process p = processes.front();
    turnTime += p.completion - p.arrival;
    numProcess++;
    processes.pop_front();
  }
  return turnTime/numProcess;
}

float avg_response(list<Process> processes){
  // Tresponse = first run - arrival
  int numProcess = 0;
  float respTime = 0;
  while(!processes.empty()){
    Process p = processes.front();
    respTime += p.first_run - p.arrival;
    numProcess++;
    processes.pop_front();
  }
  return respTime/numProcess;
}

void show_metrics(list<Process> processes) {
  float avg_t = avg_turnaround(processes);
  float avg_r = avg_response(processes);
  cout << '\n';
  show_processes(processes);
  cout << '\n';
  cout << yellow << "Average Turnaround Time: " << avg_t << reset <<endl;
  cout << yellow <<"Average Response Time:   " << avg_r << reset << endl;
}

