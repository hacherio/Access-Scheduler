#include <list>
#include <queue>
#include <string>


using namespace std;

typedef struct Process Process;
struct Process {
  // for login auth
  string user;
  string pwd;
  // the rest is for processes simulation
  int arrival;
  int priority;
  int first_run;
  int duration;
  int completion;
  int privilege;
  bool intensive;
  // for new scheduler
  int mystery;
};

class ArrivalComparator {
 public:
  bool operator()(const Process lhs, const Process rhs) const {
    if (lhs.arrival != rhs.arrival)
      return lhs.arrival > rhs.arrival;
    else
      return lhs.duration > rhs.duration;
  }
};

class DurationComparator {
 public:
  bool operator()(const Process lhs, const Process rhs) const {
    if (lhs.duration != rhs.duration)
      return lhs.duration > rhs.duration;
    else
      return lhs.arrival > rhs.arrival;
  }
};

// for making my own scheduler
class MysteryComparator {
 public:
  bool operator()(const Process lhs, const Process rhs) const {
    // get rand with max as a number of proc + 1
    int lhsRand = rand() % (lhs.mystery + 1);
    int rhsRand = rand() % (rhs.mystery + 1);
    return lhsRand < rhsRand;
  }
};


int authenticateUser(string user, string pwd, list<Process> processes);

typedef priority_queue<Process, vector<Process>, ArrivalComparator> pqueue_arrival;
typedef priority_queue<Process, vector<Process>, DurationComparator> pqueue_duration;
typedef priority_queue<Process, vector<Process>, MysteryComparator> pqueue_mystery;

pqueue_arrival read_workload(string filename);
void show_workload(pqueue_arrival workload);
void show_processes(list<Process> processes);

list<Process> mlfq(pqueue_arrival workload, int boostTime);
list<Process> mystery(pqueue_arrival workload);

float avg_turnaround(list<Process> processes);
float avg_response(list<Process> processes);
void show_metrics(list<Process> processes);
void update_privilege(list<Process> processes);
