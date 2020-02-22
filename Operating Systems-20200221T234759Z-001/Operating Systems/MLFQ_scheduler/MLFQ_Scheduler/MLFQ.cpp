//In this program, FCFS' method of implementation became very complicated and 
//is not efficient for MLFQ, so I redefined process and its initialization.
//Furthermore, for MLFQ, I stored the data in a single list instead of two separate vectors.
//I did this because it's easier to manipulate a single object instead of two vectors.
//Thus, whenever the item in the list becomes 0, it alternates betweeen decrementing the CPU burst when the process is executing
//and decrementing when the process is in I/O.


#include <iostream>
#include <fstream>
#include <cstdlib>
#include <queue>
#include <initializer_list>
#include <vector>
#include <iomanip>
#include <string>


using namespace std;

class process {
private:
	queue<int> bursts; //CPU and IO bursts are kept in a queue
public:
	process() {}; //default constructor
	explicit process(initializer_list<int> t) : bursts(t) {}

	//get size of burst list
	int size() {
		return bursts.size();
	}
	//returns burst value in front of the list
	int front() {
		return bursts.front();
	}
	//check if burst is empty
	bool done() {
		return bursts.empty();
	}
	//decrement burst
	bool decrement() {
		if ((--bursts.front()) == 0) {    //if current burst is now 0
			bursts.pop();    //remove the burst
			return true;    //returns true if the burst is done
		}
		return false; //otherwise, the burst is not done
	}
	string id;    //id for printing output
	int responseTime = -1;    //how long it takes to start
	int waitingTime = 0;    //how long it waits
	int turnaroundTime = 0; //how long it takes to finish
	int lastInstruction = 0; //used to calculate waitingTime
	int quantum = -1;    //number of time quantums for the process
	int level = -1; //keep track of priority level; this is also used as in index, so 0 = queue1, 1 = queue2, 2 = queue3
	int state = 0; //0 = not admitted, 1 = waiting, 2 = executing, 3 = blocking (I/O), 4 = completed

};

void MLFQ(ofstream& output, vector<process*> processes);
process* FindRunningProcessAddress(vector<deque<process*>> processes);
void PrintOutput(ofstream& output, vector<deque<process*>> queue, vector<process*> IOlist, process* running, int timeUnit, bool preempt);
void PrintReadyQueue(ofstream& output, vector<deque<process*>> queue);
void PrintIOlist(ofstream& output, vector<process*> IOlist);


int main() {

	//initialize variables
	ofstream output;
output.open("MLFQ_output.txt");

//Initialize the processes
process P1{ 4, 27, 3, 31, 2, 43, 4, 18, 4, 22, 4, 26, 3, 24, 4 };
process P2{ 16, 24, 17, 21, 5, 36, 16, 26, 7, 31, 13, 28, 11, 21, 6, 13, 3, 11, 4 };
process P3{ 8, 33, 12, 41, 18, 65, 14, 21, 4, 61, 15, 18, 14, 26, 5, 31, 6 };
process P4{ 3, 35, 4, 41, 4, 45, 3, 51, 4, 61, 3, 54, 6, 82, 5, 77, 3 };
process P5{ 4, 48, 5, 44, 7, 42, 12, 37, 9, 46, 4, 41, 9, 31, 7, 43, 8 };
process P6{ 11, 22, 4, 8, 5, 10, 6, 12, 7, 14, 9, 18, 12, 24, 15, 30, 8 };
process P7{ 14, 46, 17, 41, 11, 42, 15, 21, 4, 32, 7, 19, 16, 33, 10 };
process P8{ 4, 14, 5, 33, 6, 51, 14, 63, 16, 87,6, 74, 7 };
process P9{ 3, 37, 9, 41, 8, 30, 4, 29, 7, 33, 5, 22, 4, 24, 5, 29, 16 };
vector<process*> processes{ &P1, &P2, &P3, &P4, &P5, &P6, &P7, &P8, &P9 };
P1.id = "P1";
P2.id = "P2";
P3.id = "P3";
P4.id = "P4";
P5.id = "P5";
P6.id = "P6";
P7.id = "P7";
P8.id = "P8";
P9.id = "P9";

MLFQ(output, processes);
cout << endl << "Finished" << endl;

output.close();
return 0;
}

void MLFQ(ofstream& output, vector<process*> processes) {
	deque<process*> queue1; //RR TQ = 4
	deque<process*> queue2; //RR TQ = 9
	deque<process*> queue3; //FCFS
	vector<deque<process*>> queue = { queue1, queue2, queue3 };
	vector<process*> IOlist;
	process* running = NULL; //points to running process, using a pointer instead of an index (in FCFS implementation)
							 //because the processes are split up into different queues
	int timeUnit = 0; //current time unit
	int cpuTime = 0; //used to calculate CPU utilization
					 //did not use idle time to calculate CPU utilization because it becomes more complicated to implement because the processes
					 //are split up into different queues
	bool preempt = false; //indicate if preemption occurs

	//load processes into the queue
	for (unsigned i = 0; i < processes.size(); i++) {
		//Place processes into the first queue with proper level and quantum
		processes[i]->level = 0;
		processes[i]->quantum = 4;
		processes[i]->state = 1;
		queue[0].push_back(processes[i]);
	}
	queue[0][0]->state = 2;
	running = queue[0][0];
	PrintOutput(output, queue, IOlist, running, timeUnit, preempt);

	//Scheduling code
	//Condition: Any queue that is nonempty
	//Implied Condition: If all of the queues are empty, then all of the processes are completed
	while ((!queue[0].empty()) || (!queue[1].empty()) || (!queue[2].empty()) || (!IOlist.empty())) {
		timeUnit++; //increment time at the end
		preempt = false;

		//If IOlist is not empty, decrement the remaining I/O times
		if (!IOlist.empty()) {
			for (unsigned i = 0; i < IOlist.size(); i++) {    //decrement i/o time
				bool ioBurstComplete = IOlist[i]->decrement();
				if (ioBurstComplete) { //if done with IO
					IOlist[i]->lastInstruction = timeUnit + 1; //set lastInstruction as time the process enters back into the queue
															   //IOlist[i]->lastInstruction = time; //set lastInstruction as time the process enters back into the queue
					if (IOlist[i]->done()) {
						IOlist[i]->turnaroundTime = timeUnit + 1;
						//IOlist[i]->turnaroundTime = time;
					}
					else {

						if (IOlist[i]->level == 0) {
							IOlist[i]->quantum = 4;
						}

						else if (IOlist[i]->level == 1) {
							IOlist[i]->quantum = 9;
						}

						IOlist[i]->state = 1;
						queue[IOlist[i]->level].push_back(IOlist[i]); //use level value to determine which queue to put it back into
					}

					//preemption
					//find running address, if a process enters in the queue with a higher priority than running process
					//the current running process then leaves the queue and reenters the queue in the back
					if (IOlist[i]->level < running->level) {
						running->state = 1;
						queue[running->level].pop_front();
						queue[running->level].push_back(running);
						running = NULL;
						preempt = true;
					}
						IOlist.erase(IOlist.begin() + i);
						i--;

				}
			}
		}
		

		bool cpuBurstComplete = false; //reset the cpuBurstComplete to false by default

		running = FindRunningProcessAddress(queue);

		if (running != NULL) { //if a process is running


			//If queue1 is not empty, schedule for queue1
			if (running->level == 0) { //if first queue is not empty

				if (!queue[1].empty()) {    //if queue2 is not empty, reset the process' time quantum to 9
					queue[1][0]->quantum = 9;
				}

				if (queue[0].size() > 1) {
					queue[0][1]->quantum = 4; //reset the time quantum for next process in the queue
				}

				if (running->responseTime == -1) { //set response time if the process hasn't run yet
					running->responseTime = timeUnit - 1;
				}
				running->waitingTime += timeUnit - running->lastInstruction; //increment waiting time based on last time it was on the CPU
				running->lastInstruction = timeUnit + 1;

				cpuBurstComplete = running->decrement(); //decrement running and return if the process is complete
				running->quantum--; //decrement the quantum

									//Condition: process' quantum equals 0 and its CPU burst did not finish, only time when the process downgrades
				if ((!cpuBurstComplete) && (running->quantum == 0)) { //if quantum equals 0 without finishing the CPU burst, 
																	  //downgrade the process to a lower level priority queue
					running->level = 1;
					running->quantum = 9;
					running->state = 1;
					queue[1].push_back(running); //add the running process to queue2
					queue[0].pop_front(); //remove the running process from queue1

					//find running address
					if (!queue[0].empty()) {
						running = queue[0][0];
						running->state = 2;
					}
					else if (!queue[1].empty()) {
						running = queue[1][0];
						running->state = 2;
					}
					else if (!queue[2].empty()) {
						running = queue[2][0];
						running->state = 2;
					}
					running = FindRunningProcessAddress(queue);

					//if (!queue[(running->level) - 1].empty()) {
					//	running = queue[running->level - 1].front();
					//}

					//else {
					//	running = queue[(running->level)].front();
					//}

					//PrintOutput(output, queue, running, timeUnit);

				}
				cpuTime++; //increments cpuTime since a process in queue1 was running in this unit of time
			}
			//If queue1 is empty, schedule for queue2
			else if (running->level == 1) {

				if (running->responseTime == -1) {    //set response time if the process hasnt run yet
					running->responseTime = timeUnit;
				}
				running->waitingTime += timeUnit - running->lastInstruction;
				running->lastInstruction = timeUnit + 1;

				cpuBurstComplete = running->decrement();   	 //decrement running
				running->quantum--;
				if ((!cpuBurstComplete) && (running->quantum == 0)) { //if quantum runs out without finishing burst, shift to next queue
					running->level = 2;
					running->state = 1;
					queue[2].push_back(running);
					queue[1].pop_front();

					//find running address
					if (!queue[0].empty()) {
						running = queue[0][0];
						running->state = 2;
					}
					else if (!queue[1].empty()) {
						running = queue[1][0];
						running->state = 2;
					}
					else if (!queue[2].empty()) {
						running = queue[2][0];
						running->state = 2;
					}
					running = FindRunningProcessAddress(queue);
				}
				cpuTime++; //increments cpuTime since a process in queue2 was running in this unit of time
			}
			//If queue2 is empty, schedule for queue3
			else if (running->level == 2) {

				if (running->responseTime == -1) { //set response time if the process hasnt run yet
					running->responseTime = timeUnit;
				}
				running->waitingTime += timeUnit - running->lastInstruction;
				running->lastInstruction = timeUnit + 1;
				cpuBurstComplete = running->decrement();   	 //decrement running
				cpuTime++; //increments cpuTime since a process in queue3 was running in this unit of time
			}
		}

		//if running state is null, check to see if there are any processes in any of the queues
		else if (running == NULL) {
			if (!queue[0].empty()) {
				running = queue[0][0];
				running->state = 2;
			}
			else if (!queue[1].empty()) {
				running = queue[1][0];
				running->state = 2;
			}
			else if (!queue[2].empty()) {
				running = queue[2][0];
				running->state = 2;
			}
		}

		//if the process is complete
		if (cpuBurstComplete) {

			if (running->done()) { //the process is complete
				running->turnaroundTime = timeUnit + 1;
				//cout << endl << "Process " << running->id << " finished at time " << timeUnit << endl;
			}
			else { //send the process to I/O
				running->state = 3;
				IOlist.push_back(running);
			}
			queue[running->level].pop_front(); //remove the process from the queue

			//check if any of the queues are empty
			if (!queue[0].empty()) {
				running = queue[0][0];
				running->state = 2;
			}
			else if (!queue[1].empty()) {
				running = queue[1][0];
				running->state = 2;
			}
			else if (!queue[2].empty()) {
				running = queue[2][0];
				running->state = 2;
			}

			running = FindRunningProcessAddress(queue);
		}

		else {
			//PrintOutput(output, queue, running, timeUnit);
		}


		PrintOutput(output, queue, IOlist, running,  timeUnit, preempt);
	}

}

//finds pointer to running process
process* FindRunningProcessAddress(vector<deque<process*>> processes) {

	for (unsigned int i = 0; i < processes.size(); i++) {
		if (!processes[i].empty()) {
			if (processes[i][0]->state == 2) {
				return processes[i][0]; //returns index of running process
			}
		}
	}
	return NULL;
}

void PrintOutput(ofstream& output, vector<deque<process*>> queue, vector<process*> IOlist, process* running, int timeUnit, bool preempt) {
	output << "Current Time: " << timeUnit << endl << endl;

	if (running != NULL) {
		output << "Current Process on the CPU: " << (running)->id << endl;
	}

	else {
		output << "Current Process on the CPU: [idle]" << endl;
	}

	//Checks for the first queue that's not empty and prints that process as the next process on the CPU
	if (((!queue[0].empty()) || (!queue[1].empty()) || (!queue[2].empty())) && preempt == false ) {

		if (!queue[0].empty() && (queue[0].size() > 1)) {
			output << "The Next Process on the CPU: " << ((queue[0][1]))->id << endl;
		}
		else if (!queue[1].empty() && (queue[1].size()) > 1) {
			output << "The Next Process on the CPU: " << ((queue[1][1]))->id << endl;
		}
		else if (!queue[2].empty() && (queue[2].size()) > 1) {
			output << "The Next Process on the CPU: " << ((queue[2][1]))->id << endl;
		}

		else {
			output << "The Next Process on the CPU: [idle]" << endl;
		}
	}

	else if (((!queue[0].empty()) || (!queue[1].empty()) || (!queue[2].empty())) && preempt == true) {
		if (!queue[0].empty() && (queue[0].size() > 1)) {
			output << "The Next Process on the CPU: " << ((queue[0][0]))->id << endl;
		}
		else if (!queue[1].empty() && (queue[1].size()) > 1) {
			output << "The Next Process on the CPU: " << ((queue[1][0]))->id << endl;
		}
		else if (!queue[2].empty() && (queue[2].size()) > 1) {
			output << "The Next Process on the CPU: " << ((queue[2][0]))->id << endl;
		}

		else {
			output << "The Next Process on the CPU: [idle]" << endl;
		}
	}

		output << "...................................." << endl << endl << endl;
		output << "List of Processes in the Ready Queue:" << endl << endl;
		output << "Process" << setw(10) << "Burst" << setw(10) << "Priority level" <<endl;
		PrintReadyQueue(output, queue);

		output << "List of Processes in I/O:" << endl << endl;
		output << "Process" << setw(23) << "Remaining I/O Time" << endl;
		PrintIOlist(output, IOlist);
	
	output << "................." << endl;
	output << "................." << endl << endl << endl << endl;
}

//prints the process names and current cpu burst for that process in the ready queue
void PrintReadyQueue(ofstream& output, vector<deque<process*>> queue) {
	int count = queue.size();
	if (count > 0) {
		for (int i = 0; i < count; i++) {
			if (!queue[i].empty()) {
				for (unsigned int j = 0; j < queue[i].size(); j++ ) {
					if (queue[i][j]->state == 1) {
						output << setw(5) << queue[i][j]->id << setw(10) << (*queue[i][j]).front() << setw(10) << (queue[i][j]->level)+1 << endl;
					}
				}
			}
		}
		output << endl << "................." << endl << endl << endl;
	}

	else { //no processes are in the readyQueue
		output << "     [empty]" << endl << endl;
		output << "................." << endl << endl << endl;
	}
}

//prints the process names and current cpu burst for that process in the IO list
void PrintIOlist(ofstream& output, vector<process*> IOlist) {
	int count = IOlist.size();
	if (count > 0) {

		for (int i = 0; i < count; i++) {
			output << setw(5) << IOlist[i]->id << setw(10) << (*IOlist[i]).front() << endl;
		}
	}

	else { //no processes are in IO
		output << "     [empty]" << endl << endl;
	}
}