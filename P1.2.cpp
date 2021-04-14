#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <stack>
#include <chrono>
#include <ctime>

using namespace std;

typedef struct node
{
    vector<node *> parents, children;
    int dist = -1;
    string color = "white";
} * Node;

struct Graph
{
    int N, E;
    vector<Node> nodes;
};

Graph G;

void parseInput()
{
    // Read the number of nodes
    if (!scanf("%d %d", &G.N, &G.E))
        exit(EXIT_FAILURE);

    // Make the nodes vector the size needed
    G.nodes.resize(G.N);

    //ios_base::sync_with_stdio(false);

    std::vector<int> parentVector = std::vector<int>(G.E);
    std::vector<int> childVector = std::vector<int>(G.E);

    for (int i = 0; i < G.E; i++) {
    
        scanf("%d %d", &parentVector[i], &childVector[i]);

    }

    int parent, child;
    
    for (int i = 0; i < G.E; i++)
    {
        parent = parentVector[i] - 1;
        child = childVector[i] - 1;
        
        // If either the parent node or the child node dont existe, create them
        if (!G.nodes[child])
            G.nodes[child] = new node;

        if (!G.nodes[parent])
            G.nodes[parent] = new node;

        // // Add the parent to the childs 'parents' list and the child to the parents 'children' list
        G.nodes[child]->parents.emplace_back(G.nodes[parent]);
        G.nodes[parent]->children.emplace_back(G.nodes[child]);

    }


}

vector<Node> topologicalSort()
{
    stack<Node> stack;
    vector<Node> topOrder;

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

                if (v->color == "white") {
                    v->color = "gray";
                    for (int i = 0; i < int(v->children.size()); i++)
                    {
                        Node w = v->children[i];

                        if (w->color == "white")
                            stack.push(w);
                    }
                }   
                else if (v->color == "black") {
                    stack.pop();
                }
                else
                {
                    v->color = "black";
                    topOrder.insert(topOrder.begin(), stack.top());
                    stack.pop();
                }

            }
        }
    }
    return topOrder;
}

int main()
{

    // auto start_parse = std::chrono::system_clock::now();
    parseInput();
    // auto end_parse = std::chrono::system_clock::now();

    // std::chrono::duration<double> elapsed_seconds_parse = end_parse - start_parse;

    // std::cout << "Parse Input time: " << elapsed_seconds_parse.count() << "s\n";

    int sources = 0, longest_path = 1;

    // auto start_topologicalSort = std::chrono::system_clock::now();
    vector<Node> topOrder = topologicalSort(); //HERE
    // auto end_topologicalSort = std::chrono::system_clock::now();

    // std::chrono::duration<double> elapsed_seconds_topologicalSort = end_topologicalSort - start_topologicalSort;

    // std::cout << "Topological Sort time: " << elapsed_seconds_topologicalSort.count() << "s\n";

    // auto start_algo = std::chrono::system_clock::now();
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

    std::cout << sources << " " << longest_path << endl;

    for (int i = 0; i < int(G.nodes.size()); i++)
        delete (G.nodes[i]);

    // auto end_algo = std::chrono::system_clock::now();

    // std::chrono::duration<double> elapsed_seconds_algo = end_algo - start_algo;

    // std::cout << "Algorithm time: " << elapsed_seconds_algo.count() << "s\n";

    return 0;
}

