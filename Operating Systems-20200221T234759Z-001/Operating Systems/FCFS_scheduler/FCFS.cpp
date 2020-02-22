/*
#include <iostream>
#include <string>
#include <queue>
using namespace std;

class Process {
public:
	//oofplox
	string processName;
	queue<int> cpuBurst;
	queue<int> ioTime;
	int waitTime = 0;
	int turnAroundTime = 0;
	int state; //0 = waiting, 1 = executing, 2 = blocking, 3 = completed

	//runningQueue.pushback(queueFront(readyQueue));
	//readyQueue.pop();

	//calculate turnaround time
	//calculate response time
	//calculate wait time
	//calculate averages of these 3
	
};//gg

void ReadyQueue(vector<Process*> &readyQueue, Process* &runningProcess) {
	//processes' waiting time is incremented, including processes that enter the running state in this unit of time
	for (unsigned int i = 0; i < readyQueue.size(); i++) {
		readyQueue[i]->waitTime++;
		readyQueue[i]->turnAroundTime++;
	}
	//if no process is running, move the process in the readyQueue into the runningProcess
	if (runningProcess == NULL) {
		runningProcess = readyQueue.front();
		readyQueue.erase(readyQueue.begin());
	}
}

void RunningProcess(Process *runningProcess, vector<Process*> &waitingQueue) {
	if (runningProcess != NULL) {
		runningProcess->cpuBurst.front()--;
		runningProcess->turnAroundTime++;
		if (runningProcess->cpuBurst.front() <= 0) {
			//By not putting a process in waitingQueue it has effectively been terminated
			if (!runningProcess->ioTime.empty()) {
				waitingQueue.push_back(runningProcess);
			}
			runningProcess = NULL;
		}
	}
}

void WaitingQueue(vector<Process*> &waitingQueue, vector<Process*> &readyQueue) {
	for (unsigned int i = 0; i < waitingQueue.size(); i++) {
		waitingQueue[i]->ioTime.front()--;
		if (waitingQueue[i]->ioTime.front() <= 0) {
			readyQueue.push_back(waitingQueue[i]);
			waitingQueue.erase(waitingQueue.begin() + i);
		}
	}
}

vector<Process*> InitializeProcesses() {
	//Create proceses
	vector<Process*> processes;
	return processes;
}

int main() {
	//declare process states
	vector<Process*> readyQueue;
	Process *runningProcess;
	vector<Process*> waitingQueue;

	//Initialize processes
	vector<Process*> processes = InitializeProcesses();
	//Put processes in ready queue
	for (unsigned int i = 0; i < processes.size(); i++) {
		readyQueue.push_back(processes[i]);
	}
	//Run loops
	while (true) {
		ReadyQueue();
		RunningProcess();
		WaitingQueue();
		//Check if all processes are terminated
		if (runningProcess == NULL && waitingQueue.empty() && readyQueue.empty()) {
			//Implement functionality for when all processes are terminated
			break();
		}
	}

	int current_cpu_burst;
	int current_io;
	int response_time;
	//int state; //0 = waiting, 1 = executing, 2 = blocking, 3 = completed
	//int time_unit = 690;
	//string ready_queue[9] = { "p1", "p2", "p3", "p4", "p5", "p6", "p7", "p8", "p9" }; //can hold at most 9 processes
	//process p1[8], p2[10], p3[9], p4[9], p5[9], p6[9], p7[8], p8[7], p9[9]; //initialize the processes

	//test
	int time_unit = 31;
	string ready_queue[3] = { "p1", "p2", "p3" };
	Process p1[1];
	Process p2[1]; 
	Process p3[1];
	//initialize processes
	p1[0].cpu_burst = 24;
	p2[0].cpu_burst = 3;
	p3[0].cpu_burst = 4;


	for (int i = 0; i < time_unit; i++) {

	}


	return 0;
}

*/