#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <fstream>
#include <iomanip>
using namespace std;

//class structure called Process which contains all of the necessary information for a process
//the cpu bursts and ioTime will be stored as a queue rather than an array
class Process {
public:
	//constructors
	Process(string, vector<int>, int, vector<int>, int, int, int, int, int);

	//destructor
	~Process();

	//accessor functions
	string getProcessName();
	vector<int> getCpuBurst();
	int getCpuBurstIndex();
	int getCpuBurstSize();
	vector<int> getIoTime();
	int getIoIndex();
	int getIoSize();
	int getWaitTime();
	int getResponseTime();
	int getTurnAroundTime();
	int getState();

	//mutator functions
	void setProcessName(string);
	void setCpuBurst(int, int);
	void setCpuBurstIndex(int);
	void setIoTime(int, int);
	void setIoIndex(int);
	void setWaitTime(int);
	void setResponseTime(int);
	void setTurnAroundTime(int);
	void setState(int);
	void eraseCpuBurstTime();
	void eraseIoTime();

private:
	string newProcessName;
	vector<int> newCpuBurst;
	int newCpuBurstIndex;
	vector<int> newIoTime;
	int newIoIndex;
	int newWaitTime;
	int newResponseTime;
	int newTurnAroundTime;
	int newState; //0 = not admitted, 1 = waiting, 2 = executing, 3 = blocking (I/O), 4 = completed

};
//accessor functions
string Process::getProcessName() {
	return newProcessName;
}
vector<int> Process::getCpuBurst() {
	return newCpuBurst;
}
int Process::getCpuBurstIndex() {
	return newCpuBurstIndex;
}
int Process::getCpuBurstSize() {
	return newCpuBurst.size();
}
vector<int> Process::getIoTime() {
	return newIoTime;
}
int Process::getIoIndex() {
	return newIoIndex;
}
int Process::getIoSize() {
	return newIoTime.size();
}
int Process::getWaitTime() {
	return newWaitTime;
}
int Process::getResponseTime() {
	return newResponseTime;
}
int Process::getTurnAroundTime() {
	return newTurnAroundTime;
}
int Process::getState() {
	return newState;
}
//mutator functions
void Process::setProcessName(string processName) {
	newProcessName = processName;
}
void Process::setCpuBurst(int index, int value) {
	newCpuBurst[index] = value;
}
void Process::setCpuBurstIndex(int CpuBurstIndex) {
	newCpuBurstIndex = CpuBurstIndex;
}
void Process::setIoTime(int index, int value) {

	newIoTime[index] = value;
}
void Process::setIoIndex(int IoIndex) {
	newIoIndex = IoIndex;
}
void Process::setWaitTime(int waitTime) {
	newWaitTime = waitTime;
}
void Process::setResponseTime(int responseTime) {
	newResponseTime = responseTime;
}
void Process::setTurnAroundTime(int turnAroundTime) {
	newTurnAroundTime = turnAroundTime;
}
void Process::setState(int state) {
	newState = state;
}
void Process::eraseCpuBurstTime() {
	newCpuBurst.erase(newCpuBurst.begin());
}
void Process::eraseIoTime() {
	newIoTime.erase(newIoTime.begin());
}

//overload constructor
Process::Process(string processName, vector<int> cpuBurst, int CpuBurstIndex, vector<int> ioTime, int IoIndex, int waitTime, int responseTime,
	int turnAroundTime, int state) {
	newProcessName = processName;
	newCpuBurst = cpuBurst;
	newCpuBurstIndex = CpuBurstIndex;
	newIoTime = ioTime;
	newIoIndex = IoIndex;
	newWaitTime = waitTime;
	newResponseTime = responseTime;
	newTurnAroundTime = turnAroundTime;
	newState = state;
}
//destructor
Process::~Process() {
}

//overload << operator
bool operator<(Process &s1, Process &s2) {
	return s1.getProcessName() < s2.getProcessName();
}

//Function Prototypes
/*****************************************/
void InitializeProcesses(vector<Process>& processes);
void IncrementWaitTime(ofstream& output, vector<Process>& processes);
void LoadtoReadyQueue(Process * process, queue<Process*>& readyQueue);
void LoadtoIOlist(Process & process, vector<Process*>& IOlist);
int FindRunningProcessIndex(vector<Process> processes);
void CpuBurstDecrement(vector<Process>& processes, int index);
void DecrementIO(vector<Process*> IOlist);
void SortIO(vector<Process*>& IOlist);
void PrintOutput(ofstream& output, queue<Process*> readyQueue, vector<Process*> IOlist, vector<Process>& processes, int runningProcessIndex, vector<string>& completed, int timeUnit, int done);
void PrintReadyQueue(ofstream& output, queue<Process*> readyQueue);
void PrintIOlist(ofstream& output, vector<Process*> IOlist);
void Results(ofstream& output, vector<Process>& processes, int timeUnit, int idleTime, int context);

//Main Driver
/*****************************************/
int main() {

	//declare variables
	vector<Process> processes; //stores the data for the processes
	queue<Process*> readyQueue; //ready queue will be a queue that contains the addresses of the processes waiting for CPU time
	vector<Process*> IOlist; //vector of processes that are blocking in I/O
	vector<string> completed; //vector of strings of completed processes
	int runningProcessindex = 0; //index of process that is executing in the CPU
	int done = 0; //integer that indicates the number of completed processes
	int timeUnit = 0; //indicate unit of time
	int idleTime = 0; //indicate time CPU is not used
	int count = 0; //used to determine number of processes with remaining i/o time of 0
	int context = 0; //counts number of context switches
	ofstream output;
	output.open("FCFS_output.txt");

	output.setf(ios::right);
	output.setf(ios::fixed);
	output.precision(3);

	InitializeProcesses(processes);
	for (unsigned int i = 0; i < processes.size(); i++) {
		LoadtoReadyQueue(&(processes[i]), readyQueue);
	}
	processes[0].setState(2);
	context++;
	PrintOutput(output, readyQueue, IOlist, processes, runningProcessindex, completed, 0, 0); //prints first context switch
	readyQueue.pop();
	//cout << "The FCFS scheduling algorithm has started ..." << endl << endl; //for debug purposes
	while (done != processes.size()) {
		//cout << "The FCFS scheduling algorithm is still running ..." << endl; //for debug purposes
		timeUnit++;
		DecrementIO(IOlist); //decrements the remaining I/O time for all processes in the IOlist

		//increment the waiting times of the processes in the ready queue
		IncrementWaitTime(output, processes);

		//increment turnaround time if the process is not complete
		for (unsigned int i = 0; i < processes.size(); i++) {
			if (processes[i].getState() != 4) {
				processes[i].setTurnAroundTime(processes[i].getTurnAroundTime() + 1);
			}
		}

		count = 0;
		//find number of processes with remaining I/O time of 0
		for (unsigned i = 0; i < IOlist.size(); i++) {
			if (((*IOlist[i]).getIoTime())[0] <= 0) {
				count++;
			}
		}
		if (count > 1) {
			SortIO(IOlist);
		}
		
		//for all processes that complete I/O, send them to the ready Queue
		for (unsigned ind = 0; ind < IOlist.size(); ind++) {
			if (((*IOlist[ind]).getIoTime())[0] <= 0) {
				LoadtoReadyQueue(IOlist[ind], readyQueue);
				(*IOlist[ind]).eraseIoTime(); //erases element in IO time vector
				IOlist.erase(IOlist.begin() + ind); //removes the process from the I/O list
				ind = -1;
			}
		}
		
		runningProcessindex = FindRunningProcessIndex(processes); //finds the index of the running process
		//ensure that the code below only functions as long as the running process is not the last process in the scheduler
		if (runningProcessindex >= 0) { //only runs if there's a running process

			//sets response time
			if (processes[runningProcessindex].getResponseTime() == -1) {
				(processes[runningProcessindex].setResponseTime(timeUnit - 1)); //the response time is timeUnit - 1 because the process enters the CPU in the previous timeUnit
			}

			CpuBurstDecrement(processes, runningProcessindex); //decrements CPU burst of running process

			//Condition: if the running process' CPU burst <= 0
			//this case is the only time when a context switch occurs because it means that a process has completed its CPU burst
			//so another process is loaded onto the CPU
			//The special case where a process goes to I/O is included here
			//Result: adjust according data and send the process to IO
			//(processes[runningProcessindex].getCpuBurst())[processes[runningProcessindex].getCpuBurstIndex()] finds runnings process' CPU Burst
			if ((processes[runningProcessindex].getCpuBurst())[0] <= 0) {
				context++;
				processes[runningProcessindex].eraseCpuBurstTime(); //erase the cpu burst element in the vector
				
				//if the process has remaining I/O, send it to I/O
				if (processes[runningProcessindex].getIoSize() > 0) {//the process is only sent to I/O if an I/O exists for the process
					LoadtoIOlist(processes[runningProcessindex], IOlist); //sends the running process to I/O
				}
				//if the ready queue is not empty, load the next process in the ready queue onto the CPU
				if (readyQueue.size() > 0) {// if the ready queue has another process, then set up the process to be the running process in the next unit of time
					(*(readyQueue.front())).setState(2); //finds the next process in the ready queue and change its state to executing
					readyQueue.pop(); //removes that process from the ready queue
				}
				//if process' CPUBurst vector is empty, then the process is completed
				if (processes[runningProcessindex].getCpuBurstSize() <= 0) { 
					processes[runningProcessindex].setState(4);
					completed.push_back(processes[runningProcessindex].getProcessName());
					sort(completed.begin(), completed.end());
					done++;
				}
				
				runningProcessindex = FindRunningProcessIndex(processes); //sets runningProcessindex to the next process in the ready queue
				PrintOutput(output, readyQueue, IOlist, processes, runningProcessindex, completed, timeUnit, done); //print the context switch
			}

			else {
				//for debug purposes
				//PrintOutput(output, readyQueue, IOlist, processes, runningProcessindex, completed, timeUnit, done);
			}

		}

		//if there's no existing process that's running, check to see if there's processes in the ready queue that can be placed on the CPU
		else if (readyQueue.size() > 0) {
			(*(readyQueue.front())).setState(2); //finds the next process in the ready queue and change its state to executing
			readyQueue.pop(); //removes that process from the ready queue
			idleTime++;
			//for debug purposes
			//PrintOutput(output, readyQueue, IOlist, processes, runningProcessindex, completed, timeUnit, done);
		}

		else {
			//the CPU is idle
			idleTime++;
			//for debug purposes
			//PrintOutput(output, readyQueue, IOlist, processes, runningProcessindex, completed, timeUnit, done);
		}
	}

	//display final results
	cout << "Finished" << endl << endl;
	output << "Finished" << endl << endl;
	Results(output, processes, timeUnit, idleTime, context);

	output.close();
	return 0;
}

//Function Definitions
/*****************************************/

//initializes the values of the processes
void InitializeProcesses(vector<Process>& processes) {
	
	//Create process P1
	string processName = "P1";
	vector<int> cpuBurst;
	//cpuBurst.push_back(3);
	//cpuBurst.push_back(4);

	cpuBurst.push_back(4);
	cpuBurst.push_back(3);
	cpuBurst.push_back(2);
	cpuBurst.push_back(4);
	cpuBurst.push_back(4);
	cpuBurst.push_back(4);
	cpuBurst.push_back(3);
	cpuBurst.push_back(4);


	vector<int> ioTime;
	//ioTime.push_back(2);

	ioTime.push_back(27);
	ioTime.push_back(31);
	ioTime.push_back(43);
	ioTime.push_back(18);
	ioTime.push_back(22);
	ioTime.push_back(26);
	ioTime.push_back(24);

	//the variables below are the same for each process during initialization
	int CpuBurstIndex = 0;
	int IoIndex = 0;
	int waitTime = 0;
	int responseTime = -1;
	int turnAroundTime = 0;
	int state = 0;

	Process p1 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p1);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//Create process P2
	processName = "P2";
	//cpuBurst.push_back(2);
	//cpuBurst.push_back(6);

	cpuBurst.push_back(16);
	cpuBurst.push_back(17);
	cpuBurst.push_back(5);
	cpuBurst.push_back(16);
	cpuBurst.push_back(7);
	cpuBurst.push_back(13);
	cpuBurst.push_back(11);
	cpuBurst.push_back(6);
	cpuBurst.push_back(3);
	cpuBurst.push_back(4);

	//ioTime.push_back(1);

	ioTime.push_back(24);
	ioTime.push_back(21);
	ioTime.push_back(36);
	ioTime.push_back(26);
	ioTime.push_back(31);
	ioTime.push_back(28);
	ioTime.push_back(21);
	ioTime.push_back(13);
	ioTime.push_back(11);

	Process p2 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p2);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//Create process P3
	processName = "P3";
	//cpuBurst.push_back(5);
	//cpuBurst.push_back(2);

	cpuBurst.push_back(8);
	cpuBurst.push_back(12);
	cpuBurst.push_back(18);
	cpuBurst.push_back(14);
	cpuBurst.push_back(4);
	cpuBurst.push_back(15);
	cpuBurst.push_back(14);
	cpuBurst.push_back(5);
	cpuBurst.push_back(6);

	//ioTime.push_back(2);

	ioTime.push_back(33);
	ioTime.push_back(41);
	ioTime.push_back(65);
	ioTime.push_back(21);
	ioTime.push_back(61);
	ioTime.push_back(18);
	ioTime.push_back(26);
	ioTime.push_back(31);

	Process p3 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p3);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//Create process P4
	processName = "P4";

	cpuBurst.push_back(3);
	cpuBurst.push_back(4);
	cpuBurst.push_back(4);
	cpuBurst.push_back(3);
	cpuBurst.push_back(4);
	cpuBurst.push_back(3);
	cpuBurst.push_back(6);
	cpuBurst.push_back(5);
	cpuBurst.push_back(3);

	//ioTime.push_back(2);

	ioTime.push_back(35);
	ioTime.push_back(41);
	ioTime.push_back(45);
	ioTime.push_back(51);
	ioTime.push_back(61);
	ioTime.push_back(54);
	ioTime.push_back(82);
	ioTime.push_back(77);

	Process p4 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p4);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//Create process P5
	processName = "P5";

	cpuBurst.push_back(4);
	cpuBurst.push_back(5);
	cpuBurst.push_back(7);
	cpuBurst.push_back(12);
	cpuBurst.push_back(9);
	cpuBurst.push_back(4);
	cpuBurst.push_back(9);
	cpuBurst.push_back(7);
	cpuBurst.push_back(8);

	//ioTime.push_back(2);

	ioTime.push_back(48);
	ioTime.push_back(44);
	ioTime.push_back(42);
	ioTime.push_back(37);
	ioTime.push_back(46);
	ioTime.push_back(41);
	ioTime.push_back(31);
	ioTime.push_back(43);

	Process p5 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p5);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//Create process P6
	processName = "P6";

	cpuBurst.push_back(11);
	cpuBurst.push_back(4);
	cpuBurst.push_back(5);
	cpuBurst.push_back(6);
	cpuBurst.push_back(7);
	cpuBurst.push_back(9);
	cpuBurst.push_back(12);
	cpuBurst.push_back(15);
	cpuBurst.push_back(8);

	//ioTime.push_back(2);

	ioTime.push_back(22);
	ioTime.push_back(8);
	ioTime.push_back(10);
	ioTime.push_back(12);
	ioTime.push_back(14);
	ioTime.push_back(18);
	ioTime.push_back(24);
	ioTime.push_back(30);

	Process p6 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p6);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//Create process P7
	processName = "P7";

	cpuBurst.push_back(14);
	cpuBurst.push_back(17);
	cpuBurst.push_back(11);
	cpuBurst.push_back(15);
	cpuBurst.push_back(4);
	cpuBurst.push_back(7);
	cpuBurst.push_back(16);
	cpuBurst.push_back(10);

	//ioTime.push_back(2);

	ioTime.push_back(46);
	ioTime.push_back(41);
	ioTime.push_back(42);
	ioTime.push_back(21);
	ioTime.push_back(32);
	ioTime.push_back(19);
	ioTime.push_back(33);

	Process p7 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p7);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//Create process P8
	processName = "P8";

	cpuBurst.push_back(4);
	cpuBurst.push_back(5);
	cpuBurst.push_back(6);
	cpuBurst.push_back(14);
	cpuBurst.push_back(16);
	cpuBurst.push_back(6);
	cpuBurst.push_back(7);

	//ioTime.push_back(2);

	ioTime.push_back(14);
	ioTime.push_back(33);
	ioTime.push_back(51);
	ioTime.push_back(63);
	ioTime.push_back(87);
	ioTime.push_back(74);

	Process p8 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p8);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//Create process P9
	processName = "P9";

	cpuBurst.push_back(3);
	cpuBurst.push_back(9);
	cpuBurst.push_back(8);
	cpuBurst.push_back(4);
	cpuBurst.push_back(7);
	cpuBurst.push_back(5);
	cpuBurst.push_back(4);
	cpuBurst.push_back(5);
	cpuBurst.push_back(16);

	//ioTime.push_back(2);

	ioTime.push_back(37);
	ioTime.push_back(41);
	ioTime.push_back(30);
	ioTime.push_back(29);
	ioTime.push_back(33);
	ioTime.push_back(22);
	ioTime.push_back(24);
	ioTime.push_back(29);

	Process p9 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p9);

}

void IncrementWaitTime(ofstream& output, vector<Process>& processes) {
	for (unsigned int i = 0; i < processes.size(); i++) {
		if (processes[i].getState() == 1) {
			processes[i].setWaitTime(processes[i].getWaitTime() + 1 );
		}
	}
}

//Loads the processes into the ready queue
void LoadtoReadyQueue(Process * process, queue<Process*>& readyQueue) {
	(*process).setState(1);
	readyQueue.push(process);
}

//Loads the processes into the IOlist
void LoadtoIOlist(Process & process, vector<Process*>& IOlist) {
	process.setState(3); //sets running process state as blocking in I/O
	IOlist.push_back(&process);
}

//Find the index of the process with a state of 2, which indicates that that process is being executed in the CPU
//if no process is being executed in the CPU, then returns -1
int FindRunningProcessIndex(vector<Process> processes) {
	
	for (unsigned int i = 0; i < processes.size(); i++) {
		if (processes[i].getState() == 2) {
			return i; //returns index of running process
		}
	}
	return -1;
}

//decrements the CPU burst of the running process
void CpuBurstDecrement(vector<Process>& processes, int index) {
	int burstindex = processes[index].getCpuBurstIndex();
	int burst = (processes[index].getCpuBurst())[burstindex];
	processes[index].setCpuBurst(burstindex, burst - 1);
}

//decrements the remaining I/O time for the processes in the IOlist
void DecrementIO(vector<Process*> IOlist) {
	if (IOlist.size() > 0) {
		for (unsigned int i = 0; i < IOlist.size(); i++) {
			(*IOlist[i]).setIoTime(0 , (((*IOlist[i]).getIoTime())[0]) - 1);
		}
	}
}

//sorts the I/O list only when multiple processes have a remaining I/O time of 0 after being decremented
void SortIO(vector<Process*>& IOlist) {
	vector<Process*> unsorted;
	vector<int> index;

	for (unsigned int i = 0; i < IOlist.size(); i++) {
		if (((*IOlist[i]).getIoTime())[0] <= 0) {
			unsorted.push_back(IOlist[i]);
			index.push_back(i);
		}
	}
	sort(unsorted.begin(), unsorted.end());
	for (unsigned int i = 0; i < unsorted.size(); i++) {
		IOlist[index[i]] = unsorted[i];
	}
}

void PrintOutput(ofstream& output, queue<Process*> readyQueue, vector<Process*> IOlist, vector<Process>& processes, int runningProcessIndex, vector<string>& completed, int timeUnit, int done) {
	output << "Current Time: " << timeUnit << endl << endl;

	if (readyQueue.size() <= 0 && runningProcessIndex < 0) {
		//for debug purposes
		//output << "Current Process on the CPU: [idle]" << endl;
		output << "The Next Process On the CPU: [idle]" << endl;
	}

	else if (readyQueue.size() <= 0) {
		//for debug purposes
		//output << "Current Process on the CPU: " << processes[runningProcessIndex].getProcessName() << endl;
		output << "The Next Process On the CPU: [idle]" << endl;
	}

	else {
		//for debug purposes
		//output << "Current Process on the CPU: " << processes[runningProcessIndex].getProcessName() << endl;
		output << "The Next Process On the CPU: " << (*(readyQueue.front())).getProcessName() << endl;
	}

	output << "...................................." << endl << endl << endl;
	output << "List of Processes in the Ready Queue:" << endl << endl;
	output << "Process" << setw(10) << "Burst" << endl;
	PrintReadyQueue(output, readyQueue);

	output << "List of Processes in I/O:" << endl << endl;
	output << "Process" << setw(23) << "Remaining I/O Time" << endl;
	PrintIOlist(output, IOlist);

	if (done > 0) {
		output << "................." << endl << endl;
		output << "Completed: ";

		for (int i = 0; i < done; i++) {
			output << completed[i] << " ";
		}
		output << endl << endl;
	}
	output << "................." << endl;
	output << "................." << endl << endl << endl << endl;
}

//prints the process names and current cpu burst for that process in the ready queue
void PrintReadyQueue(ofstream& output, queue<Process*> readyQueue) {
	int count = readyQueue.size();
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			output << setw(5) << (*(readyQueue.front())).getProcessName() << setw(10) <<
				((*(readyQueue.front())).getCpuBurst())[0] << endl;
			readyQueue.pop();
		}
		output << endl << "................." << endl << endl << endl;
	}

	else { //no processes are in the readyQueue
		output << "     [empty]" << endl << endl;
		output << "................." << endl << endl << endl;
	}
}

//prints the process names and current cpu burst for that process in the IO list
void PrintIOlist(ofstream& output, vector<Process*> IOlist) {
	int count = IOlist.size();
	if (count > 0 ) {
		for (int i = 0; i < count; i++) {
			output << setw(5) << (*IOlist[i]).getProcessName() << setw(10) << ((*IOlist[i]).getIoTime())[0] << endl;
		}
	}

	else { //no processes are in IO
		output << "     [empty]" << endl << endl;
	}
}

//calculates CPU utilization, average waiting time, average turnaround times, average response times
//prints total time, waiting times, turnaround times, and response times, and the calculations
void Results(ofstream& output, vector<Process>& processes, int timeUnit, int idleTime, int context) {
	output << endl << endl << "The number of context switches are: " << context << endl;
	output << "The Total time is: " << timeUnit << endl << endl;
	output << "The idle time is: " << idleTime << endl;
	output << "Therefore, the CPU utilization is " << (((double)timeUnit - (double)idleTime) / (double)timeUnit) * 100 << "%";

	//wait times
	output << endl << endl << "Waiting Times:" << endl;
	for (unsigned int i = 0; i < processes.size(); i++) {
		output << "P" << i + 1 << ": " << processes[i].getWaitTime() << " ";
	}
	//average waiting time
	double avgwait = 0, totalwait = 0;
	for (unsigned int i = 0; i < processes.size(); i++) {
		totalwait += processes[i].getWaitTime();
	}
	avgwait = totalwait / 9;
	output << endl << "Average Waiting Time: " << avgwait;

	//turnaround times
	output << endl << endl << "Turnaround Times:" << endl;
	for (unsigned int i = 0; i < processes.size(); i++) {
		output << "P" << i + 1 << ": " << processes[i].getTurnAroundTime() << " ";
	}
	//average turnaround time
	double avgturn = 0, totalturn = 0;
	for (unsigned int i = 0; i < processes.size(); i++) {
		totalturn += processes[i].getTurnAroundTime();
	}
	avgturn = totalturn / 9;
	output << endl << "Average Turnaround Time: " << avgturn;

	//response times
	output << endl << endl << "Response Times:" << endl;
	for (unsigned int i = 0; i < processes.size(); i++) {
		output << "P" << i + 1 << ": " << processes[i].getResponseTime() << " ";
	}
	//average response time
	double avgres = 0, totalres = 0;
	for (unsigned int i = 0; i < processes.size(); i++) {
		totalres += processes[i].getResponseTime();
	}
	avgres = totalres / 9;
	output << endl << "Average Response Time: " << avgres;
}