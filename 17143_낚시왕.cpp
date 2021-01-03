#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

class Shark {
public:
	int y;
	int x;
	int direction;
	int speed;
	int length;
	bool exist;
public:
	Shark(int y, int x, int speed, int direction, int length) {
		this->y = y;
		this->x = x;
		this->speed = speed;
		this->direction = direction;
		this->length = length;
		exist = true;
	}

	Shark() {}
};

int dy[] = { -1, 1, 0, 0 };
int dx[] = { 0, 0, 1, -1 };

int n, m;
int map[100][100];
vector<Shark> v;

void input() {
	memset(map, -1, sizeof(map));

	int k, r, c, s, d, z;
	cin >> n >> m >> k;

	for (int i = 0; i < k; i++) {
		cin >> r >> c >> s >> d >> z;
		Shark shark(r - 1, c - 1, s, d - 1, z);
		v.push_back(shark);
		map[r - 1][c - 1] = i;
	}
}

int catchShark(int x) {
	int length = v.size();

	for (int i = 0; i < n; i++) {
		if (map[i][x] != -1 && v[map[i][x]].exist) {
			v[map[i][x]].exist = false;
			int returnValue = v[map[i][x]].length;
			return returnValue;
		}
	}

	return 0;
}

bool exceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < m) {
		return true;
	}

	return false;
}

void move() {
	memset(map, -1, sizeof(map));
	int length = v.size();

	for (int i = 0; i < length; i++) {
		if (v[i].exist) {
			int y = v[i].y;
			int x = v[i].x;
			int direction = v[i].direction;
			int speed = v[i].speed;

			if (direction == 0 || direction == 1) {
				speed = speed % (2 * n - 2);
			}
			else {
				speed = speed % (2 * m - 2);
			}

			for (int j = 0; j < speed; j++) {
				y += dy[direction];
				x += dx[direction];

				if (!exceptionHandling(y, x)) {
					if (direction == 0) direction = 1;
					else if (direction == 1) direction = 0;
					else if (direction == 2) direction = 3;
					else direction = 2;

					y += dy[direction] * 2;
					x += dx[direction] * 2;
				}
			}

			if (map[y][x] == -1) {
				map[y][x] = i;
				v[i].y = y;
				v[i].x = x;
				v[i].direction = direction;
			}
			else {
				if (v[map[y][x]].length > v[i].length) {
					v[i].exist = false;
				}
				else {
					v[map[y][x]].exist = false;
					map[y][x] = i;
					v[i].y = y;
					v[i].x = x;
					v[i].direction = direction;
				}
			}
		}
	}
}


int solve() {
	int sum = 0;
	int position = -1;

	while (true) {
		position++;
		if (position == m) break;
		sum += catchShark(position);
		move();
	}

	return sum;
}

int main() {
	input();
	cout << solve() << endl;
}