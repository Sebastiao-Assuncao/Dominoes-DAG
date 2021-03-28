#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

typedef struct Node
{
    vector<int> parents;
    vector<int> children;
    int d = 0, f = 0, dist = -1, dfs_parent;
    string color;
} Node;

typedef struct Graph
{
    int N, E;
    vector<Node> nodes;
} Graph;

Graph G;
vector<int> topOrder;

void parseInput(string filename)
{
    ifstream file(filename);
    string line;
    vector<string> result;

    //Get the number of vertices and edges. N is the number of nodes, E is the number of edges
    getline(file, line);
    istringstream iss(line);

    for (string line; iss >> line;)
        result.push_back(line);

    stringstream temp1(result[0]);
    stringstream temp2(result[1]);
    temp1 >> G.N;
    temp2 >> G.E;

    // Make the nodes vector the size needed
    G.nodes.resize(G.N);

    result.clear();

    //Get the edges
    while (getline(file, line))
    {
        istringstream iss(line);
        int parent, child;

        for (string line; iss >> line;)
            result.push_back(line);

        istringstream aux0(result[0]);
        istringstream aux1(result[1]);

        aux0 >> parent;
        aux1 >> child;
        parent -= 1;
        child -= 1;

        if (G.nodes[child].dist == 0) // Se ainda nao tiver sido criado
        {
            Node new_child;
            G.nodes[child] = new_child;
        }

        if (G.nodes[parent].dist == 0)
        {
            Node new_parent;
            G.nodes[parent] = new_parent;
        }

        G.nodes[child].parents.push_back(parent);
        G.nodes[parent].children.push_back(child);

        result.clear();
    }
}

int DFS_visit(int v_index, int time)
{

    G.nodes[v_index].color = "gray";
    time++;
    G.nodes[v_index].d = time;

    for (int i = 0; i < G.nodes[v_index].children.size(); i++)
    {

        int u_index = G.nodes[v_index].children[i];
        if (G.nodes[u_index].color == "white")
        {
            time = DFS_visit(u_index, time);
            G.nodes[u_index].dfs_parent = v_index;
        }
    }

    G.nodes[v_index].color = "black";
    time++;
    G.nodes[v_index].f = time;

    topOrder.insert(topOrder.begin(), v_index);

    return time;
}

vector<int> topologicalOrder()
{

    for (int i = 0; i < G.N; i++)
    {
        G.nodes[i].color = "white";
        G.nodes[i].dfs_parent = -1;
    }

    int time = 0;

    for (int i = 0; i < G.N; i++)
    {
        if (G.nodes[i].color == "white")
            time = DFS_visit(i, time);
    }

    return topOrder;
}

int main()
{
    int sources = 0;
    int longest_path = 1;

    parseInput("banana.txt");
    topOrder = topologicalOrder();

    for (int i = 0; i < G.N; i++)
    {
        int v_index = topOrder[i];

        if (G.nodes[v_index].parents.size() == 0)
        {
            G.nodes[v_index].dist = 1;
            sources++;
        }

        else
        {
            int max = 0;

            for (int k = 0; k < G.nodes[v_index].parents.size(); k++)
                if (G.nodes[G.nodes[v_index].parents[k]].dist > max)
                    max = G.nodes[G.nodes[v_index].parents[k]].dist;
            max += 1;

            G.nodes[v_index].dist = max;

            if (max > longest_path)
                longest_path = max;
        }
    }

    for (int i = 0; i < G.N; i++)
    {
        cout << topOrder[i] + 1 << "->";
    }
    cout << endl;

    cout << "Number of sources: " << sources << endl;
    cout << "Longest path: " << longest_path << endl;
    return 0;
}