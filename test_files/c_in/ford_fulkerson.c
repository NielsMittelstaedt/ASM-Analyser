#include <stdio.h>

#define A 0
#define B 1
#define C 2
#define MAX_NODES 50
#define O 1000000000

int num;
int e;
int capacity[MAX_NODES][MAX_NODES];
int flow[MAX_NODES][MAX_NODES];
int color[MAX_NODES];
int pred[MAX_NODES];

int min(int x, int y) {
  return x < y ? x : y;
}

int head, tail;
int q[MAX_NODES + 2];

void enqueue(int x) {
  q[tail] = x;
  tail++;
  color[x] = B;
}

int dequeue() {
  int x = q[head];
  head++;
  color[x] = C;
  return x;
}

// Using BFS as a searching algorithm
int bfs(int start, int target) {
  int u, v;
  for (u = 0; u < num; u++) {
    color[u] = A;
  }
  head = tail = 0;
  enqueue(start);
  pred[start] = -1;
  while (head != tail) {
    u = dequeue();
    for (v = 0; v < num; v++) {
      if (color[v] == A && capacity[u][v] - flow[u][v] > 0) {
        enqueue(v);
        pred[v] = u;
      }
    }
  }
  return color[target] == C;
}

// Applying fordfulkerson algorithm
int fordFulkerson(int source, int sink) {
  int i, j, u;
  int max_flow = 0;
  for (i = 0; i < num; i++) {
    for (j = 0; j < num; j++) {
      flow[i][j] = 0;
    }
  }

  // Updating the residual values of edges
  while (bfs(source, sink)) {
    int increment = O;
    for (u = num - 1; pred[u] >= 0; u = pred[u]) {
      increment = min(increment, capacity[pred[u]][u] - flow[pred[u]][u]);
    }
    for (u = num - 1; pred[u] >= 0; u = pred[u]) {
      flow[pred[u]][u] += increment;
      flow[u][pred[u]] -= increment;
    }
    // Adding the path flows
    max_flow += increment;
  }

  return max_flow;
}

int main() {
  for (int i = 0; i < num; i++) {
    for (int j = 0; j < num; j++) {
      capacity[i][j] = 0;
    }
  }
  num = 16;
  e = 33;

  capacity[0][1] = 1;
  capacity[0][2] = 1;
  capacity[0][3] = 1;
  capacity[0][4] = 1;
  capacity[0][5] = 1;
  capacity[0][6] = 1;
  capacity[0][7] = 1;

  capacity[1][9] = 1;
  capacity[1][13] = 1;
  capacity[2][9] = 1;
  capacity[2][11] = 1;
  capacity[3][8] = 1;
  capacity[3][10] = 1;
  capacity[3][12] = 1;
  capacity[4][8] = 1;
  capacity[4][10] = 1;
  capacity[4][12] = 1;
  capacity[5][9] = 1;
  capacity[5][11] = 1;
  capacity[5][13] = 1;
  capacity[6][10] = 1;
  capacity[6][11] = 1;
  capacity[6][12] = 1;
  capacity[6][13] = 1;
  capacity[6][14] = 1;
  capacity[7][13] = 1;

  capacity[8][15] = 1;
  capacity[9][15] = 1;
  capacity[10][15] = 1;
  capacity[11][15] = 1;
  capacity[12][15] = 1;
  capacity[13][15] = 1;
  capacity[14][15] = 1;

  int s = 0, t = 15;
  printf("Max Flow: %d\n", fordFulkerson(s, t));
}