import java.util.*;
public class cpu_sched {

    // SJF
    private int [] sjf_ct;
    private int [] sjf_wt;
    private int [] sjf_tat;

    // PRIORITY
    private int [] priority_wt;
    private int [] priority_tat;
    private int [] pr;

    // Round Robin
    // private int [] rr_wt;
    // private int [] rr_tat;

    
    // constructor
    public cpu_sched(int P)
    {
        sjf_ct = new int[P];
        sjf_wt = new int[P];
        sjf_tat = new int[P];
        
        pr = new int[P];
        priority_wt = new int[P];
        priority_tat = new int[P];

        // rr_wt = new int[P];
        // rr_tat = new int[P];

    }

    public void SJF(int arrivalTime[], int burstTime[], int pid[], int P)
    {
    
        int [] executed = new int[P];
        for(int x=0; x<P; x++) executed[x] = 0;

        int iter = 0; // to keep the count of number of processes that have been executed
        int start_time = 0; // control variable

        System.out.print("\n\t\tNon Preemptive SJF\n");

        System.out.println("\n\tGantt Chart ");
        System.out.print("\t");

        while(true)
        {
            if(iter == P) break; // all the processes have been executed

            int minP = P;
            int min = Integer.MAX_VALUE;

            // to find which process will be executed next
            for(int i=0; i<P; i++)
            {
                if((arrivalTime[i] <= start_time) && (executed[i] == 0) && (burstTime[i] < min))
                {
                    min = burstTime[i];
                    minP = i;
                } 
            }

            if(minP == P) start_time++; // no process is there in ready queue;
            else
            {
                sjf_ct[minP] = start_time + burstTime[minP];
                sjf_tat[minP] = sjf_ct[minP] - arrivalTime[minP];
                // sjf_wt[minP] = sjf_tat[minP] - burstTime[minP];
                sjf_wt[minP] = start_time - arrivalTime[minP];
                
                System.out.print("| " + start_time + " |");
                System.out.print(" P[" + (minP+1) + "] ");

                executed[minP] = 1;
                start_time+=burstTime[minP];
                iter++;
            }

        }
        System.out.print("| " + start_time + " |");

        float avg_wt = 0;
        float avg_tat = 0;
        for(int i=0; i<P; i++)
        {
            avg_tat += sjf_tat[i];
            avg_wt += sjf_wt[i];
        }
        avg_tat = (float)(avg_tat/P);
        avg_wt = (float)(avg_wt/P);


        System.out.print("\n\n\t");
        for(int i=0; i<38; i++) System.out.print("_");

        System.out.println("\n\tProcess\t AT\t BT\t WT\t TAT");
        System.out.print("\t");

        for(int i=0; i<38; i++) System.out.print("_");

        for(int i=0; i<P; i++)
        {
            System.out.printf("\n\t%3d", pid[i]);
            System.out.printf("\t%3d", arrivalTime[i]);
            System.out.printf("\t%3d", burstTime[i]);
            System.out.printf("\t%3d", sjf_wt[i]);
            System.out.printf("\t%3d", sjf_tat[i]);
            // System.out.printf("\t%3d", sjf_ct[i]);
        }

        System.out.println("");
        System.out.print("\t");

        for(int i=0; i<38; i++) System.out.print("_");
        System.out.println("\t");

        System.out.println("\n\tAverage turnaround time is " + avg_tat);
        System.out.println("\tAverage waiting time is " + avg_wt);
    }

    // PRIORITY SCHEDULING
    
    public void priority(int arrivalTime[], int burstTime[], int pid[], int P)
    {
        System.out.print("\n\t\tPreemptive Priority\n");

        Scanner sc = new Scanner(System.in);
        System.out.println("\nEnter the priorities of the processes ");
        for(int i=0; i<P; i++)
        {
            System.out.print("Process " + pid[i] + " : ");
            pr[i] = sc.nextInt();
        }
        sc.close();

        int [] burstTime_copy = new int[P];
        for(int i=0; i<P; i++) burstTime_copy[i] = burstTime[i];

        int start_time = 0;
        int iter = 0;

        float avg_wt = 0;
        float avg_tat = 0;
        int previous = -1, present;

        System.out.println("\n\tGantt Chart");
        System.out.print("\t");
        while(iter != P)
        {
            int minP = P;
            int pt = Integer.MAX_VALUE;
            for(int i=0; i<P; i++)
            {
                if((pt > pr[i]) && (arrivalTime[i] <= start_time) && (burstTime_copy[i] > 0))
                {
                    minP = i;
                    pt = pr[minP];
                }
            }

            if(minP == P) break;
            burstTime_copy[minP] = burstTime_copy[minP] - 1;

            present = minP;
            if(present != previous)
            {             
                System.out.print("| " + start_time + " |");
                System.out.print(" P["+(minP+1)+"] ");
            }
            
            if(burstTime_copy[minP] == 0)
            {
                iter++;
                priority_tat[minP] = start_time + 1 - arrivalTime[minP];
                priority_wt[minP] = priority_tat[minP] - burstTime[minP];
                
                avg_tat += priority_tat[minP];
                avg_wt += priority_wt[minP];
            }
            previous = present;
            start_time++;
        }

        System.out.print("| " + start_time + " |");


        System.out.print("\n\t");
        for(int i=0; i<46; i++) System.out.print("_");

        System.out.println("\n\tProcess\t AT\t BT\t PR\t WT\t TAT");
        System.out.print("\t");

        for(int i=0; i<46; i++) System.out.print("_");

        for(int i=0; i<P; i++)
        {
            System.out.printf("\n\t%3d", pid[i]);
            System.out.printf("\t%3d", arrivalTime[i]);
            System.out.printf("\t%3d", burstTime[i]);
            System.out.printf("\t%3d", pr[i]);
            System.out.printf("\t%3d", priority_wt[i]);
            System.out.printf("\t%3d", priority_tat[i]);
        }

        System.out.println("");
        System.out.print("\t");

        for(int i=0; i<46; i++) System.out.print("_");
        System.out.println("\t");

        avg_tat = (float)(avg_tat/P);
        avg_wt = (float)(avg_wt/P);

        System.out.println("\n\tAverage turnaround time is " + avg_tat);
        System.out.println("\tAverage waiting time is " + avg_wt);
    }

    public void roundRobin(int arrivalTime[], int burstTime[], int pid[], int P)
    {
        System.out.print("\n\t\tRound Robin\n");

        Scanner sc = new Scanner(System.in);
        System.out.print("\nEnter the time quantum value: ");
        int quantum = sc.nextInt();

        int [] remaining_time = new int[P];
        for(int x=0; x<P; x++) remaining_time[x] = burstTime[x];

        // sort by arrival times
        for(int i=0; i<P-1; i++)
        {
            for(int j=0; j<P-1-i; j++)
            {
                if(arrivalTime[j] > arrivalTime[j+1])
                {
                    int temp1 = arrivalTime[j];
                    arrivalTime[j] = arrivalTime[j + 1];
                    arrivalTime[j + 1] = temp1;

                    int temp2 = pid[j];
                    pid[j] = pid[j+1];
                    pid[j+1] = temp2;

                    int temp3 = burstTime[j];
                    burstTime[j] = burstTime[j+1];
                    burstTime[j+1] = temp3;

                    int temp4 = remaining_time[j];
                    remaining_time[j] = remaining_time[j+1];
                    remaining_time[j+1] = temp4;
                }
            }
        }

        Queue<Integer> q = new LinkedList<>();
        int start_time = 0;
        int executed = 0;
        // int process = 0;
        int [] inQueue =  new int [P];
        for(int x=0; x<P; x++)
        {
            inQueue[x] = 0;
        }

        while(executed != P)
        {
            for(int i=0; i<P; i++)
            {
                if(arrivalTime[i] <= start_time && inQueue[i]==0)
                {
                    q.add(i);
                    inQueue[i] = 1;
                }
            }
            int temp=-1;
            if(temp != -1) q.add(temp);

            if(q.size() > 0)          
            {
                int exec_pro = q.peek(); // gives the executing process pid;
                if(remaining_time[exec_pro] <= quantum)
                {
                    System.out.print("| " + start_time + " | P[" + pid[exec_pro] + "] ");
                    start_time += remaining_time[exec_pro];
                    remaining_time[exec_pro] = 0;
                    q.remove();
                    executed++;
                }
                else
                {
                    System.out.print("| " + start_time + " | P[" + pid[exec_pro] + "] ");
                    start_time += quantum;
                    remaining_time[exec_pro] = remaining_time[exec_pro] - quantum;
                    temp = q.peek();
                    q.remove();
                }

            }
            else
            {
                start_time++;
            }
        }

        sc.close();
    }
    public static void main(String[] args)
    {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the number of processes: ");
        int P = sc.nextInt();

        int [] arrivalTime = new int[P];
        int [] burstTime = new int[P];
        int [] pid = new int[P];

        System.out.println("\nEnter the corresponding arrival time and CPU burst time for each process");
        for(int i=0; i<P; i++)
        {
            System.out.print("Process " + (i+1) + " : ");
            int a = sc.nextInt();
            int b = sc.nextInt();
            arrivalTime[i] = a;
            burstTime[i] = b;
            pid[i] = i+1;
        }
        
        System.out.print("\n\t\tSummary\n");

        System.out.print("\t");
        for(int i=0; i<20; i++) System.out.print("_");

        System.out.println("\n\tProcess\t AT\t BT");
        System.out.print("\t");

        for(int i=0; i<20; i++) System.out.print("_");

        for(int i=0; i<P; i++)
        {
            System.out.printf("\n\t%3d", pid[i]);
            System.out.printf("\t%3d", arrivalTime[i]);
            System.out.printf("\t%3d", burstTime[i]);
        }

        System.out.println("");
        System.out.print("\t");

        for(int i=0; i<20; i++) System.out.print("_");
        System.out.println("\t");

        // summary closed

        cpu_sched sch = new cpu_sched(P);
        sch.SJF(arrivalTime, burstTime, pid, P);

        cpu_sched sch1 = new cpu_sched(P);
        sch1.priority(arrivalTime, burstTime, pid, P);

        cpu_sched sch2 = new cpu_sched(P);
        sch2.roundRobin(arrivalTime, burstTime, pid, P);
        sc.close();
    }
}
