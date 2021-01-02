#include <iostream>
#include <string.h>
using namespace std;

struct Robot {
	int y;
	int x;
	int direction;
};

int n, m;
int map[50][50];
bool check[50][50];
Robot robot;
int dy[] = { -1, 0, 1, 0 };
int dx[] = { 0, 1, 0, -1 };

void input() {
	cin >> n >> m;
	cin >> robot.y >> robot.x >> robot.direction;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	memset(check, false, sizeof(check));
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n &&x >= 0 && x < m) {
		return true;
	}

	return false;
}

int solve() {
	int result = 1;
	check[robot.y][robot.x] = true;

	while (true) {
		int direction = robot.direction;
		bool flag = true;
		int ny, nx;

		for (int i = 0; i < 4; i++) {
			direction--;
			if (direction == -1) direction = 3;

			ny = robot.y + dy[direction];
			nx = robot.x + dx[direction];

			if (exceptionHandling(ny, nx)) {
				if (map[ny][nx] == 0 && !check[ny][nx]) {
					check[ny][nx] = true;
					robot.y = ny;
					robot.x = nx;
					robot.direction = direction;
					result++;
					flag = false;
					break;
				}
			}
		}

		if (flag) {
			int tmp;
			if (direction == 0) tmp = 2;
			else if (direction == 1) tmp = 3;
			else if (direction == 2) tmp = 0;
			else if (direction == 3) tmp = 1;

			ny = robot.y + dy[tmp];
			nx = robot.x + dx[tmp];

			if (map[ny][nx] == 0) {
				robot.y = ny;
				robot.x = nx;
				robot.direction = direction;
			}
			else {
				return result;
			}
		}
	}
}

int main() {
	input();
	cout << solve() << endl;
}