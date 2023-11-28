#include <iostream>
using namespace std;

class Process{
    private:
        int pid;
        int priority;
        int arrivalTime;
        int burstTime;
        string type;
        int currentTime;

    public:

        // Process() : pid(0), priority(0), arrivalTime(0), burstTime(0), type("unknown"), currentTime(0) {}

        Process(int pid, int priority, int arrivalTime, int burstTime, string type)
        {
            this->pid = pid;
            this->priority = priority;
            this->arrivalTime = arrivalTime;
            this->burstTime = burstTime;
            this->type = type;
            this->currentTime = 0;
        }

        int getPid(){ return pid; }
        int getArrivalTime(){ return arrivalTime; }
        int getPriority(){ return priority; }
        int getBurstTime(){ return burstTime; }
        void setBurstTime(int burstTime){ this->burstTime = burstTime; }
        string getType(){ return type; }
        int getCurrentTime(){ return currentTime; }
        void setCurrentTime(int currentTime){ this->currentTime = currentTime; }
};

// PRIORITY QUEUE ACCORDING TO ARRIVAL TIME
class priority_queue{
    private:
        Process **heap;
        int size;
        int capacity;

    public:
        priority_queue(int capacity)
        {
            this->capacity = capacity;
            this->size = 0;
            this->heap = new Process*[capacity];
        }

    private:

        int parent(int i) { return (i - 1) / 2; }
        int leftChild(int i) { return 2 * i + 1; }
        int rightChild(int i) { return 2 * i + 2; }
        void swap(int i, int j) {
            Process *temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
        }

        void minHeapify(int i) {
            int left = leftChild(i);
            int right = rightChild(i);
            int smallest = i;
    
            if (left < size && heap[left]->getArrivalTime() < heap[i]->getArrivalTime())
                smallest = left;
            if (right < size && heap[right]->getArrivalTime() < heap[smallest]->getArrivalTime())
                smallest = right;
    
            if (smallest != i) {
                swap(i, smallest);
                minHeapify(smallest);
            }
        }
    
    public:

        void insert(Process *process)
        {
            if (size >= capacity) {
                cout << "Heap is full, cannot insert.";
                return;
            }

            size++;
            int i = size - 1;
            heap[i] = process;

            while (i != 0 && heap[parent(i)]->getArrivalTime() > heap[i]->getArrivalTime()) {
                swap(i, parent(i));
                i = parent(i);
            }
        }

        Process *extractMin()
        {
            if(size <= 0)
            {
                cout << "Heap is empty" << endl;
                return NULL; // might be an error at this return statement
            }
            
            if(size == 1)
            {
                size--;
                return heap[0];
            }

            Process *root = heap[0];
            heap[0] = heap[size-1];
            size--;
            minHeapify(0);

            return root;
        }

        Process *top(){ return heap[0];}
        bool isEmpty(){ if(size==0) return true; return false;}
        
};

// PRIORITY QUEUE ACCORDING TO PRIORITY NUMBER 
class priority_queue_pr{
    private:
        Process **heap;
        int size;
        int capacity;

    public:
        priority_queue_pr(int capacity)
        {
            this->capacity = capacity;
            this->size = 0;
            this->heap = new Process*[capacity];
        }

    private:

        int parent(int i) { return (i - 1) / 2; }
        int leftChild(int i) { return 2 * i + 1; }
        int rightChild(int i) { return 2 * i + 2; }
        void swap(int i, int j) {
            Process *temp = heap[i];
            heap[i] = heap[j];
            heap[j] = temp;
        }

        void minHeapify(int i) {
            int left = leftChild(i);
            int right = rightChild(i);
            int smallest = i;
    
            if (left < size && (heap[left]->getPriority() < heap[i]->getPriority() 
                || (heap[left]->getPriority() == heap[i]->getPriority() 
                && heap[left]->getArrivalTime() < heap[i]->getArrivalTime())))
                smallest = left;

            if (right < size && (heap[right]->getPriority() < heap[smallest]->getPriority() 
                || (heap[right]->getPriority() == heap[smallest]->getPriority()
                && heap[right]->getArrivalTime() < heap[smallest]->getArrivalTime())))
                smallest = right;
    
            if (smallest != i) {
                swap(i, smallest);
                minHeapify(smallest);
            }
        }
    
    public:

        void insert(Process *process)
        {
            if (size >= capacity) {
                cout << "Heap is full, cannot insert.";
                return;
            }

            size++;
            int i = size - 1;
            heap[i] = process;

            while (i != 0) {
                if (heap[parent(i)]->getPriority() > heap[i]->getPriority()
                    || (heap[parent(i)]->getPriority() == heap[i]->getPriority()
                    && heap[parent(i)]->getArrivalTime() > heap[i]->getArrivalTime())) {
                    swap(i, parent(i));
                    i = parent(i);
                } else {
                    break;
                }
            }
        }

        Process *extractMin()
        {
            if(size <= 0)
            {
                cout << "Heap is empty" << endl;
                return NULL; // might be an error at this return statement
            }
            
            if(size == 1)
            {
                size--;
                return heap[0];
            }

            Process *root = heap[0];
            heap[0] = heap[size-1];
            size--;
            minHeapify(0);

            return root;
        }

        Process *top(){ return heap[0];}
        bool isEmpty(){ if(size==0) return true; return false;}
        
};



class queue{
    private:
        int front;
        int rear;
        int size;
        int capacity;
        Process **Queue;

    public:
        queue(int capacity){
            this->capacity = capacity;
            this->front = this->size = 0;
            this->rear = capacity-1;
            this->Queue = new Process*[capacity];
        }

        bool isFull() { if(size==capacity) return true; return false;}
        bool isEmpty() { if(size == 0) return true; return false;}

        void enqueue(Process *process)
        {
            if(isFull())
            {
                cout << "Queue is full, cannot enqueue\n";
                return;
            }

            rear = (rear+1)%capacity;
            Queue[rear] = process;
            size++;
        }

        Process *dequeue()
        {
            if(isEmpty())
            {
                cout << "Queue is empty, cannot dequeue\n";
                NULL;
            }

            Process *process = Queue[front];
            front = (front+1)%capacity;
            size--;
            return process;
        }

        Process *Front()
        {
            if(isEmpty())
            {
                cout << "Queue is empty\n";
                return NULL;
            }
            return Queue[front];
        }

        void runForOneSec()
        {
            if(isEmpty())
            {
                cout << "Queue is empty, cannot run\n";
                return;
            }
            Queue[front]->setBurstTime(Queue[front]->getBurstTime()-1);
            Queue[front]->setCurrentTime(Queue[front]->getCurrentTime()+1);
        }
};
class GanttChart
{
    public:
        int pid;
        int startTime;
        int endtime;
        GanttChart *next;
    // private:
        GanttChart(int pid, int startTime,int endtime){
            this->pid = pid;
            this->startTime = startTime;
            this->endtime = endtime;
            this->next = NULL;
        }
};

GanttChart *chart = new GanttChart(-1,0,0);

void executeProcess(Process *process, int start_time, int end_time)
{
    chart->next = new GanttChart(process->getPid(), start_time, end_time);
    chart = chart->next;
}

void RoundRobin(queue *ready_queue, int &current_time, int turnaround_time[], int waiting_time[], int arrival_time[])
{
    int timeQuantum = 2;
    ready_queue->runForOneSec();
    Process *executingProcess = ready_queue->Front();
    int id = executingProcess->getPid()-1;
    int remainingBurstTime = executingProcess->getBurstTime();
    waiting_time[id] += (current_time - arrival_time[id]);

    if(remainingBurstTime == 0) // process has been executed
    {
        current_time += 1;
        // execute process
        executeProcess(executingProcess, current_time-1, current_time);
        ready_queue->dequeue();
        turnaround_time[id] = current_time - executingProcess->getArrivalTime();
    }
    else if(executingProcess->getCurrentTime() == timeQuantum)
    {
        current_time += 1;
        ready_queue->dequeue();
        ready_queue->enqueue(executingProcess);
        // execute process
        executeProcess(executingProcess, current_time-1, current_time);
        arrival_time[id] = current_time;
        executingProcess->setCurrentTime(0);
    }
    else
    {
        current_time += 1;
        // execute process
        executeProcess(executingProcess, current_time-1, current_time);
        arrival_time[id] = current_time;
    }
}

void FCFS_Scheduler(priority_queue *ready_queue, int &current_time, int turnaround_time[], int waiting_time[], int arrival_time[]){
    Process *process = ready_queue->extractMin();
    int remainingBurstTime = process->getBurstTime();
    int id = process->getPid() - 1;
    waiting_time[id] += (current_time - arrival_time[id]);
    if (remainingBurstTime <= 1) {
        current_time += 1;
        // execute process
        executeProcess(process, current_time-1, current_time);
        turnaround_time[id] = current_time - process->getArrivalTime();
    } else {
        current_time += 1;
        process->setBurstTime(remainingBurstTime - 1);
        ready_queue->insert(process);
        // execute process
        executeProcess(process, current_time-1, current_time);
        arrival_time[id] = current_time;
    }
}

void priority_scheduler(priority_queue_pr *ready_queue, int &current_time, int turnaround_time[], int waiting_time[], int arrival_time[]){
    Process *process = ready_queue->extractMin();
    int remainingBurstTime = process->getBurstTime();
    int id = process->getPid()-1;
    waiting_time[id] += (current_time - arrival_time[id]);
    if(remainingBurstTime <= 1)
    {
        current_time += 1;
        // execute process
        executeProcess(process, current_time-1, current_time);
        turnaround_time[id] = current_time - process->getArrivalTime();
    }
    else
    {
        current_time += 1;
        process->setBurstTime(remainingBurstTime-1);
        ready_queue->insert(process);
        // execute process 
        executeProcess(process, current_time-1, current_time);
        arrival_time[id] = current_time;
    }
}

string getTypeString(int type) {
    switch (type) {
        case 1:
            return "System";
        case 2:
            return "Interactive";
        case 3:
            return "Batch";
        default:
            return "Unknown";
    }
}

int main()
{
    cout << "Enter the number of processes: ";
    int num_of_processes; cin >> num_of_processes;

    // sets priority by arrival Time
    // priority_queue *arrivedProcesses(num_of_processes);
    priority_queue *arrivedProcesses = new priority_queue(num_of_processes);
    int turnaround_time[num_of_processes];
    int waiting_time[num_of_processes];
    int burstTime[num_of_processes];
    int arrival_Time[num_of_processes];
    int arrival_time_copy[num_of_processes];
    static int current_time = 0;

    priority_queue_pr *systemProcesses = new priority_queue_pr(num_of_processes);
    queue *interactiveProcesses = new queue(num_of_processes);
    priority_queue *batchProcesses = new priority_queue(num_of_processes);


    GanttChart *head = chart;
    // input at and wt of different processes

    for(int i=0; i<num_of_processes; i++)
    {
        cout << "\nEnter info of Process " << i+1 << "\n";
        cout << "Arrival Time: "; int at; cin >> at;
        cout << "Burst Time: "; int bt; cin >> bt;
        cout << "Type (1->System, 2->Interactive, 3->Batch): "; int type; cin >> type;
        cout << "Priority: "; int priority; cin >> priority;

        // create the object
        Process *process = new Process(i+1, priority, at, bt, getTypeString(type));
        arrivedProcesses->insert(process);
        arrival_Time[i] = at;
        arrival_time_copy[i] = at;
        burstTime[i] = bt;
        waiting_time[i] = 0;
        turnaround_time[i] = 0;
    }

    // static GanttChart *chart = new GanttChart(-1,0,0);

    // SCHEDULING
    cout << "EXECUTING...\n";

    while(!arrivedProcesses->isEmpty() || !systemProcesses->isEmpty() || !interactiveProcesses->isEmpty() || !batchProcesses->isEmpty())
    {
        while(!arrivedProcesses->isEmpty() && arrivedProcesses->top()->getArrivalTime() <= current_time)
        {
            Process *to_be_executed = arrivedProcesses->extractMin();
            if(to_be_executed->getType() == "System") systemProcesses->insert(to_be_executed);
            else if(to_be_executed->getType() == "Interactive") interactiveProcesses->enqueue(to_be_executed);
            else if(to_be_executed-> getType() == "Batch") batchProcesses->insert(to_be_executed);
        }

        if(!systemProcesses->isEmpty()) priority_scheduler(systemProcesses, current_time, turnaround_time, waiting_time, arrival_time_copy);
        else if(!interactiveProcesses->isEmpty()) RoundRobin(interactiveProcesses, current_time, turnaround_time, waiting_time, arrival_time_copy);
        else if(!batchProcesses->isEmpty()) FCFS_Scheduler(batchProcesses, current_time, turnaround_time, waiting_time, arrival_time_copy);
        else current_time ++;
    }

    
    chart = head->next;

    // SUMMARY
    cout << "PID\tAT\tBT\tWT\tTAT" << endl;
    double avg_wt = 0;
    double avg_tat = 0;
    for(int i=0; i<num_of_processes; i++)
    {
        printf("%2d\t%2d\t%2d\t%2d\t%2d\n", i+1, arrival_Time[i], burstTime[i], waiting_time[i], turnaround_time[i]);
        avg_wt += waiting_time[i];
        avg_tat += (turnaround_time[i]);
    }

    avg_wt /= num_of_processes;
    avg_tat /= num_of_processes;

    cout << ("GRANT CHART \n");
    cout << "0";
    int prev = 0;
    while (chart != NULL) {
        if (prev != chart->startTime) {
            cout << (" | IDLE");
            cout << (" | ");
            cout << (chart->startTime);
        }
        while (chart->next != NULL && chart->pid == chart->next->pid) {
            chart = chart->next;
        }
        cout << " | P";
        cout << chart->pid;
        cout << " | ";
        cout << chart->endtime;
        prev = chart->endtime;
        chart = chart->next;
    }

    cout << endl;
    cout << "Average waiting time : " << avg_wt << endl;
    cout << "Average turnaround time : " << avg_tat << endl;

}