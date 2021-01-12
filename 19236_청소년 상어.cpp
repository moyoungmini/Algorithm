#include <iostream>
using namespace std;

struct Cordinate {
	int y;
	int x;
	int direction;
};

struct Fish {
	Cordinate cordinate;
	bool exist = true;
	int index;
};

const int n = 4;
const int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
const int dx[] = { 0, -1, -1, -1, 0, 1, 1, 1 };
int map[n][n];
int result = 0;
Cordinate shark;
Fish fishList[n*n];

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n &&x >= 0 && x < n) return true;

	return false;
}

void moveFish() {
	for (int i = 0; i < n*n; i++) {
		if (fishList[i].exist) {
			int y = fishList[i].cordinate.y;
			int x = fishList[i].cordinate.x;
			int d = fishList[i].cordinate.direction;

			int ny = y;
			int nx = x;
			for (int j = 0; j < 8; j++) {
				ny = y + dy[d];
				nx = x + dx[d];

				if (exceptionHandling(ny, nx) && !(shark.y == ny && shark.x == nx)) {
					fishList[i].cordinate.direction = d;
					fishList[i].cordinate.y = ny;
					fishList[i].cordinate.x = nx;
					fishList[map[ny][nx]].cordinate.y = y;
					fishList[map[ny][nx]].cordinate.x = x;

					int tmp = map[ny][nx];
					map[ny][nx] = i;
					map[y][x] = tmp;
					break;
				}

				d = (d + 1) % 8;
			}

		}
	}
}

void brouteForce(int sum) {
	int tmpMap[n][n];
	Fish tmpFishList[n*n];

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			tmpMap[i][j] = map[i][j];
		}
	}
	for (int i = 0; i < n*n; i++) {
		tmpFishList[i] = fishList[i];
	}

	sum += fishList[map[shark.y][shark.x]].index + 1;
	shark.direction = fishList[map[shark.y][shark.x]].cordinate.direction;
	fishList[map[shark.y][shark.x]].exist = false;
	if (sum > result) result = sum;
	// Catch Fish

	moveFish();
	// Move Fish

	int y = shark.y;
	int x = shark.x;
	int d = shark.direction;

	while (true) {
		y += dy[d];
		x += dx[d];

		if (!exceptionHandling(y, x)) break;

		if (fishList[map[y][x]].exist) {
			shark.y = y;
			shark.x = x;
			brouteForce(sum);
		}
	}
	// Move Shark

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j] = tmpMap[i][j];
		}
	}
	for (int i = 0; i < n * n; i++) {
		fishList[i] = tmpFishList[i];
	}
}

void input() {
	int index, direction;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> index >> direction;
			fishList[index - 1].cordinate.y = i;
			fishList[index - 1].cordinate.x = j;
			fishList[index - 1].cordinate.direction = direction - 1;
			fishList[index - 1].index = index - 1;
			map[i][j] = index - 1;
		}
	}
}

int main() {
	input();
	brouteForce(0);
	cout << result << endl;
}