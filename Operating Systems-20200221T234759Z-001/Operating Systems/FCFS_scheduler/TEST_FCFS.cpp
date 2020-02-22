/*

#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;
//uptodate

//class structure called Process which contains all of the necessary information for a process
//the cpu bursts and ioTime will be stored as a queue rather than an array
class Process {
public:
	//constructors
	Process (string, vector<int>, int, vector<int>, int, int, int, int, int);
	
	//destructor
	~Process ();

	//accessor functions
	string getProcessName ();
	vector<int> getCpuBurst ();
	int getCpuBurstIndex();
	int getCpuBurstSize();
	vector<int> getIoTime ();
	int getIoIndex();
	int getIoSize();
	int getWaitTime ();
	int getResponseTime ();
	int getTurnAroundTime ();
	int getState ();

	//mutator functions
	void setProcessName (string);
	void setCpuBurst (int, int);
	void setCpuBurstIndex(int);
	void setIoTime (int, int);
	void setIoIndex(int);
	void setWaitTime (int);
	void setResponseTime (int);
	void setTurnAroundTime (int);
	void setState (int);

	//operator overloading functions
	friend ostream& operator<<(ostream& os, Process& result);
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
string Process::getProcessName () {
	return newProcessName;
}
vector<int> Process::getCpuBurst () {
	return newCpuBurst;
}
int Process::getCpuBurstIndex() {
	return newCpuBurstIndex;
}
int Process::getCpuBurstSize() {
	return newCpuBurst.size();
}
vector<int> Process::getIoTime () {
	return newIoTime;
}
int Process::getIoIndex() {
	return newIoIndex;
}
int Process::getIoSize() {
	return newIoTime.size();
}
int Process::getWaitTime () {
	return newWaitTime;
}
int Process::getResponseTime () {
	return newResponseTime;
}
int Process::getTurnAroundTime () {
	return newTurnAroundTime;
}
int Process::getState () {
	return newState;
}

//mutator functions
void Process::setProcessName (string processName) {
	newProcessName = processName;
}
void Process::setCpuBurst (int index, int value) {
	newCpuBurst[index] = value;
}
void Process::setCpuBurstIndex(int CpuBurstIndex) {
	newCpuBurstIndex = CpuBurstIndex;
}
void Process::setIoTime (int index, int value) {

	newIoTime[index] = value;
}
void Process::setIoIndex(int IoIndex) {
	newIoIndex = IoIndex;
}
void Process::setWaitTime (int waitTime) {
	newWaitTime = waitTime;
}
void Process::setResponseTime (int responseTime) {
	newResponseTime = responseTime;
}
void Process::setTurnAroundTime (int turnAroundTime) {
	newTurnAroundTime = turnAroundTime;
}
void Process::setState (int state) {
	newState = state;
}

//overload constructor
Process::Process (string processName, vector<int> cpuBurst, int CpuBurstIndex, vector<int> ioTime, int IoIndex, int waitTime, int responseTime,
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
}

//needs edited
//Overloading << operator
ostream &operator<< (ostream& os, Process& result) {
	os << result.getCpuBurst().front();
	return os;
}

//Function Prototypes
void InitializeProcesses(vector<Process>& processes, queue<Process>& readyQueue, Process runningProcess, vector<Process>& IOlist);
void LoadtoReadyQueue(Process & process, queue<Process>& readyQueue);
void DecrementCpuBurst(Process& runningprocess);
void DecrementIOlist(vector<Process>& IOlist, queue<Process>& readyQueue);
void LoadtoIOlist(Process & process, vector<Process>& IOlist);
void PrintReadyQueue(queue<Process> readyQueue);
void PrintIOlist(vector<Process> IOlist);
void PrintOutput(queue<Process> readyQueue, vector<Process> IOlist, Process runningProcess, int i);


//main driver
int main() {

	//declare variables
	vector<Process> processes;
	queue<Process> readyQueue; //ready queue will be a queue that contains the addresses of the processes waiting for CPU time
	vector<Process> IOlist; //vector of processes that are blocking in I/O
	Process runningProcess = { "", {0}, 0, {0}, 0, 0, 0, 0, 0 }; //points to current running process
	bool done; //boolean value that indicates whether all of the processes are  completed

	//help format the output
	cout.setf(ios::right);
	cout.setf(ios::fixed);

	InitializeProcesses(processes, readyQueue, runningProcess, IOlist);

	//for loop that runs the FCFS scheduling algorithm for each time unit
	for (int i = 1; i < 50; i++) {
		//decrements processes remaining IO time in the IOlist
		DecrementIOlist(IOlist, readyQueue);
	
		//checks if ready queue has processes that are waiting and if running process is running a process
		//if the running process is not, then the next process on the ready queue becomes a running process
		if (readyQueue.size() > 0 && runningProcess.getProcessName() == "") {
			runningProcess = readyQueue.front();
			runningProcess.setState(2);
			readyQueue.pop();
		}

		else if(readyQueue.size() == 0) {
			runningProcess = {"",{ 0 }, 0,{ 0 }, 0, 0, 0, 0, 0 };
		}

		if (runningProcess.getProcessName() != "") {
			//decrements running process CPU burst time
			DecrementCpuBurst(runningProcess);

			//if running process completes CPUBurst, send it to IO
			//then increment the running process' cpu burst index
			//then assign the next process in the ready queue to runningProcess
			if ((runningProcess).getCpuBurst()[(runningProcess).getCpuBurstIndex()] <= 0 &&
				((runningProcess).getIoIndex() < ((runningProcess).getIoSize()) - 1)) {
				
				(runningProcess).setCpuBurstIndex( ((runningProcess).getCpuBurstIndex()) + 1); //increments the cpu burst index
				LoadtoIOlist(runningProcess, IOlist); //this function also changes the state of the running process to 3
				runningProcess = (readyQueue.front()); //loads next process on the ready queue to running process
				runningProcess.setState(2);
				readyQueue.pop();
			}

			//if the IO index is equal to the size of the IO vector - 1 and the remaining Cpu burst is 0,
			//then that means the running process is completed
			else if ((runningProcess).getCpuBurst()[(runningProcess).getCpuBurstIndex()] <= 0 &&
				((runningProcess).getIoIndex() == ((runningProcess).getIoSize()) - 1) ) {
				(runningProcess).setState(4);
			}


		}

		PrintOutput(readyQueue, IOlist, runningProcess, i);
	}


	return 0;
}

//Initializes the processes
//The data is hard coded and provided by the assignment
//The processes are initialized at time unit 0
//The processes will be stored in a process vector instead of an array for general purposes
void InitializeProcesses(vector<Process>& processes, queue<Process>& readyQueue, Process runningProcess, vector<Process>& IOlist) {
	//Create process p1
	string processName = "p1";
	vector<int> cpuBurst;
	cpuBurst.push_back(4);
	cpuBurst.push_back(3);
	cpuBurst.push_back(2);
	cpuBurst.push_back(4);
	cpuBurst.push_back(4);
	cpuBurst.push_back(4);
	cpuBurst.push_back(3);
	cpuBurst.push_back(4);

	vector<int> ioTime;
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
	int responseTime = 0;
	int turnAroundTime = 0;
	int state = 0;

	Process p1 = { processName, cpuBurst, CpuBurstIndex, ioTime, IoIndex, waitTime, responseTime,
		turnAroundTime, state };
	processes.push_back(p1);

	//empty the queues for to initialize the next process
	cpuBurst.clear();
	ioTime.clear();

	//create process p2
	processName = "p2";
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

	ioTime;
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

	//create process p3
	processName = "p3";
	cpuBurst.push_back(8);
	cpuBurst.push_back(12);
	cpuBurst.push_back(18);
	cpuBurst.push_back(14);
	cpuBurst.push_back(4);
	cpuBurst.push_back(15);
	cpuBurst.push_back(14);
	cpuBurst.push_back(5);
	cpuBurst.push_back(6);

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

	//create process p4
	processName = "p4";
	cpuBurst.push_back(3);
	cpuBurst.push_back(4);
	cpuBurst.push_back(4);
	cpuBurst.push_back(3);
	cpuBurst.push_back(4);
	cpuBurst.push_back(3);
	cpuBurst.push_back(6);
	cpuBurst.push_back(5);
	cpuBurst.push_back(3);

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

	//create process p5
	processName = "p5";
	cpuBurst.push_back(4);
	cpuBurst.push_back(5);
	cpuBurst.push_back(7);
	cpuBurst.push_back(12);
	cpuBurst.push_back(9);
	cpuBurst.push_back(4);
	cpuBurst.push_back(9);
	cpuBurst.push_back(7);
	cpuBurst.push_back(8);

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

	//create process p6
	processName = "p6";
	cpuBurst.push_back(11);
	cpuBurst.push_back(4);
	cpuBurst.push_back(5);
	cpuBurst.push_back(6);
	cpuBurst.push_back(7);
	cpuBurst.push_back(9);
	cpuBurst.push_back(12);
	cpuBurst.push_back(15);
	cpuBurst.push_back(8);

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

	//create process p7
	processName = "p7";
	cpuBurst.push_back(14);
	cpuBurst.push_back(17);
	cpuBurst.push_back(11);
	cpuBurst.push_back(15);
	cpuBurst.push_back(4);
	cpuBurst.push_back(7);
	cpuBurst.push_back(16);
	cpuBurst.push_back(10);

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

	//create process p8
	processName = "p8";
	cpuBurst.push_back(4);
	cpuBurst.push_back(5);
	cpuBurst.push_back(6);
	cpuBurst.push_back(14);
	cpuBurst.push_back(16);
	cpuBurst.push_back(6);
	cpuBurst.push_back(7);

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

	//create process p9
	processName = "p9";
	cpuBurst.push_back(3);
	cpuBurst.push_back(9);
	cpuBurst.push_back(8);
	cpuBurst.push_back(4);
	cpuBurst.push_back(7);
	cpuBurst.push_back(5);
	cpuBurst.push_back(4);
	cpuBurst.push_back(5);
	cpuBurst.push_back(16);

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


	//At time unit 0, all  nine of the processes enter the ready queue
	for (int i = 0; i < 9; i++) {
		LoadtoReadyQueue(processes[i], readyQueue);
	}

	PrintOutput(readyQueue, IOlist, runningProcess, 0);

}

//Loads the processes into the ready queue
void LoadtoReadyQueue(Process & process, queue<Process>& readyQueue) {
	process.setState(1);
	readyQueue.push(process);
}

//Decrements CPU Burst time for the process executing in the CPU
void DecrementCpuBurst(Process& runningprocess) {

	if (runningprocess.getProcessName() != "") {
		int burstIndex = (runningprocess).getCpuBurstIndex();
		int burstTime = (runningprocess).getCpuBurst()[burstIndex];
		(runningprocess).setCpuBurst(burstIndex, burstTime - 1);
	}
}

//Decrements remaining IO time for processes in the IO list
void DecrementIOlist(vector<Process>& IOlist, queue<Process>& readyQueue) {
	if (IOlist.size() > 0) {
		int count = IOlist.size();
		int IOtime, index;
		for (int i = 0; i < count; i++) {
			index = IOlist[i].getIoIndex();
			IOtime = ((IOlist[i].getIoTime())[index]) - 1;
			IOlist[i].setIoTime(index, IOtime);

			//check if process finishes IO and needs to go back to ready queue
			//if process in I/O completes remaining I/O time, it gets loaded back into the ready queue in the same unit of time
			if (IOtime <= 0) { //size of I/O vector, not 10
				if (index != IOlist[i].getIoSize() - 1) {
					IOlist[i].setIoIndex(index + 1);
				}
				LoadtoReadyQueue(IOlist[i], readyQueue);
				IOlist.erase(IOlist.begin() + i); //being + index
			}
		}
	}
}

//Loads the processes into the IOlist
void LoadtoIOlist(Process & process, vector<Process>& IOlist) {
	process.setState(3);
	IOlist.push_back(process);
}

//prints the process names and current cpu burst for that process in the ready queue
void PrintReadyQueue(queue<Process> readyQueue) {
	int count = readyQueue.size();
	for (int i = 0; i < count; i++) {
		cout << setw(5) << (readyQueue.front()).getProcessName() << setw(10) << ((readyQueue.front()).getCpuBurst())[(readyQueue.front()).getCpuBurstIndex()] << endl;
		readyQueue.pop();
	}
	cout << "................." << endl << endl << endl;
}

//prints the process names and current cpu burst for that process in the IO list
void PrintIOlist(vector<Process> IOlist) {
	int count = IOlist.size();
	int IOindex;
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			IOindex = IOlist[i].getIoIndex();
			cout << setw(5) << IOlist[i].getProcessName() << setw(10) << (IOlist[i].getIoTime())[IOindex] << endl;
		}
		cout << "................." << endl;
		cout << "................." << endl << endl << endl << endl;
	}

	else { //no processes are in IO
		cout << "     [empty]" << endl << endl;
		cout << "................." << endl;
		cout << "................." << endl << endl << endl << endl;
	}
}

void PrintOutput(queue<Process> readyQueue, vector<Process> IOlist, Process runningProcess, int i) {
	if (i == 0) {
		cout << "Current Time: " << i << endl << endl;
		cout << "The Next Process On the CPU: " << (readyQueue.front()).getProcessName() << endl;
		cout << "..............................." << endl << endl;

		cout << "List of Processes in the Ready Queue:" << endl << endl;
		cout << "Process" << setw(10) << "Burst" << endl;
		PrintReadyQueue(readyQueue);

		cout << "List of Processes in I/O:" << endl << endl;
		cout << "Process" << setw(23) << "Remaining I/O Time" << endl;
		PrintIOlist(IOlist);
	}

	else {
		cout << "Current Time: " << i << endl << endl;
		cout << "The Next Process On the CPU: " << (readyQueue.front()).getProcessName() << endl;
		cout << "..............................." << endl << endl;

		cout << "List of Processes in the Ready Queue:" << endl << endl;
		cout << "Process" << setw(10) << "Burst" << endl;
		PrintReadyQueue(readyQueue);

		cout << "List of Processes in I/O:" << endl << endl;
		cout << "Process" << setw(23) << "Remaining I/O Time" << endl;
		PrintIOlist(IOlist);
	}
}

*/

