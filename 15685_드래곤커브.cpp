#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

int dy[] = { 0, -1, 0, 1 };
int dx[] = { 1, 0, -1, 0 };

const int n = 101;
int map[n][n];

void solve(int y, int x, int direction, int time) {

	vector<int> v;
	map[y][x] = true;
	y += dy[direction];
	x += dx[direction];
	map[y][x] = true;
	v.push_back(direction);

	for (int t = 0; t < time; t++) {
		int count = v.size();
		for (int i = count - 1; i >= 0; i--) {
			int newDirection = (v[i] + 1) % 4;

			y += dy[newDirection];
			x += dx[newDirection];

			map[y][x] = true;
			v.push_back(newDirection);
		}
	}
}

void input() {
	int count, y, x, direction, time;

	cin >> count;
	memset(map, false, sizeof(map));
	for (int i = 0; i < count; i++) {
		cin >> x >> y >> direction >> time;
		solve(y, x, direction, time);
	}
}

bool checkSquare(int y, int x) {
	if (map[y][x] && map[y + 1][x] && map[y][x + 1] && map[y + 1][x + 1]) {
		return true;
	}

	return false;
}

int calculate() {
	int sum = 0;

	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - 1; j++) {
			if (checkSquare(i, j)) {
				sum++;
			}
		}
	}

	return sum;
}

int main() {
	input();
	cout << calculate() << endl;
}
