#include <iostream>
using namespace std;

int n, m;
int map[100][100];

void input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

void rotate() {
	int tmp[100][100];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmp[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[j][n - 1 - i] = tmp[i][j];
		}
	}
}

int calculate() {
	int sum = 0;

	for (int i = 0; i < n; i++) {
		int value = map[i][0];
		int count = 1;
		bool flag = true;

		for (int j = 1; j < n; j++) {
			if (value == map[i][j]) {
				count++;
			}
			else if (value == map[i][j] + 1) {
				int k;
				for (k = 0; k < m; k++) {
					if (value - 1 != map[i][j + k]) {
						flag = false;
						break;
					}
				}
				if (flag) {
					j = j + k - 1;
					value = map[i][j];
					count = 0;
				}
			}
			else if (value + 1 == map[i][j]) {
				if (count >= m) {
					value = map[i][j];
					count = 1;
				}
				else {
					flag = false;
					break;
				}
			}
			else {
				flag = false;
				break;
			}
		}

		if (flag) {
			sum++;
		}
	}

	return sum;
}

int main() {
	input();
	int horizontal = calculate();
	rotate();
	int vertical = calculate();

	cout << horizontal + vertical << endl;
}
