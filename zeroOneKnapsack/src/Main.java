import java.util.Scanner;
public class Main {

    static int max(int a, int b)
    {
        if(a > b) return a;
        else return b;
    }
    static int knapsack_0_1(int cap, int profit[], int weight[], int n)
    {
        int [][]dp = new int[n+1][cap+1];

//        System.out.print("Capacity of bag-> :");
        System.out.print("  x |");
        for(int i=0; i<=cap; i++) System.out.printf("%3d", i);
        System.out.println();
        for(int i=0; i<=cap; i++) System.out.print("---");
        System.out.print("------");
        System.out.println();
//        System.out.println("\nWeight of bags");

        for(int i=0; i<=n; i++){
            for(int j=0; j<=cap; j++){
                if(i==0 || j==0) dp[i][j] = 0;
                else if(weight[i] > j) dp[i][j] = dp[i-1][j];
                else{
                    dp[i][j] = max(profit[i] + dp[i-1][j-weight[i]], dp[i-1][j]);
                }
            }

            System.out.printf("%3d |", weight[i]);
            for(int j=0; j<=cap; j++) System.out.printf("%3d", dp[i][j]);
            System.out.println();
        }

        int x = n; int y = cap;
        while(x>0 && y>0){
            if(dp[x][y] != dp[x-1][y]) {
                System.out.println("Selected item weight is :" + weight[x]);
                y = y - weight[x];
            }
            x--;
        }
        return dp[n][cap];
    }
    public static void main(String[] args) {
        Scanner inp = new Scanner(System.in);
        System.out.print("Enter the capacity of the bag: ");
        int cap = inp.nextInt();

        System.out.print("Enter the number of items: ");
        int n = inp.nextInt();

        System.out.print("Enter the weights of " + n + " items : ");
        int []weight = new int[n+1];
        weight[0] = 0;
        for(int i=1; i<=n; i++){
            weight[i] = inp.nextInt();
        }

        System.out.print("Enter the corresponding profits of " + n + " items: ");
        int []profit = new int[n+1];
        profit[0] = 0;
        for(int i=1; i<=n; i++){
            profit[i] = inp.nextInt();
        }

        int ans = knapsack_0_1(cap, profit, weight, n);
        System.out.print("The maximum profit that can be earned is : " + ans);
        inp.close();

    }
}