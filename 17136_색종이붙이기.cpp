#include <iostream>
#include <limits.h>
using namespace std;

const int n = 10;
int paperCount[6] = { 0, 5, 5, 5, 5, 5 };
int map[n][n];
int result = INT_MAX;

void input() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}
}

bool exceptionHandling(int y, int x) {
	if (x >= 0 && x < n && y >= 0 && y < n) {
		return true;
	}

	return false;
}

bool paperCheck(int y, int x, int length) {
	bool flag = true;

	for (int i = y; i < y + length; i++) {
		if (!flag) break;
		for (int j = x; j < x + length; j++) {
			if (exceptionHandling(i, j)) {
				if (map[i][j] == 0) {
					flag = false;
					break;
				}
			}
			else {
				flag = false;
				break;
			}
		}
	}

	return flag;
}

void solution(int y, int x, int count) {
	for (int i = y; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] == 1) {
				for (int k = 1; k <= 5; k++) {
					if (paperCount[k] > 0 && paperCheck(i, j, k)) {
						for (int a = i; a < i + k; a++) {
							for (int b = j; b < j + k; b++) {
								map[a][b] = 0;
							}
						}
						paperCount[k]--;

						solution(i, j, count + 1);

						paperCount[k]++;
						for (int a = i; a < i + k; a++) {
							for (int b = j; b < j + k; b++) {
								map[a][b] = 1;
							}
						}
					}
				}

				return;
				// 종이를 붙이지 않는 경우 이므로 가지 치기 필수!
			}
		}
	}

	if (result > count) {
		result = count;
	}
}

void output() {
	if (result == INT_MAX) result = -1;
	cout << result << endl;
}

int main() {
	input();
	solution(0, 0, 0);
	output();
}