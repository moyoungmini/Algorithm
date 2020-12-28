#include <iostream>
#include <vector>
#include <queue>
#include <math.h>
#include <string.h>
#include <limits.h>
using namespace std;

int n;
int people[10];
vector<int> edge[10];
vector<int> leftNode;
vector<int> rightNode;
bool check[10];
int result = INT_MAX;

void solve() {
	memset(check, false, sizeof(check));
	for (int i = 0; i < rightNode.size(); i++) {
		check[rightNode[i]] = true;
	}

	queue<int> q;
	check[leftNode[0]] = true;
	q.push(leftNode[0]);
	while (!q.empty()) {
		int front = q.front();	q.pop();

		for (int i = 0; i < edge[front].size(); i++) {
			int next = edge[front][i];
			if (!check[next]) {
				check[next] = true;
				q.push(next);
			}
		}
	}

	for (int i = 0; i < leftNode.size(); i++) {
		if (!check[leftNode[i]]) {
			return;
		}
	}
	// 왼쪽 팀 갈 수 있는지 체크

	memset(check, false, sizeof(check));
	for (int i = 0; i < leftNode.size(); i++) {
		check[leftNode[i]] = true;
	}

	check[rightNode[0]] = true;
	q.push(rightNode[0]);
	while (!q.empty()) {
		int front = q.front();	q.pop();

		for (int i = 0; i < edge[front].size(); i++) {
			int next = edge[front][i];
			if (!check[next]) {
				check[next] = true;
				q.push(next);
			}
		}
	}

	for (int i = 0; i < rightNode.size(); i++) {
		if (!check[rightNode[i]]) {
			return;
		}
	}
	//오른쪽 팀 갈 수 있는지 체크

	int leftSum = 0;
	int rightSum = 0;

	for (int i = 0; i < leftNode.size(); i++) {
		leftSum += people[leftNode[i]];
	}
	for (int i = 0; i < rightNode.size(); i++) {
		rightSum += people[rightNode[i]];
	}

	if (result > abs(leftSum - rightSum)) {
		result = abs(leftSum - rightSum);
	}

}

void reculsive(int index) {
	if (index == n) {
		if (leftNode.size() == 0 || rightNode.size() == 0) return;
		solve();
		return;
	}
	leftNode.push_back(index);
	reculsive(index + 1);
	leftNode.pop_back();

	rightNode.push_back(index);
	reculsive(index + 1);
	rightNode.pop_back();
}

void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> people[i];
	}

	int tmp, count;
	for (int i = 0; i < n; i++) {
		cin >> count;
		for (int j = 0; j < count; j++) {
			cin >> tmp;
			edge[i].push_back(tmp - 1);
		}
	}
}

int main() {
	input();
	reculsive(0);

	if (result == INT_MAX) result = -1;
	cout << result << endl;
}
