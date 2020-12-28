#include <iostream>
#include <queue>
#include <algorithm>
#include <string.h>
#include <limits.h>
using namespace std;

struct cordinate {
	int x;
	int y;
};

class Edge {
public:
	int n1;
	int n2;
	int weight;
public:
	Edge() {}
	bool operator <(Edge & edge) {
		if (this->weight > edge.weight) {
			return false;
		}
		else if (this->weight == edge.weight) {
			return false;
		}
		else {
			return true;
		}
	}
};

int n, m;
int map[10][10];
int value[6][6];
int islandCount = 0;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };
vector<Edge> edgeList;

bool exceptionHandling(int y, int x) {
	if (x >= 0 && x < m && y >= 0 && y < n) {
		return true;
	}

	return false;
}

void divideIsland() {
	bool check[10][10];
	memset(check, false, sizeof(check));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 1 && !check[i][j]) {
				cordinate init;
				init.x = j;
				init.y = i;
				queue<cordinate> q;
				q.push(init);
				check[i][j] = true;
				islandCount++;
				map[i][j] = islandCount;

				while (!q.empty()) {
					cordinate front = q.front();	q.pop();

					for (int k = 0; k < 4; k++) {
						int nx = front.x + dx[k];
						int ny = front.y + dy[k];

						if (exceptionHandling(ny, nx) && map[ny][nx] == 1 && !check[ny][nx]) {
							check[ny][nx] = true;
							map[ny][nx] = islandCount;
							cordinate newValue;
							newValue.x = nx;
							newValue.y = ny;
							q.push(newValue);
						}
					}
				}
			}
		}
	}
}

void solveDistance() {
	for (int i = 0; i < islandCount; i++) {
		for (int j = 0; j < islandCount; j++) {
			if (i == j) value[i][j] = 0;
			else value[i][j] = INT_MAX;
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] != 0) {
				for (int k = 0; k < 4; k++) {
					int nx = j;
					int ny = i;
					int length = 0;

					while (true) {
						nx += dx[k];
						ny += dy[k];
						if (!exceptionHandling(ny, nx) || map[ny][nx] == map[i][j]) {
							break;
						}
						else if (map[ny][nx] == 0) {
							length++;
						}
						else {
							int n1 = map[i][j] - 1;
							int n2 = map[ny][nx] - 1;
							if (length >= 2 && value[n1][n2] > length) {
								value[n1][n2] = length;
								value[n2][n1] = length;
							}
							break;
						}
					}
				}
			}
		}
	}
}

int mst() {
	for (int i = 0; i < islandCount; i++) {
		for (int j = i + 1; j < islandCount; j++) {
			if (value[i][j] > 0 && value[i][j] < INT_MAX) {
				Edge newEdge;
				newEdge.n1 = i;
				newEdge.n2 = j;
				newEdge.weight = value[i][j];
				edgeList.push_back(newEdge);
			}
		}
	}
	sort(edgeList.begin(), edgeList.end());

	int node[6];
	int sum = 0;
	for (int i = 0; i < islandCount; i++) {
		node[i] = i;
	}

	for (int i = 0; i < edgeList.size(); i++) {
		int n1 = edgeList[i].n1;
		int n2 = edgeList[i].n2;
		if (node[n1] != node[n2]) {
			int parent = node[n1];
			for (int j = 0; j < islandCount; j++) {
				if (node[j] == parent) {
					node[j] = node[n2];
				}
			}
			sum += edgeList[i].weight;
		}
	}

	int parent = node[0];
	for (int i = 0; i < islandCount; i++) {
		if (node[i] != parent) {
			return -1;
		}
	}

	return sum;
}

int main() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	divideIsland();
	solveDistance();
	int result = mst();

	cout << result << endl;
}