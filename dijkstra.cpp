#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>

using namespace std;

struct Edge
{
  char dest;
  int weight;
  Edge(char d, int w) : dest(d), weight(w) {}
};

void dijkstra(vector<vector<Edge>> &graph, char start, char end)
{
  int V = 5;
  int start_idx = start - 'A';
  int end_idx = end - 'A';

  vector<int> dist(V, INT_MAX);
  vector<bool> visited(V, false);
  vector<int> parent(V, -1);

  priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

  dist[start_idx] = 0;
  pq.push({0, start_idx});

  while (!pq.empty())
  {
    int curr_dist = pq.top().first;
    int curr = pq.top().second;
    pq.pop();

    if (visited[curr])
      continue;
    visited[curr] = true;

    if (curr == end_idx)
      break;

    for (const Edge &edge : graph[curr])
    {
      int neighbor = edge.dest - 'A';
      int weight = edge.weight;

      if (!visited[neighbor] && curr_dist + weight < dist[neighbor])
      {
        dist[neighbor] = curr_dist + weight;
        parent[neighbor] = curr;
        pq.push({dist[neighbor], neighbor});
      }
    }
  }

  if (dist[end_idx] == INT_MAX)
  {
    cout << "No path from " << start << " to " << end << endl;
    return;
  }

  vector<char> path;
  int curr = end_idx;
  while (curr != -1)
  {
    path.push_back(static_cast<char>('A' + curr));
    curr = parent[curr];
  }

  cout << "Shortest path from " << start << " to " << end << ": ";
  for (int i = path.size() - 1; i > 0; i--)
  {
    cout << path[i] << " -> ";
  }
  cout << path[0] << endl;
  cout << "Total cost: " << dist[end_idx] << endl;
}

int main()
{
  vector<vector<Edge>> graph(5);

  graph[0].push_back(Edge('B', 10)); // A->B
  graph[0].push_back(Edge('E', 3));  // A->E
  graph[4].push_back(Edge('B', 1));  // E->B
  graph[4].push_back(Edge('C', 2));  // E->C
  graph[1].push_back(Edge('C', 8));  // B->C
  graph[1].push_back(Edge('D', 2));  // B->D
  graph[2].push_back(Edge('D', 7));  // C->D
  graph[3].push_back(Edge('E', 4));  // D->E

  char start, end;
  cout << "Enter start node (A-E): ";
  cin >> start;
  cout << "Enter end node (A-E): ";
  cin >> end;

  if (start < 'A' || start > 'E' || end < 'A' || end > 'E')
  {
    cout << "Invalid nodes! Use A, B, C, D, or E." << endl;
    return 1;
  }

  dijkstra(graph, start, end);

  return 0;
}
