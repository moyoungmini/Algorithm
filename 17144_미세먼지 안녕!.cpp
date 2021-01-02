#include <iostream>
#include <string.h>
using namespace std;

struct Cordinate {
	int y;
	int x;
};

int n, m, k;
int map[50][50];
int tmp[50][50];
int dy[2][4] = { { 0, -1, 0, 1 }, { 0, 1, 0, -1 } };
int dx[2][4] = { { 1, 0, -1, 0 }, { 1, 0, -1, 0 } };
Cordinate aircordinate[2];

void input() {
	cin >> n >> m >> k;
	aircordinate[0].y = -1;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];

			if (map[i][j] == -1) {
				if (aircordinate[0].y == -1) {
					aircordinate[0].y = i;
					aircordinate[0].x = j;
				}
				else {
					aircordinate[1].y = i;
					aircordinate[1].x = j;
				}
			}
		}
	}
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < m) return true;

	return false;
}

void dustSpread() {
	memset(tmp, 0, sizeof(tmp));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] >= 5) {
				int count = 0;

				for (int k = 0; k < 4; k++) {
					int ny = i + dy[0][k];
					int nx = j + dx[0][k];

					if (exceptionHandling(ny, nx) && map[ny][nx] != -1) {
						count++;
						tmp[ny][nx] += map[i][j] / 5;
					}
				}

				if (count > 0) {
					tmp[i][j] = tmp[i][j] - (map[i][j] / 5) * count;
				}
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			map[i][j] += tmp[i][j];
		}
	}
}

void runAir() {
	int y, x, direction;

	for (int i = 0; i < 2; i++) {
		direction = 0;
		y = aircordinate[i].y + dy[i][direction];
		x = aircordinate[i].x + dx[i][direction];

		int move = map[y][x];
		map[y][x] = 0;

		while (direction < 4) {
			y += dy[i][direction];
			x += dx[i][direction];

			if (exceptionHandling(y, x) && map[y][x] != -1) {
				int tmp = map[y][x];
				map[y][x] = move;
				move = tmp;
			}
			else {
				y -= dy[i][direction];
				x -= dx[i][direction];
				direction++;
			}

		}
	}
}

int calculate() {
	int sum = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] != -1) sum += map[i][j];
		}
	}

	return sum;
}

int main() {
	input();

	for (int i = 0; i < k; i++) {
		dustSpread();
		runAir();
	}

	cout << calculate() << endl;
}