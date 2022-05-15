#include <bits/stdc++.h>
using namespace std;

#define inf INT_MAX

//Util to find the the vertex with min distance
int GetVertexWithMinDistance(int distance[], bool visited[], int noVert)
{
    int min = inf;
    int minVertex;
 
    for (int i = 0; i < noVert; i++)
    {
        // If the node is not visited already and the distance is min 
        if (visited[i] == false && distance[i] < min)
        {
            min = distance[i];
            minVertex = i;
        }
    }
 
    return minVertex;
}

//Util to print the MST
void printMST(std::vector<std::vector<int>> graph, int parent[])
{
    int noVert = graph.size();
    int MSTWeight = 0;
    printf("\n\nPrim's Minimum Spanning Tree is");
    //For every vertex, print the edge from its parent to itself
    for (int i = 1; i < noVert; i++)
    {
        printf("\n\t%d --> %d = %d",parent[i], i, graph[i][parent[i]]);
        MSTWeight += graph[i][parent[i]];
    }
    printf("\n\nWeight of Minimum Spanning Tree %d" , MSTWeight);
}

void FindMSTUsingPrims(std::vector<std::vector<int>> graph)
{
    int noVert = graph.size();
    int distance[noVert];
    int parent[noVert];
    bool visited[noVert];
 
    //Set distance to inf and set visited as false
    for (int i = 0; i < noVert; i++)
    {
        distance[i] = inf;
        visited[i] = false;
    }

    //Assign distance as 0 to first vertex
    distance[0] = 0;

    //First vertex is root of MST
    parent[0] = -1; 
    for (int i = 0; i < noVert - 1; i++)
    {
        //Get Vertix with minimum distance which is not visited
        int u = GetVertexWithMinDistance(distance, visited, noVert);
 
        //Set it to visited
        visited[u] = true;
 
        //Go over the adjacency matrix
        for (int v = 0; v < noVert; v++)
        {
            //Check if the node v is adjacent to u and if its not visited
            if (graph[u][v] && visited[v] == false)
            {
                //Update the distance list if the weight of the edge is lesser than the distance list
                if(graph[u][v] < distance[v])
                {
                    distance[v] = graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }
 
    // Print the MST
    printMST(graph, parent);
}

int main()
{
    std::vector<std::vector<int>> graph;
    int noVert;

    printf("\nEnter the number of vertex\n");
    scanf("%d", &noVert);

    for(int i = 0; i < noVert; i++)
    {
        graph.push_back(std::vector<int> (noVert, 0));
    }

    printf("\nEnter the weight of i, j. Enter 0 if they are not connected");
	for(int i = 0; i < noVert; i++)
	{
		for(int j = 0; j < noVert; j++)
		{
			if ( j != i)
            {
                if(0 == graph[i][j])
                {
                    printf("\nEnter the weight of edge %d to %d is \t", i, j);
                    int x;
                    scanf("%d", &x);
                    graph[j][i] = graph[i][j] = x;
                }
            }
		}
	}

    printf("\nThe input graph is \n");
    for(int i=0;i<noVert;i++)
    {
        printf("\n\t");
        for(int j=0;j<noVert;j++)
        {
            printf("%d  ", graph[i][j]);
        }
    }

    FindMSTUsingPrims(graph);
    return 0;
}