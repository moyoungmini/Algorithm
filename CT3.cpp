#include <string>
#include <vector>
#include <string.h>
#include <limits.h>
using namespace std;

class Edge {
public:
	int time;
	int pay;
public:
	Edge(int time, int pay) {
		this->time = time;
		this->pay = pay;
	}
	Edge() { time = -1; pay = -1; }
};

int n;
int minsuPay;
Edge map[101][101];
bool check[101];
int answer = INT_MAX;

void dfs(int node, int pay, int time) {
	if (time > answer) return;
	// Back Tracking

	if (node == n - 1) {
		if (answer > time) answer = time;
		return;
	}
	// Finish

	for (int next = 0; next < n; next++) {
		if (map[node][next].pay != -1 && pay + map[node][next].pay <= minsuPay) {
			check[next] = true;
			dfs(next, pay + map[node][next].pay, time + map[node][next].time);
			check[next] = false;
		}
	}
	// Next Node
}

int solution(int inputN, int m, vector<vector<int>> paths) {
	n = inputN;
	minsuPay = m;

	int length = paths.size();
	for (int i = 0; i < length; i++) {
		map[paths[i][0] - 1][paths[i][1] - 1].time = paths[i][2];
		map[paths[i][0] - 1][paths[i][1] - 1].pay = paths[i][3];

		map[paths[i][1] - 1][paths[i][0] - 1].time = paths[i][2];
		map[paths[i][1] - 1][paths[i][0] - 1].pay = paths[i][3];
	}
	// Making Graph

	memset(check, false, sizeof(check));
	check[0] = true;
	dfs(0, 0, 0);
	// BrouteForece

	if (answer == INT_MAX) answer = -1;
	return answer;
}