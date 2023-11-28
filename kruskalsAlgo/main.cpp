#include <iostream>
#include "minheap.h"
using namespace std;

int find(int i, int parent[])
{
    if (parent[i] == -1)
        return i;
 
    return parent[i] = find(parent[i], parent);
}

void Union(int x, int y, int parent[], int rank[])
{
    int s1 = find(x, parent);
    int s2 = find(y, parent);

    if (s1 != s2) {
        if (rank[s1] < rank[s2]) {
            parent[s1] = s2;
        }
        else if (rank[s1] > rank[s2]) {
            parent[s2] = s1;
        }
        else {
            parent[s2] = s1;
            rank[s1] += 1;
        }
    }
}

// Step 1: Sort all edges in increasing order of their edge weights.
// Step 2: Pick the smallest edge.
// Step 3: Check if the new edge creates a cycle or loop in a spanning tree.
// Step 4: If it doesn’t form the cycle, then include that edge in MST. Otherwise, discard it.
// Step 5: Repeat from step 2 until it includes |V| - 1 edges in MST.

// TC = O(V LogE)
void KruskalAlgo(int weight[], int source[], int destination[], int Edges, int vertices)
{
    MinHeap H(Edges);

    for(int i=0; i<Edges; i++)
        H.insertKey(weight[i], source[i], destination[i]);

    int *parent = new int[vertices];
    int *rank = new int[vertices];

    for(int i=0; i<vertices; i++)
    {
        parent[i] = -1;
        rank[i] = 1;
    }

    int count = 1;
    int minCost = 0;
    cout << "\nedge1 -- edge2 = cost" << endl;

    while(count <= vertices-1)
    {
        int w = H.getMin();
        int s = H.getsrc();
        int d = H.getdest();

        if (find(s, parent) != find(d, parent)){
            Union(s, d, parent, rank);
            count++;
            minCost += w;
            cout << "  " << s << "   --   " << d << "   =   " << w << endl;
        }
        int x = H.DeleteMin();
    }

    cout << "\nMinimum Cost of Tree = " << minCost << endl;
}

int main()
{
    cout << "Enter the number of Vertices and Edges in your graph: ";
    int V, E;
    cin >> V >> E;

    // initialise your graph

    int cost[V][V];
    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            cost[i][j] = 0;
        }
    }

    int source[E];
    int destination[E];
    int weight[E];
    
    for(int i=0; i<E; i++)
    {
        cout << "Enter the vertices between which the edge exists and hence the edge weight: ";
        int s, d, c;
        cin >> s >> d >> c;

        source[i] = s;
        destination[i] = d;
        weight[i] = c;

        cost[s][d] = c;
        cost[d][s] = c;
    }

    KruskalAlgo(weight, source, destination, E, V);
   
    return 0;
}