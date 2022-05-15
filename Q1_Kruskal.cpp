#include <bits/stdc++.h>
using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
};

struct Graph
{
    int numVertices = -1;
    std::vector<Edge> edgeVector = {};
};

//Compares weight of given 2 edge
bool compareWeight(Edge e1, Edge e2)
{
    return (e1.weight < e2.weight);
}

//Util to find parent
int find(int parent[], int node)
{
    if (parent[node] == -1)
    {
        return node;
    }
    else
    {
        return parent[node] = find(parent, parent[node]);
    }
}

//Util to unite 2 given node
void unite(int (& parent) [], int (&rank) [], int n1, int n2)
{
    //Find parent of node 1
    int n1Parent = find(parent, n1);
    //Find parent of node 2
    int n2Parent = find(parent, n2);

    //Checks if parent of both nodes same or not
    if (n1Parent != n2Parent)
    {
        // Link subtree of smaller rank to the subtree of higher rank
        if (rank[n1Parent] < rank[n2Parent])
        {
            parent[n1Parent] = n2Parent;
            rank[n2Parent] += rank[n1Parent];
        }
        else
        {
            parent[n2Parent] = n1Parent;
            rank[n1Parent] += rank[n2Parent];
        }
    }
}

//Function to find minimum spanning tree using Kruskal
void FindMSTUsingKruskal(Graph g)
{
    int MSTWeight = 0;
    int parent[g.numVertices];
    int rank[g.numVertices];
    for (int i = 0; i < g.numVertices; i++)
    {
        rank[i] = 1;
        parent[i] = -1;
    }

    printf("\nAfter Sorting the edges based on weight");
    // Sort the edges based on weight
    sort(g.edgeVector.begin(), g.edgeVector.end(), compareWeight);
    for (auto e : g.edgeVector)
    {
            printf("\n\t%d --> %d = %d",e.source, e.destination, e.weight);
    }

    printf("\n\nKruskal's Minimum Spanning Tree is");
    for (auto e : g.edgeVector)
    {
        // If the parent of src and dest is same, then it will form cycle
        if (find(parent, e.source) != find(parent, e.destination))
        {
            unite(parent, rank, e.source, e.destination);
            MSTWeight += e.weight;
            printf("\n\t%d --> %d = %d",e.source, e.destination, e.weight);
        }
    }
    printf("\n\nWeight of Minimum Spanning Tree %d" , MSTWeight);
}

int main()
{
    Graph g;
    //No of vertex, edge
    int numEdge;
    printf("\nEnter the number of vertex\n");
    scanf("%d", &g.numVertices);
    printf("\nEnter the number of edge\n");
    scanf("%d", &numEdge);

    printf("\nEnter the Edge and weight in space seperated way. Example for 0 -> 1 with weight 5, the input should be \"0 1 5\"\n");
    for (int i = 0; i < numEdge; i++)
    {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        g.edgeVector.push_back({u, v, w});
    }

    //Remove comment for default output
    /*
    g.numVertices = 4;
    g.edgeVector.push_back({0, 1, 10});
    g.edgeVector.push_back({1, 3, 15});
    g.edgeVector.push_back({2, 3, 4});
    g.edgeVector.push_back({2, 0, 6});
    g.edgeVector.push_back({0, 3, 5});*/

    FindMSTUsingKruskal(g);
    return 0;
}