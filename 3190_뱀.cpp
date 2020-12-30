#include <iostream>
#include <vector>
#include <deque>
#include <string.h>
using namespace std;

struct Com {
	int time;
	char direction;
};

struct Cordinate {
	int y;
	int x;
};

int n;
int map[100][100];
int dy[] = { 1, -1, 0, 0 };
int dx[] = { 0, 0, 1, -1 };
deque<Cordinate> dq;
deque<Com> changeDq;

void input() {
	int m, y, x, time;
	char direction;
	memset(map, 0, sizeof(map));
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		cin >> y >> x;
		map[y - 1][x - 1] = 1;
	}

	cin >> m;

	for (int i = 0; i < m; i++) {
		cin >> time >> direction;
		Com com;
		com.time = time;
		com.direction = direction;
		changeDq.push_back(com);
	}

	Cordinate init;
	init.y = 0;
	init.x = 0;
	dq.push_back(init);
	map[0][0] = 2;
}
// 0 : EMPTY + 1 : APPLE + 2 : SNAIL

bool exceptionHandling(int y, int x) {
	if (x >= 0 && x < n &&y >= 0 && y < n) {
		return true;
	}

	return false;
}

int solve() {
	int time;
	int direction = 2;

	for (time = 1;; time++) {
		int nx = dq.front().x + dx[direction];
		int ny = dq.front().y + dy[direction];

		if (exceptionHandling(ny, nx)) {
			if (map[ny][nx] == 0) {
				Cordinate newHead;
				newHead.y = ny;
				newHead.x = nx;
				dq.push_front(newHead);
				map[ny][nx] = 2;
				map[dq.back().y][dq.back().x] = 0;
				dq.pop_back();
			}
			else if (map[ny][nx] == 1) {
				Cordinate newHead;
				newHead.y = ny;
				newHead.x = nx;
				map[ny][nx] = 2;
				dq.push_front(newHead);
			}
			else if (map[ny][nx] == 2) {
				return time;
			}
		}
		else {
			return time;
		}

		if (!changeDq.empty() && time == changeDq.front().time) {
			if (direction == 0) {
				if (changeDq.front().direction == 'L') {
					direction = 2;
				}
				else {
					direction = 3;
				}
			}
			else if (direction == 1) {
				if (changeDq.front().direction == 'L') {
					direction = 3;
				}
				else {
					direction = 2;
				}
			}
			else if (direction == 2) {
				if (changeDq.front().direction == 'L') {
					direction = 1;
				}
				else {
					direction = 0;
				}
			}
			else if (direction == 3) {
				if (changeDq.front().direction == 'L') {
					direction = 0;
				}
				else {
					direction = 1;
				}
			}

			changeDq.pop_front();
		}
	}
}

int main() {
	input();
	cout << solve() << endl;
}