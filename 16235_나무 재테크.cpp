#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

struct Node {
	int food;
	vector<int> tree;
};

struct Cordinate {
	int y;
	int x;
};

int n, m, k;
int plusMap[10][10];
Node map[10][10];
int dy[] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dx[] = { 0, 1, 1, 1, 0, -1, -1, -1 };

bool expceptionHandling(int y, int x) {
	if (y >= 0 && y < n && x >= 0 && x < n) {
		return true;
	}

	return false;
}

void input() {
	cin >> n >> m >> k;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> plusMap[i][j];
			map[i][j].food = 5;
		}
	}

	int x, y, z;

	for (int i = 0; i < m; i++) {
		cin >> y >> x >> z;

		map[y - 1][x - 1].tree.push_back(z);
	}
}

void springAndSummer() {
	vector<int> alive;
	vector<int> dead;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (map[i][j].tree.size() > 0) {
				sort(map[i][j].tree.begin(), map[i][j].tree.end());
				alive.clear();
				dead.clear();

				for (int k = 0; k < map[i][j].tree.size(); k++) {
					if (map[i][j].food >= map[i][j].tree[k]) {
						alive.push_back(map[i][j].tree[k] + 1);
						map[i][j].food -= map[i][j].tree[k];
					}
					else {
						dead.push_back(map[i][j].tree[k]);
					}
				}
				map[i][j].tree.clear();
				map[i][j].tree = alive;

				for (int k = 0; k < dead.size(); k++) {
					map[i][j].food += (dead[k] / 2);
				}
			}
		}
	}
}

void fall() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			for (int k = 0; k < map[i][j].tree.size(); k++) {
				if (map[i][j].tree[k] > 0 && map[i][j].tree[k] % 5 == 0) {
					for (int q = 0; q < 8; q++) {
						int ny = i + dy[q];
						int nx = j + dx[q];

						if (expceptionHandling(ny, nx)) {
							map[ny][nx].tree.push_back(1);
						}
					}
				}
			}
		}
	}
}

void winter() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			map[i][j].food += plusMap[i][j];
		}
	}
}

int calculate() {
	int sum = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			sum += map[i][j].tree.size();
		}
	}

	return sum;
}

int main() {
	input();
	for (int i = 0; i < k; i++) {
		springAndSummer();
		fall();
		winter();
	}

	cout << calculate() << endl;
}