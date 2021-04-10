#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

typedef struct node
{
    vector<node *> parents, children;
    int dist = -1;
    string color;
} * Node;

struct Graph
{
    int N;
    vector<Node> nodes;
};

Graph G;
vector<Node> topOrder2, topOrder;

void parseInput()
{
    string line;
    vector<string> result;

    // Get the number of vertices (G.N)
    getline(cin, line);
    istringstream iss(line);

    for (string line; iss >> line;)
        result.push_back(line);

    // We dont need to store the number of edges
    stringstream temp1(result[0]);
    temp1 >> G.N;

    // Make the nodes vector the size needed
    G.nodes.resize(G.N);

    result.clear();

    // Get the edges
    while (getline(cin, line))
    {
        istringstream iss(line);
        int parent, child;

        // Parse the line
        for (string line; iss >> line;)
            result.push_back(line);

        istringstream aux0(result[0]);
        istringstream aux1(result[1]);

        // Assign the indexes to the nodes (scale with -1, because indexing in C++ starts at 0)
        aux0 >> parent;
        aux1 >> child;
        parent -= 1;
        child -= 1;

        // If either the parent node or the child node dont existe, create them
        if (!G.nodes[child])
            G.nodes[child] = (Node)malloc(sizeof(node));

        if (!G.nodes[parent])
            G.nodes[parent] = (Node)malloc(sizeof(node));

        // Add the parent to the childs 'parents' list and the child to the parents 'children' list
        G.nodes[child]->parents.push_back(G.nodes[parent]);
        G.nodes[parent]->children.push_back(G.nodes[child]);

        result.clear();
    }
}
/*void DFS_visit(Node v)
{

    v->color = "gray"; // Its currently being visited

    // Preform DFS on each of v's children
    for (int i = 0; i < int(v->children.size()); i++)
    {
        Node u = v->children[i];

        // Visit child if its 'white'
        if (u->color == "white")
        {
            DFS_visit(u);
            u->dfs_parent = v;
        }
    }

    // Close the node and assign the close time
    v->color = "black";

    // Insert the closed node at the beggining of the topological order vector
    topOrder2.insert(topOrder2.begin(), v);
}

void topologicalOrder()
{

    // Setup the nodes for the DFS
    for (int i = 0; i < G.N; i++)
        if (G.nodes[i])
        {
            G.nodes[i]->color = "white";
            G.nodes[i]->dfs_parent = NULL;
        }

    // Preform DFS for all the 'white' nodes
    for (int i = 0; i < G.N; i++)
        if (G.nodes[i])
            if (G.nodes[i]->color == "white")
                DFS_visit(G.nodes[i]);
}*/

void topologicalSort()
{
    stack<Node> stack;

    for (int i = 0; i < G.N; i++)
        if (G.nodes[i])
            G.nodes[i]->color = "white";

    for (int i = 0; i < G.N; i++)
    {
        if (G.nodes[i])
        {

            Node u = G.nodes[i];

            if (u->color != "white")
                continue;

            stack.push(u);

            while (!stack.empty())
            {

                Node v = stack.top();

                if (v->color == "white")
                    v->color = "gray";

                else
                {
                    v->color = "black";
                    topOrder.insert(topOrder.begin(), stack.top());
                    stack.pop();
                }

                for (int i = 0; i < int(v->children.size()); i++)
                {
                    Node w = v->children[i];

                    if (w->color == "white")
                    {
                        stack.push(w);
                    }
                }
            }
        }
    }
}

int main()
{
    int sources = 0, longest_path = 1;

    parseInput();

    // Create a vector for the topological order
    //topologicalOrder();
    topologicalSort();

    for (int i = 0; i < int(topOrder.size()); i++)
    {
        Node v = topOrder[i];

        // If v is a source, its distance is 1 and the number of sources increases
        if (v->parents.size() == 0)
        {
            v->dist = 1;
            sources++;
        }

        else
        {
            int max = 0;

            // The max is distance of the parent with the biggest distance plus 1 (the distance from the parent to v)
            for (int k = 0; k < int(v->parents.size()); k++)
                if (v->parents[k]->dist > max)
                    max = v->parents[k]->dist;
            max += 1;

            // Assign the biggest possible distance to v
            v->dist = max;

            // If the distance to v is bigger than the previous longest_path, longest_path becomes that distance
            if (max > longest_path)
                longest_path = max;
        }
    }

    // Add all the single sources
    sources += G.N - topOrder.size();

    cout << sources << " " << longest_path << endl;

    for (int i = 0; i < int(G.nodes.size()); i++)
        free(G.nodes[i]);

    // cout << "Number of vertices: " << G.N << endl;
    // cout << "Minimum interventions: " << sources << endl;
    // cout << "Longest path: " << longest_path << endl;
    return 0;
}
