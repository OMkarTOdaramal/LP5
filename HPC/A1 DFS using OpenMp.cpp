#include <iostream>
#include <vector>
#include <omp.h>
#include <stack>
#include <cstring>

using namespace std;

void dfs_sequential(int node, const vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> s;
    s.push(node);
    visited[node] = true;

    cout << "\nSequential DFS Traversal: ";
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << current << " ";

        for (int i = 0; i < graph[current].size(); i++) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                s.push(neighbor);
            }
        }
    }
    cout << endl;
}

void dfs_parallel(int node, const vector<vector<int>>& graph, vector<bool>& visited) {
    stack<int> s;
    s.push(node);
    visited[node] = true;

    cout << "\nParallel DFS Traversal: ";
    while (!s.empty()) {
        int current = s.top();
        s.pop();
        cout << current << " ";

        #pragma omp parallel for
        for (int i = 0; i < graph[current].size(); i++) {
            int neighbor = graph[current][i];
            if (!visited[neighbor]) {
                #pragma omp critical
                {
                    if (!visited[neighbor]) {
                        visited[neighbor] = true;
                        s.push(neighbor);
                    }
                }
            }
        }
    }
    cout << endl;
}

int main() {
    int n, e;
    cout << "Enter the number of nodes: ";
    cin >> n;

    cout << "Enter the number of edges: ";
    cin >> e;

    vector<vector<int>> graph(n);

    cout << "Enter the edges (u v):\n";
    for (int i = 0; i < e; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);  // Undirected graph
    }

    int start_node;
    cout << "Enter the starting node for DFS: ";
    cin >> start_node;

    vector<bool> visited_seq(n, false);
    vector<bool> visited_par(n, false);

    double start, end;

    // Sequential DFS
    start = omp_get_wtime();
    dfs_sequential(start_node, graph, visited_seq);
    end = omp_get_wtime();
    cout << "Time taken by Sequential DFS: " << end - start << " seconds\n";

    // Parallel DFS
    start = omp_get_wtime();
    dfs_parallel(start_node, graph, visited_par);
    end = omp_get_wtime();
    cout << "Time taken by Parallel DFS: " << end - start << " seconds\n";

    return 0;
}
