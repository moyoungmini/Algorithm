#include <iostream>
#include <queue>
#include <string.h>
#include <math.h>
using namespace std;

struct Node {
	int y;
	int x;
};

int n;
int map[64][64];
int tmpMap[64][64];
int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, -1, 1 };

void rotate(int y, int x, int length) {
	for (int i = y; i < y + length; i++) {
		for (int j = x; j < x + length; j++) {
			tmpMap[i][j] = map[i][j];
		}
	}

	for (int i = 0; i < length; i++) {
		for (int j = 0; j < length; j++) {
			map[y + j][x + length - 1 - i] = tmpMap[y + i][x + j];
		}
	}
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < n) return true;

	return false;
}

void checkIce() {
	bool check[64][64];
	memset(check, false, sizeof(check));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int count = 0;

			for (int k = 0; k < 4; k++) {
				int ny = i + dy[k];
				int nx = j + dx[k];

				if (exceptionHandling(ny, nx) && map[ny][nx] > 0) {
					count++;
				}
			}

			if (count < 3) {
				check[i][j] = true;
			}
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (check[i][j]) map[i][j]--;
		}
	}
}

void print() {
	int result = 0;
	int sum = 0;
	queue<Node> q;
	bool check[64][64];
	memset(check, false, sizeof(check));

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (!check[i][j] && map[i][j] > 0) {
				Node init;
				int count = 1;
				init.y = i;	init.x = j;
				q.push(init);
				check[i][j] = true;
				sum += map[i][j];

				while (!q.empty()) {
					Node front = q.front();	q.pop();

					for (int k = 0; k < 4; k++) {
						int ny = front.y + dy[k];
						int nx = front.x + dx[k];

						if (exceptionHandling(ny, nx) && !check[ny][nx] && map[ny][nx] > 0) {
							Node newValue;
							newValue.y = ny;
							newValue.x = nx;
							q.push(newValue);
							count++;
							check[ny][nx] = true;
							sum += map[ny][nx];
						}
					}
				}

				if (result < count) result = count;
			}
		}
	}

	cout << sum << endl;
	cout << result << endl;
}

int main() {
	int input, k;
	cin >> n >> k;

	n = pow(2, n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> map[i][j];
		}
	}

	for (int i = 0; i < k; i++) {
		cin >> input;
		int length = pow(2, input);

		for (int a = 0; a < n; a += length) {
			for (int b = 0; b < n; b += length) {
				rotate(a, b, length);
			}
		}
		checkIce();
	}

	print();
}