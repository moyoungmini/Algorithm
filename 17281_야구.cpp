#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int n;
int value[50][9];
bool check[9];
int result = 0;
vector<int> indexList;

void input() {
	cin >> n;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 9; j++) {
			cin >> value[i][j];
		}
	}
}

void calculate() {
	int score = 0;
	int running = 0;
	for (int i = 0; i < n; i++) {
		int out = 0;
		bool base[3] = { false ,false, false };
		while (true) {
			int index = indexList[running];
			running++;
			if (running == 9) running = 0;

			if (value[i][index] == 0) {
				out++;
				if (out == 3) {
					break;
				}
			}
			else if (value[i][index] == 1) {
				if (base[2]) {
					score++;
					base[2] = false;
				}
				if (base[1]) {
					base[2] = true;
					base[1] = false;
				}
				if (base[0]) {
					base[1] = true;
					base[0] = false;
				}
				base[0] = true;
			}
			else if (value[i][index] == 2) {
				if (base[2]) {
					score++;
					base[2] = false;
				}
				if (base[1]) {
					score++;
					base[1] = false;
				}
				if (base[0]) {
					base[2] = true;
					base[0] = false;
				}
				base[1] = true;
			}
			else if (value[i][index] == 3) {
				if (base[2]) {
					score++;
					base[2] = false;
				}
				if (base[1]) {
					score++;
					base[1] = false;
				}
				if (base[0]) {
					score++;
					base[0] = false;
				}
				base[2] = true;
			}
			else {
				if (base[2]) {
					score++;
					base[2] = false;
				}
				if (base[1]) {
					score++;
					base[1] = false;
				}
				if (base[0]) {
					score++;
					base[0] = false;
				}
				score++;
			}
		}
	}

	if (result < score) result = score;
}

void reculsive() {
	if (indexList.size() == 4 && indexList[3] != 0) {
		return;
	}
	if (indexList.size() == 9) {
		calculate();
		return;
	}

	for (int i = 0; i < 9; i++) {
		if (!check[i]) {
			check[i] = true;
			indexList.push_back(i);

			reculsive();

			check[i] = false;
			indexList.pop_back();
		}
	}
}

void solution() {
	memset(check, false, sizeof(check));
	reculsive();
	cout << result << endl;
}

int main() {
	input();
	solution();
}