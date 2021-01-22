#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <string.h>
using namespace std;

vector<int> connects[101];
vector<int> country;
bool check[101];

int bfs(int node) {
	queue<int> q;
	q.push(node);
	check[node] = true;
	int count = 1;

	while (!q.empty()) {
		int front = q.front();  q.pop();

		for (int i = 0; i < connects[front].size(); i++) {
			int next = connects[front][i];

			if (!check[next]) {
				count++;
				q.push(next);
				check[next] = true;
			}
		}
	}

	return count;
}

int solution(int n, vector<vector<int>> nationality) {
	int answer = 0;

	int length = nationality.size();
	for (int i = 0; i < length; i++) {
		connects[nationality[i][0] - 1].push_back(nationality[i][1] - 1);
		connects[nationality[i][1] - 1].push_back(nationality[i][0] - 1);
	}
	// Making Graph

	memset(check, false, sizeof(check));
	for (int i = 0; i < n; i++) {
		if (!check[i]) {
			int value = bfs(i);
			country.push_back(value);
		}
	}
	// BFS for counting other country student

	length = country.size();
	for (int i = 0; i < length; i++) {
		for (int j = i + 1; j < length; j++) {
			answer += country[i] * country[j];
		}
	}
	// Solve Answer

	return answer;
}
