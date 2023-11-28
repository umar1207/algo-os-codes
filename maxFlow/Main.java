import java.util.*;

public class Main{

    private int n;
    private int [] parent;
    private boolean [] visited;
    private boolean [][] augVert;
    private int [][] residGraph;

    
    public Main(int n)
    {
        this.n = n;
        parent = new int[n];
        visited = new boolean[n]; 
        augVert = new boolean[n][n];
        residGraph = new int[n][n];
    }

    boolean BFS(int [][] residGraph, int source, int sink)
    {
        int [] queue = new int[n];
        for(int i=0; i<n; i++)
        {
            parent[i] = -1;
            visited[i] = false;
            queue[i] = -1;
        }

        int front = 0, rear = 0;
        visited[source] = true;
        queue[rear++] = source;

        while(front != rear) // that is queue is not empty
        {
            int u = queue[front++]; //deque
            for(int v = 0; v<n; v++)
            {
                if(residGraph[u][v]>0 && !visited[v])
                {
                    visited[v] = true;
                    queue[rear++] = v;
                    parent[v] = u;
                }
            }
        }
        return visited[sink];
    }

    int EdmondKarp(int [][] graph, int source, int sink)
    {
        for(int u=0; u<n; u++){
            for(int v=0; v<n; v++){
                residGraph[u][v] = graph[u][v];
            }
        }

        int max_flow = 0;
        // while(BFS(residGraph, source, sink))
        BFS(residGraph, source, sink);
        while(visited[sink] == true)
        {
            
            int flow = Integer.MAX_VALUE;
            
            for(int v = sink; v != source; v = parent[v]){
                int u = parent[v];
                flow = Math.min(flow, residGraph[u][v]);
            }
            
            for(int u=0; u<n; u++){
                for(int v=0; v<n; v++){
                    augVert[u][v] = false;
                }
            }
            
            for(int v = sink; v != source; v = parent[v]){
                int u = parent[v];
                residGraph[u][v] -= flow;
                augVert[u][v] = true;
                // put an edge from u to v here
                // residGraph[v][u] += flow; // back edge
            }
            
            // System.out.print("Augmenting path : ");
            // for(int v = sink; v != source; v = parent[v]){
            //     int u = parent[v];
            //     System.out.print(v + " <-(" + (graph[u][v]-residGraph[u][v]) + "/" + graph[u][v] + ")- ");
            // }
            // System.out.println(source);
            
            max_flow += flow;
            BFS(residGraph, source, sink);
        }
        return max_flow;
    }

    public static void main(String[] args){

        
        int [][] graph;
        Scanner sc = new Scanner(System.in);

        System.out.print("Enter the number of vertices in the graph: ");
        int V = sc.nextInt();

        System.out.print("Enter the number of edges in the graph: ");
        int E = sc.nextInt();

        graph = new int[V][V];

        for(int i=0; i<V; i++)
        {
            for(int j=0; j<V; j++)
            {
                graph[i][j] = 0;
            }
        }
        
        System.out.println("\nInitialise the capacity of edges of graph: ");

        for(int i=0; i<E; i++)
        {
            System.out.print("Enter the vertices between which the edge exists and hence the cost edge weight: ");
            int u, v, c;
            u = sc.nextInt();
            v = sc.nextInt();
            c = sc.nextInt();

            graph[u][v] = c;
        }

        System.out.print("\nEnter the source of the graph: ");
        int source  = sc.nextInt();
        System.out.print("Enter the sink of the graph: ");
        int sink = sc.nextInt();
        
        Main fordFulkerson = new Main(V);
        int maxFlow = fordFulkerson.EdmondKarp(graph, source, sink);

        System.out.println("\nMaximum flow is : " + maxFlow + " ");

        sc.close();
    }
}