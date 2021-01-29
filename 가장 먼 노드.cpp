#include <string>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

vector<int> edges[20000];

int bfs(int n) {
	queue<int> q;
	q.push(0);
	int check[20000];
	memset(check, -1, sizeof(check));
	check[0] = 0;

	while (!q.empty()) {
		int front = q.front();  q.pop();

		for (int i = 0; i < edges[front].size(); i++) {
			int next = edges[front][i];
			if (check[next] == -1) {
				check[next] = check[front] + 1;
				q.push(next);
			}
		}
	}

	int max = 0;
	int result = 0;
	for (int i = 0; i < n; i++) {
		if (max < check[i]) {
			max = check[i];
			result = 1;
		}
		else if (max == check[i]) {
			result++;
		}
	}

	return result;
}

int solution(int n, vector<vector<int>> edge) {
	int answer = 0;
	int length = edge.size();
	for (int i = 0; i < length; i++) {
		edges[edge[i][0] - 1].push_back(edge[i][1] - 1);
		edges[edge[i][1] - 1].push_back(edge[i][0] - 1);
	}


	return bfs(n);
}