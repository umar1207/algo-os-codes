import java.util.*;

public class Main {
    private int[] parent;
    private Queue<Integer> queue;
    private int n;
    private boolean[] visited;

    public Main(int n) {
        this.n = n;
        this.queue = new LinkedList<Integer>();
        parent = new int[n + 1];
        visited = new boolean[n + 1];
    }

    public boolean bfs(int source, int goal, int graph[][]) {
        boolean pathFound = false;
        int destination, element;

        for (int vertex = 1; vertex <= n; vertex++) {
            parent[vertex] = -1;
            visited[vertex] = false;
        }

        queue.add(source);
        parent[source] = -1;
        visited[source] = true;

        while (!queue.isEmpty()) {
            element = queue.remove();
            destination = 1;

            while (destination <= n) {
                if (graph[element][destination] > 0 && !visited[destination]) {
                    parent[destination] = element;
                    queue.add(destination);
                    visited[destination] = true;
                }
                destination++;
            }
        }
        if (visited[goal]) {
            pathFound = true;
        }
        return pathFound;
    }

    public int fordFulkerson(int graph[][], int source, int destination) {
        int u, v;
        int maxFlow = 0;
        int pathFlow;

        int[][] residualGraph = new int[n + 1][n + 1];
        for (int sourceVertex = 1; sourceVertex <= n; sourceVertex++) {
            for (int dv = 1; dv <= n; dv++) {
                residualGraph[sourceVertex][dv] = graph[sourceVertex][dv];
            }
        }

        while (bfs(source, destination, residualGraph)) {
            pathFlow = Integer.MAX_VALUE;
            for (v = destination; v != source; v = parent[v]) {
                u = parent[v];
                pathFlow = Math.min(pathFlow, residualGraph[u][v]);
            }
            for (v = destination; v != source; v = parent[v]) {
                u = parent[v];
                residualGraph[u][v] -= pathFlow;
                residualGraph[v][u] += pathFlow;
            }
            maxFlow += pathFlow;
        }

        return maxFlow;
    }

    public static void main(String... arg) {
        int[][] graph;
        int numberOfNodes;
        int source;
        int sink;
        int maxFlow;

        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter the number of nodes");
        numberOfNodes = scanner.nextInt();
        graph = new int[numberOfNodes + 1][numberOfNodes + 1];

        System.out.println("Enter the graph matrix");
        for (int sourceVertex = 1; sourceVertex <= numberOfNodes; sourceVertex++) {
            for (int dv = 1; dv <= numberOfNodes; dv++) {
                graph[sourceVertex][dv] = scanner.nextInt();
            }
        }

        System.out.println("Enter the source of the graph");
        source = scanner.nextInt();

        System.out.println("Enter the sink of the graph");
        sink = scanner.nextInt();

        Main fordFulkerson = new Main(numberOfNodes);
        maxFlow = fordFulkerson.fordFulkerson(graph, source, sink);
        System.out.println("The Max Flow is " + maxFlow);
        scanner.close();
    }
}
