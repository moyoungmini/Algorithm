#include <iostream>
#include <vector>
#include <string.h>
using namespace std;

class node {
public:
	int y;
	int x;
	int status;
	int direction;
public:
	node(int y, int x, int status, int direction) {
		this->y = y;
		this->x = x;
		this->status = status;
		this->direction = direction;
	}
};

int n, m;
int map[8][8];
bool check[8][8];
vector<node> v;
int result;
int dx[] = { 1, -1, 0, 0 };
int dy[] = { 0, 0, 1, -1 };

void input() {
	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			cin >> map[i][j];
		}
	}

	result = n * m;
}

bool exceptionCheck(int y, int x) {
	if (x >= 0 && x < m && y >= 0 && y < n) {
		return true;
	}

	return false;
}

void move(int y, int x, int direction) {
	while (true) {
		x += dx[direction];
		y += dy[direction];

		if (exceptionCheck(y, x)) {
			if (map[y][x] == 6) {
				break;
			}
			else {
				check[y][x] = true;
			}
		}
		else {
			break;
		}
	}
}

void solve() {
	memset(check, false, sizeof(check));

	for (int i = 0; i < v.size(); i++) {
		if (v[i].status == 1) {
			move(v[i].y, v[i].x, v[i].direction);
		}
		else if (v[i].status == 2) {
			if (v[i].direction == 0) {
				move(v[i].y, v[i].x, 0);
				move(v[i].y, v[i].x, 1);
			}
			else {
				move(v[i].y, v[i].x, 2);
				move(v[i].y, v[i].x, 3);
			}
		}
		else if (v[i].status == 3) {
			if (v[i].direction == 0) {
				move(v[i].y, v[i].x, 0);
				move(v[i].y, v[i].x, 2);
			}
			else if (v[i].direction == 1) {
				move(v[i].y, v[i].x, 1);
				move(v[i].y, v[i].x, 2);
			}
			else if (v[i].direction == 2) {
				move(v[i].y, v[i].x, 1);
				move(v[i].y, v[i].x, 3);
			}
			else if (v[i].direction == 3) {
				move(v[i].y, v[i].x, 0);
				move(v[i].y, v[i].x, 3);
			}
		}
		else if (v[i].status == 4) {
			if (v[i].direction == 0) {
				move(v[i].y, v[i].x, 1);
				move(v[i].y, v[i].x, 2);
				move(v[i].y, v[i].x, 3);
			}
			else if (v[i].direction == 1) {
				move(v[i].y, v[i].x, 0);
				move(v[i].y, v[i].x, 2);
				move(v[i].y, v[i].x, 3);
			}
			else if (v[i].direction == 2) {
				move(v[i].y, v[i].x, 0);
				move(v[i].y, v[i].x, 1);
				move(v[i].y, v[i].x, 3);
			}
			else {
				move(v[i].y, v[i].x, 0);
				move(v[i].y, v[i].x, 1);
				move(v[i].y, v[i].x, 2);
			}
		}
		else if (v[i].status == 5) {
			move(v[i].y, v[i].x, 0);
			move(v[i].y, v[i].x, 1);
			move(v[i].y, v[i].x, 2);
			move(v[i].y, v[i].x, 3);
		}
	}

	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			if (map[i][j] == 0 && !check[i][j]) {
				sum++;
			}
		}
	}
	if (sum < result) result = sum;
}

void brouteForce(int y, int x) {
	if (x == m) {
		y++;
		x = 0;
	}

	for (int i = y; i < n; i++) {
		int j;
		if (i == y) j = x;
		else j = 0;

		for (; j < m; j++) {
			if (map[i][j] == 1) {
				for (int k = 0; k < 4; k++) {
					node newNode(i, j, 1, k);
					v.push_back(newNode);
					brouteForce(i, j + 1);
					v.pop_back();
				}

				return;
			}
			else if (map[i][j] == 2) {
				for (int k = 0; k < 2; k++) {
					node newNode(i, j, 2, k);
					v.push_back(newNode);
					brouteForce(i, j + 1);
					v.pop_back();
				}

				return;
			}
			else if (map[i][j] == 3) {
				for (int k = 0; k < 4; k++) {
					node newNode(i, j, 3, k);
					v.push_back(newNode);
					brouteForce(i, j + 1);
					v.pop_back();
				}

				return;
			}
			else if (map[i][j] == 4) {
				for (int k = 0; k < 4; k++) {
					node newNode(i, j, 4, k);
					v.push_back(newNode);
					brouteForce(i, j + 1);
					v.pop_back();
				}

				return;
			}
			else if (map[i][j] == 5) {
				node newNode(i, j, 5, 0);
				v.push_back(newNode);
				brouteForce(i, j + 1);
				v.pop_back();

				return;
			}
		}
	}

	solve();
}

int main() {
	input();
	brouteForce(0, 0);
	cout << result << endl;
}