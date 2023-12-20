#include <iostream>
using namespace std;

void primsAlgo(int *weight[], int source[], int destination[], int cost[], int V, int E)
{
    bool visited[V];
    for(bool val: visited) val = false;

    visited[0] = true;

    int count=0;
    while(count < (V-1))
    {
        int minWeight = INT_MAX;
        int chosen = -1;
        for(int i=0; i<V; i++)
        {
            if(visited[i] == true)
            {
                for(int j=0; j<V; j++)
                {
                    if(visited[j] == false)
                    {
                        if(weight[i][j] < minWeight && weight[i][j] > 0)
                        {
                            minWeight = weight[i][j];
                            cost[count] = weight[i][j];
                            source[count] = i;
                            destination[count] = j;
                            chosen = j;
                        }
                    }
                }
            }
        }
        visited[chosen] = true;
        count++;
    }
}


int main()
{
    //initialise graph by either entering full matrix or just the non zero weight edges
    //here done by 2nd method

    cout << "Enter the number of Vertices and Edges in your graph: ";
    int V, E;
    cin >> V >> E;

    // int weight[V][V];

    int *weight[V];
    for (int i = 0; i < V; i++) {
        weight[i] = new int[V];
    }
    for(int i=0; i<V; i++)
    {
        for(int j=0; j<V; j++)
        {
            weight[i][j] = 0;
        }
    }

    // int source[E];
    // int destination[E];
    // int weight[E];
    
    for(int i=0; i<E; i++)
    {
        cout << "Enter the vertices between which the edge exists and hence the edge weight: ";
        int s, d, c;
        cin >> s >> d >> c;

        // source[i] = s;
        // destination[i] = d;
        // weight[i] = c;

        weight[s][d] = c;
        weight[d][s] = c;
    }

    int source[V-1];
    int destination[V-1];
    int cost[V-1];

    primsAlgo(weight, source, destination, cost, V, E);

    cout << "\nMST tree is\n ";
    cout << "\nedge1 -- edge2 = cost" << endl;
    for(int i=0; i<(V-1); i++)
        cout << "  " << source[i] << "   --   " << destination[i] << "   =   " << cost[i] << endl;
}
    
