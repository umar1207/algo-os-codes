import java.util.*;

public class BankersAlgo {

    static Boolean bankerAlgo(int[][] allocated, int[][] maxNeed, int[][] remaining, int[] available, int m, int n, int [] safeSequence) {
        int[] visited = new int[m];
        
        for (int i = 0; i < m; i++)
            visited[i] = 0;

        int iter = 0;
        while (iter != m) {
            int flag = 0;
            for (int i = 0; i < m; i++) {
                if (visited[i] == 0) // process has not been counted in safe sequence yet
                {
                    int flag2 = 1;
                    for (int j = 0; j < n; j++) {
                        if (remaining[i][j] > available[j])
                            flag2 = 0;
                    }
                    if (flag2 == 1) // this process will be in safe sequence
                    {
                        flag = 1;
                        safeSequence[iter++] = i;
                        visited[i] = 1;
                        for (int k = 0; k < n; k++) {
                            available[k] += allocated[i][k];
                        }
                        // break;
                    }
                }
            }
            if (flag == 0)
                break; // deadlock exists
        }

        if (iter == m)
            return true;
        return false;

    }

    public static void main(String args[]) {
        System.out.println("Bankers Algo");
        Scanner sc = new Scanner(System.in);

        int m, n;

        System.out.print("Enter the number of processes and resources: ");
        m = sc.nextInt();
        n = sc.nextInt();

        ////////////////

        int[] available = new int[n];
        for (int i = 0; i < n; i++)
            available[i] = 0;

        ////////////

        int[] total = new int[n];
        System.out.print("\nEnter the number of instances of each resource\n");
        for (int i = 0; i < n; i++) {
            System.out.print("Resource " + (i + 1) + " : ");
            total[i] = sc.nextInt();
        }

        ////////////

        int[][] allocated = new int[m][n];
        System.out.print("\nEnter the instances of resources allocated to each process\n");

        for (int i = 0; i < m; i++) {
            System.out.print("Process " + (i + 1) + " : ");
            for (int j = 0; j < n; j++) {
                allocated[i][j] = sc.nextInt();
                available[j] += allocated[i][j];
            }
        }

        for (int i = 0; i < n; i++) {
            available[i] = total[i] - available[i];
        }

        int[] available_copy = new int[n];
        for (int i = 0; i < n; i++) {
            available_copy[i] = available[i];
        }

        /////////////

        int[][] maxNeed = new int[m][n];
        System.out.print("\nEnter the maximum needs of resources of each process\n");

        for (int i = 0; i < m; i++) {
            System.out.print("Process " + (i + 1) + " : ");
            for (int j = 0; j < n; j++)
                maxNeed[i][j] = sc.nextInt();
        }

        //////////////

        int[][] remaining = new int[m][n];
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++)
                remaining[i][j] = (maxNeed[i][j] - allocated[i][j]);
        }

        int [] safeSequence = new int[m];

        // BankersAlgo algo = new BankersAlgo();
        Boolean isSafe = bankerAlgo(allocated, maxNeed, remaining, available_copy, m, n, safeSequence);
        for(int i=0; i<n; i++) available_copy[i] = available[i];

        if (isSafe) {
            System.out.print("\nDeadlock does not exists");
            System.out.print("\nSafe Sequence is: ");
            for (int i = 0; i < m; i++)
                System.out.print((safeSequence[i] + 1) + " ");

            System.out.print("\nResource request algo\n");

            while (true) {

                System.out.print("\n\nEnter the process number and the instances of resources it is requesting\n");
                int process = sc.nextInt();

                if(process == -1) break;

                int[] request = new int[n];
                for (int i = 0; i < n; i++)
                    request[i] = sc.nextInt();

                // Check those 2 conditions
                // 1) request <= remaining; else error
                // 2) request <= available; else wait
                int fl1 = 1;
                for (int i = 0; i < n; i++) {
                    if (request[i] > remaining[process - 1][i]) {
                        fl1 = 0;
                        break;
                    }
                }

                int fl2 = 1;
                for (int i = 0; i < n; i++) {
                    if (request[i] > available[i]) {
                        fl2 = 0;
                        break;
                    }
                }

                if (fl1 == 0) {
                    System.out.print("\nError: Invalid assignment\n");
                } else if (fl2 == 0) {
                    System.out.print("\nProcess has to wait since resources are not available\n");
                } else {

                    int[][] allocated_copy = new int[m][n];
                    for (int i = 0; i < m; i++) {
                        for (int j = 0; j < n; j++) {
                            allocated_copy[i][j] = allocated[i][j];
                        }
                    }

                    int[][] remaining_copy = new int[m][n];
                    for (int i = 0; i < m; i++) {
                        for (int j = 0; j < n; j++)
                            remaining_copy[i][j] = remaining[i][j];
                    }

                    for (int i = 0; i < n; i++) {
                        available_copy[i] -= request[i];
                        allocated_copy[process - 1][i] += request[i];
                        remaining_copy[process - 1][i] -= request[i];
                    }

                    // BankersAlgo subAlgo = new BankersAlgo();
                    Boolean isSAFE = bankerAlgo(allocated_copy, maxNeed, remaining_copy, available_copy, m, n, safeSequence);
                    for(int i=0; i<n; i++) available_copy[i] = available[i];

                    if (isSAFE) {
                        System.out.print("\nDeadlock does not exists");
                        System.out.print("\nSafe Sequence is: ");
                        for (int i = 0; i < m; i++)
                            System.out.print((safeSequence[i] + 1) + " ");
                    } else {
                        System.out.print("\nDeadlock Exists");
                    }
                }
            }

        } else {
            System.out.print("\nDeadlock Exists");
        }

        sc.close();
    }
}

