#include <iostream>
#include <vector>
using namespace std;

struct Cordinate {
	int y;
	int x;
};

int n, m;
int map[20][20];
int dice[4][3];
int dy[] = { 0, 0, -1, 1 };
int dx[] = { 1, -1, 0, 0 };
Cordinate diceCordinate;
vector<int> v;

void input() {
	int y, x, k;

	cin >> n >> m >> y >> x >> k;

	diceCordinate.y = y;
	diceCordinate.x = x;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		cin >> y;
		v.push_back(y - 1);
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			dice[i][j] = 0;
		}
	}
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < m) {
		return true;
	}

	return false;
}

void rotateDice(int direction) {
	int tmp[4][3];
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			tmp[i][j] = dice[i][j];
		}
	}

	if (direction == 0) {
		dice[1][0] = tmp[1][1];
		dice[1][1] = tmp[1][2];
		dice[1][2] = tmp[3][1];
		dice[3][1] = tmp[1][0];
	}
	else if (direction == 1) {
		dice[1][0] = tmp[3][1];
		dice[1][1] = tmp[1][0];
		dice[1][2] = tmp[1][1];
		dice[3][1] = tmp[1][2];
	}
	else if (direction == 2) {
		dice[0][1] = tmp[3][1];
		dice[1][1] = tmp[0][1];
		dice[2][1] = tmp[1][1];
		dice[3][1] = tmp[2][1];
	}
	else if (direction == 3) {
		dice[0][1] = tmp[1][1];
		dice[1][1] = tmp[2][1];
		dice[2][1] = tmp[3][1];
		dice[3][1] = tmp[0][1];
	}
}

void solve() {
	for (int i = 0; i < v.size(); i++) {
		int ny = diceCordinate.y + dy[v[i]];
		int nx = diceCordinate.x + dx[v[i]];

		if (exceptionHandling(ny, nx)) {
			rotateDice(v[i]);

			if (map[ny][nx] == 0) {
				map[ny][nx] = dice[1][1];
			}
			else {
				dice[1][1] = map[ny][nx];
				map[ny][nx] = 0;
			}

			cout << dice[3][1] << endl;
			diceCordinate.y = ny;
			diceCordinate.x = nx;
		}
	}
}

int main() {
	input();
	solve();
}