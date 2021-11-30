#include <iostream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

class Graph
{
    // private
    int N, E;
    vector<int> *children;
    vector<int> *parents;

public:
    Graph(int N, int E); // Constructor
    void addEdge(int u, int v);
    vector<int> topologicalSort();
    int longestPath(int &sources);
};

Graph::Graph(int N, int E)
{
    this->N = N;
    this->E = E;
    children = new vector<int>[N];
    parents = new vector<int>[N];
}

void Graph::addEdge(int u, int v)
{
    children[u].emplace_back(v);
    parents[v].emplace_back(u);
}

vector<int> Graph::topologicalSort()
{

    queue<int> q;

    vector<int> in_degree(N, 0);

    for (int i = 0; i < N; i++)
        in_degree[i] = parents[i].size();

    for (int i = 0; i < N; i++)
        if (parents[i].empty())
            q.push(i);

    vector<int> top_order;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        top_order.push_back(u);

        for (auto itr = children[u].begin(); itr != children[u].end(); itr++)
        {

            if (--in_degree[*itr] == 0)
                q.push(*itr);
        }
    }

    return top_order;
}

int Graph::longestPath(int &sources)
{
    vector<int> topOrder = this->topologicalSort();

    vector<int> distances(N, 0);

    int longest_path = 0;

    for (int i = 0; i < int(topOrder.size()); i++)
    {
        int v = topOrder[i];
        if (parents[v].size() == 0)
        {
            distances[v] = 1;
            sources++;
            continue;
        }

        for (int k = 0; k < int(parents[v].size()); k++)
        {
            distances[v] = max(distances[v], distances[parents[v][k]] + 1);
            longest_path = max(longest_path, distances[v]);
        }
    }

    return longest_path;
}

Graph parseInput()
{
    int N, E;

    scanf("%d %d", &N, &E);

    Graph g = Graph(N, E);

    vector<int> parentVector(E);
    vector<int> childVector(E);

    for (int i = 0; i < E; i++)
    {
        scanf("%d %d", &parentVector[i], &childVector[i]);
    }

    int parent, child;

    for (int i = 0; i < E; i++)
    {
        parent = parentVector[i] - 1;
        child = childVector[i] - 1;

        g.addEdge(parent, child);
    }

    return g;
}

int main()
{

    Graph g = parseInput();

    int sources = 0; // The number of sources in the graph is the number of interventions needed to make them all fall

    int longest_path = g.longestPath(sources);

    if (longest_path == 0)
    {
        longest_path++;
    }

    std::cout << sources << " " << longest_path << endl;

    return 0;
}