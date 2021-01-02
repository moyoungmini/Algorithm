#include <iostream>
using namespace std;

int n, m;
int map[500][500];
int result = 0;

int dy[][4] = {
	{0, 0, 0, 0}, {0, 1, 2, 3},
	{0, 0, 1, 1},
	{0, 1, 2, 2}, {0, 0, 0, 1}, {0, 0, 1, 2}, {0, 1, 1, 1}, {0, 1, 2, 2}, {0, 1, 1, 1}, {0, 0, 1, 2}, {0, 0, 0, 1},
	{0, 1, 1, 2}, {0, 0, 1, 1}, {0, 1, 1, 2}, {0, 0, 1, 1},
	{0, 0, 0, 1}, {0, 1, 1, 2}, {0, 1, 1, 1}, {0, 1, 1, 2}
};

int dx[][4] = {
	{0, 1, 2, 3}, {0, 0, 0, 0},
	{0, 1, 0, 1},
	{0, 0, 0, 1}, {0, 1, 2, 0}, {0, 1, 1, 1}, {0, 0, -1, -2}, {0, 0, 0, -1}, {0, 0, 1, 2}, {0, 1, 0, 0}, {0, 1, 2, 2},
	{0, 0, 1, 1}, {0, -1, -1, -2}, {0, 0, -1, -1}, {0, 1, 1, 2},
	{0, 1, 2, 1}, {0, -1, 0, 0}, {0, -1, 0, 1}, {0, 0, 1, 0}
};

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n &&x >= 0 && x < m) {
		return true;
	}

	return false;
}

void solve() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {

			for (int a = 0; a < 19; a++) {
				int tmp = 0;
				bool flag = true;

				for (int b = 0; b < 4; b++) {
					int ny = i + dy[a][b];
					int nx = j + dx[a][b];

					if (exceptionHandling(ny, nx)) {
						tmp += map[ny][nx];
					}
					else {
						flag = false;
						break;
					}
				}

				if (flag && result < tmp) {
					result = tmp;
				}
			}
		}
	}
}

void input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
}

int main() {
	input();
	solve();
	cout << result << endl;
}