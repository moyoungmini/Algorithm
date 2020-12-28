#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct cordinate {
	int x;
	int y;
};
int n, m;
int map[8][8];
int tmp[8][8];
int result = 0;
int dx[] = { -1, 1, 0, 0 };
int dy[] = { 0, 0, -1, 1 };

void input() {
	cin >> n >> m;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}
}

bool exceptionCheck(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < m) return true;
	return false;
}

void solve() {
	int sum = 0;
	queue<cordinate> q;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			tmp[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tmp[i][j] == 2) {
				cordinate newValue;
				newValue.y = i;
				newValue.x = j;
				q.push(newValue);
			}
		}
	}

	while (!q.empty()) {
		cordinate front = q.front();	q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = front.x + dx[i];
			int ny = front.y + dy[i];

			if (exceptionCheck(ny, nx)) {
				if (tmp[ny][nx] == 0) {
					tmp[ny][nx] = 2;
					cordinate newValue;
					newValue.y = ny;
					newValue.x = nx;
					q.push(newValue);
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (tmp[i][j] == 0) sum++;
		}
	}

	if (sum > result) result = sum;
}

void brouteForce(int y, int x, int count) {
	if (count == 3) {
		solve();
		return;
	}

	for (int i = y; i < n; i++) {
		int j;
		if (i == y) {
			j = x;
		}
		else {
			j = 0;
		}

		for (; j < m; j++) {
			if (map[i][j] == 0) {
				map[i][j] = 1;
				brouteForce(i, j, count + 1);
				map[i][j] = 0;
			}
		}
	}
}

int main() {
	input();
	brouteForce(0, 0, 0);
	cout << result << endl;
}