#include <iostream>
#include <string>
#include <string.h>
using namespace std;

struct Cordinate {
	int x;
	int y;
};

struct Ball {
	Cordinate red;
	Cordinate blue;
};

int n, m, result;
Ball ball;
bool check[10][10][10][10];
string map[10];
int dy[] = { -1,1, 0, 0 };
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

	result = 11;
	memset(check, false, sizeof(check));
	check[ball.red.y][ball.red.x][ball.blue.y][ball.blue.x] = true;
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

			if (check[redY][redX][blueY][blueX]) {
				return 2;
			}
			else {
				ball.red.y = redY;
				ball.red.x = redX;
				ball.blue.y = blueY;
				ball.blue.x = blueX;

				return 0;
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

				if (check[redY][redX][blueY][blueX]) {
					return 2;
				}
				else {
					ball.red.y = redY;
					ball.red.x = redX;
					ball.blue.y = blueY;
					ball.blue.x = blueX;

					return 0;
				}
			}
		}
		else if (map[redY][redX] != '#' && map[blueY][blueX] == '#') {
			blueY -= dy[direction];
			blueX -= dx[direction];

			if (redY == blueY && redX == blueX) {
				redY -= dy[direction];
				redX -= dx[direction];

				if (check[redY][redX][blueY][blueX]) {
					return 2;
				}
				else {
					ball.red.y = redY;
					ball.red.x = redX;
					ball.blue.y = blueY;
					ball.blue.x = blueX;

					return 0;
				}
			}
		}
	}
}

void brouteForce(int count) {
	Ball tmp = ball;
	if (count >= 11) return;
	for (int i = 0; i < 4; i++) {
		int value = move(i);

		if (value == 0) {
			check[ball.red.y][ball.red.x][ball.blue.y][ball.blue.x] = true;
			brouteForce(count + 1);
			check[ball.red.y][ball.red.x][ball.blue.y][ball.blue.x] = false;
			ball = tmp;
		}
		else if (value == 1) {
			if (result > count + 1) {
				result = count + 1;
			}

			return;
		}
	}
}

int main() {
	input();
	brouteForce(0);
	if (result == 11) result = -1;
	cout << result << endl;
}