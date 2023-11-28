import java.util.Scanner;

public class DiskSched{
    static int fcfs(int []sequence, int total, int head)
    {
        int total_head_movement = 0;
        for(int i=0; i<total; i++)
        {
            if(i==0)
            {
                if(sequence[i] < head) total_head_movement = head - sequence[i];
                else total_head_movement = sequence[i] - head;
            }
            else
            {
                if(sequence[i] < sequence[i-1]) total_head_movement += (sequence[i-1] - sequence[i]);
                else total_head_movement += (sequence[i] - sequence[i-1]);
            }
        }
        return total_head_movement;
    }
    static void BubbleSort(int []sequence, int total)
    {
        for(int i=0; i<total-1; i++)
        {
            for(int j=0; j<total-i-1; j++)
            {
                if(sequence[j] > sequence[j+1])
                {
                    int temp = sequence[j];
                    sequence[j] = sequence[j+1];
                    sequence[j+1] = temp;
                }
            }
        }

        System.out.print("\nSorted array is: ");
        for(int i=0; i<total; i++) System.out.print(sequence[i] + " ");
    }
    static int scan(int []sequence, int total, int head, int direction)
    {
        int total_head_movement = 0;
        BubbleSort(sequence, total);
        
        // left - 0; right -1 
        if(direction == 0) total_head_movement = (head-sequence[0] + sequence[total-1] - sequence[0]);
        else total_head_movement = (sequence[total-1] - head + sequence[total-1] - sequence[0]);

        return total_head_movement;
    }
    public static void main(String args[])
    {
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the total number of cylinder numbers: ");
        int total = sc.nextInt();

        System.out.print("Enter the sequence: ");
        int [] sequence = new int[total];
        for(int i=0; i<total; i++)
        {
            sequence[i] = sc.nextInt();
        }

        System.out.print("Enter the head position: ");
        int head = sc.nextInt();

        System.out.println("Total head movement: " + fcfs(sequence, total, head));

        System.out.print("Enter the direction: Left-0; Right-1: ");
        int direction = sc.nextInt();
        System.out.println("Total head movement: " + scan(sequence, total, head, direction));


        sc.close();
    }
}