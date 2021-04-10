#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>

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
            G.nodes[child] = new node;

        if (!G.nodes[parent])
            G.nodes[parent] = new node;

        // Add the parent to the childs 'parents' list and the child to the parents 'children' list
        G.nodes[child]->parents.push_back(G.nodes[parent]);
        G.nodes[parent]->children.push_back(G.nodes[child]);

        result.clear();
    }
}

vector<Node> topologicalSort()
{
    stack<Node> stack;
    vector<Node> topOrder;

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
    return topOrder;
}

int main()
{
    int sources = 0, longest_path = 1;

    parseInput();

    // Create a vector for the topological order
    //topologicalOrder();
    vector<Node> topOrder = topologicalSort();

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
        delete (G.nodes[i]);

    return 0;
}
