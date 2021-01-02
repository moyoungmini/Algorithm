#include <iostream>
#include <vector>
#include <limits.h>
using namespace std;

int n;
vector<int> numList;
vector<int> operList;
int operCount[4];
int resultMax = INT_MIN;
int resultMin = INT_MAX;

void input() {
	cin >> n;

	int input;
	for (int i = 0; i < n; i++) {
		cin >> input;
		numList.push_back(input);
	}

	for (int i = 0; i < 4; i++) {
		cin >> operCount[i];
	}
}

void solve() {
	int value = numList[0];

	for (int i = 0; i < n - 1; i++) {
		if (operList[i] == 0) {
			value += numList[i + 1];
		}
		else if (operList[i] == 1) {
			value -= numList[i + 1];
		}
		else if (operList[i] == 2) {
			value *= numList[i + 1];
		}
		else if (operList[i] == 3) {
			value /= numList[i + 1];
		}
	}

	if (value > resultMax) {
		resultMax = value;
	}
	if (value < resultMin) {
		resultMin = value;
	}
}

void brouteForce() {
	if (operList.size() == n - 1) {
		solve();
		return;
	}

	for (int i = 0; i < 4; i++) {
		if (operCount[i] > 0) {
			operList.push_back(i);
			operCount[i] --;
			brouteForce();
			operList.pop_back();
			operCount[i]++;
		}
	}
}

int main() {
	input();
	brouteForce();
	cout << resultMax << '\n' << resultMin << '\n';

}