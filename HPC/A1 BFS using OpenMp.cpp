#include <iostream>
#include <vector>
#include <queue>
#include <omp.h>
#include <cstring>

using namespace std;

const int MAX = 100000;
vector<int> graph[MAX];

void bfs_sequential(int start, bool visited[]) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    cout << "\nSequential BFS Traversal: ";
    while (!q.empty()) {
        int node = q.front(); q.pop();
        cout << node << " ";
        for (int j = 0; j < graph[node].size(); j++) {
            int neighbor = graph[node][j];
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                q.push(neighbor);
            }
        }
    }
    cout << endl;
}

void bfs_parallel(int start, bool visited[]) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    cout << "\nParallel BFS Traversal: ";
    while (!q.empty()) {
        int qSize = q.size();
        vector<int> nextLevel;

        for (int i = 0; i < qSize; i++) {
            int node = q.front(); q.pop();
            cout << node << " ";

            for (int j = 0; j < graph[node].size(); j++) {
                int neighbor = graph[node][j];
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    nextLevel.push_back(neighbor);
                }
            }
        }

        for (int i = 0; i < nextLevel.size(); i++) {
            q.push(nextLevel[i]);
        }
    }
    cout << endl;
}

int main() {
    int n, m, start_node;

    cout << "Enter No of Nodes, Edges, and Start Node: ";
    cin >> n >> m >> start_node;

    cout << "Enter Pairs of Edges:\n";
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }

    bool visited_seq[MAX], visited_par[MAX];
    memset(visited_seq, false, sizeof(visited_seq));
    memset(visited_par, false, sizeof(visited_par));

    double start, end;

    // Time Sequential BFS
    start = omp_get_wtime();
    bfs_sequential(start_node, visited_seq);
    end = omp_get_wtime();
    cout << "Time taken by Sequential BFS: " << end - start << " seconds\n";

    // Time Parallel BFS
    start = omp_get_wtime();
    bfs_parallel(start_node, visited_par);
    end = omp_get_wtime();
    cout << "Time taken by Parallel BFS: " << end - start << " seconds\n";

    return 0;
}
