#include <iostream>
#include <vector>
#include <math.h>
#include <limits.h>
using namespace std;

int n;
int map[20][20];
int result = INT_MAX;
vector<int> leftTeam;
vector<int> rightTeam;

void input() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

void solve() {
	int leftSum = 0;
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n / 2; j++) {
			leftSum += map[leftTeam[i]][leftTeam[j]];
		}
	}

	int rightSum = 0;
	for (int i = 0; i < n / 2; i++) {
		for (int j = 0; j < n / 2; j++) {
			rightSum += map[rightTeam[i]][rightTeam[j]];
		}
	}

	if (abs(leftSum - rightSum) < result) {
		result = abs(leftSum - rightSum);
	}
}

void brouteForce(int index) {
	if (index == n) {
		if (leftTeam.size() == rightTeam.size()) {
			solve();
		}
		return;
	}

	if (leftTeam.size() < n / 2) {
		leftTeam.push_back(index);
		brouteForce(index + 1);
		leftTeam.pop_back();
	}

	if (rightTeam.size() < n / 2) {
		rightTeam.push_back(index);
		brouteForce(index + 1);
		rightTeam.pop_back();
	}
}

int main() {
	input();
	brouteForce(0);
	cout << result << endl;
}