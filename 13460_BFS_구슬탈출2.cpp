#include <iostream>
#include <queue>
#include <string>
#include <string.h>
using namespace std;

struct Cordinate {
	int y;
	int x;
};

struct Ball {
	Cordinate red;
	Cordinate blue;
};

int n, m;
int result = 11;
Ball ball;
string map[10];
int check[10][10][10][10];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		cin >> map[i];

		for (int j = 0; j < m; j++) {
			if (map[i][j] == 'R') {
				ball.red.y = i;
				ball.red.x = j;
			}
			else if (map[i][j] == 'B') {
				ball.blue.y = i;
				ball.blue.x = j;
			}
		}
	}

	memset(check, -1, sizeof(check));
	check[ball.red.y][ball.red.x][ball.blue.y][ball.blue.x] = 0;
}

int move(int direction) {
	int redY = ball.red.y;
	int redX = ball.red.x;
	int blueY = ball.blue.y;
	int blueX = ball.blue.x;

	while (true) {
		redY += dy[direction];
		redX += dx[direction];
		blueY += dy[direction];
		blueX += dx[direction];

		if (map[redY][redX] == '#' && map[blueY][blueX] == '#') {
			redY -= dy[direction];
			redX -= dx[direction];
			blueY -= dy[direction];
			blueX -= dx[direction];

			if (check[redY][redX][blueY][blueX] == -1) {
				ball.red.y = redY;
				ball.red.x = redX;
				ball.blue.y = blueY;
				ball.blue.x = blueX;
				return 0;
			}
			else {
				return 2;
			}
		}
		else if (map[redY][redX] == 'O') {
			while (true) {
				if (map[blueY][blueX] == '#') {
					return 1;
				}
				else if (map[blueY][blueX] == 'O') {
					return 2;
				}
				blueY += dy[direction];
				blueX += dx[direction];
			}
		}
		else if (map[blueY][blueX] == 'O') {
			return 2;
		}
		else if (map[redY][redX] == '#' && map[blueY][blueX] != '#') {
			redY -= dy[direction];
			redX -= dx[direction];

			if (redY == blueY && redX == blueX) {
				blueY -= dy[direction];
				blueX -= dx[direction];

				if (check[redY][redX][blueY][blueX] == -1) {
					ball.red.y = redY;
					ball.red.x = redX;
					ball.blue.y = blueY;
					ball.blue.x = blueX;
					return 0;
				}
				else {
					return 2;
				}
			}
		}
		else if (map[redY][redX] != '#' && map[blueY][blueX] == '#') {
			blueY -= dy[direction];
			blueX -= dx[direction];

			if (redY == blueY && redX == blueX) {
				redY -= dy[direction];
				redX -= dx[direction];

				if (check[redY][redX][blueY][blueX] == -1) {
					ball.red.y = redY;
					ball.red.x = redX;
					ball.blue.y = blueY;
					ball.blue.x = blueX;
					return 0;
				}
				else {
					return 2;
				}
			}
		}
	}
}

void solve() {
	queue<Ball> q;
	q.push(ball);

	while (!q.empty()) {
		Ball front = q.front();	q.pop();

		if (check[front.red.y][front.red.x][front.blue.y][ball.blue.x] >= 10) {
			continue;
		}

		for (int i = 0; i < 4; i++) {
			ball = front;
			int value = move(i);

			if (value == 0) {
				Ball newValue = ball;
				q.push(newValue);
				check[ball.red.y][ball.red.x][ball.blue.y][ball.blue.x] = check[front.red.y][front.red.x][front.blue.y][front.blue.x] + 1;
			}
			else if (value == 1) {
				if (result > check[front.red.y][ball.red.x][ball.blue.y][ball.blue.x] + 1) {
					result = check[front.red.y][ball.red.x][ball.blue.y][ball.blue.x] + 1;
				}
				return;
			}
		}
	}
}

int main() {
	input();
	solve();
	if (result == 11) result = -1;
	cout << result << endl;
}