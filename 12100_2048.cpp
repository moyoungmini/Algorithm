#include <iostream>
#include <vector>
using namespace std;

int n;
int result = 0;
int init[21][21];
int map[21][21];
vector<int> orderList;

void print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void input() {
	cin >> n;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> init[i][j];
		}
	}
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < n) {
		return true;
	}

	return false;
}

void rotate1() {
	int tmp[21][21];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmp[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[j][n - i - 1] = tmp[i][j];
		}
	}
}

void rotate2() {
	int tmp[21][21];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmp[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[n - j - 1][i] = tmp[i][j];
		}
	}
}

void move(int direction) {
	for (int i = 0; i < direction; i++) {
		rotate1();
	}

	for (int j = 0; j < n; j++) {
		for (int i = 0; i < n - 1; i++) {
			int ny = i;
			int nx = j;

			if (map[i][j] == 0) {
				while (true) {
					ny++;
					if (exceptionHandling(ny, nx)) {
						if (map[ny][nx] != 0) {
							map[i][j] = map[ny][nx];
							map[ny][nx] = 0;
							i--;
							break;
						}
					}
					else {
						i = n - 1;
						break;
					}
				}
			}
			else {
				while (true) {
					ny++;
					if (exceptionHandling(ny, nx)) {
						if (map[ny][nx] == map[i][j]) {
							map[i][j] *= 2;
							map[ny][nx] = 0;
							break;
						}
						else if (map[ny][nx] != 0 && map[ny][nx] != map[i][j]) {
							break;
						}
					}
					else {
						i = n - 1;
						break;
					}
				}
			}
		}
	}

	for (int i = 0; i < direction; i++) {
		rotate2();
	}
}

void solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = init[i][j];
		}
	}

	for (int i = 0; i < orderList.size(); i++) {
		move(orderList[i]);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j] > result) {
				result = map[i][j];
			}
		}
	}
}

void brouteForce() {

	if (orderList.size() > 5) {
		return;
	}

	if (orderList.size() > 0) {
		solve();
	}

	for (int i = 0; i < 4; i++) {
		orderList.push_back(i);
		brouteForce();
		orderList.pop_back();
	}
}

int main() {
	input();
	brouteForce();
	cout << result << endl;
}