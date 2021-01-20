#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <math.h>
#include <string.h>
#include <limits.h>
using namespace std;

struct Node {
	int parkingNumber;
	vector<int> connects;
};

Node trees[100001];
bool check[100001];

int calculate(int n1, int n2, int n) {
	memset(check, false, sizeof(check));

	queue<int> q;
	int sum1 = 0;
	int sum2 = 0;
	bool flag = false;

	for (int i = 0; i < n; i++) {
		if (!check[i]) {
			q.push(i);
			if (flag) sum1 += trees[i].parkingNumber;
			else sum2 += trees[i].parkingNumber;
			check[i] = true;

			while (!q.empty()) {
				int front = q.front();  q.pop();

				for (int j = 0; j < trees[front].connects.size(); j++) {
					int next = trees[front].connects[j];

					if (!check[next]) {
						if ((front == n1 && next == n2) || (front == n2 && next == n1)) {
							flag = true;
							continue;
						}

						if (flag) sum1 += trees[next].parkingNumber;
						else sum2 += trees[next].parkingNumber;
						check[next] = true;
						q.push(next);
					}
				}
			}
		}
	}

	return abs(sum1 - sum2);
}

int solution(int n, vector<int> cars, vector<vector<int>> links) {
	int answer = INT_MAX;

	for (int i = 0; i < n; i++) {
		trees[i].parkingNumber = cars[i];
	}

	int length = links.size();
	for (int i = 0; i < length; i++) {
		trees[links[i][0] - 1].connects.push_back(links[i][1] - 1);
		trees[links[i][1] - 1].connects.push_back(links[i][0] - 1);
	}
	// Making Tree

	for (int i = 0; i < length; i++) {
		int value = calculate(links[i][0] - 1, links[i][1] - 1, n);
		if (value < answer) answer = value;
	}
	// BrouteForce & BFS

	return answer;
}
