#include<iostream>
using namespace std;

void Swap(int *num1, int *num2)
{
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void Sort(int weight[], int source[], int destination[], int E)
{
    for(int i=0; i<E-1; i++)
    {
        for(int j=0; j<E-1-i; j++)
        {
            if(weight[j]>weight[j+1])
            {
                Swap(&weight[j], &weight[j+1]);
                Swap(&source[j], &source[j+1]);
                Swap(&destination[j], &destination[j+1]);
            }
        }
    }

}

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


void kruskalsAlgo(int weight[], int source[], int destination[], int V, int E)
{

    Sort(weight, source, destination, E);

    int *parent = new int[V];
    int *rank = new int[V];

    for(int i=0; i<V; i++)
    {
        parent[i] = -1;
        rank[i] = 1;
    }

    int count = 1;
    int minCost = 0;
    cout << "\nedge1 -- edge2 = cost" << endl;

    int iter = 0;
    while(count <= (V-1))
    {
        int w = weight[iter];
        int s = source[iter];
        int d = destination[iter];

        if(find(s, parent)!= find(d, parent))
        {
            Union(s, d, parent, rank);
            count ++;
            minCost += w;
            cout << "  " << s << "   --   " << d << "   =   " << w << endl;
        }
        iter++;
    }
    cout << "\nMinimum Cost of Tree = " << minCost << endl;

}

int main()
{
    cout << "Enter the number of Vertices and Edges in your graph: ";
    int V, E;
    cin >> V >> E;

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
    }

    kruskalsAlgo(weight, source, destination, V, E);
}