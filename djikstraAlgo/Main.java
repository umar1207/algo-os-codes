import java.util.Scanner;

public class Main {

    void printIntermediate(int shortestPath[], int V)
    {
        int a = -1;
        System.out.println();
        System.out.print("Distance : ");
        for(int i=0; i<V; i++) {
            if(shortestPath[i] != (int)1e7) System.out.printf("%3d", shortestPath[i]);
            else System.out.printf("%3d", a);
        }
    }
    void printDistance(int shortestPath[], int source, int V)
    {
        System.out.println("\nVertex\t" + "Shortest Path from Source" );
        for(int i=0; i<V; i++)
        {
            System.out.println(i + "\t\t\t\t" + shortestPath[i]);
        }
    }

    int currentVertex(int shortestPath[], Boolean permVertex[], int v)
    {
        int minimum = (int)1e7, index = -1;
        for(int i=0; i<v; i++)
        {
            if(shortestPath[i] < minimum && permVertex[i] == false)
            {
                minimum = shortestPath[i];
                index = i;
            }
        }
        return index;
    }
    void Dijkstra(int weight[][], int source, int V)
    {
        int shortestPath[] = new int[V];
        Boolean permVertex[] = new Boolean[V];

//        initialise shortest path , source ->0 & other -> infinite
//        set all vertices initially as unprocessed ie permVertex -> false
        for(int i=0; i<V; i++)
        {
            shortestPath[i] = (int)1e7;
            permVertex[i] = false;
        }
        shortestPath[source] = 0;

        System.out.println("Source Vertex: " + source);
        System.out.print("Vertex No: ");
        for(int i=0; i<V; i++) {
            System.out.printf("%3d", i);
        }

        for(int it=0; it<V-1; it++)
        {
            int u = currentVertex(shortestPath, permVertex, V);
//            u is marked as permanent vertex since now it will be processed
            permVertex[u] = true;

            for(int v=0; v<V; v++)
            {
                if(permVertex[v] == false && weight[u][v]>0 && shortestPath[u]!=(int)1e7)
                    shortestPath[v] = Math.min(shortestPath[v], shortestPath[u]+weight[u][v]);
            }
            printIntermediate(shortestPath, V);

        }
//        printDistance(shortestPath, source, V);
    }
    public static void main(String[] args) {
        Scanner inp = new Scanner(System.in);


        System.out.print("Enter the number of vertices & edges: ");
        int V, E;
        V = inp.nextInt();
        E = inp.nextInt();

//        declaring the graph
        int [][] graph = new int[V][V];

//        initialising the graph
        System.out.println("Initialise the graph");

        for(int i=0; i<V; i++){
            for(int j=0; j<V; j++){
                graph[i][j] = 0;
            }
        }

        for(int i=0; i<E; i++){
            System.out.print("Enter the vertices number between which the edge exists and hence enter the edge weight: ");
            int u = inp.nextInt();
            int v = inp.nextInt();
            int w = inp.nextInt();

            graph[u][v] = w;
            graph[v][u] = w;
        }
//        graph initialised


        for(int i=0; i<V; i++)
        {
            System.out.println("\n------------------------------------------------");
            Main t = new Main();
            t.Dijkstra(graph, i, V);
        }
        System.out.println("\n------------------------------------------------");
        inp.close();
    }
}