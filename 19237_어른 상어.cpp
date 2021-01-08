#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
using namespace std;

int n, m, k;

class Smell {
public:
	int sharkIndex;
	int startTime;
public:
	Smell() {
		sharkIndex = -1;
		startTime = -1;
	}

	bool isGoShark(int time) {
		if (startTime == -1) return true;
		if (startTime + k <= time) return true;

		return false;
	}
};

class Shark {
public:
	int index;
	int y;
	int x;
	int direction;
	int priority[4][4];
	bool exist;
public:
	Shark() { exist = true; }

	bool operator < (Shark & shark) {
		if (this->index < shark.index) return true;

		return false;
	}
};

Smell map[20][20];
vector<Shark> sharkList;

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n&&x >= 0 && x < n) return true;

	return false;
}

void spreadSmell(int time) {
	for (int i = 0; i < m; i++) {
		if (sharkList[i].exist) {
			map[sharkList[i].y][sharkList[i].x].sharkIndex = i;
			map[sharkList[i].y][sharkList[i].x].startTime = time;
		}
	}
}

int moveSharks(int time) {
	int sharkMap[20][20];
	memset(sharkMap, -1, sizeof(sharkMap));
	int result = 0;

	for (int i = 0; i < m; i++) {
		if (sharkList[i].exist) {
			int direction = sharkList[i].direction;
			int y = sharkList[i].y;
			int x = sharkList[i].x;
			int ny, nx, nextDirection;
			bool flag = true;

			for (int j = 0; j < 4; j++) {
				nextDirection = sharkList[i].priority[direction][j];
				ny = y + dy[nextDirection];
				nx = x + dx[nextDirection];

				if (exceptionHandling(ny, nx) && map[ny][nx].isGoShark(time)) {
					flag = false;
					break;
				}
			}

			if (flag) {
				for (int j = 0; j < 4; j++) {
					nextDirection = sharkList[i].priority[direction][j];
					ny = y + dy[nextDirection];
					nx = x + dx[nextDirection];

					if (exceptionHandling(ny, nx) && map[ny][nx].sharkIndex == i) {
						flag = false;
						break;
					}
				}
			}

			if (sharkMap[ny][nx] == -1) {
				sharkList[i].y = ny;	sharkList[i].x = nx;
				sharkList[i].direction = nextDirection;
				sharkMap[ny][nx] = i;
			}
			else {
				if (sharkMap[ny][nx] < i) {
					sharkList[i].exist = false;
				}
				else {
					sharkList[i].y = ny;	sharkList[i].x = nx;
					sharkList[i].direction = nextDirection;
					sharkList[sharkMap[ny][nx]].exist = false;
					sharkMap[ny][nx] = i;
				}

				result++;
			}
		}
	}

	return result;
}

void input() {
	cin >> n >> m >> k;

	int input;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> input;

			if (input != 0) {
				Shark shark;
				shark.index = input;
				shark.y = i;	shark.x = j;
				sharkList.push_back(shark);
			}
		}
	}

	sort(sharkList.begin(), sharkList.end());

	for (int i = 0; i < m; i++) {
		cin >> input;
		sharkList[i].direction = input - 1;
	}

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				cin >> input;
				sharkList[i].priority[j][k] = input - 1;
			}
		}
	}
}

int solve() {
	int eraseShark = 0;
	spreadSmell(0);

	for (int t = 0; t < 1000; t++) {
		eraseShark += moveSharks(t);
		spreadSmell(t + 1);

		if (eraseShark == m - 1) return t + 1;
	}

	return -1;
}

int main() {
	input();
	cout << solve() << endl;
}